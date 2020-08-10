# Clock
A digital clock based on the AtTiny85 chip.

### Features:
 * Simple interface, designed for the elderly who just need a simple clock.
 * Time is kept even after a power loss, provided the battery is working.
 * After a power loss if the battery is dead a reminder is shown to change it, and the user is forced to set the time. 
 * Great time keeping accuracy, thanks to the 2ppm accuracy of the DS3231 chip (basically in the worse case it will gain/lose 1 minute every year).
 * Brightness can be adjusted, the value is saved and will be restored even after a complete power loss.
 * Can display ambient temperature (the value is updated internally every minute or so).
 * Nearly instant boot time.
 * Easy to build PCB, ideal for beginners.
 * Cheap, around $10.
 * Energy efficient: the display consumes most of the power, so in theory it's possible to run the clock on batteries [not tested yet]. 
 * Fully open source.

## PCB Design

## 3D printed case

## Firmware

### Building

### Flashing