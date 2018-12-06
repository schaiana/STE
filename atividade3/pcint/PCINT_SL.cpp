/*
 * EI_PCINT.cpp
 *
 *  Author: Layssa Pacheco e Schaiana Sonaglio
 */

#include "UART.h"
#include "PCINT_SL.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

CALLBACK_t PCINT_SL::_pCallback[] = {NULL};
uint8_t PCINT_SL::portHist[] = {0};
uint8_t PCINT_SL::pinsChanged[] = {0};

//uint8_t EI_PCINT::porthistory[3];
//uint8_t EI_PCINT::changedbits;

PCINT_SL::PCINT_SL(){
	PCICR |= (1 << PCIE2) | (1 << PCIE1) | (1 << PCIE0);
	//salva o estado atual cara cada um dos registradores
		//PCMSK0: PB0 até PB6  ... PCINT0 até PCINT6
	PCINT_SL::portHist[0] = PINB;
		//PCMSK1: PE0 + PJ0 até PJ6 ... PCINT7 até PCINT15
	PCINT_SL::portHist[1] = ((PINJ << 1) | ((PINE & (1 << PINE0))<<7)); //precisamos adicionar PINE0 + PINJ
		//PCMSK2: PK0 até PK6 ... PCINT16 até PCINT23
	PCINT_SL::portHist[2] = PINK;
	sei();
}

void PCINT_SL::enable(uint8_t PCINTx, CALLBACK_t pCallback){
	cli();
	if(PCINTx < 8){ 
		PCMSK0 |= (1<<PCINTx);	
	} else if(PCINTx < 16){
		PCMSK1 |= (1<<(PCINTx-8));
	} else if (PCINTx < 24) {
		PCMSK2 |= (1<<(PCINTx-16));
	}
	_pCallback[PCINTx] = pCallback;
	sei();
}

void PCINT_SL::disable(uint8_t PCINTx){
	if(PCINTx < 8){
		PCMSK0 &= ~(1<<PCINTx);
	} else if(PCINTx < 16){
		PCMSK0 &= ~(1<<(PCINTx-8));
	} else if (PCINTx < 24) {
		PCMSK0 &= ~(1<<(PCINTx-16));
	}
	_pCallback[PCINTx] = NULL;
}


void PCINT_SL::callback(uint8_t PCINTx){
	// adicionar a interrupção
	uint8_t changedbits;
	uint8_t i = 0;
	
	if(PCINTx == 0){
		changedbits = (PINB ^ portHist[0]) & PCMSK0;
		pinsChanged[0] |= changedbits;
		portHist[0] = PINB;
	} else if(PCINTx == 1){
	    changedbits = (((PINJ << 1) | ((PINE & (1 << PINE0))<<7)) ^ portHist[1]) & PCMSK1;
		pinsChanged[1] |= changedbits;
	    portHist[1] = ((PINJ << 1) | ((PINE & (1 << PINE0))<<7)) & PCMSK2;
	} else if(PCINTx == 2) {
		changedbits = PINK ^ portHist[2];
		pinsChanged[2] |= changedbits;
		portHist[2] = PINK;
	}
}

void PCINT_SL::manager(){
	int registrador,pino,nCallback;
	
	for(registrador=0; registrador<=2; registrador++){
		for(pino=0;pino<=7;pino++){
			if((pinsChanged[registrador]&(1<<pino))==(1<<pino)){
				pinsChanged[registrador] &= ~(1<<pino);
				nCallback = (registrador*8) + pino; 
				(*_pCallback[nCallback])();
			}
		}
	}
};
	

PCINT_SL::~PCINT_SL(){}

ISR(PCINT0_vect) {PCINT_SL::callback(0);}
ISR(PCINT1_vect) {PCINT_SL::callback(1);}
ISR(PCINT2_vect) {PCINT_SL::callback(2);}

/******************************************************************************************************/
/*PCI2 setado como 1, possibilita interrup��o nos pinos PCINT16:23, habilitado pelo registrador PCMSK2*/
/*PCI1 setado como 1, possibilita interrup��o nos pinos PCINT8:15, habilitado pelo registrador PCMSK1 */
/*PCI0 setado como 1, possibilita interrup��o nos pinos PCINT0:7, habilitado pelo registrador PCMSK0  */
/******************************************************************************************************/
