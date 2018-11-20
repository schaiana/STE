/*
 * EI_PCINT.cpp
 *
 *  Author: Layssa Pacheco e Schaiana Sonaglio
 */

#include "UART.h"
#include "EI_PCINT.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

CALLBACK_t EI_PCINT::_pcallback[8];

void EI_PCINT::enable(){

	if(_id < 8){ PCICR |= (1 << PCIE0);	}
	else if(_id < 16){ PCICR |= (1 << PCIE1); }
	else { PCICR |= (1 << PCIE2); }

	sei();
}

void EI_PCINT::disable(){ cli(); }

void EI_PCINT::callback(){ (_pcallback[_id])(); }

EI_PCINT::EI_PCINT(PCINT_ID_t id, CALLBACK_t pCallback){
	_id = id;
	_pCallback[_id] = pCallback;

	EI_PCINT::disable();

	if(_id < 8){
		PCMSK0 |= (1<<_id);
		PCIFR |= (1 << PCIE0);
	} else if(_id < 16){
		PCMSK1 |= (1<<(_id-8));
		PCIFR |= (1 << PCIE1);
	} else {
		PCMSK2 |= (1<<(_id-16));
		PCIFR |= (1 << PCIE2);
	}

	EI_PCINT::enable();

	EIFR |= (1 << _id);
}

EI_PCINT::~EI_PCINT(){}
/*
ISR(PCINT0_vect) {EI_PCINT::callback();}
ISR(PCINT1_vect) {EI_PCINT::callback();}
ISR(PCINT2_vect) {EI_PCINT::callback();}
*/

/**********************************************************************************************************/
/* PCI2 setado como 1, possibilita interrup��o nos pinos PCINT16:23, habilitado pelo registrador PCMSK2  */
/*PCI1 setado como 1, possibilita interrup��o nos pinos PCINT8:15, habilitado pelo registrador PCMSK1    */
/*PCI0 setado como 1, possibilita interrup��o nos pinos PCINT0:7, habilitado pelo registrador PCMSK0     */
/***********************************************************************************************************/
