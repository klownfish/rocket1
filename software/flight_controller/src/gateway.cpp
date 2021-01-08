#include <Arduino.h>
#include <RH_RF69.h>
#include <stdint.h>

#include "definitions.h" // pin definitions

#define RADIO_BUF_LEN 64

RH_RF69 radio {RF_CS, RF_G0}; 
bool transmit = false;
uint32_t last_serial_read = 0;

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

void setup() {
    Serial.begin(BAUD);
    init_radio();
}

void loop() {
    if (!transmit && Serial.available()) {
        int16_t c = Serial.read();
        switch (c) {
            case GATEWAY_HANDSHAKE:
                Serial.write(GATEWAY_HANDSHAKE);
                break;

            case GATEWAY_TRANSMIT:
                transmit = true;
                break;
        }
    }
    
    if (transmit && Serial.available()) {
        delay(100); //wait 100ms for the full message to come
        uint8_t buf[64];
        uint8_t index = 0;
        while (true) {
            uint8_t c = Serial.read();
            if (c == -1) break;
            buf[index++] = c;
        }
        radio.send(buf, index);
    }

    uint8_t buf[RADIO_BUF_LEN];
    uint8_t len;
    if (radio.recv(buf, &len)) {
        for (uint8_t i = 0; i < len; i++) {
            Serial.write(buf[i]);
        }
    }
}