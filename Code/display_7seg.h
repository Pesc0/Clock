#ifndef DISPLAY_7SEG_H_
#define DISPLAY_7SEG_H_

#include <stdint.h>
#include <stdbool.h>

void disp_init();
void disp_set_brightness(uint8_t b);
void disp_blink_rate(uint8_t b); //blinks all display
void disp_draw_colon(bool state);
void disp_write_digit_raw(uint8_t digit, uint8_t bitmask);
void disp_write_digit_num(uint8_t digit, uint8_t num, bool dot);
void disp_clear();
void disp_update();

#endif