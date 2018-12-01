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

//namespace EI_PCINT{
	
	typedef void (*CALLBACK_t)();

	class PCINT_SL {
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
				PCINT_8 = 8,
				PCINT_9 = 9,
				PCINT_10 = 10,
				PCINT_11 = 11,
				PCINT_12 = 12,
				PCINT_13 = 13,
				PCINT_14 = 14,
				PCINT_15 = 15,
				//PCMSK2
				PCINT_16 = 16,
				PCINT_17 = 17,
				PCINT_18 = 18,
				PCINT_19 = 19,
				PCINT_20 = 20,
				PCINT_21 = 21,
				PCINT_22 = 22,
				PCINT_23 = 23
			};

		PCINT_SL();
		~PCINT_SL();
		void enable(uint8_t PCINTx, CALLBACK_t pCallback);
		void disable(uint8_t PCINTx);
		static void callback(uint8_t PCINTx);

		static uint8_t portHist[3];
		//PCINT_ID_t _id;
		static CALLBACK_t _pCallback[24];
	};
//};/* namespace EI_PCINT */
#endif /* EI_PCINT_H_ */
