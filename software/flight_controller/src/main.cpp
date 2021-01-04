#include <Arduino.h>
#include <SPIMemory.h> // for flash chip
#include <RH_RF69.h> // the version from the platformio repo doesn't work,
                     // i have included a working version in the git repo
#include <Adafruit_BMP280.h>
#include <Adafruit_MPU6050.h>
#include <Wire.h> // i2c

#include "Moving_average.h" // simple data filter
#include "definitions.h" // pin definitions

#define GYRO_CALIBRATION_CYCLES 20;
#define ALTITUDE_CALIBRATION_CYCLES 20;

RH_RF69 radio {RF_CS, RF_G0}; 
SPIFlash flash {FLASH_CS};
Adafruit_BMP280 bmp;
Adafruit_MPU6050 mpu;

Moving_average<float> altitude {10};
Moving_average<float> temperature {10};

Moving_average<float> acc_x {5};
Moving_average<float> acc_y {5};
Moving_average<float> acc_z {5};

Moving_average<float> gyro_x {5};
Moving_average<float> gyro_y {5};
Moving_average<float> gyro_z {5};

float sea_level_pressure = 1013.25; // set by rocket operator through radio
float air_temp = 0; // set by rocket operator through radio, 
                    // maybe unnecessary bmp280 might not need calibration for temperature readings

float ground_level = 0; // set by altitude calibration

void init_pins() {
    pinMode(FLASH_CS, OUTPUT);
    pinMode(RF_CS, OUTPUT);
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
    radio.setTxPower(TX_POWER);
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

}

void setup() {
    Serial.begin(9600); // USB serial
    init_pins();    
    init_flash();
    init_radio();
    init_MPU();
    init_BMP();

    calibrate();
}

void loop() {
    // put your main code here, to run repeatedly:

}