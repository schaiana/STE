/*
 * main.cpp
 *
 * Author : Layssa Pacheco e Schaiana Sonaglio
 */ 

#include <avr/interrupt.h>
#include "EXTINT.h"
#include "uart.h"

UART uart(9600, UART::EIGHT_DB, UART::NONE_PAR, UART::TWO_SB, UART::DS_DISABLE);

void int0_handler(void){
	uart.puts("0\n");
	return;
}

void int1_handler(void){
	uart.puts("1\n");
	return;
}

void int2_handler(void){
	uart.puts("2\n");
	return;
}

void int3_handler(void){
	uart.puts("3\n");
	return;
}

void int4_handler(void){
	uart.puts("4\n");
	return;
}

void int5_handler(void){
	uart.puts("5\n");
	return;
}

void int6_handler(void){
	uart.puts("6\n");
	return;
}

void int7_handler(void){
	uart.puts("7\n");
	return;
}

int main(){

	EXTINT int0_obj(EXTINT::INT_0, EXTINT::FALLING, &int0_handler);
	EXTINT int1_obj(EXTINT::INT_1, EXTINT::FALLING, &int1_handler);
	EXTINT int2_obj(EXTINT::INT_2, EXTINT::FALLING, &int2_handler);
	EXTINT int3_obj(EXTINT::INT_3, EXTINT::FALLING, &int3_handler);
	EXTINT int4_obj(EXTINT::INT_4, EXTINT::FALLING, &int4_handler);
	EXTINT int5_obj(EXTINT::INT_5, EXTINT::FALLING, &int5_handler);
	EXTINT int6_obj(EXTINT::INT_6, EXTINT::FALLING, &int6_handler);
	EXTINT int7_obj(EXTINT::INT_7, EXTINT::FALLING, &int7_handler);

	int0_obj.enable();
	int1_obj.enable();
	int2_obj.enable();
	int3_obj.enable();
	int4_obj.enable();
	int5_obj.enable();
	int6_obj.enable();
	int7_obj.enable();

	
	while(1){                                   
		if (uart.has_data()){
			uart.put(uart.get());                
			uart.puts("\n");
		}
	}
	return 0;
}
