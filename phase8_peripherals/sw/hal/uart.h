#ifndef HAL_UART_H
#define HAL_UART_H

#include "periph_base.h"

// Register offsets (byte addresses from UART_BASE)
// 0x00 TXDATA  [7:0]=byte  [31]=tx_full (read)
// 0x04 RXDATA  [7:0]=byte  [31]=valid; reading pops the FIFO
// 0x08 STATUS  [0]=tx_empty [1]=rx_valid [2]=tx_full [3]=rx_full
// 0x0C BAUD    clock divisor (default 868 = 100 MHz / 115200)

static inline void uart_putc(char c) {
    // wait until TX FIFO is not full (status[2]==0)
    while (MMIO32(UART_BASE + 0x08) & 0x4)
        ;
    MMIO32(UART_BASE + 0x00) = (unsigned char)c;
}

static inline int uart_getc(void) {
    // returns -1 if no byte waiting, else the byte
    unsigned int r = MMIO32(UART_BASE + 0x04);
    if (!(r & 0x80000000u)) return -1;
    return r & 0xFF;
}

static inline void uart_puts(const char *s) {
    while (*s) uart_putc(*s++);
}

static inline void uart_set_baud(unsigned int divisor) {
    MMIO32(UART_BASE + 0x0C) = divisor;
}

#endif
