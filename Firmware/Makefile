all: build


Srcs = main.c DS3231.c USI_I2C_Master.c HT16K33_display.c eeprom.c

build:
	avr-gcc -std=c99 -Wall -Os -mmcu=attiny85 -DF_CPU=1000000 src/*.c -o Build/Fw.out
	avr-objcopy -j .text -j .data -O ihex Build/Fw.out Build/Fw.hex

flash: build
	avrdude -p attiny85 -c avrisp -b 19200 -P /dev/ttyACM0 -U flash:w:Build/Fw.hex

fuse:
	avrdude -p attiny85 -c avrisp -b 19200 -P /dev/ttyACM0 -U lfuse:w:0x52:m -U hfuse:w:0xDD:m -U efuse:w:0xFF:m 

install: flash fuse

clean:
	-rm Build/*