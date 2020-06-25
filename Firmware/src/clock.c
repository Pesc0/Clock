#include "clock.h"
#include "DS3231.h"
#include "HT16K33_display.h"
#include "eeprom.h"
#include "config.h"

#include <avr/interrupt.h>
#include <avr/wdt.h> //watchdog interrupt used to periodically update the clock
#include <stdint.h>
#include <stdbool.h>
#include <float.h>


volatile bool blink = 0;
volatile uint8_t seconds_in_temp_mode = 0;
volatile uint8_t brightness = 0; 
volatile uint8_t old_bright = 0; //dummy variable to prevent useless eeprom writes

volatile Time_t now = {0, 0};

typedef enum 
{
    DISPLAY_TIME = 0,
    DISPLAY_TEMP,
    SET_HOUR,
    SET_MIN,
    SET_BRIGHT,
    ERR_DEAD_BATTERY
} ClockState;

volatile ClockState clock_state = 0;

void clock_update();

//when called immediately updates clock and reset watchdog to trigger after 1 second
void force_update()
{
    wdt_reset();
    clock_update();
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
    clock_update();
}


void clock_init()
{
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
    clock_update(); //display as soon as possible

    WDTCR = (1 << WDIE); //enable watchdog;
    update_freq_1hz(); //ensure that for default DISPLAY mode clockUpdate() is called once per second
}

//a long press is required only when jumping from display_time to set_hour mode
bool clock_check_for_mode_button_long_press()
{
    return clock_state == DISPLAY_TIME;
}

//plus and minus buttons are active only when needed, they do nothing in other modes
bool clock_are_adjust_buttons_active()
{
    return clock_state == SET_HOUR || clock_state == SET_MIN || clock_state == SET_BRIGHT;
}


void clock_mode_button_short_press()
{
    switch (clock_state)
    {
    case DISPLAY_TIME:
        clock_state = DISPLAY_TEMP;
        seconds_in_temp_mode = 0; //reset counter
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
        //if brightness got changed write new brightness value to eeprom when exiting SET_BRIGHT mode
        if(brightness != old_bright) {
            eeprom_write(EEPROM_BRIGHT_ADDR, brightness); 
        }

        clock_state = DISPLAY_TIME; //return to time mode
        update_freq_1hz(); //go back to normal blinking in display modes
        break;

    case DISPLAY_TEMP:
        clock_state = DISPLAY_TIME; //go back to time mode
        break;

    case ERR_DEAD_BATTERY: //if battery was dead display "dead - batt" and wait for button press
        clock_state = SET_HOUR; //time has to be reset
        update_freq_2hz(); //fast blinking in setting modes
        break;

    default: return;
    }

    //so that digits blink as soon as you change mode, making the interface more "reactive"
    //when going back to display time mode turn on colon immediately instead [cosmetic]
    blink = (clock_state == DISPLAY_TIME); 

    force_update();
}


void clock_mode_button_long_press()
{
    switch(clock_state) //should be always true when this function is called
    {
    case DISPLAY_TIME:
        clock_state = SET_HOUR; //require long press to enter settings modes
        update_freq_2hz(); //fast blinking in setting modes
        blink = false;
        break;
    
    default: return;
    }

    force_update();
}


void clock_plus_button_press()
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
}


void clock_minus_button_press()
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
}


//update the display in different ways depending on the current mode
void clock_update()
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