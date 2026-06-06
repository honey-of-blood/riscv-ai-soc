/* Application linker script.
 *
 * Apps are uploaded by the bootloader and executed from instruction BRAM
 * starting at 0x0000_1000 (the bootloader occupies 0x0000_0000–0x0000_0FFF).
 *
 * Data, heap, and stack live in the 64 KB AXI SRAM (data bus, same 0x0 base).
 * Heap occupies the region between BSS end and the stack guard.
 *
 * Stack grows downward from 0x0000_FFFC (top of SRAM minus 4).
 * Guard: 1 KB gap between heap ceiling and stack base.
 */

MEMORY {
    IRAM (rx)  : ORIGIN = 0x00001000, LENGTH = 60K   /* app code region in BRAM  */
    DRAM (rwx) : ORIGIN = 0x00001000, LENGTH = 60K   /* app data region in SRAM  */
}

ENTRY(_start)

SECTIONS {
    .text : {
        KEEP(*(.text.startup))
        *(.text*)
        *(.rodata*)
        . = ALIGN(4);
        _text_end = .;
    } > IRAM

    .data : {
        _data_start = .;
        *(.data*)
        . = ALIGN(4);
        _data_end = .;
    } > DRAM AT > IRAM

    _data_lma = LOADADDR(.data);

    .bss : {
        _bss_start = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _bss_end = .;
    } > DRAM

    /* Heap: from BSS end to 1 KB below stack top */
    _heap_start = _bss_end;
    _heap_end   = ORIGIN(DRAM) + LENGTH(DRAM) - 1024 - 4;

    /* Stack top */
    _stack_top  = ORIGIN(DRAM) + LENGTH(DRAM) - 4;
}
