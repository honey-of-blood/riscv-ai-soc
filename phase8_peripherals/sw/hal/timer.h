#ifndef HAL_TIMER_H
#define HAL_TIMER_H

#include "periph_base.h"

// Register offsets (byte addresses from TIMER_BASE)
// 0x00 MTIME_LO    mtime[31:0]    read-only
// 0x04 MTIME_HI    mtime[63:32]   read-only
// 0x08 MTIMECMP_LO mtimecmp[31:0]
// 0x0C MTIMECMP_HI mtimecmp[63:32]
// 0x10 CTRL        [0]=enable  [1]=irq_en

static inline unsigned long long timer_read(void) {
    unsigned int lo, hi0, hi1;
    // Read hi twice around lo to guard against 32-bit rollover
    do {
        hi0 = MMIO32(TIMER_BASE + 0x04);
        lo  = MMIO32(TIMER_BASE + 0x00);
        hi1 = MMIO32(TIMER_BASE + 0x04);
    } while (hi0 != hi1);
    return ((unsigned long long)hi0 << 32) | lo;
}

static inline void timer_set_cmp(unsigned long long cmp) {
    // Write HI=max first to avoid spurious compare while writing
    MMIO32(TIMER_BASE + 0x0C) = 0xFFFFFFFFu;
    MMIO32(TIMER_BASE + 0x08) = (unsigned int)(cmp & 0xFFFFFFFFu);
    MMIO32(TIMER_BASE + 0x0C) = (unsigned int)(cmp >> 32);
}

static inline void timer_enable(int irq_en) {
    MMIO32(TIMER_BASE + 0x10) = irq_en ? 0x3 : 0x1;
}

static inline void timer_disable(void) {
    MMIO32(TIMER_BASE + 0x10) = 0x0;
}

// Schedule next tick relative to current time
static inline void timer_set_interval(unsigned long long ticks) {
    timer_set_cmp(timer_read() + ticks);
}

#endif
