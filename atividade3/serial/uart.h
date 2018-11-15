#ifndef UART_H_
#define UART_H_

#include <stdint.h>

class UART{
	public:
    enum DataBits_t {
        FIVE_DB = 0,
        SIX_DB = 1,
        SEVEN_DB = 2,
        EIGHT_DB = 3
    };

    enum Parity_t {
        NONE_PAR = 0,
        EVEN_PAR = 2,
        ODD_PAR = 3
    };

    enum StopBit_t {
        ONE_SB = 0,
        TWO_SB = 1
    };



    UART(uint16_t baud, DataBits_t db, Parity_t par, StopBit_t sb, uint8_t double_speed=0);
    ~UART();
    void put(uint8_t data);
    uint8_t get();


};

#endif /* UART_H_ */
