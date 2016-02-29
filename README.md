# AVR_blinky
Test for ATMEGA8L 8PU

make

##############################################################################
#for circuit avr_led.png
#set AVR fuse: Int. RC Osc. 1 Mhz; already the default state 
avrdude -c usbasp -p m8 -U lfuse:w:0xe1:m

make flash1M

##############################################################################

#for circuit with 7,373Mhz External Crystal avr_led7_373Mhz.png
#set AVR fuse: Ext. Crystal/Resonator High Freq.; Start-up time 16 CK + 64ms; [CKSEL=1111 SUT=11]
sudo avrdude -c usbasp -p m8 -U lfuse:w:0xff:m

make flash7M




http://www.ladyada.net/learn/avr/fuses.html
http://www.nongnu.org/avr-libc/user-manual/group__demo__project.html
http://www.cs.ou.edu/~fagg/classes/general/atmel/avrdude.pdf
