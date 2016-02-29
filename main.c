
#ifdef AVR_AT_7373MHZ
#define F_CPU 7372800UL  /* 7.3728 MHz Internal Oscillator */
#else
#define F_CPU 1000000UL  /* 1 MHz Internal Oscillator */
#endif

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define FOSC 7372800UL// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( unsigned int ubrr)
{
	/* Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;

	/* Enable receiver and transmitter */
	/* When the USART Transmitter is enabled, this (Port D, Bit 1) pin is configured as an output regardless of the value of DDD1 */
	/* When the USART Receiver is enabled this (Port D, Bit 0) pin is configured as an input regardless of the value of DDD0. */
	/*  When the USART forces this (Port D, Bit 0) pin to be an input, the pull-up can still be controlled by the PORTD0 bit.*/
	//UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);

	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )	;
	/* Put data into buffer, sends the data */
	UDR = data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
}


// http://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html
SIGNAL(USART_RXC_vect)
{
   char ReceivedByte;
   ReceivedByte = UDR; // Fetch the received byte value into the variable "ByteReceived"
   UDR = ReceivedByte; // Echo back the received byte back to the computer
}



//http://www.fourwalledcubicle.com/AVRArticles.php
//http://www.protostack.com/blog/2010/06/introduction-to-io-registers/
//http://www.nongnu.org/avr-libc/user-manual/FAQ.html
//http://www.avr-tutorials.com/digital/digital-input-output-c-programming-atmel-avr-8-bits-microcontrollers
//http://maxembedded.com/2011/06/avr-basics/
//http://maxembedded.com/2011/06/port-operations-in-avr/
//http://elecrom.com/2008/02/12/avr-tutorial-2-avr-input-output/


int main (void)
{
	DDRC = _BV (PC0);

	USART_Init ( MYUBRR );

	sei();	//enable interrupt

	USART_Transmit('I');
	USART_Transmit('T');
	USART_Transmit(' ');
	USART_Transmit('W');
	USART_Transmit('O');
	USART_Transmit('R');
	USART_Transmit('K');
	USART_Transmit('S');
	USART_Transmit('\n');


	while (1)
	{
		PORTC &= ~_BV(PC0);
		_delay_ms(1000);

		PORTC |= _BV(PC0);
		_delay_ms(1000);
	}

	return 1;
}
