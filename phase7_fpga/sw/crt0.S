# crt0.S — minimal C runtime startup for RV32IM SoC
# Responsibilities:
#   1. Set stack pointer
#   2. Copy .data from IROM load address to SRAM run address
#   3. Zero .bss
#   4. Call main()
#   5. Halt on return (infinite loop)

    .section .text.startup
    .global _start
    .type   _start, @function

_start:
    # -----------------------------------------------------------------------
    # 1. Initialise stack pointer
    # -----------------------------------------------------------------------
    la      sp, _stack_top

    # -----------------------------------------------------------------------
    # 2. Copy .data from load address (IROM) to run address (SRAM)
    # -----------------------------------------------------------------------
    la      a0, _data_lma      # source: LMA in IROM
    la      a1, _data_start    # destination: VMA in SRAM
    la      a2, _data_end
    beq     a0, a1, .Lbss_init # skip if LMA == VMA (no copy needed)
.Ldata_copy:
    beq     a1, a2, .Lbss_init
    lw      t0, 0(a0)
    sw      t0, 0(a1)
    addi    a0, a0, 4
    addi    a1, a1, 4
    j       .Ldata_copy

    # -----------------------------------------------------------------------
    # 3. Zero .bss
    # -----------------------------------------------------------------------
.Lbss_init:
    la      a0, _bss_start
    la      a1, _bss_end
.Lbss_zero:
    beq     a0, a1, .Lcall_main
    sw      zero, 0(a0)
    addi    a0, a0, 4
    j       .Lbss_zero

    # -----------------------------------------------------------------------
    # 4. Call main()
    # -----------------------------------------------------------------------
.Lcall_main:
    call    main

    # -----------------------------------------------------------------------
    # 5. Halt (spin forever on return from main)
    # -----------------------------------------------------------------------
.Lhalt:
    j       .Lhalt

    .size _start, . - _start
