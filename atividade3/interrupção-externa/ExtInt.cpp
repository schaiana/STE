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


EXTINT * EXTINT::_EXTINT_singletons[] = {NULL};

void EXTINT::enable(){
	cli();
	EIMSK |= (1 << _id);
	sei();
}

void EXTINT::disable(){
	cli();
	EIMSK &= ~(1 << _id);
	sei();
}

void EXTINT::callback(){
	(*_pCallback)();
}

EXTINT::EXTINT(INT_ID_t id, ISC_t cfg, CALLBACK_t pCallback){
	_id = id;
	_pCallback = pCallback;
	EXTINT::_EXTINT_singletons[_id] = this;
	cli();
	

	//setar interrupcao
	if (id < 4){
		EICRA |= (cfg<<(id*2));
	} else {
		EICRB |= (cfg<<((id-4)*2));
	}

	EIFR |= (1 << _id);
	sei();
}

EXTINT::~EXTINT(){}

ISR(INT0_vect) { EXTINT::_EXTINT_singletons[0]->callback(); }

ISR(INT1_vect) { EXTINT::_EXTINT_singletons[1]->callback(); }

ISR(INT2_vect) { EXTINT::_EXTINT_singletons[2]->callback(); }

ISR(INT3_vect) { EXTINT::_EXTINT_singletons[3]->callback(); }

ISR(INT4_vect) { EXTINT::_EXTINT_singletons[4]->callback(); }

ISR(INT5_vect) { EXTINT::_EXTINT_singletons[5]->callback(); }

ISR(INT6_vect) { EXTINT::_EXTINT_singletons[6]->callback(); }

ISR(INT7_vect) { EXTINT::_EXTINT_singletons[7]->callback(); }
