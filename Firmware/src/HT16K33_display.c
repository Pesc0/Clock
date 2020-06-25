#include "HT16K33_display.h"

#include "USI_I2C_Master.h"

#define HT16K33_ADDRESS 0x70

#define HT16K33_BLINK_CMD 0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_BLINK_2HZ  1
#define HT16K33_BLINK_1HZ  2
#define HT16K33_BLINK_HALFHZ  3

#define HT16K33_BRIGHTNESS_CMD 0xE0

#define SEVENSEG_DIGITS 5 //colon is considered a digit
static uint8_t displaybuffer[SEVENSEG_DIGITS];

static const uint8_t number_table[] = { 
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
};


void disp_init() 
{
    I2C_init_write(HT16K33_ADDRESS);
    I2C_write(0x21);  // turn on oscillator
    I2C_stop();

    //turn on display without blinking
    I2C_init_write(HT16K33_ADDRESS);
    I2C_write(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (HT16K33_BLINK_OFF << 1)); 
    I2C_stop();

    disp_set_brightness(15); // max brightness
}

void disp_set_brightness(uint8_t b) 
{
    if (b > 15) {
        b = 15;
    }

    I2C_init_write(HT16K33_ADDRESS);
    I2C_write(HT16K33_BRIGHTNESS_CMD | b);
    I2C_stop(); 
}

void disp_draw_colon(bool state) 
{
    if (state) {
        displaybuffer[2] = 0xFF;
    }
    else {
        displaybuffer[2] = 0;
    }
} 

void disp_write_digit_raw(uint8_t digit, uint8_t bitmask) 
{
    if (digit > (SEVENSEG_DIGITS - 1)) {
        return;
    }

    displaybuffer[digit] = bitmask;
}

void disp_write_digit_num(uint8_t digit, uint8_t num, bool dot) 
{
    if (digit > (SEVENSEG_DIGITS - 1)) {
        return;
    }

    disp_write_digit_raw(digit, number_table[num] | (dot << 7));
} 

void disp_clear() 
{
    for (uint8_t i = 0; i < SEVENSEG_DIGITS; i++) {
        displaybuffer[i] = 0;
    }
} 

void disp_update() 
{
    I2C_init_write(HT16K33_ADDRESS);
    I2C_write(0x00); // start at address 0x00

    for (uint8_t i = 0; i < SEVENSEG_DIGITS; i++)  {
	    I2C_write(displaybuffer[i]); //only write lower part of 16bit ram registers
	    I2C_write(0); //Higher 8 bits are always 0
    }

    I2C_stop();  
}