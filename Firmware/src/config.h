#include "buttons.h"

#define MODE_BTT BTT_2 
#define PLUS_BTT BTT_1
#define MINUS_BTT BTT_3 

//how many second it takes to stop displaying temperature and automatically go back to time
#define MAX_SECONDS_IN_TEMP_MODE 10 

#define BRIGHT_MIN 1 //min 0 (but at 0 the display is off)
#define BRIGHT_MAX 15 //max 15

//where the brightness value is saved in the eeprom [128/256/512 bytes depending on tiny85 model]
#define EEPROM_BRIGHT_ADDR 0 

//time needed to register a long press or to start button quick repeat
#define LONG_PRESS_TIME_MS 1000 

//when quick repeat is active wait this time between presses
#define REPEAT_TIME_MS 100