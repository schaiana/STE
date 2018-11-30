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

    // Set output port
    DDRH |= (1 << DDH5);				// Set 1 to DDRH5 (PH5)

	Timer timer = Timer(1000, Timer::timer_16bits);
	timer.addTimeout(2000, &toogle_led);

	sei();

    while (true) {
    	timer.timeoutManager();
    }
}
