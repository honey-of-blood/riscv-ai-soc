/* Bootloader linker script.
 *
 * Memory layout (Harvard SoC):
 *   ROM  (instruction bus) — 0x0000_0000, 4 KB  — bootloader code + rodata
 *   SRAM (data bus)        — 0x0000_0000, 4 KB  — bootloader stack + BSS
 *     (first 4 KB of the 64 KB AXI SRAM alias)
 *
 * The bootloader receives an ELF image over UART and writes it to the
 * instruction BRAM at offset 0x1000 via AXI slave port (0x2000_xxxx).
 * The CPU then jumps to 0x0000_1000 to execute the uploaded app.
 */

MEMORY {
    ROM  (rx)  : ORIGIN = 0x00000000, LENGTH = 4K
    SRAM (rwx) : ORIGIN = 0x00000000, LENGTH = 4K
}

ENTRY(_start)

SECTIONS {
    .text : {
        KEEP(*(.text.startup))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
    } > ROM

    .data : {
        _data_start = .;
        *(.data*)
        . = ALIGN(4);
        _data_end = .;
    } > SRAM AT > ROM

    _data_lma = LOADADDR(.data);

    .bss : {
        _bss_start = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _bss_end = .;
    } > SRAM

    _stack_top = ORIGIN(SRAM) + LENGTH(SRAM) - 4;
}
