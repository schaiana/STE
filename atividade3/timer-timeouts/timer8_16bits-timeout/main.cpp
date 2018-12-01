#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Timer.h"

bool led_state = 0;
void toogle_led() {
	if (led_state) PORTH &= ~(1 << PH5);
	else PORTH |= (1 << PH5);
	led_state = !led_state;
}

int main(void) {
	cli();
    DDRE &= ~(1 << DDE5);
    DDRH |= (1 << DDH5);

	Timer timer = Timer(1000);
	timer.addTimeout(2000, &toogle_led);
	sei();

    while (true) {

    	timer.timeoutManager();
    	_delay_ms(100);

    }
}
