#ifndef HAL_PLIC_H
#define HAL_PLIC_H

#include "periph_base.h"

// Register offsets (byte addresses from PLIC_BASE)
// 0x00-0x1F  prio[0..7]  priority per source (2 bits each, one per word)
// 0x20       PENDING     [7:0] interrupt pending bits (read-only)
// 0x24       ENABLE      [7:0] interrupt enable per source
// 0x28       THRESHOLD   [2:0] only irqs with prio > threshold pass
// 0x2C       CLAIM/COMPLETE  R=claim (returns highest-prio ID), W=complete

static inline void plic_set_priority(unsigned int src, unsigned int prio) {
    MMIO32(PLIC_BASE + src * 4) = prio & 0x3;
}

static inline void plic_enable(unsigned char mask) {
    MMIO32(PLIC_BASE + 0x24) = mask;
}

static inline void plic_set_threshold(unsigned int thresh) {
    MMIO32(PLIC_BASE + 0x28) = thresh & 0x7;
}

static inline unsigned int plic_claim(void) {
    return MMIO32(PLIC_BASE + 0x2C) & 0xF;
}

static inline void plic_complete(unsigned int id) {
    MMIO32(PLIC_BASE + 0x2C) = id;
}

static inline unsigned char plic_pending(void) {
    return (unsigned char)(MMIO32(PLIC_BASE + 0x20) & 0xFF);
}

#endif
