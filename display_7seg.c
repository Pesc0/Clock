#include "display_7seg.h"

#include "USI_I2C_Master.h"

#define HT16K33_ADDRESS 0x70

#define HT16K33_BLINK_CMD 0x80
#define HT16K33_BLINK_DISPLAYON 0x01
#define HT16K33_BLINK_OFF 0
#define HT16K33_BLINK_2HZ  1
#define HT16K33_BLINK_1HZ  2
#define HT16K33_BLINK_HALFHZ  3

#define HT16K33_CMD_BRIGHTNESS 0xE0

#define SEVENSEG_DIGITS 5

static const uint8_t numbertable[] = { 
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
	0x77, /* a */
	0x7C, /* b */
	0x39, /* C */
	0x5E, /* d */
	0x79, /* E */
	0x71, /* F */
    0x78, /* t */
    0x40, /* - */
    0x50, /* r */
    0x10, /* i */
    0x3D, /* g */
};

uint8_t displaybuffer[SEVENSEG_DIGITS];


void disp_init() 
{
    I2C_init_write(HT16K33_ADDRESS);
    I2C_write(0x21);  // turn on oscillator
    I2C_stop();

    disp_blink_rate(HT16K33_BLINK_OFF);
    disp_set_brightness(15); // max brightness
}

void disp_set_brightness(uint8_t b) 
{
    if (b > 15) {
        b = 15;
    }

    I2C_init_write(HT16K33_ADDRESS);
    I2C_write(HT16K33_CMD_BRIGHTNESS | b);
    I2C_stop(); 
}

void disp_blink_rate(uint8_t b) 
{
    if (b > 3) {
        b = 0; // turn off if not sure
    }

    I2C_init_write(HT16K33_ADDRESS);
    I2C_write(HT16K33_BLINK_CMD | HT16K33_BLINK_DISPLAYON | (b << 1)); 
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
    if (digit > 4) {
        return;
    }

    displaybuffer[digit] = bitmask;
}

void disp_write_digit_num(uint8_t digit, uint8_t num, bool dot) 
{
    if (digit > 4) {
        return;
    }

    disp_write_digit_raw(digit, numbertable[num] | (dot << 7));
} 

void disp_clear(void) 
{
    for (uint8_t i = 0; i < SEVENSEG_DIGITS; i++) {
        displaybuffer[i] = 0;
    }
} 

void disp_update(void) 
{
    I2C_init_write(HT16K33_ADDRESS);
    I2C_write(0x00); // start at address 0x00

    for (uint8_t i = 0; i < SEVENSEG_DIGITS; i++)  {
	    I2C_write(displaybuffer[i]); //only write lower part of 16bit ram registers
	    I2C_write(0); //Higher 8 bits are always 0
    }

    I2C_stop();  
}