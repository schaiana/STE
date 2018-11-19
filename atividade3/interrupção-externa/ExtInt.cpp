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

CALLBACK_t _pcallback[8];
uint8_t _id;

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

EXTINT::EXTINT(INT_ID_t id, ISC_t cfg, CALLBACK_t pCallback){
	_id = id;
	_pCallback[_id] = pCallback;

	//desabilitar interrup��es
	disable();

	//setar interrup��o
	if (id < 4){
		EICRA = cfg;
		EICRA = 0b00000000;
	} else {
		EICRB = cfg;
		EICRA = 0b00000000;
	}

	//habilitar interrup��o
	enable();

	//que que isso mesmo?
	EIFR |= (1 << _id);
}

EXTINT::~EXTINT(){}

ISR(INT0_vect) {
	(*_pcallback[_id])();
}

ISR(INT1_vect) {
	(*_pcallback[_id])();
}

ISR(INT2_vect) {
	(*_pcallback[_id])();
}

ISR(INT3_vect) {
	(*_pcallback[_id])();
}

ISR(INT4_vect) {
	(*_pcallback[_id])();
}

ISR(INT5_vect) {
	(*_pcallback[_id])();
}

ISR(INT6_vect) {
	(*_pcallback[_id])();
}

ISR(INT7_vect) {
	(*_pcallback[_id])();
}
