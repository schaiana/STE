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

//CALLBACK_t _pcallback[8];
//uint8_t _id;

EXTINT::EXTINT instance;

void EXTINT::enable(){
	sei();
	EIMSK |= (1 << _id);
}

void EXTINT::disable(){
	cli();
	//	EIMSK &= ~(1 << _id);
}

void EXTINT::callback(){
	(instance.*_pcallback[_id])(void);
//	(*_pcallback[_id])(); //ponteiro para o m�todo definido atrav�s
}

EXTINT::EXTINT(INT_ID_t id, ISC_t cfg, CALLBACK_t pCallback){
	_id = id;
	_pCallback[_id] = pCallback;

	//desabilitar interrup��es
	disable();

	//setar interrup��o
	if (id < 4){
		EICRA = cfg;
		EICRB = 0b00000000;
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

ISR(INT0_vect) { callback(); }

ISR(INT1_vect) { callback(); }

ISR(INT2_vect) { callback(); }

ISR(INT3_vect) { callback(); }

ISR(INT4_vect) { callback(); }

ISR(INT5_vect) { callback(); }

ISR(INT6_vect) { callback(); }

ISR(INT7_vect) { callback(); }
