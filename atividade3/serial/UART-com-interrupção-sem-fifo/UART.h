
#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "Singleton.h"

class UART : public Singleton<UART> {
public:
    enum DataBits_t {
        FIVE_DB = 0,
        SIX_DB = 2,
        SEVEN_DB = 4,
        EIGHT_DB = 6
    };

    enum Parity_t {
        NONE_PAR = 0,
        EVEN_PAR = 32,
        ODD_PAR = 48
    };

    enum StopBit_t {
        ONE_SB = 0,
        TWO_SB = 8
    };

    UART(uint16_t baud, DataBits_t db, Parity_t par, StopBit_t sb);
    ~UART();
    void put(uint8_t data);
    uint8_t get();
    bool has_data();

    // Interrupt handlers
    static void rxc_isr_handler();
    static void udre_isr_handler();

private:
    bool _new_data;
    uint8_t _rx_buffer;
    uint8_t _tx_buffer;
};

#endif /* UART_H_ */
