#!/bin/bash

src=main
baud=9600
programmerDev=/dev/bus/usb/005/001
programmerType=avrisp2
avrType=atmega328p
avrFreq=1843200


cflags="-g -DF_CPU=${avrFreq} -Wall -Os -Werror -Wextra"

avr-gcc ${cflags} -mmcu=${avrType} -Wa,-ahlmns=${src}.lst -c -o ${src}.o ${src}.c

avrdude -p ${avrType} -c ${programmerType} -P ${programmerDev} -b ${baud} -v -U flash:w:${src}.flash.hex

echo done
