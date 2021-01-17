#if __has_include("callsign.h")
#   include "callsign.h"
#   define TX_POWER 13
#   define IS_HAM true
#else
#   define TX_POWER 13
#   define IS_HAM false
#endif

#define RF_CS 14 //default ss because the SPIMemory doesn't work...
#define FLASH_CS 10
#define RF_G0 15
#define BAT_READ A9
#define RF_RST 17

#define RADIO_BUF_LEN 128

#define FREQUENCY 433.800
#define MODULATION RH_RF69::ModemConfigChoice::GFSK_Rb4_8Fd9_6

#define ID_TELEMETRY 0x01
#define ID_STATE 0x02

#define ID_PARAMETERS 0x81
#define ID_CALIBRATE 0x82
#define ID_SLEEP 0x83
#define ID_WAKE_UP 0x84

#define HANDSHAKE 0xB0
#define CONTROLLER_DUMP_FLASH 0xB1
#define GATEWAY_TRANSMIT 0xB2
#define IS_CONTROLLER 0xB3
#define IS_GATEWAY 0xB4

#define GATEWAY_RSSI 0xE0

#define BAUD 115200