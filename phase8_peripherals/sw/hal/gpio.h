#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include "periph_base.h"

// Register offsets (byte addresses from GPIO_BASE)
// 0x00 DATA   R=synchronized inputs  W=output register [15:0]
// 0x04 DIR    [15:0]  1=output  0=input per bit
// 0x08 IEN    [15:0]  interrupt enable per bit (any edge)
// 0x0C ISTAT  [15:0]  interrupt status; write 1 to clear (W1C)

static inline void gpio_set_dir(unsigned short dir) {
    MMIO32(GPIO_BASE + 0x04) = dir;
}

static inline void gpio_write(unsigned short val) {
    MMIO32(GPIO_BASE + 0x00) = val;
}

static inline unsigned short gpio_read(void) {
    return (unsigned short)(MMIO32(GPIO_BASE + 0x00) & 0xFFFF);
}

static inline void gpio_irq_enable(unsigned short mask) {
    MMIO32(GPIO_BASE + 0x08) = mask;
}

static inline unsigned short gpio_irq_status(void) {
    return (unsigned short)(MMIO32(GPIO_BASE + 0x0C) & 0xFFFF);
}

static inline void gpio_irq_clear(unsigned short mask) {
    MMIO32(GPIO_BASE + 0x0C) = mask;
}

#endif
