#pragma once
#include <stdint.h>

/* PMP permission bits (pmpcfg) */
#define PMP_R    0x01u
#define PMP_W    0x02u
#define PMP_X    0x04u
#define PMP_NAPOT 0x18u   /* Address mode: naturally-aligned power of 2 */
#define PMP_TOR   0x08u   /* Address mode: top of range */

/* RISC-V CSR access macros */
#define write_csr(reg, val) asm volatile("csrw " #reg ", %0" :: "r"(val))
#define read_csr(reg, val)  asm volatile("csrr %0, " #reg  : "=r"(val))

/*
 * NAPOT encoding: pmpaddr = (base >> 2) | ((size/2 - 1) >> 2)
 * For a region [base, base+size), size must be a power of 2 >= 8.
 */
static inline uint32_t pmp_napot(uint32_t base, uint32_t size) {
    return (base >> 2) | ((size / 2 - 1) >> 2);
}

void pmp_setup_isolation(void);
