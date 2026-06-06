/* Bootloader CRT0 — minimal startup for ROM-resident bootloader.
 * Linked at 0x0000_0000 (4 KB ROM region of instr_bram).
 * Stack top placed at 0x0000_0FFC (top of the 4 KB ROM window that the
 * CPU's data port sees as a separate SRAM alias — depends on SOC wiring). */

    .section .text.startup
    .globl  _start
    .type   _start, @function

_start:
    /* Set stack pointer to top of bootloader data region. */
    la      sp, _stack_top

    /* Zero the BSS section. */
    la      t0, _bss_start
    la      t1, _bss_end
1:  bge     t0, t1, 2f
    sw      zero, 0(t0)
    addi    t0, t0, 4
    j       1b

2:  /* Call main(). */
    call    main

    /* Halt if main returns. */
3:  wfi
    j       3b

    .size _start, . - _start
