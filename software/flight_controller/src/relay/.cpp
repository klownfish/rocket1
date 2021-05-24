#include <Arduino.h>
#include <RH_RF69.h>
#include <stdint.h>

#include "definitions.h" // pin definitions

RH_RF69 radio {RF_CS, RF_G0}; 
bool transmit = false;
uint32_t last_serial_read = 0;


//write into to a byte array
template<typename T>
void write_int_to_array(uint8_t* array, T num, uint8_t* index) {
    for(uint8_t i = 0; i < sizeof(T); i++) {
        array[*index] = num & 0xFF;
        num >>= 8;
        (*index)++;
    }
}

void init_pins() {
    pinMode(RF_CS, OUTPUT);
    pinMode(RF_RST, OUTPUT);

    digitalWrite(RF_CS, HIGH);
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

bool get_usb_message(uint8_t* buf, uint8_t* len) {
    if (Serial.available()) {
        delay(100); //wait 100ms for the full message to come
        *len = Serial.available();
        Serial.readBytes((char*) buf, *len);
        return true;
    }
    return false;
}

void generate_checksum(uint8_t* buf, uint8_t* index) {
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < *index; i++) {
        checksum ^= buf[i];
    }
    buf[*index] = checksum;
    (*index)++;
}

void setup() {
    Serial.begin(BAUD);
    init_pins();
    init_radio();
    Serial.println("done");
}

void loop() {
    uint8_t buf[RADIO_BUF_LEN];
    uint8_t len = RADIO_BUF_LEN;
    if (get_usb_message(buf, &len)) {
        //switch on id
        switch (buf[6]) {
            case HANDSHAKE:
                Serial.write(HANDSHAKE);
                Serial.flush();
                delay(100);
                break;

            case IS_CONTROLLER:
                Serial.write(0);
                break;

            case IS_GATEWAY:
                Serial.write(1);
                break;
            
            default:
                //relay message
                radio.send(buf, len);
                radio.waitPacketSent();
        }
    }

    len = RADIO_BUF_LEN;
    if (radio.recv(buf, &len)) {
        //relay the raw packet
        Serial.write(buf, len);
        Serial.flush();

        //generate RSSI message
        uint8_t msg[32];
        uint8_t index = 0;
        msg[index] = '$';
        index++;
        index++; //skip len
    
        write_int_to_array(msg, (int32_t) 0, &index);
        msg[index] = GATEWAY_RSSI;
        index++;
        write_int_to_array(msg, (int32_t) radio.lastRssi(), &index);
        msg[1] = index;
        generate_checksum(msg, &index);
        Serial.write(msg, index);
        Serial.flush();
    }   
}