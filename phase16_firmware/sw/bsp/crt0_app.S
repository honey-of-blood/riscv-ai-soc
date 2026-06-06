/* Application CRT0.
 * Sets up sp, copies .data from ROM LMA to SRAM VMA, zeroes BSS, calls main. */

    .section .text.startup
    .globl  _start
    .type   _start, @function

_start:
    la      sp, _stack_top

    /* Copy initialised data from LMA (ROM) to VMA (SRAM). */
    la      t0, _data_lma
    la      t1, _data_start
    la      t2, _data_end
1:  bge     t1, t2, 2f
    lw      t3, 0(t0)
    sw      t3, 0(t1)
    addi    t0, t0, 4
    addi    t1, t1, 4
    j       1b

2:  /* Zero BSS. */
    la      t0, _bss_start
    la      t1, _bss_end
3:  bge     t0, t1, 4f
    sw      zero, 0(t0)
    addi    t0, t0, 4
    j       3b

4:  call    main

    /* main returned — halt. */
5:  wfi
    j       5b

    .size _start, . - _start
