#include "pmp_config.h"

/*
 * Establish PMP isolation for the SoC memory map:
 *
 *   Region 0: ROM  0x00000000–0x0FFFFFFF  (256 MiB)  RX, no write
 *   Region 1: SRAM 0x20000000–0x2003FFFF  (256 KiB)  RWX
 *   Region 2: MMIO 0x40000000–0x4FFFFFFF  (256 MiB)  RW, no execute
 *   Region 3: catch-all — any unmatched access faults (no R/W/X)
 *
 * Uses NAPOT encoding throughout.  Bootloader calls this before
 * jumping to application code so the app runs with privilege checks active.
 */
void pmp_setup_isolation(void) {
    /* Region 0: ROM — 256 MiB at 0x0000_0000, RX */
    write_csr(pmpaddr0, pmp_napot(0x00000000u, 0x10000000u));

    /* Region 1: SRAM — 256 KiB at 0x2000_0000, RWX */
    write_csr(pmpaddr1, pmp_napot(0x20000000u, 0x00040000u));

    /* Region 2: MMIO — 256 MiB at 0x4000_0000, RW (no X) */
    write_csr(pmpaddr2, pmp_napot(0x40000000u, 0x10000000u));

    /* Region 3: catch-all TOR covering 4 GiB — no permissions */
    write_csr(pmpaddr3, 0xFFFFFFFFu);

    /*
     * pmpcfg0 packs cfg[3:0] in bytes [31:0]:
     *   byte 0 → region 0: PMP_R | PMP_X | PMP_NAPOT
     *   byte 1 → region 1: PMP_R | PMP_W | PMP_X | PMP_NAPOT
     *   byte 2 → region 2: PMP_R | PMP_W | PMP_NAPOT
     *   byte 3 → region 3: PMP_TOR (no R/W/X → default deny)
     */
    uint32_t cfg = ((uint32_t)PMP_TOR                         << 24) |
                   ((uint32_t)(PMP_R|PMP_W|PMP_NAPOT)         << 16) |
                   ((uint32_t)(PMP_R|PMP_W|PMP_X|PMP_NAPOT)   <<  8) |
                   ((uint32_t)(PMP_R|PMP_X|PMP_NAPOT)         <<  0);
    write_csr(pmpcfg0, cfg);
}
