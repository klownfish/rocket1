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

#define CYCLE_DELAY 50

#define FLASH_TEST_BYTES 10

#define MAGNETOMETER_OFFSET_ADDR 0

RH_RF69 radio {PIN_RF_CS, PIN_RF_G0}; 
SPIFlash flash; //Use the default SPI SS
Adafruit_BMP280 bmp;
MPU9250 mpu;

uint32_t flash_addr = 0;
float ground_level = 0;
float sea_level_hpa = 1001.25;
bool error = false;

void dispRgb(uint8_t R, uint8_t G, uint8_t B) {
    analogWrite(PIN_LED_R, R);
    analogWrite(PIN_LED_G, G);
    analogWrite(PIN_LED_B, B);
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
}

void restoreFlashAddr() {
    uint8_t buf[FLASH_TEST_BYTES];
    uint8_t empty_in_row = 0;
    while (true) {
        if (flash.readByte(flash_addr) == 0xff) {
            empty_in_row += 1;
        } else {
            empty_in_row = 0;
        }
        if (empty_in_row == FLASH_TEST_BYTES) {
            flash_addr -= FLASH_TEST_BYTES - 1;
            break;
        }
        
    }
}

void initFlash() {
    flash.setClock(18e6);
    if (!flash.begin()) {
        Serial.println("Could not init flash chip");
        error = true;
        return;
    }
    uint8_t buf[FLASH_TEST_BYTES];
    if (!flash.readByteArray(0, buf, FLASH_TEST_BYTES)) {
        for (uint8_t i = 0; i < FLASH_TEST_BYTES; i++) {
            if (buf[i] != 0xff) {
                restoreFlashAddr();
                Serial.print("restoring to addres: ");
                Serial.println(flash_addr);
                return;
            }
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
    while (!Serial && boot < 5000) {}    
    initPins();
    dispRgb(0, 0, 255);
    initFlash();
    initMpu();
    initBmp();
    initRadio();
    Serial.println("init finished");
    if (error) {
        dispRgb(255, 0, 0);
        analogWrite(PIN_BUZZER, 128);
        delay(1000);
        analogWrite(PIN_BUZZER, 0);
    } else {
        dispRgb(0, 255, 0);
        analogWrite(PIN_BUZZER, 128);
        delay(200);
        analogWrite(PIN_BUZZER, 0);
        delay(200);
        analogWrite(PIN_BUZZER, 128);
        delay(200);
        analogWrite(PIN_BUZZER, 0);
    }
}

void loop() {
    static uint32_t last_sample;
    uint8_t buf[RADIO_BUF_LEN]; 
    uint8_t len = RADIO_BUF_LEN;

    uint32_t time = millis();
    if (time - last_sample < CYCLE_DELAY) {
        return;
    }
}