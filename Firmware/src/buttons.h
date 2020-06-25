#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <avr/io.h>

#define BTT_1 (1 << PB1)
#define BTT_2 (1 << PB4)
#define BTT_3 (1 << PB3)

void buttons_init();

#endif