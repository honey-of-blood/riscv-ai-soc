/* uart.c — NS16550 UART driver implementation */
#include <stdarg.h>
#include <stdint.h>
#include "uart.h"
#include "soc.h"

#define UART_REG(off)  REG32(UART_BASE, (off))

void uart_init(uint32_t baud) {
    /* Set DLAB to access divisor latches */
    UART_REG(UART_LCR) = UART_LCR_DLAB;
    uint32_t div = PERI_HZ / (16u * baud);
    UART_REG(UART_DLL) = div & 0xFF;
    UART_REG(UART_DLH) = (div >> 8) & 0xFF;
    /* 8N1, clear DLAB */
    UART_REG(UART_LCR) = UART_LCR_WLS8;
    /* Enable and reset FIFOs, trigger level = 1 byte */
    UART_REG(UART_FCR) = 0x07u;
    /* Disable interrupts (polled mode by default) */
    UART_REG(UART_IER) = 0x00u;
}

int uart_tx_ready(void) {
    return (UART_REG(UART_LSR) & UART_LSR_THRE) != 0;
}

int uart_rx_ready(void) {
    return (UART_REG(UART_LSR) & UART_LSR_DR) != 0;
}

void uart_putchar(char c) {
    while (!uart_tx_ready()) {}
    if (c == '\n') uart_putchar('\r');
    UART_REG(UART_THR) = (uint32_t)c;
}

void uart_puts(const char *s) {
    while (*s) uart_putchar(*s++);
}

char uart_getchar(void) {
    while (!uart_rx_ready()) {}
    return (char)(UART_REG(UART_RBR) & 0xFF);
}

/* Minimal formatted print — supports %d %u %x %s %c %% */
void uart_printf(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    char buf[20];
    while (*fmt) {
        if (*fmt != '%') { uart_putchar(*fmt++); continue; }
        fmt++;
        switch (*fmt++) {
        case 'd': {
            int v = va_arg(ap, int);
            if (v < 0) { uart_putchar('-'); v = -v; }
            int i = 0;
            if (v == 0) { buf[i++] = '0'; }
            else { while (v) { buf[i++] = '0' + v % 10; v /= 10; } }
            while (i--) uart_putchar(buf[i]);
            break;
        }
        case 'u': {
            unsigned v = va_arg(ap, unsigned);
            int i = 0;
            if (v == 0) { buf[i++] = '0'; }
            else { while (v) { buf[i++] = '0' + v % 10; v /= 10; } }
            while (i--) uart_putchar(buf[i]);
            break;
        }
        case 'x': case 'X': {
            unsigned v = va_arg(ap, unsigned);
            const char *hex = "0123456789abcdef";
            int i = 0;
            if (v == 0) { buf[i++] = '0'; }
            else { while (v) { buf[i++] = hex[v & 0xF]; v >>= 4; } }
            while (i--) uart_putchar(buf[i]);
            break;
        }
        case 's': { uart_puts(va_arg(ap, const char *)); break; }
        case 'c': { uart_putchar((char)va_arg(ap, int)); break; }
        case '%': { uart_putchar('%'); break; }
        default:  { uart_putchar('?'); break; }
        }
    }
    va_end(ap);
}
