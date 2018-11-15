//UART BLOQUEANTE
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#define FOSC 16000000


UART::UART(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb){

  /* Set baud rate */
  ubrr = (fosc/16*baud)-1;
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;

  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);

  /* Set frame format: stop_bit, data_bits */
  UCSR0C = (parity<<UPM0)|(sb<<USBS0)|(db<<UCSZ0);
}

UART::~UART(){}

void UART::put(uint8_t data){
  /* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));

	/* Put data into buffer, sends the data */
	UDR0 = data;
}

uint8_t UART::get(){
  /* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );

	/* Get and return received data from buffer */
	return UDR0;
}
