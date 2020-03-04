all: clean build

build:
	avr-gcc -std=c99 -Wall -Os -mmcu=attiny85 -DF_CPU=1000000 main.c DS3231.c USI_I2C_Master.c display_7seg.c eeprom.c
	avr-objcopy -j .text -j .data -O ihex a.out a.hex

flash: all
	avrdude -p attiny85 -c avrisp -b 19200 -P /dev/ttyACM0 -U flash:w:a.hex

fuse:
	avrdude -p attiny85 -c avrisp -b 19200 -P /dev/ttyACM0 -U lfuse:w:0x52:m -U hfuse:w:0xDD:m -U efuse:w:0xFF:m 

install: flash fuse

clean:
	-rm a.out
	-rm a.hex