/* RV32IM SoC linker script
 * Memory map:
 *   IROM: 0x0000_0000 — 0x0000_3FFF  (16 KB, instruction ROM)
 *   SRAM: 0x0000_0000 — 0x0000_FFFF  (64 KB, AXI SRAM on crossbar S0)
 *
 * Harvard architecture: .text lives in IROM (imem port), all data in SRAM
 * (dmem port, addressed independently — both start at 0x0).
 *
 * Stack grows down from top of SRAM (0x0000_FFFC).
 */

MEMORY {
    IROM (rx)  : ORIGIN = 0x00000000, LENGTH = 16K
    SRAM (rwx) : ORIGIN = 0x00000000, LENGTH = 64K
}

ENTRY(_start)

SECTIONS {
    /* ------------------------------------------------------------------ */
    /* Code and read-only data → instruction ROM                           */
    /* ------------------------------------------------------------------ */
    .text : {
        KEEP(*(.text.startup))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    } > IROM

    /* ------------------------------------------------------------------ */
    /* Initialised data — load address in IROM, run address in SRAM        */
    /* crt0.S copies .data from LMA to VMA at startup.                    */
    /* ------------------------------------------------------------------ */
    .data : {
        _data_start = .;
        *(.data*)
        . = ALIGN(4);
        _data_end = .;
    } > SRAM AT > IROM

    _data_lma = LOADADDR(.data);

    /* ------------------------------------------------------------------ */
    /* Zero-initialised data → SRAM (crt0.S zeroes at startup)            */
    /* ------------------------------------------------------------------ */
    .bss : {
        _bss_start = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _bss_end = .;
    } > SRAM

    /* Stack top — 4-byte aligned, at the top of SRAM */
    _stack_top = ORIGIN(SRAM) + LENGTH(SRAM) - 4;
}
