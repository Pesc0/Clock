#include "USI_I2C_Master.h"
#include "DS3231.h"
#include "HT16K33_display.h"
#include "eeprom.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>

#define BTT_1 (1 << PB1)
#define BTT_2 (1 << PB4)
#define BTT_3 (1 << PB3)

volatile bool blink = 0;
volatile uint8_t seconds_in_temp_mode = 0;
volatile uint8_t brightness = 0; 
volatile uint8_t old_bright = 0; //dummy variable to prevent useless eeprom writes

volatile Time_t now = {0, 0};

typedef enum {
    DISPLAY_TIME = 0,
    DISPLAY_TEMP,
    SET_HOUR,
    SET_MIN,
    SET_BRIGHT,
    ERR_DEAD_BATTERY
} ClockState;

volatile ClockState clock_state = 0;

#include "config.h"

/*------------------------------------------*/

//update the display in different ways depending on the current mode
void update_clock()
{
    disp_clear();

    switch (clock_state)
    {
    case DISPLAY_TIME:
        now = RTC_get_time(); //update time

        //write digit by digit to ensure that e.g. midnight looks "00:00" instead of "  : 0"
        disp_write_digit_num(0, now.hh/10, false);
        disp_write_digit_num(1, now.hh%10, false);
        disp_write_digit_num(3, now.mm/10, false);
        disp_write_digit_num(4, now.mm%10, false);
            
        disp_draw_colon(blink); //blink colon 

        break;
    
    case DISPLAY_TEMP:
        {
            float temp = RTC_get_temperature();

            if(temp < 0) { //-12C
                disp_write_digit_raw(0, 0x40); // '-' 
                temp = -temp; //pretend temp is positive
                disp_write_digit_num(1, (uint8_t)(temp/10.0f)%10, false); //tens of degrees
                disp_write_digit_num(3, (uint8_t)(temp)%10, false); //units of degrees
            }
            else { //12.3C
                disp_write_digit_num(0, (uint8_t)(temp/10.0f)%10, false); //tens of degrees
                disp_write_digit_num(1, (uint8_t)(temp)%10, true); //units of degrees + dot
                disp_write_digit_num(3, (uint8_t)(temp*10.0f)%10, false); //tenths of degree
            }
        }

        disp_write_digit_raw(4, 0x39); //write final C for celsius

        if(seconds_in_temp_mode >= MAX_SECONDS_IN_TEMP_MODE) { //go back to normal time display after time elapsed
            clock_state = DISPLAY_TIME;
        }
        seconds_in_temp_mode++; //increase counter

        break;

    case SET_HOUR:

        if(blink) { //blink hour digits
            disp_write_digit_num(0, now.hh/10, false);
            disp_write_digit_num(1, now.hh%10, false);
        }

        disp_write_digit_num(3, now.mm/10, false);
        disp_write_digit_num(4, now.mm%10, false);

        disp_draw_colon(true); //keep colon lit during time setting modes

        break;

    case SET_MIN:

        disp_write_digit_num(0, now.hh/10, false);
        disp_write_digit_num(1, now.hh%10, false);

        if(blink) { //blink minute digits
            disp_write_digit_num(3, now.mm/10, false);
            disp_write_digit_num(4, now.mm%10, false);
        }

        disp_draw_colon(true); //keep colon lit during time setting modes

        break;

    case SET_BRIGHT:
        disp_set_brightness(brightness);
        disp_write_digit_raw(0, 0x7C); // 'b'
        disp_write_digit_raw(1, 0x50); // 'r'
        disp_write_digit_raw(3, 0x10); // 'i'
        disp_write_digit_raw(4, 0x3D); // 'G'
        break;

    case ERR_DEAD_BATTERY:

        //alternate "dEAd" and "bAtt"
        if(blink) {
            disp_write_digit_raw(0, 0x5E); // 'd'
            disp_write_digit_raw(1, 0x79); // 'E'
            disp_write_digit_raw(3, 0x77); // 'A'
            disp_write_digit_raw(4, 0x5E); // 'd'
        }
        else {
            disp_write_digit_raw(0, 0x7C); // 'b'
            disp_write_digit_raw(1, 0x77); // 'A'
            disp_write_digit_raw(3, 0x78); // 't'
            disp_write_digit_raw(4, 0x78); // 't'
        }

        break;
    }

    blink = !blink; //toggle blink
    disp_update(); //push changes to the display
}

