#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Singleton.h"
#include "Fila.h"

UART::UART(uint16_t baud, DataBits_t db, Parity_t par, StopBit_t sb, uint8_t double_speed)
{
    //Setar baud rate
    UBRR0 = FOSC/16/baud-1;

    //Setar TX e RX
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

    //Setar paridade, stop bits e data bits
    UCSR0C = par | sb | db;

    //Setar double speed
    UCSR0A = (double_speed << U2X0);

    tx_buffer.clear();
    rx_buffer.clear();
}

UART::~UART() {
    // TODO Auto-generated destructor stub
}

void UART::put(uint8_t data) {
	while (tx_buffer.cheia());

    tx_buffer.enfileira(data);
    UCSR0B |= (1 << UDRIE0);
}

void UART::puts(char* data) {
    for (int i = 0; data[i]! = 0; i++) put(data[i]);
}

uint8_t UART::get() {
	while (rx_buffer.vazia());

	uint8_t data = rx_buffer.desenfileira();
    return data;
}

bool UART::has_data( ) {
    return rx_buffer.tamanho();
}

//Handlers de interrupção
ISR(USART0_rx_vect)
{UART::rx_isr_handler();}

ISR(USART0_tx_vect)
{UART::tx_isr_handler();}

void UART::rx_isr_handler() {
	if (self()->rx_buffer.cheia()) return;
	self()->rx_buffer.enfileira((uint8_t) UDR0);
}

void UART::tx_isr_handler() {
	UDR0 = self()->tx_buffer.desenfileira();
	if (self()->tx_buffer.vazia())
		UCSR0B &= ~(1 << UDRIE0);
}
