#include <Arduino.h>
#include <SPI.h>
#include <Wire.h> // i2c
#include <SPIMemory.h> // for flash chip
#include <RH_RF69.h> // the version from the platformio repo doesn't work,
                     // i have included a working version in the git repo
#include <Adafruit_BMP280.h>
#include <Adafruit_MPU6050.h>

#include "MovingAverage.h" // simple data filter
#include "definitions.h" // pin and protocol definitions

#define SAMPLE_DELAY 50
#define RADIO_CYCLES 2

#define ALTITUDE_FILTER_LEN 10
#define TEMPERATURE_FILTER_LEN 10
#define GYRO_FILTER_LEN 5
#define ACCELERATION_FILTER_LEN 5

#define ACCELERATION_CALIBRATION_CYCLES 20
#define ALTITUDE_CALIBRATION_CYCLES 5

RH_RF69 radio {RF_CS, RF_G0}; 
SPIFlash flash {FLASH_CS};
Adafruit_BMP280 bmp;
Adafruit_MPU6050 mpu;

MovingAverage<float> altitude {10};
MovingAverage<float> temperature {10};

MovingAverage<float> acc_x {5};
MovingAverage<float> acc_y {5};
MovingAverage<float> acc_z {5};

MovingAverage<float> gyro_x {5};
MovingAverage<float> gyro_y {5};
MovingAverage<float> gyro_z {5};

float sea_level_pressure = 1013.25; // set by rocket operator through radio
float ground_level = 0; // set by altitude calibration
uint32_t last_sample = 0; // when the last sample was taken
bool sleeping = true;
uint32_t flash_index = 0;
int32_t sample = 0;

template<typename T>
void write_int_to_array(uint8_t* array, T num, uint8_t* index) {
    for(uint8_t i = 0; i < sizeof(T); i++) {
        array[*index] = num & 0xFF;
        num >>= 8;
        (*index)++; 
    }
}

int32_t array_to_int(uint8_t* array, uint8_t len) {
    int64_t num = 0;
    for (uint8_t i = 0; i < len; i++) {
        num += array[i] << (8 * i); 
    }
    return num;
}

void init_pins() {
    pinMode(FLASH_CS, OUTPUT);
    pinMode(RF_CS, OUTPUT);
    pinMode(BAT_READ, INPUT);
    pinMode(RF_RST, OUTPUT);

    digitalWrite(FLASH_CS, LOW);
    digitalWrite(RF_CS, LOW);
}

void init_flash() {
    if (!flash.begin()) {
        Serial.println("Could not initialize flash chip");
    }
}

void init_radio() {
    digitalWrite(RF_RST, LOW);
    delay(100);
    digitalWrite(RF_RST, HIGH);
    delay(100);
    digitalWrite(RF_RST, LOW);
    delay(100);
    if (!radio.init()) {
        Serial.println("could not initialize radio modem");
        return;
    }
    radio.setFrequency(FREQUENCY);
    //radio.setModemConfig(MODULATION);
    radio.setTxPower(TX_POWER, true);
    if (IS_HAM) { 
        radio.send(CALLSIGN, sizeof(CALLSIGN));
    }
}

void init_MPU() {
    if (!mpu.begin()) {
        Serial.println("could not initialize MPU");
        return;
    }
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
    mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
}

void init_BMP() {
    if (!bmp.begin()) {
        Serial.println("could not initialize BMP");
    }
}

void calibrate() {
    ground_level = altitude.get_value();   
}

float get_battery_voltage() {
    analogReadResolution(12);
    float volt = (float) analogRead(BAT_READ);
    return volt / (2 << 12) * 3.3;   
}

void enter_sleep() {
    //mpu.enableSleep(true);
    sleeping = true;
}

void wake_up() {
    //mpu.enableSleep(false);
    sleeping = false;
}

void send_message(uint8_t* msg, uint8_t len, bool use_radio) {
    if (use_radio) {
        radio.send(msg, len);
    }
    //flash.writeByteArray(flash_index, msg, len);
    flash_index += len;
    Serial.write(msg, len);
}

void generate_checksum(uint8_t* buf, uint8_t* index) {
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < *index; i++) {
        checksum ^= buf[i];
    }
    buf[*index] = checksum;
    (*index)++;
}