//when called immediately updates clock and reset watchdog to trigger after 1 second
void force_update()
{
    wdt_reset();
    update_clock();
}

//set the watchdog to call updateClock() once per second
void update_freq_1hz() 
{
    WDTCR = (1 << WDIE) | (1 << WDP2) | (1 << WDP1);
}

//set the interrupt to call updateClock() twice per second
void update_freq_2hz() 
{
    WDTCR = (1 << WDIE) | (1 << WDP2) | (1 << WDP0);
}

//interrupt executed at 1 or 2 Hz
ISR(WDT_vect) 
{
    update_clock();
}

//button interrupt
ISR(PCINT0_vect)
{    
    _delay_ms(15); //debounce switch
    GIFR = (1 << PCIF); //remove interrupt flag set by bouncing switch

    if(!(PINB & MODE_BTT)) //middle button press changes mode
    {
        switch (clock_state)
        {
        case DISPLAY_TIME:

            // check for a button released every 1ms for a maximum of 1 second
            for(uint16_t i = 0; i < LONG_PRESS_TIME_MS && !(PINB & MODE_BTT); i++) {
                _delay_ms(1);
            }
            
            if( !(PINB & MODE_BTT) ) { //button is still pressed. this is a long press: enter settings mode
                clock_state = SET_HOUR;
                update_freq_2hz(); //fast blinking in setting modes
            }
            else { //button has been released, redirect to temp display mode
                clock_state = DISPLAY_TEMP;
                seconds_in_temp_mode = 0; //reset counter
            }

            break;

        //cycle trough setting options and finally back to display mode
        case SET_HOUR:
            clock_state = SET_MIN;
            break;

        case SET_MIN:
            RTC_set_time(now); //write new time when exiting time setting modes

            //entering SET_BRIGHT mode: keep track of old brightness value to avoid writing 
            //to eeprom if the value didnt change
            clock_state = SET_BRIGHT;
            old_bright = brightness; 
            break;

        case SET_BRIGHT:
            clock_state = DISPLAY_TIME; //return to time mode
            update_freq_1hz(); //go back to normal blinking in display modes

            //if brightness got changed write new brightness value to eeprom when exiting SET_BRIGHT mode
            if(brightness != old_bright) {
                eeprom_write(EEPROM_BRIGHT_ADDR, brightness); 
            }

            break;

        case DISPLAY_TEMP:
            clock_state = DISPLAY_TIME; //go back to time mode
            break;

        case ERR_DEAD_BATTERY: //if battery was dead display "dead - batt" and wait for button press
            clock_state = SET_HOUR; //time has to be reset
            update_freq_2hz(); //fast blinking in setting modes
            break;
        }

        //so that digits blink as soon as you change mode, making the interface more "reactive"
        //when going back to display time mode turn on colon immediately instead [cosmetic]
        blink = (clock_state == DISPLAY_TIME); 
        force_update();
    }

    if(!(PINB & MINUS_BTT)) // button 1 decrease
    {
        bool first_time = true; //require a long press before triggering the quick repeat
        uint16_t delay_time_ms = 0;

        do //loop to decrease quickly when the button is held down
        {
            switch (clock_state)
            {     
            case SET_HOUR:
                now.hh--; //decrease time by one hour
                if(now.hh > 23) {
                    now.hh = 23; //underflow
                }
                break;

            case SET_MIN:
                now.mm--; //decrease by one minute
                if(now.mm > 59) {
                    now.mm = 59; //underflow
                }
                break;

            case SET_BRIGHT:
                brightness--;
                if(brightness < BRIGHT_MIN || brightness > BRIGHT_MAX) {
                    brightness = BRIGHT_MAX; 
                }
                break;

            default: return; //skip update in other modes
            }
        
            //so that the new value is instantly updated and shown, 
            //instead of having to wait 1 second in case it happened to be blinking
            blink = true;
            force_update();

            if(first_time)
            {
                first_time = false;
                delay_time_ms = LONG_PRESS_TIME_MS;
            }
            else
            {
                delay_time_ms = LONG_PRESS_REPEAT_TIME_MS;
            }

            for(uint16_t i = 0; i < delay_time_ms && !(PINB & MINUS_BTT); i++) {
                _delay_ms(1);
            }

        } while (!(PINB & MINUS_BTT));
    }

    if(!(PINB & PLUS_BTT)) // button 3 increase
    {
        bool first_time = true; //require a long press before triggering the quick repeat
        uint16_t delay_time_ms = 0;

        do //loop to increase quickly when the button is held down
        {
            switch (clock_state)
            {
            case SET_HOUR:
                now.hh++; //increase time by one hour
                if(now.hh > 23) {
                    now.hh = 0;
                }
                break;

            case SET_MIN:
                now.mm++; //increase by one minute
                if(now.mm > 59) {
                    now.mm = 0;
                }
                break;

            case SET_BRIGHT:
                brightness++;
                if(brightness > BRIGHT_MAX) {
                    brightness = BRIGHT_MIN; //wrap around to minimum
                }
                break;
            
            default: return; //skip update in other modes
            }

            //so that the new value is instantly updated and shown, 
            //instead of having to wait 1 second in case it happened to be blinking
            blink = true;
            force_update();  

            if(first_time)
            {
                first_time = false;
                delay_time_ms = LONG_PRESS_TIME_MS;
            }
            else
            {
                delay_time_ms = LONG_PRESS_REPEAT_TIME_MS;
            }

            for(uint16_t i = 0; i < delay_time_ms && !(PINB & PLUS_BTT); i++) {
                _delay_ms(1);
            }

        } while (!(PINB & PLUS_BTT));
    }

} //button ISR


