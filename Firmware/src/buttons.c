#include "buttons.h"

#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <stdint.h>

#include "clock.h"
#include "config.h"

void buttons_init()
{
    //enable button as input pullups
    DDRB &= ~(BTT_1 | BTT_2 | BTT_3);
    PORTB |= (BTT_1 | BTT_2 | BTT_3);
    _delay_ms(10); //delay to stabilize the input pullups in order to avoid generating a premature interrupt

    //setup buttons interrupt
    PCMSK = (1 << PCINT1) | (1 << PCINT3) | (1 << PCINT4);
    GIMSK = (1 << PCIE);
}


bool button_is_pressed(uint8_t button)
{
    return !(PINB & button);
}

void wait_while_button_is_pressed(uint16_t max_delay_ms, uint8_t button)
{
    //exit when button is released or when max time is reached
    for(uint16_t i = 0; i < max_delay_ms && button_is_pressed(button); i++) {
        _delay_ms(1);
    }
}


//button interrupt
ISR(PCINT0_vect)
{    
    _delay_ms(15); //debounce switch
    GIFR = (1 << PCIF); //remove interrupt flag set by bouncing switch

    if(button_is_pressed(MODE_BTT)) 
    {
        if(clock_check_for_mode_button_long_press())
        {
            wait_while_button_is_pressed(LONG_PRESS_TIME_MS, MODE_BTT);
            
            if(button_is_pressed(MODE_BTT)) //still pressed, this is a long press
            { 
                clock_mode_button_long_press();
            }
            else //button has been released before minimum time, short press
            { 
                clock_mode_button_short_press();
            }
        }
        else
        {
            clock_mode_button_short_press();
        }
    }

    if(clock_are_adjust_buttons_active())
    {
        if(button_is_pressed(MINUS_BTT)) 
        {
            clock_minus_button_press();

            wait_while_button_is_pressed(LONG_PRESS_TIME_MS, MINUS_BTT);

            while(button_is_pressed(MINUS_BTT)) //repeat action quickly when the button is held down
            {
                clock_minus_button_press();

                wait_while_button_is_pressed(REPEAT_TIME_MS, MINUS_BTT);
            }       
        }

        if(button_is_pressed(PLUS_BTT)) 
        {
            clock_plus_button_press();

            wait_while_button_is_pressed(LONG_PRESS_TIME_MS, PLUS_BTT);

            while(button_is_pressed(PLUS_BTT)) //repeat action quickly when the button is held down
            {
                clock_plus_button_press();

                wait_while_button_is_pressed(REPEAT_TIME_MS, PLUS_BTT);
            }
        }
    }

} //button ISR

