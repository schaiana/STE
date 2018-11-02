#include "avr/io.h"
#include "avr/interrupt.h"
#include <util/delay.h>

int interrupt_source = 0;        //you can select two interrupt sources: 0 (pin 2) and 1 (pin 3)
bool led_state = false;               //state = 0, led is off; state = 1, led is on
bool button_state = false;
long debounce_limit = 16000;        //limit time in ms between interrupts to debounce the electric signal
long counter_last_accepted_interrupt = 0;
long counter=0;

void led_value(bool led_state);
bool debounce();

int main(void) {
	//pino 9 (PH6) led - output
	DDRH |= (1 << DD6);

	EICRB |= (1<<0);
	//habilita o interrupt INT4
	EIMSK |= (1 << 4);

	sei();
    while(1) {
        led_value(led_state);
        counter++;
        if(counter>2000000000){
        	counter = 0;
        	counter_last_accepted_interrupt = 0;
        }

    }
}


void led_value(bool led_state){
	if(led_state== true){
		//liga led pino 9 (PH6)
		PORTH |= (1 << PIN6);
	} else {
		//desliga led pino 9 (PH6)
		PORTH &= ~(1 << PIN6);
	}
}

ISR(INT4_vect){
	if (debounce()){
		if(!(PINE & (1 << PIN4))){// se o botão ainda estiver pressionado
			led_state = true;
		} else {
			led_state = false;
		}
	}
	counter++;
}

bool debounce(){
    //debounce is the function responsible for stabilizing the interruption requests
    if(counter - counter_last_accepted_interrupt>debounce_limit) {
    	counter_last_accepted_interrupt = counter;
        return true;
    }
    else
        return false;
}
