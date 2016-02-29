PROJECT=avr_blinky

all: all1M all7M

all1M:
	avr-gcc -mmcu=atmega8 -Wall -I./ -o $(PROJECT)1M.out main.c
	avr-objcopy -j .text -O ihex $(PROJECT)1M.out $(PROJECT)1M.hex

all7M:
	avr-gcc -mmcu=atmega8 -Wall -DAVR_AT_7373MHZ -I./ -o $(PROJECT)7M.out main.c
	avr-objcopy -j .text -O ihex $(PROJECT)7M.out $(PROJECT)7M.hex
	

flash1M: $(PROJECT)1M.hex
	avrdude -p m8 -c usbasp -e -U flash:w:$(PROJECT)1M.hex

flash7M: $(PROJECT)7M.hex
	avrdude -p m8 -c usbasp -e -U flash:w:$(PROJECT)7M.hex
	
clean:
	rm -f $(PROJECT).o
	rm -f $(PROJECT)1M.out
	rm -f $(PROJECT)1M.map
	rm -f $(PROJECT)1M.hex
	rm -f $(PROJECT)7M.out
	rm -f $(PROJECT)7M.map
	rm -f $(PROJECT)7M.hex