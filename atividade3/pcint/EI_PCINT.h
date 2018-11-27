/*
 * ExtInt.h
 *
 *  Author: Layssa Pacheco e Schaiana Sonaglio
 */

#ifndef EI_PCINT_H_
#define EI_PCINT_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

typedef void (*CALLBACK_t)(void); //define CALLBACK_t como um ponteiro para um m�todo que n�o tem nenhum par�metro e n�o retorna nada

class EI_PCINT {
	public:
		enum PCINT_ID_t {
			//PCMSK0
			PCINT_0 = 0,
			PCINT_1 = 1,
			PCINT_2 = 2,
			PCINT_3 = 3,
			PCINT_4 = 4,
			PCINT_5 = 5,
			PCINT_6 = 6,
			PCINT_7 = 7,
			//PCMSK1
			PCINT_8 = 0,
			PCINT_9 = 1,
			PCINT_10 = 2,
			PCINT_11 = 3,
			PCINT_12 = 4,
			PCINT_13 = 5,
			PCINT_14 = 6,
			PCINT_15 = 7,
			//PCMSK2
			PCINT_16 = 0,
			PCINT_17 = 1,
			PCINT_18 = 2,
			PCINT_19 = 3,
			PCINT_20 = 4,
			PCINT_21 = 5,
			PCINT_22 = 6,
			PCINT_23 = 7
		};

		EI_PCINT(PCINT_ID_t id, CALLBACK_t pCallback);
		~EI_PCINT();
		void enable();
		void disable();
		void callback();

		//EI_PCINT _ExtInt_singletons[8];

		private:
			uint8_t _id;
			static CALLBACK_t _pCallback[8];
};
/* namespace EI_PCINT */
#endif /* EI_PCINT_H_ */
