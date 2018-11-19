/*
 * ExtInt.cpp
 *
 *  Author: Layssa Pacheco e Schaiana Sonaglio
 */

//INTERRUP��O EXTERNA
#include "uart.h"
#include "ExtInt.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

CALLBACK_t EXTINT::_pcallback[8];

void EXTINT::enable(){
	sei();
	EIMSK |= (1 << _id);
}

void EXTINT::disable(){
	cli();
	//	EIMSK &= ~(1 << _id);
}

void EXTINT::callback(){
	(*_pcallback[_id])(); //ponteiro para o m�todo definido atrav�s
}

EXTINT::ExtInt(INT_ID_t id, ISC_t cfg, CALLBACK_t pCallback)
	_id = id;
	_pCallback[_id] = pCallback;

	//desabilitar interrup��es
	EXTINT::disable()

	//setar interrup��o
	if (id < 4){
		EICRA = cfg;
		EICRA = 0b00000000;
		} else {
		EICRB = cfg;
		EICRA = 0b00000000;
	}

	//habilitar interrup��o
	EXTINT::enable();

	//que que isso mesmo?
	EIFR |= (1 << _id);
}

EXTINT::~ExtInt(){}

ISR(INT0_vect) {
	EXTINT::callback();
}

ISR(INT1_vect) {
	EXTINT::callback();
}

ISR(INT2_vect) {
	EXTINT::callback();
}

ISR(INT3_vect) {
	EXTINT::callback();
}

ISR(INT4_vect) {
	EXTINT::callback();
}

ISR(INT5_vect) {
	EXTINT::callback();
}

ISR(INT6_vect) {
	EXTINT::callback();
}

ISR(INT7_vect) {
	EXTINT::callback();
}
