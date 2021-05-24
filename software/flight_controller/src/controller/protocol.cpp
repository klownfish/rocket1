#include "controller.h"

#include "DataProtocol.h"
#include "protocol.h"
#include "rocket.h"

#define RADIO_EVERY 3

uint8_t message_count[255] = {0}; //init to 0

void handleDataStreams() {
    static DataProtocol radio_protocol;
    static DataProtocol serial_protocol;

    uint8_t buf[RH_RF69_MAX_MESSAGE_LEN]; 
    uint8_t len = RH_RF69_MAX_MESSAGE_LEN;
    if (radio.recv(buf, &len)) {
        radio_protocol.parse_bytes(buf, len);
    }
    while (Serial.available()) {
        serial_protocol.parse_byte(Serial.read());
    }
}

void sendMsg(rocket::MessageBase* msg, enum send_when send) {
    uint8_t id = msg->get_id();
    uint8_t len = msg->get_size() + HEADER_SIZE;
    uint8_t buf[len];
    DataProtocol::build_buf(msg, buf, &len);
    if (flash_enabled) {
        flash.writeByteArray(flash_addr, buf, len);
        flash_addr += len;
    }
    Serial.write(buf, len);

    switch (send) {
        case REGULAR:
            message_count[id] = (message_count[id] + 1) % RADIO_EVERY;
            if (message_count[id] == 0) {
                radio.send(buf, len);
            }
            break;
        case ALWAYS:
            radio.send(buf, len);
            break;
        case NEVER:
            break;
    }
}

void dataProtocolCallback(uint8_t id, uint8_t* buf, uint8_t len) {
    uint8_t header[HEADER_SIZE];
    uint8_t header_len;
    DataProtocol::build_header(id, header, &header_len);

    if (flash_enabled) {
        flash.writeByteArray(flash_addr, header, header_len);
        flash_addr += header_len;
        flash.writeByteArray(flash_addr, buf, len);
        flash_addr += len;
    }
    rocket::parse_message(id, buf);
}

void rocket::rx(rocket::handshake_from_ground_to_rocket msg) {
    rocket::handshake_from_rocket_to_ground response;
    delay(200);
    sendMsg(&response, ALWAYS);
    delay(500);
}

void rocket::rx(rocket::set_state_from_ground_to_rocket msg) {
    ::state = msg.get_state();
    rocket::state_from_rocket_to_ground response;
    response.set_state(::state);
    sendMsg(&response, ALWAYS);
}

void rocket::rx(rocket::simple_calibration_from_ground_to_rocket msg) {
    dispRgb(255, 0, 255);
    mpu.calibrateAccelGyro();
    ground_level = bmp.readAltitude();
    dispRgb(0, 255, 0);
}

void rocket::rx(rocket::mag_calibration_from_ground_to_rocket msg) {
    dispRgb(255, 0, 255);
    mpu.setMagneticDeclination(msg.get_declination());
    mpu.calibrateMag();
    dispRgb(0, 255, 0);
}