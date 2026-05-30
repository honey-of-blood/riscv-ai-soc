#ifndef HAL_CLINT_H
#define HAL_CLINT_H

#include "periph_base.h"

// Register offsets (byte addresses from CLINT_BASE)
// 0x00 MSIP         [0]=machine software interrupt pending
// 0x04 MTIME_LO     mtime[31:0]    read-only (pass-through from timer)
// 0x08 MTIME_HI     mtime[63:32]   read-only
// 0x0C MTIMECMP_LO  mtimecmp[31:0] — write updates timer
// 0x10 MTIMECMP_HI  mtimecmp[63:32]

static inline void clint_set_msip(int val) {
    MMIO32(CLINT_BASE + 0x00) = val & 1;
}

static inline unsigned long long clint_read_mtime(void) {
    unsigned int lo, hi0, hi1;
    do {
        hi0 = MMIO32(CLINT_BASE + 0x08);
        lo  = MMIO32(CLINT_BASE + 0x04);
        hi1 = MMIO32(CLINT_BASE + 0x08);
    } while (hi0 != hi1);
    return ((unsigned long long)hi0 << 32) | lo;
}

static inline void clint_set_timecmp(unsigned long long cmp) {
    MMIO32(CLINT_BASE + 0x10) = 0xFFFFFFFFu;
    MMIO32(CLINT_BASE + 0x0C) = (unsigned int)(cmp & 0xFFFFFFFFu);
    MMIO32(CLINT_BASE + 0x10) = (unsigned int)(cmp >> 32);
}

#endif
