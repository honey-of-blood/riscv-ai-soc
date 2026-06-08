/* uart.h — NS16550-compatible UART driver API */
#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "soc.h"

/* ── Register offsets (register stride = 4 bytes, reg-shift=2) ─────────── */
#define UART_RBR    0x00U   /* Receiver Buffer (R, DLAB=0) */
#define UART_THR    0x00U   /* Transmitter Holding (W, DLAB=0) */
#define UART_IER    0x04U   /* Interrupt Enable */
#define UART_FCR    0x08U   /* FIFO Control (W) */
#define UART_IIR    0x08U   /* Interrupt ID (R) */
#define UART_LCR    0x0CU   /* Line Control */
#define UART_MCR    0x10U   /* Modem Control */
#define UART_LSR    0x14U   /* Line Status */
#define UART_DLL    0x00U   /* Divisor Latch Low  (DLAB=1) */
#define UART_DLH    0x04U   /* Divisor Latch High (DLAB=1) */

/* ── LSR bits ────────────────────────────────────────────────────────────── */
#define UART_LSR_DR   (1u << 0)   /* Data Ready */
#define UART_LSR_THRE (1u << 5)   /* TX Holding Register Empty */
#define UART_LSR_TEMT (1u << 6)   /* TX Empty */

/* ── LCR bits ────────────────────────────────────────────────────────────── */
#define UART_LCR_WLS8 0x03u   /* 8-bit word length */
#define UART_LCR_STOP1 0x00u  /* 1 stop bit */
#define UART_LCR_DLAB  (1u << 7) /* Divisor Latch Access */

/* ── API ─────────────────────────────────────────────────────────────────── */

/**
 * uart_init - configure UART for 8N1 at the given baud rate
 * @baud: desired baud rate (e.g. 115200)
 *
 * Assumes the peripheral clock is PERI_HZ (25 MHz by default).
 * Enables TX/RX FIFOs and clears them.
 */
void uart_init(uint32_t baud);

/**
 * uart_putchar - transmit one byte, blocking
 */
void uart_putchar(char c);

/**
 * uart_puts - transmit a null-terminated string
 */
void uart_puts(const char *s);

/**
 * uart_getchar - receive one byte, blocking
 */
char uart_getchar(void);

/**
 * uart_rx_ready - non-blocking check: returns 1 if a byte is waiting
 */
int uart_rx_ready(void);

/**
 * uart_tx_ready - non-blocking check: returns 1 if TX FIFO has room
 */
int uart_tx_ready(void);

/**
 * uart_printf - formatted print over UART (uses uart_putchar internally)
 * Limited to 256-byte output; no floating-point support.
 */
void uart_printf(const char *fmt, ...);

#endif /* UART_H_ */
