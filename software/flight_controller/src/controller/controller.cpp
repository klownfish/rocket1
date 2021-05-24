#include <Arduino.h>
#include <SPI.h>
#include <Wire.h> // i2c
#include <SerialFlash.h> // for flash chip
#include <SPIMemory.h>
#include <RH_RF69.h>
#include <Adafruit_BMP280.h>
#include <elapsedMillis.h>

#include "MPU9250.h"
#include "definitions.h" // pin and protocol definitions
#include "rocket.h"
#include "protocol.h"

void megalovania(); //haha lolz
void dance();

#define FLASH_TEST_BYTES 10

#define MAGNETOMETER_OFFSET_ADDR 0

RH_RF69 radio {PIN_RF_CS, PIN_RF_G0}; 
SPIFlash flash {PIN_FLASH_CS};
Adafruit_BMP280 bmp;
MPU9250 mpu;

uint32_t flash_addr = 0;
float ground_level = 0;
bool error = false;
bool flash_enabled = false;

rocket::state state = rocket::state::sleeping;

uint16_t stateToCycleDelay(enum rocket::state state) {
    switch (state) {
        case rocket::state::sleeping:
            return ~0; //max
            break;
        case rocket::state::awake:
            return 1000;
            break;
        default:
            return 1; //LIGHT SPEED BABY
    }
}

void dispRgb(uint8_t R, uint8_t G, uint8_t B) {
    analogWrite(PIN_LED_R, R / 16); // this led is so bright...
    analogWrite(PIN_LED_G, G / 16);
    analogWrite(PIN_LED_B, B / 16);
}

void initPins() {
    pinMode(PIN_RF_CS, OUTPUT);
    pinMode(PIN_BAT_READ, INPUT);
    pinMode(PIN_RF_RST, OUTPUT);
    pinMode(PIN_FLASH_CS, OUTPUT);
    pinMode(PIN_FLASH_WP, OUTPUT);
    pinMode(PIN_FLASH_HOLD, OUTPUT);
    pinMode(PIN_LED_R, OUTPUT);
    pinMode(PIN_LED_G, OUTPUT);
    pinMode(PIN_LED_B, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);

    SPI.setMISO(PIN_MISO);
    SPI.setMOSI(PIN_MOSI);
    SPI.setSCK(PIN_SCK);
    SPI.begin();
    Wire.begin();

    analogWriteFrequency(PIN_BUZZER, 3000);
    digitalWrite(PIN_RF_CS, HIGH);
    digitalWrite(PIN_FLASH_CS, HIGH);
    digitalWrite(PIN_FLASH_WP, HIGH);
    digitalWrite(PIN_FLASH_HOLD, HIGH);
    delay(100);
}

void restoreFlashAddr() {
    uint8_t empty_in_row = 0;
    uint8_t byte = 0;
    while (true) {
        if ((byte = flash.readByte(flash_addr)) == 0xff) {
            empty_in_row += 1;
        } else {
            empty_in_row = 0;
        }
        if (empty_in_row == FLASH_TEST_BYTES) {
            flash_addr -= FLASH_TEST_BYTES - 1;
            break;
        }
        flash_addr++;        
    }
}

void initFlash() {   
    flash.setClock(104000000 / 2);
    if (!flash.begin()) {
        Serial.println("Could not init flash chip");
        error = true;
        return;
    }
    for (uint8_t i = 0; i < FLASH_TEST_BYTES; i++) {
        if (flash.readByte(i) != 0xff) {
            restoreFlashAddr();
            Serial.print("restoring to addres: ");
            Serial.println(flash_addr);
            return;
        }
    }
}

void initRadio() {
    digitalWrite(PIN_RF_RST, LOW);
    delay(100);
    digitalWrite(PIN_RF_RST, HIGH);
    delay(100);
    digitalWrite(PIN_RF_RST, LOW);
    delay(100);
    if (!radio.init()) {
        Serial.println("could not initialize radio modem");
        error = true;
        return;
    }
    radio.setFrequency(FREQUENCY);
    radio.setTxPower(TX_POWER, true);
    if (IS_HAM) { 
        radio.send(CALLSIGN, sizeof(CALLSIGN));
    }
}

void initMpu() {
    if (!mpu.setup(0x68)) {
        Serial.println("could not initialize MPU");
        error = true;
        return;
    }
}

void initBmp() {
    if (!bmp.begin(0x76)) {
        Serial.println("could not initialize BMP");
        error = true;
    }
}

void calibrateHeight() {
    ground_level = bmp.readAltitude();
}

float readBatteryVoltage() {
    analogReadResolution(12);
    float volt = (float) analogRead(PIN_BAT_READ);
    return volt / ((1 << 12) - 1) * 3.3 * 2;   
}

void setup() {
    Serial.begin(BAUD); // USB serial
    elapsedMillis boot;
    while (!Serial && boot < 2000) {}    
    initPins();
    dispRgb(0, 0, 255);
    initFlash();
    initMpu();
    initBmp();
    initRadio();
    Serial.println("init finished");
    if (error) {
        // not good
        dispRgb(255, 0, 0);
        analogWrite(PIN_BUZZER, 128);
        delay(1000);
        analogWrite(PIN_BUZZER, 0);
    } else {
        // the all good song
        dance();
        dispRgb(0, 255, 0);
    }
}

void loop() {
    static uint32_t last_sample;
    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN]; 
    uint8_t len = RH_RF69_MAX_MESSAGE_LEN;
    handleDataStreams();

    uint32_t time = millis();
    if (time - last_sample < stateToCycleDelay(state)) {
        return;
    }
    // set current time
    last_sample = time;
    rocket::timestamp_from_rocket_to_ground msg;
    msg.set_ms_since_boot(time);
    sendMsg(&msg, ALWAYS);

    rocket::state_from_rocket_to_ground state_msg;
    state_msg.set_state(state);
    sendMsg(&msg, REGULAR);

    if (mpu.available()) {
        mpu.update();
        rocket::mpu_from_rocket_to_ground mpu_msg;
        mpu_msg.set_acc_x(mpu.getAccX());
        mpu_msg.set_acc_y(mpu.getAccY());
        mpu_msg.set_acc_z(mpu.getAccZ());
        mpu_msg.set_mag_x(mpu.getMagX());
        mpu_msg.set_mag_y(mpu.getMagY());
        mpu_msg.set_mag_z(mpu.getMagZ());
        mpu_msg.set_gyro_x(mpu.getGyroX());
        mpu_msg.set_gyro_y(mpu.getGyroY());
        mpu_msg.set_gyro_z(mpu.getGyroZ());
        sendMsg(&mpu_msg, REGULAR);
    }

    rocket::bmp_from_rocket_to_ground bmp_msg;
    bmp_msg.set_altitude(bmp.readAltitude() - ground_level);
    bmp_msg.set_temperature(bmp.readTemperature());
    sendMsg(&bmp_msg, REGULAR);
}