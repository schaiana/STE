#include "UART.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Singleton.h"

UART::UART(uint16_t baud, DataBits_t db, Parity_t par, StopBit_t sb) {
    // Set baud rate
    UBRR0 = F_CPU/16/baud-1;

    // Set TX and RX
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

    // Set frame format (asynchronous mode)
    UCSR0C = par | sb | db;

    _new_data = 0;
    _rx_buffer = 0;
    _tx_buffer = 0;

}

UART::~UART() {
    // TODO Auto-generated destructor stub
}

void UART::put(uint8_t data) {
    this->_tx_buffer = data;
    UCSR0B |= (1 << UDRIE0);
}

uint8_t UART::get() {
    this->_new_data = 0;
    return this->_rx_buffer;
}

bool UART::has_data() {
    return this->_new_data;
}

// Interrupt Handlers
ISR(USART0_RX_vect)
{ UART::rxc_isr_handler(); }

void UART::rxc_isr_handler() {
    self()->_rx_buffer = UDR0;
    self()->_new_data = 1;
}

ISR(USART0_UDRE_vect)
{ UART::udre_isr_handler(); }

void UART::udre_isr_handler() {
    UDR0 = self()->_tx_buffer;
    UCSR0B &= ~(1 << UDRIE0);
}