void send_state() {
    uint8_t buf[24];
    uint8_t index = 0;
    buf[index++] = '$';
    index++; // skip len byte
    write_int_to_array(buf, millis(), &index);
    buf[index++] = ID_STATE;
    write_int_to_array(buf, (int32_t) radio.lastRssi(), &index);
    write_int_to_array(buf, (int32_t) (get_battery_voltage() * 1000), &index); 
    write_int_to_array(buf, (int32_t) (sea_level_pressure * 1000), &index);
    write_int_to_array(buf, (int32_t) (ground_level * 1000), &index);
    buf[index++] = sleeping;
    buf[1] = index;
    generate_checksum(buf, &index);
    send_message(buf, index, true);
}

bool verify_message(uint8_t* msg, uint8_t len) {
    if (msg[0] != '$') {
        return false;
    }
    uint8_t msg_len = msg[1];
    if (msg_len > len) { 
        return false;
    }

    uint8_t checksum = 0x00;
    uint8_t i;
    for (i = 0; i < len - 1; i++) {
        checksum ^= msg[i];
    }
    if (msg[i] == checksum) {
        return true;
    }
    return false;
}

bool get_message(uint8_t* buf, uint8_t* len) {
    if (Serial.available()) {
        delay(100); //wait 100ms for the full message to come
        *len = Serial.available();
        Serial.readBytes((char*) buf, *len);
        return true;
    }

    if (radio.recv(buf, len)) {
        Serial.write(buf, *len);
        return true;
    }
    return false;
}

void setup() {
    delay(5000);
    Serial.begin(BAUD); // USB serial
    init_pins();    
    //init_flash();
    Serial.print("I'm going in");
    Serial.print("yooo");
    init_MPU();
    init_BMP();
    init_radio();
    Serial.println("init finished");
}

void loop() {
    uint8_t buf[RADIO_BUF_LEN]; 
    uint8_t len = RADIO_BUF_LEN;

    //parse radio command, the time doesn't really matter so skip it
    if (get_message(buf, &len) && verify_message(buf, len)) {
        switch (buf[6]) {
            case ID_PARAMETERS:
                int32_t raw; 
                raw = array_to_int(buf + 7, 4);
                sea_level_pressure = ((float) raw) / 1000;
                break;
            case ID_CALIBRATE:
                calibrate();
                break;
            case ID_SLEEP:
                enter_sleep();
                break;
            case ID_WAKE_UP:
                wake_up();
                break;
            case CONTROLLER_DUMP_FLASH:
                for (uint32_t i = 0; i < flash_index; i++) {
                    Serial.write(flash.readByte(i));
                }
                break;
            case HANDSHAKE:
                Serial.write(HANDSHAKE);
                Serial.flush();
                delay(100);
                break;
            case IS_CONTROLLER:
                Serial.write(1);
                break;
            case IS_GATEWAY:
                Serial.write(0);
                break;
        }
        send_state();
    }

    if (sleeping){
        return;
    }

    uint32_t time = millis();
    if (time - last_sample < SAMPLE_DELAY) {
        return;
    }
    last_sample = time;

    //bmp
    altitude.insert(bmp.readAltitude(sea_level_pressure));
    temperature.insert(bmp.readTemperature());
    //mpu
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    acc_x.insert(a.acceleration.x);
    acc_y.insert(a.acceleration.y);
    acc_z.insert(a.acceleration.z);
    gyro_x.insert(g.gyro.x);
    gyro_y.insert(g.gyro.y);
    gyro_z.insert(g.gyro.z);

    //build message
    uint8_t index = 0;
    buf[index] = '$';
    index++;
    index++; //skip the len byte
    write_int_to_array(buf, time, &index);
    buf[index] = ID_TELEMETRY;
    index++;
    write_int_to_array(buf, (int32_t) (altitude.get_value() * 1000), &index);
    write_int_to_array(buf, (int32_t) (temperature.get_value() * 1000), &index);
    write_int_to_array(buf, (int32_t) (acc_x.get_value() * 1000), &index);
    write_int_to_array(buf, (int32_t) (acc_y.get_value()* 1000), &index);
    write_int_to_array(buf, (int32_t) (acc_z.get_value() * 1000), &index);
    write_int_to_array(buf, (int32_t) (gyro_x.get_value() * 1000), &index);
    write_int_to_array(buf, (int32_t) (gyro_y.get_value() * 1000), &index);
    write_int_to_array(buf, (int32_t) (gyro_z.get_value() * 1000), &index);
    write_int_to_array(buf, (int32_t) (get_battery_voltage() * 1000), &index); 
    buf[1] = index; // length
    generate_checksum(buf, &index);
    bool use_radio = !(sample % RADIO_CYCLES);
    sample++;
    send_message(buf, index, use_radio);
}