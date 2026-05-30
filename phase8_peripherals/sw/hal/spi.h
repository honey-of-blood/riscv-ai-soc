#ifndef HAL_SPI_H
#define HAL_SPI_H

#include "periph_base.h"

// Register offsets (byte addresses from SPI_BASE)
// 0x00 TXDATA/RXDATA  W=byte to send; R=[7:0]=rx_data after transfer
// 0x04 CTRL           R/W [0]=busy [1]=cpol [2]=cpha [9:3]=clk_div
// 0x08 CS             [15:0] chip-select bitmap (0=assert, 1=deassert per bit)

static inline void spi_configure(unsigned char clk_div, int cpol, int cpha) {
    MMIO32(SPI_BASE + 0x04) = ((unsigned int)clk_div << 3)
                            | ((cpol & 1) << 1)
                            | ((cpha & 1) << 2);
}

static inline void spi_cs_assert(void) {
    MMIO32(SPI_BASE + 0x08) = 0x0000;
}

static inline void spi_cs_deassert(void) {
    MMIO32(SPI_BASE + 0x08) = 0xFFFF;
}

static inline unsigned char spi_transfer(unsigned char byte) {
    // Wait for any prior transfer to finish
    while (MMIO32(SPI_BASE + 0x04) & 0x1)
        ;
    // Writing TXDATA starts the transfer
    MMIO32(SPI_BASE + 0x00) = byte;
    // Wait for completion
    while (MMIO32(SPI_BASE + 0x04) & 0x1)
        ;
    return (unsigned char)(MMIO32(SPI_BASE + 0x00) & 0xFF);
}

#endif
