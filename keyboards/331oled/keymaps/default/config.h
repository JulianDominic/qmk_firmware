#pragma once

#define RP2040_MCUCONF

// OLED
#define I2C_DRIVER I2CD0
#define I2C1_SCL_PIN GP1
#define I2C1_SDA_PIN GP0
#define OLED_DISPLAY_128X64

// DIP Switch
#define DIP_SWITCH_PINS { GP19 }

// Matrix Keyboard
#define MATRIX_ROWS 3
#define MATRIX_COLS 3
