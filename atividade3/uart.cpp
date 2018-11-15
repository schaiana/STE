#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
#define FOSC 16000000


UART::UART(uint32_t baud, DATABITS_t db, PARITY_t parity, STOPBITS_t sb){

  //setar baudrate
  ubrr = (fosc/16*baud)-1;
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;

  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);

  /* Set frame format: stop_bit, data_bits */
  UCSR0C = (parity<<UPM0)|(sb<<USBS0)|(db<<UCSZ0);


  new_data = 0;
  _tx_buffer.clear();
  _rx_buffer.clear();
}

UART::~UART(){}

void UART::put(uint8_t data){
  /* Wait for empty transmit buffer */
	while (!(UCSR0A & (1<<UDRE0)));

	/* Put data into buffer, sends the data */
	UDR0 = data;
}

bool UART::has_data( ) {
    return _new_data;
}
// Interrupt Handlers
ISR(USART0_rx_vect)
{ UART::rx_isr_handler(); }

void UART::rx_isr_handler() {
	if (self()->_rx_buffer.is_full()) return;

	self()->_rx_buffer.put((uint8_t) UDR0);
    self()->_new_data = 1;
}

ISR(USART0_tx_vect)
{ UART::tx_isr_handler(); }

void UART::tx_isr_handler() {
	UDR0 = self()->_tx_buffer.get();
	if (self()->_tx_buffer.is_empty())
		UCSR0B &= ~(1 << UDRIE0);
}

uint8_t UART::get(){
  /* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );

	/* Get and return received data from buffer */
	return UDR0;
}