int main()
{
    I2C_init();
    disp_init();
    RTC_init();

    brightness = eeprom_read(EEPROM_BRIGHT_ADDR); //retrieve saved value
    //ensure eeprom didnt get corrupted
    if(brightness > BRIGHT_MAX || brightness < BRIGHT_MIN) {
        brightness = BRIGHT_MAX;
    }
    disp_set_brightness(brightness); 

    if(RTC_lost_power()) {
        clock_state = ERR_DEAD_BATTERY;
    }
    else {
        clock_state = DISPLAY_TIME;
    }

    blink = true; //start with [colon on] or ["dead"]
    update_clock(); //display as soon as possible

    WDTCR = (1 << WDIE); //enable watchdog;
    update_freq_1hz(); //ensure that for default DISPLAY mode clockUpdate() is called once per second

    //enable button as input pullups
    DDRB &= ~(BTT_1 | BTT_2 | BTT_3);
    PORTB |= (BTT_1 | BTT_2 | BTT_3);
    _delay_ms(10); //delay to stabilize the input pullups in order to avoid generating a premature interrupt

    //setup buttons interrupt
    PCMSK = (1 << PCINT1) | (1 << PCINT3) | (1 << PCINT4);
    GIMSK = (1 << PCIE);

    /* power saving */
    ADCSRA &= ~(1 << ADEN); //disable adc
    ACSR = (1 << ACD); //disable analog comparator
    PRR |= (1 << PRTIM1) | (1 << PRTIM0) | (1 << PRADC); //disable adc and timers. 
    //for convenience leave usi active to avoid having to re initialize it

    set_sleep_mode(SLEEP_MODE_PWR_DOWN); //setup to enter sleep mode
    sleep_enable();

    while(1) {

        //temporarily disable interrupts to allow timed sequence to disable bod during sleep
        cli(); 
        sleep_bod_disable(); 
        sei();

        sleep_cpu(); //go to sleep and wait for an interrupt. 

        //after the interrupt has woken up the cpu and executed the loop will restart
    }

    return 0; //never reached
}