
all:  *.cpp
	avr-gcc -mmcu=atmega328 -c *.cpp

IRremote.o:
	avr-gcc -mmcu=atmega328 -c IRremote.cpp

