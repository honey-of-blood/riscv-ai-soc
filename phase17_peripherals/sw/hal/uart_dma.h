#ifndef UART_DMA_H
#define UART_DMA_H

#include <stdint.h>

#define UART_DMA_BASE   0x1000B000UL

#define UDMA_TXDATA     (*(volatile uint32_t *)(UART_DMA_BASE + 0x00))
#define UDMA_RXDATA     (*(volatile uint32_t *)(UART_DMA_BASE + 0x04))
#define UDMA_STATUS     (*(volatile uint32_t *)(UART_DMA_BASE + 0x08))
#define UDMA_BAUD       (*(volatile uint32_t *)(UART_DMA_BASE + 0x0C))
#define UDMA_DMA_CTRL   (*(volatile uint32_t *)(UART_DMA_BASE + 0x10))
#define UDMA_FIFO_LVL   (*(volatile uint32_t *)(UART_DMA_BASE + 0x14))

#define UDMA_ST_TX_EMPTY      (1u << 0)
#define UDMA_ST_RX_VALID      (1u << 1)
#define UDMA_ST_TX_FULL       (1u << 2)
#define UDMA_ST_RX_FULL       (1u << 3)
#define UDMA_ST_TX_HALF_EMPTY (1u << 4)
#define UDMA_ST_RX_HALF_FULL  (1u << 5)

#define UDMA_DMA_TX_EN (1u << 0)
#define UDMA_DMA_RX_EN (1u << 1)

static inline void udma_init(uint32_t baud_div) {
    UDMA_BAUD = baud_div;
}

static inline void udma_putc(uint8_t c) {
    while (UDMA_STATUS & UDMA_ST_TX_FULL) {}
    UDMA_TXDATA = c;
}

static inline uint8_t udma_getc(void) {
    while (!(UDMA_STATUS & UDMA_ST_RX_VALID)) {}
    return (uint8_t)(UDMA_RXDATA & 0xFF);
}

static inline void udma_dma_enable(int tx_en, int rx_en) {
    UDMA_DMA_CTRL = (tx_en ? UDMA_DMA_TX_EN : 0u) |
                    (rx_en ? UDMA_DMA_RX_EN : 0u);
}

#endif /* UART_DMA_H */
