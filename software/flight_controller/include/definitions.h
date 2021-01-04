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

#define FREQUENCY 433.800
