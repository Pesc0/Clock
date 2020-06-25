#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdbool.h>

void clock_init();

bool clock_check_for_mode_button_long_press();
void clock_mode_button_short_press();
void clock_mode_button_long_press();

bool clock_check_for_repeated_press();
void clock_plus_button_press();
void clock_minus_button_press();

#endif