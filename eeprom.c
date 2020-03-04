#include "eeprom.h"

#include <avr/io.h>


uint8_t eeprom_read(uint16_t addr)
{
    while( EECR & (1 << EEPE) ); //Wait for completion of previous write

    EEAR = addr; //Set EEPROM address register

	EECR = (1 << EERE); //Start EEPROM read operation

	return EEDR; //Return the byte read from EEPROM
}

void eeprom_write(uint16_t addr, uint8_t data)
{
    while( EECR & (1 << EEPE) ); //Wait for completion of previous write
    
    EECR = (0 << EEPM1) | (0 << EEPM0); //Erase and write in one operation

    EEAR = addr; //Set EEPROM address register

    EEDR = data; //fill eeprom data register
    
    EECR = (1 << EEMPE); //Set the Master Program Enable bit    
    EECR |= (1 << EEPE); //Start eeprom write by setting the Program Enable bit
}