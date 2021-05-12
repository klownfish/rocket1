#if __has_include("callsign.h")
#   include "callsign.h"
#   define TX_POWER 13
#   define IS_HAM true
#else
#   define TX_POWER 13
#   define IS_HAM false
#endif

#define RADIO_BUF_LEN 128

#define FREQUENCY 433.800
#define MODULATION RH_RF69::ModemConfigChoice::GFSK_Rb4_8Fd9_6

#define PIN_EXT_RX 0
#define PIN_EXT_TX 0
#define PIN_LED_R 2
#define PIN_LED_G 3
#define PIN_LED_B 4
#define PIN_EXT_CS 7
#define PIN_FLASH_HOLD 8
#define PIN_FLASH_WP 9
#define PIN_FLASH_CS 10
#define PIN_MOSI 11
#define PIN_MISO 12
#define PIN_SCK 13
#define PIN_BAT_READ 15
#define PIN_SDA 18
#define PIN_SCL 19
#define PIN_RF_CS 20
#define PIN_RF_G0 21
#define PIN_RF_RST 22
#define PIN_BUZZER 23


#define BAUD 115200