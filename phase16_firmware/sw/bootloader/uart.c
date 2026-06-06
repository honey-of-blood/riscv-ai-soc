#include "uart.h"

/* Rough iteration count for 1 ms at 100 MHz (reading STATUS is ~4 cycles). */
#define ITERS_PER_MS  25000UL

void uart_putc(char c) {
    while (UART_STATUS & UART_TX_FULL)
        ;
    UART_TXDATA = (uint8_t)c;
}

char uart_getc(void) {
    while (!(UART_STATUS & UART_RX_VALID))
        ;
    return (char)(UART_RXDATA & 0xFF);
}

void uart_puts(const char *s) {
    while (*s)
        uart_putc(*s++);
}

int uart_getc_timeout(uint32_t timeout_ms) {
    uint32_t limit = timeout_ms * ITERS_PER_MS;
    for (uint32_t i = 0; i < limit; i++) {
        if (UART_STATUS & UART_RX_VALID)
            return (uint8_t)(UART_RXDATA & 0xFF);
    }
    return -1;
}
