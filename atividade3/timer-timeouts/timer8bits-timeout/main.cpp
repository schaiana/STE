#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Timer.h"

bool led_state = 0;
void toogle_led() {
	if (led_state) PORTB &= ~(1 << PB7);
	else PORTB |= (1 << PB7);
	led_state = !led_state;
}

int main(void) {
	cli();
    DDRE &= ~(1 << DDE5);
    DDRB |= (1 << DDB7);

	Timer timer = Timer(1000);
	timer.addTimeout(100, &toogle_led);
	sei();

    while (true) {

    	timer.timeoutManager();
    	_delay_ms(100);

    }
}
