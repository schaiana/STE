/*
 * EXTINT.h
 *
 *  Author: Layssa Pacheco e Schaiana Sonaglio
 */

//INTERRUP��O EXTERNA

#ifndef EXTINT_H_
#define EXTINT_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//namespace EXTINT{

	typedef void (*CALLBACK_t)(void);

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

			EXTINT(INT_ID_t id, ISC_t cfg, CALLBACK_t pCallback);
			~EXTINT();
			void enable();
			void disable();
			void callback();

			static EXTINT * _EXTINT_singletons[8];

			private:
				uint8_t _id;
				CALLBACK_t _pCallback;
	};
//};/* namespace EXTINT */
#endif /* EXTINT_H_ */
