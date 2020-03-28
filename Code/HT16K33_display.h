#ifndef HT16K33_DISPLAY_H_
#define HT16K33_DISPLAY_H_

#include <stdint.h>
#include <stdbool.h>

void disp_init();
void disp_set_brightness(uint8_t b);
void disp_draw_colon(bool state);
void disp_write_digit_raw(uint8_t digit, uint8_t bitmask);
void disp_write_digit_num(uint8_t digit, uint8_t num, bool dot);
void disp_clear();
void disp_update();

#endif