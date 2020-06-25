#include "USI_I2C_Master.h"
#include "DS3231.h"
#include "HT16K33_display.h"
#include "eeprom.h"
#include "buttons.h"
#include "clock.h"
#include "config.h"


#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>


int main()
{
    I2C_init();
    disp_init();
    RTC_init();
    clock_init();
    buttons_init();

    /* power saving */
    ADCSRA &= ~(1 << ADEN); //disable adc
    ACSR = (1 << ACD); //disable analog comparator
    PRR |= (1 << PRTIM1) | (1 << PRTIM0) | (1 << PRADC); //disable adc and timers. 
    //for convenience leave usi active to avoid having to re initialize it

    set_sleep_mode(SLEEP_MODE_PWR_DOWN); //setup to enter sleep mode
    sleep_enable();

    while(true) 
    {

        //temporarily disable interrupts to allow timed sequence to disable bod during sleep
        cli(); 
        sleep_bod_disable(); 
        sei();

        sleep_cpu(); //go to sleep and wait for an interrupt. 

        //after the interrupt has woken up the cpu and executed the loop will restart
    }

    return 0; //never reached
}