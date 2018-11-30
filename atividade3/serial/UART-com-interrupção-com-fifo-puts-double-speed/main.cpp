#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
#include <stdlib.h>
#include "UART.h"


int main(void) {

    UART uart(9600, UART::EIGHT_DB, UART::NONE_PAR, UART::TWO_SB, UART::DS_DISABLE);
    sei();

    uint8_t input = 0x41;
    uart.put('a');
    while (1) {
        if (uart.has_data()) {
            input = uart.get();
            uart.puts("Dados: ");
            uart.put(input);
            uart.puts("\n");
        }
    }
}
