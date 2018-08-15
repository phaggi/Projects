DMS.hex: DMS.o
	avr-objcopy -O ihex DMS.o DMS.hex
DMS.o: start.c
	avr-gcc -mmcu=atmega8515  -Os -o DMS.o start.c
load: 
	sudo avrdude -p m8515 -c stk500 -P /dev/ttyUSB0  -U flash:w:DMS.hex
all: clean help
.PHONY: all
clean:
	rm -f DMS.o DMS.hex; ls -la
help:
	cat help_makefile
