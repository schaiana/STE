/*
 * main.cpp
 *
 * Author : Layssa Pacheco e Schaiana Sonaglio
 */ 

#include <avr/interrupt.h>
#include "PCINT_SL.h"
#include "UART.h"

UART uart(9600, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB, UART::DS_DISABLE);
PCINT_SL pcint_sl = PCINT_SL();

void int4_handler(){
	uart.puts("4\n");
	return;
}

void int9_handler(void){
	uart.puts("9\n");
	return;
}

void int10_handler(void){
	uart.puts("10\n");
	return;
}

void int16_handler(void){
	uart.puts("16\n");
	return;
}

int main( void ){
	pcint_sl.enable(PCINT_SL::PCINT_4, &int4_handler);
	pcint_sl.enable(PCINT_SL::PCINT_9, &int9_handler);
	pcint_sl.enable(PCINT_SL::PCINT_10, &int10_handler);
	pcint_sl.enable(PCINT_SL::PCINT_16, &int16_handler);

	uart.puts("teste1234567890_teste1234567890\n");
	while(1){
		/*if (uart.has_data()){
			uart.put(uart.get());
			//uart.puts("\n");
		}*/
		pcint_sl.manager();
		_delay_ms(100);
	}
	return 0;
}
