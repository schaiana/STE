#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"

int main(void) {

    UART uart(57600, UART::EIGHT_DB, UART::NONE_PAR, UART::ONE_SB);
    sei();

    uint8_t input = 0xFF;
    while (1) {
        if (uart.has_data()) {
            input = uart.get();
            uart.put(input);
        }
    }
}
