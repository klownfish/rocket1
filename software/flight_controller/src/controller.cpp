#include <Arduino.h>
#include <SPIMemory.h> // for flash chip
#include <RH_RF69.h> // the version from the platformio repo doesn't work,
                     // i have included a working version in the git repo
#include <Adafruit_BMP280.h>
#include <Adafruit_MPU6050.h>
#include <Wire.h> // i2c

#include "MovingAverage.h" // simple data filter
#include "definitions.h" // pin definitions

#define SAMPLE_DELAY 100

#define RADIO_BUF_LEN 64

#define ALTITUDE_FILTER_LEN 10
#define TEMPERATURE_FILTER_LEN 10
#define GYRO_FILTER_LEN 5
#define ACCELERATION_FILTER_LEN 5

#define ACCELERATION_CALIBRATION_CYCLES 20
#define ALTITUDE_CALIBRATION_CYCLES 20

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
bool sleeping = false;
uint32_t flash_index = 0;

template<typename T>
void write_int_to_array(uint8_t* array, T num, uint8_t* index) {
    for(uint8_t i = 0; i < sizeof(T); i++) {
        array[*index] = num & 0xAA;
        num >>= 8;
        index++; 
    }
}

void init_pins() {
    pinMode(FLASH_CS, OUTPUT);
    pinMode(RF_CS, OUTPUT);
    pinMode(BAT_READ, INPUT);
}

void init_flash() {
    if (!flash.begin()) {
        Serial.println("Could not initialize flash chip");
    }
}

void init_radio() {
    if (!radio.init()) {
        Serial.println("could not initialize radio modem");
    }
    radio.setFrequency(FREQUENCY);
    radio.setTxPower(TX_POWER, true);
    if (IS_HAM) { 
        radio.send(CALLSIGN, sizeof(CALLSIGN));
    }
}

void init_MPU() {
    if (!mpu.begin()) {
        Serial.println("could not initialize MPU");
    }
}

void init_BMP() {
    if (!bmp.begin()) {
        Serial.println("could not initialize BMP");
    }
}

void calibrate() {
    MovingAverage<float> temp {ALTITUDE_CALIBRATION_CYCLES};
    for (uint8_t i = 0; i < ALTITUDE_CALIBRATION_CYCLES; i++) {
        float val = bmp.readAltitude(sea_level_pressure);
        temp.insert(val);
        delay(100);
    }
    ground_level = temp.get_value();   
}

float get_battery_voltage() {
    analogReadResolution(12);
    float volt = (float) analogRead(BAT_READ);
    return volt / (2 << 12) * 3.3;   
}

void enter_sleep() {
    mpu.enableSleep(true);
    sleeping = true;
}

void wake_up() {
    mpu.enableSleep(false);
    sleeping = false;
}

void generate_checksum(uint8_t* buf, uint8_t* index) {
    uint8_t checksum = 0;
    for (uint8_t i = 1; i < *index; i++) {
        checksum ^= buf[i];
    }
    buf[*index] = '*';
    index++;
    buf[*index] = checksum;
    index++;
}

void send_state() {
    uint8_t buf[24];
    uint8_t index = 0;
    buf[index++] = '$';
    write_int_to_array(buf, (uint16_t) (get_battery_voltage() * 1000), &index); 
    write_int_to_array(buf, (uint16_t) (sea_level_pressure * 1000), &index);
    write_int_to_array(buf, (uint16_t) (ground_level * 1000), &index);
    buf[index++] = sleeping;
    generate_checksum(buf, &index);
    radio.send(buf, index);
}

bool verify_message(uint8_t* msg, uint8_t len) {
    if (msg[0] != '$') {
        return false;
    }
    uint8_t checksum = 0x00;
    uint8_t i;
    for (i = 1; i < len; i++) {
        if (msg[i] == '*') break;
        checksum ^= msg[i];
    }
    if (msg[++i] == checksum) {
        return true;
    } 
    return false;
}

void setup() {
    Serial.begin(BAUD); // USB serial
    init_pins();    
    init_flash();
    init_radio();
    init_MPU();
    init_BMP();
}

void loop() {
    uint8_t buf[RADIO_BUF_LEN]; 
    uint8_t len;

    //parse USB command
    if (Serial.available()) {
        uint8_t c = Serial.read();
        switch (c){
            case USB_DUMP_FLASH:
                for (uint32_t i = 0; i < flash_index; i++) {
                    Serial.write(flash.readByte(i));
                }
                break;
            
            case USB_HANDSHAKE:
                Serial.write(2);
        }
    }

    //parse radio command
    if (radio.recv(buf, &len) && verify_message(buf, len)) {       
        switch (buf[1]) {
            case ID_PRESSURE_SEA_LEVEL:
                sea_level_pressure = ((float) (buf[2] + (buf[3] >> 8))) / 1000;
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
        }
        send_state();
    }
    if (sleeping){
        return;
    }
    uint32_t time = millis();
    if (time - last_sample < 100) {
        return;
    }
    
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
    buf[index++] = '$';
    write_int_to_array(buf, radio.lastRssi(), &index);
    write_int_to_array(buf, time, &index);
    write_int_to_array(buf, (uint16_t) (altitude.get_value() * 1000), &index);
    write_int_to_array(buf, (uint16_t) (temperature.get_value() * 1000), &index);
    write_int_to_array(buf, (uint16_t) (acc_x.get_value() * 1000), &index);
    write_int_to_array(buf, (uint16_t) (acc_y.get_value() * 1000), &index);
    write_int_to_array(buf, (uint16_t) (acc_z.get_value() * 1000), &index);
    write_int_to_array(buf, (uint16_t) (gyro_x.get_value() * 1000), &index);
    write_int_to_array(buf, (uint16_t) (gyro_y.get_value() * 1000), &index);
    write_int_to_array(buf, (uint16_t) (get_battery_voltage() * 1000), &index); 
    generate_checksum(buf, &index);

    radio.send(buf, index);
    flash.writeAnything(flash_index, buf);
    flash_index += index;
}