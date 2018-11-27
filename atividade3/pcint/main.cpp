/*
 * main.cpp
 *
 * Author : Layssa Pacheco e Schaiana Sonaglio
 */ 

#include <avr/interrupt.h>
#include "EI_PCINT.h"
#include "UART.h"

UART uart(19200, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB);

void int0_handler(void){
	uart.put('0');
	return;
}

void int1_handler(void){
	uart.put('1');
	return;
}

void int2_handler(void){
	uart.put('2');
	return;
}

int main( void ){

	EI_PCINT int0_obj(EI_PCINT::PCINT_0, &int0_handler);
	EI_PCINT int1_obj(EI_PCINT::PCINT_1, &int1_handler);
	EI_PCINT int2_obj(EI_PCINT::PCINT_2, &int2_handler);

	int0_obj.enable();
	int1_obj.enable();
	int2_obj.enable();

	sei();
	while(1){                                   /* forever */
		if (uart.has_data()){
			uart.put(uart.get());                 /* echo the received character */
//			uart.put((EICRA));
		}
	}

	return 0;
}
