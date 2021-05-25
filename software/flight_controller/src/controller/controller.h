#include "SPIFlash.h"
#include "RH_RF69.h"
#include "Adafruit_BMP280.h"
#include "MPU9250.h"
#include "rocket.h"
#include "definitions.h"

void dispRgb(uint8_t R, uint8_t G, uint8_t B);

extern RH_RF69 radio; 
extern SPIFlash flash;
extern Adafruit_BMP280 bmp;
extern MPU9250 mpu;

extern uint32_t flash_addr;
extern float ground_level;
extern bool error;
extern rocket::state rocket_state;
extern bool flash_enabled;
extern bool negative_z;