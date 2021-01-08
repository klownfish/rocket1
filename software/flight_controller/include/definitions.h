#if __has_include("callsign.h")
#   include "callsign.h"
#   define TX_POWER 20
#   define IS_HAM true
#else
#   define TX_POWER 13
#   define IS_HAM false
#endif

#define RF_CS 14
#define FLASH_CS 16
#define RF_G0 15
#define BAT_READ A9

#define FREQUENCY 433.800

#define ID_TELEMETRY 0x01
#define ID_STATE 0x02

#define ID_PARAMETERS 0x81
#define ID_CALIBRATE 0x82
#define ID_SLEEP 0x83
#define ID_WAKE_UP 0x84

#define CONTROLLER_DUMP_FLASH 1
#define CONTROLLER_HANDSHAKE 2
#define GATEWAY_HANDSHAKE 3
#define GATEWAY_TRANSMIT 4

#define BAUD 115200