#!/bin/bash

src=main
src_files="main.c"
baud=9600
programmerDev=usb
programmerType=avrisp2
avrType=atmega328p
avrFreq=1843200


cflags="-g -DF_CPU=${avrFreq} -Wall -Os -Werror -Wextra"

avr-gcc ${cflags} -mmcu=${avrType} -Wa,-ahlmns=${src}.lst -c -o ${src}.o ${src_files}

avr-gcc ${cflags} -mmcu=${avrType} -o ${src}.elf ${src}.o

avr-objcopy -j .text -j .data -O ihex ${src}.elf ${src}.flash.hex

avrdude -p ${avrType} -c ${programmerType} -P ${programmerDev} -b ${baud} -v -U flash:w:${src}.flash.hex

echo done
