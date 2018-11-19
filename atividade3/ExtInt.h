/*
 * ExtInt.h
 *
 *  Author: Layssa Pacheco e Schaiana Sonaglio
 */

//INTERRUP��O EXTERNA

#ifndef EXTINT_H_
#define EXTINT_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

typedef void (*CALLBACK_t)(void); //define CALLBACK_t como um ponteiro para um m�todo que n�o tem nenhum par�metro e n�o retorna nada

class EXTINT {
	public:
		enum INT_ID_t {
			INT_0 = 0,
			INT_1 = 1,
			INT_2 = 2,
			INT_3 = 3,
			INT_4 = 4,
			INT_5 = 5,
			INT_6 = 6,
			INT_7 = 7
		};

		enum ISC_t {
			LOW = 0,
			ANY = 1,
			FALLING = 2,
			RISING = 3
		};

		ExtInt(INT_ID_t id, ISC_t cfg, CALLBACK_t pCallback);
		~ExtInt();
		void enable();
		void disable();
		void callback();

		ExtInt _ExtInt_singletons[8];

		private:
			uint8_t _id;
			static CALLBACK_t _pCallback[8];
};
/* namespace EXTINT */
#endif /* EXTINT_H_ */
