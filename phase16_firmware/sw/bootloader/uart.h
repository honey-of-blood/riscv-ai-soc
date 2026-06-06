#ifndef UART_H
#define UART_H

#include <stdint.h>

/* Phase 8 UART — APB slave at 0x1000_1xxx (sel=1 in apb_demux.sv)
 *   0x00  TXDATA   [7:0]=byte  [31]=tx_full  (write sends, read is status)
 *   0x04  RXDATA   [7:0]=byte  [31]=rx_valid  (read pops FIFO)
 *   0x08  STATUS   [0]=tx_empty [1]=rx_valid [2]=tx_full [3]=rx_full
 *   0x0C  BAUD     divisor (default 868 = 100 MHz / 115 200 baud)
 */
#define UART_BASE   0x10001000UL
#define UART_TXDATA (*(volatile uint32_t *)(UART_BASE + 0x00))
#define UART_RXDATA (*(volatile uint32_t *)(UART_BASE + 0x04))
#define UART_STATUS (*(volatile uint32_t *)(UART_BASE + 0x08))
#define UART_BAUD   (*(volatile uint32_t *)(UART_BASE + 0x0C))

#define UART_TX_FULL   (1u << 2)
#define UART_RX_VALID  (1u << 1)

void  uart_putc(char c);
char  uart_getc(void);
void  uart_puts(const char *s);

/* Returns received byte on success, -1 on timeout.
 * timeout_ms is approximate (counts busy-loop iterations at 100 MHz). */
int   uart_getc_timeout(uint32_t timeout_ms);

#endif /* UART_H */
