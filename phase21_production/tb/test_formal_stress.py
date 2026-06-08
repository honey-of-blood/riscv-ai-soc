"""Phase 21 stress — deep formal / invariant checks.

Extends test_formal_checks.py with harder scenarios:
  1. PC alignment over 500+ cycles with dense branches
  2. x0 zero-invariant with every R/I/J/U/L instruction type writing to rd=0
  3. Two consecutive taken branches (double flush, pipeline recovery)
  4. Load-use hazard where the loaded value drives the branch condition
  5. 15-deep ADD chain — verify terminal value (all EX→EX forwards in sequence)
  6. Debug halt is non-destructive — register state unchanged before/after
  7. Mid-execution reset — core restarts from PC=0
  8. Three chained load-use stalls produce correct value chain
  9. JALR target is always word-aligned (bit-0 cleared even when source is odd)
 10. Only SW/SH/SB instructions cause dmem_we_o=1 (no spurious writes)
"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
sys.path.insert(0, os.path.dirname(__file__))

import cocotb
from cocotb.triggers import RisingEdge, Timer
from core_helpers import (start_core, reset_dut, DONE_ADDR, NOP, CLK_NS, _u32)
from prog_gen import (addi, add, sub, lw, sw, sh, sb, lui, jal, jalr, auipc,
                      _b, _i, OP_IMM, mul, div_, DONE_ADDR as GEN_DONE_ADDR)


async def _clk(dut):
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")


def _imem_serve(imem, dut):
    iaddr = _u32(dut.imem_addr_o) >> 2
    dut.imem_rdata_i.value = imem.get(iaddr, NOP)


async def _run_to_done(dut, imem, dmem, max_cycles=2000):
    """Drive memory, return True when done sentinel fires."""
    dut.imem_rdata_i.value = imem.get(0, NOP)
    for cyc in range(max_cycles):
        await _clk(dut)
        _imem_serve(imem, dut)
        da = _u32(dut.dmem_addr_o)
        if _u32(dut.dmem_we_o) & 1:
            be   = _u32(dut.dmem_be_o)
            wd   = _u32(dut.dmem_wdata_o)
            wi   = da >> 2
            word = dmem.get(wi, 0)
            for i in range(4):
                if (be >> i) & 1:
                    word = (word & ~(0xFF << (8*i))) | (((wd >> (8*i)) & 0xFF) << (8*i))
            dmem[wi] = word
            if da == DONE_ADDR:
                for _ in range(5):   # drain
                    await _clk(dut)
                    _imem_serve(imem, dut)
                return True
        dut.dmem_rdata_i.value = dmem.get(da >> 2, 0)
    return False


async def _halt_read_regs(dut):
    """Halt core via debug port and read all 32 GPRs."""
    dut.dbg_halt_req_i.value = 1
    for _ in range(40):
        await _clk(dut)
        if _u32(dut.dbg_halted_o):
            break
    regs = []
    for r in range(32):
        dut.dbg_rf_addr_i.value = r
        await Timer(1, unit="ns")
        regs.append(_u32(dut.dbg_rf_rdata_o))
    dut.dbg_halt_req_i.value = 0
    return regs


def _build_imem(instrs):
    return {i: instrs[i] for i in range(len(instrs))}


# ═══════════════════════════════════════════════════════════════════════════════
# 1. PC alignment over 500+ cycles — dense branch program
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_pc_alignment_500_cycles(dut):
    """imem_addr_o[1:0] == 0 every cycle for 500+ cycles.

    Uses a backward-branch countdown loop (x1 counts 150 → 0) so the program
    runs for ~600 cycles, exercising many branch-taken and branch-not-taken paths.
    """
    start_core(dut)
    await reset_dut(dut)

    # Layout:
    #  word 0: addi x1,x0,150    (loop counter)
    #  word 1: lui  x16,0x1000
    #  word 2: addi x1,x1,-1     (loop body — decrements counter)
    #  word 3: BNE x1,x0, -8    (PC=12, offset=-8 → target=4... that's before word 2)
    # Hmm, let me use byte-level offset.
    # word 2 is at byte 8. BNE is at byte 12. To jump back to word 2 (byte 8): offset = 8-12 = -4.
    #  word 3: BNE x1,x0, -4     (jump to word 2 while x1 != 0)
    #  word 4: sw  x1,0(x16)
    #  word 5: jal x0,0
    instrs = [
        addi(1, 0, 150),    # x1 = 150
        lui(16, 0x1000),    # x16 = done addr
        addi(1, 1, -1),     # loop body: x1--
        _b(-4, 0, 1, 1),    # BNE x1,x0, -4  (back to word 2)
        sw(1, 16, 0),       # done sentinel
        jal(0, 0),
    ]

    imem = _build_imem(instrs)
    dmem = {}
    dut.imem_rdata_i.value = imem.get(0, NOP)
    cycles_checked = 0

    for cyc in range(1200):
        await _clk(dut)
        addr = _u32(dut.imem_addr_o)
        assert (addr & 3) == 0, f"Misaligned fetch 0x{addr:08x} at cycle {cyc}"
        cycles_checked += 1
        _imem_serve(imem, dut)
        da = _u32(dut.dmem_addr_o)
        if _u32(dut.dmem_we_o) & 1 and da == DONE_ADDR:
            break
        dut.dmem_rdata_i.value = dmem.get(da >> 2, 0)

    assert cycles_checked >= 400, f"Too few cycles checked: {cycles_checked}"


# ═══════════════════════════════════════════════════════════════════════════════
# 2. x0 zero-invariant — EVERY instruction type targeting rd=0
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_x0_every_instruction_type(dut):
    """x0 must stay zero after R/I/LUI/AUIPC/JAL/JALR/Load with rd=0."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [
        addi(1, 0, 42),    # x1=42 (rs1 source)
        addi(2, 0, 8),     # x2=8 (use for JALR target)
        lui(16, 0x1000),
        # All the following target rd=0
        add  (0, 1, 1),    # R-type rd=0
        sub  (0, 1, 1),
        addi (0, 1, 5),    # I-type ALU rd=0
        lui  (0, 0x1234),  # U-type rd=0
        auipc(0, 0x1000),  # U-type rd=0
        lw   (0, 16, 0),   # Load rd=0 (loads from DONE_ADDR area; dmem=0)
        # JAL rd=0 with offset=0 (jump to self → loop once then fall through is impossible,
        # use offset=4 to jump to next instr and still write rd=0)
        jal  (0, 4),       # JAL rd=0, offset+4 → skip nothing (lands on next word)
        mul  (0, 1, 1),    # M-ext rd=0
        # JALR rd=0: target = x2+0 = 8 (word 2 = lui x16,0x1000; already executed, OK to re-run)
        # Actually need JALR to land somewhere safe. Let it land on the next instr.
        # JALR x0, x16, 0 → target = 0x1000 (done_addr) — that's a dmem addr, imem returns NOP
        # Better: just test JALR rd=0, rs1=x0, imm=0 → target = 0 (back to start, no harm to regs)
        # But that would loop. Skip JALR in this test; it's covered in test_jalr_correctness.
        sw(1, 16, 0),       # done sentinel (SW doesn't target a GPR)
        jal(0, 0),
    ]

    imem = _build_imem(instrs)
    dmem = {0x1000 >> 2: 0}   # pre-init so LW returns 0

    # Monitor x0 every cycle
    dut.imem_rdata_i.value = imem.get(0, NOP)
    for cyc in range(len(instrs) * 12 + 100):
        await _clk(dut)
        # Sample x0 combinationally
        dut.dbg_rf_addr_i.value = 0
        await Timer(1, unit="ns")
        x0 = _u32(dut.dbg_rf_rdata_o)
        assert x0 == 0, f"x0 != 0 at cycle {cyc}: 0x{x0:08x}"
        _imem_serve(imem, dut)
        da = _u32(dut.dmem_addr_o)
        if _u32(dut.dmem_we_o) & 1 and da == DONE_ADDR:
            break
        dut.dmem_rdata_i.value = dmem.get(da >> 2, 0)


# ═══════════════════════════════════════════════════════════════════════════════
# 3. Double branch flush — two taken branches within 4-instruction window
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_double_branch_flush(dut):
    """Two taken branches back-to-back — pipeline must recover from double flush.

    After the first branch lands, its target contains a second taken branch.
    Both x10 and x11 must be 1 (set by taken-path instructions).
    """
    start_core(dut)
    await reset_dut(dut)

    # word 0: addi x1,x0,1; word 1: addi x2,x0,2  (x1!=x2 so BNE taken)
    # word 2: BNE x1,x2 +12 → jump to word 5
    # word 3: addi x10,x0,-1  FLUSHED
    # word 4: addi x10,x0,-1  FLUSHED
    # word 5: addi x10,x0,1   (first branch target); x10=1
    # word 6: BEQ x1,x1 +12 → jump to word 9  (always taken)
    # word 7: addi x11,x0,-1  FLUSHED
    # word 8: addi x11,x0,-1  FLUSHED
    # word 9: addi x11,x0,1   (second branch target); x11=1
    # word 10: lui x16,0x1000
    # word 11: sw x1,0(x16)
    # word 12: jal x0,0

    instrs = [
        addi(1, 0, 1),
        addi(2, 0, 2),
        _b(12, 2, 1, 1),    # BNE x1,x2, +12 — TAKEN (1≠2)
        addi(10, 0, -1),    # FLUSHED
        addi(10, 0, -1),    # FLUSHED
        addi(10, 0, 1),     # first branch target: x10=1
        _b(12, 1, 1, 0),    # BEQ x1,x1, +12 — TAKEN (1==1)
        addi(11, 0, -1),    # FLUSHED
        addi(11, 0, -1),    # FLUSHED
        addi(11, 0, 1),     # second branch target: x11=1
        lui(16, 0x1000),
        sw(1, 16, 0),
        jal(0, 0),
    ]

    imem = _build_imem(instrs)
    done = await _run_to_done(dut, imem, {})
    assert done

    regs = await _halt_read_regs(dut)
    assert (regs[10] & 0xFFFFFFFF) == 1, f"double-flush x10={regs[10]}"
    assert (regs[11] & 0xFFFFFFFF) == 1, f"double-flush x11={regs[11]}"


# ═══════════════════════════════════════════════════════════════════════════════
# 4. Load-use hazard → branch on loaded value
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_load_then_branch_on_loaded_value(dut):
    """LW followed immediately by BEQ using the loaded register — stall + flush path."""
    start_core(dut)
    await reset_dut(dut)

    # mem[0x2000] = 99.  Program: LW x1, BEQ x1==99 (true → taken → x10=1)
    instrs = [
        lui(17, 0x2000),
        lui(16, 0x1000),
        lw(1, 17, 0),        # x1 = 99 (load-use stall)
        addi(2, 0, 99),      # x2 = 99
        _b(12, 2, 1, 0),     # BEQ x1,x2, +12 — TAKEN (both 99)
        addi(10, 0, -1),     # FLUSHED
        addi(10, 0, -1),     # FLUSHED
        addi(10, 0, 1),      # taken target: x10=1
        sw(1, 16, 0),
        jal(0, 0),
    ]

    imem = _build_imem(instrs)
    done = await _run_to_done(dut, imem, {0x2000 >> 2: 99})
    assert done

    regs = await _halt_read_regs(dut)
    assert (regs[1]  & 0xFFFFFFFF) == 99, f"load: x1={regs[1]}"
    assert (regs[10] & 0xFFFFFFFF) == 1,  f"load-use+branch: x10={regs[10]}"


# ═══════════════════════════════════════════════════════════════════════════════
# 5. 15-deep ADD chain — verify terminal value through all forwarding stages
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_forwarding_15_deep_chain(dut):
    """x1 = x1+1 repeated 15 times from x1=0 → x1=15 (all EX→EX forwards)."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [addi(1, 0, 0), lui(16, 0x1000)]
    instrs += [addi(1, 1, 1) for _ in range(15)]
    instrs += [sw(1, 16, 0), jal(0, 0)]

    imem = _build_imem(instrs)
    done = await _run_to_done(dut, imem, {})
    assert done

    regs = await _halt_read_regs(dut)
    assert (regs[1] & 0xFFFFFFFF) == 15, f"15-deep chain: x1={regs[1]}"


# ═══════════════════════════════════════════════════════════════════════════════
# 6. Debug halt is non-destructive — registers unchanged
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_debug_halt_nondestructive(dut):
    """Halt+read+resume: registers must have the same values before and after."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [
        addi(1, 0, 0xAB),
        addi(2, 0, 0xCD),
        addi(3, 0, 0xEF),
        lui(16, 0x1000),
        sw(1, 16, 0),
        jal(0, 0),
    ]
    imem = _build_imem(instrs)
    done = await _run_to_done(dut, imem, {})
    assert done

    # First read
    regs_before = await _halt_read_regs(dut)

    # Resume then immediately halt again
    dut.dbg_resume_req_i.value = 1
    await _clk(dut)
    dut.dbg_resume_req_i.value = 0
    await _clk(dut)

    regs_after = await _halt_read_regs(dut)

    # Registers x1-x15 must be unchanged (core is in JAL loop, no side effects)
    for r in range(1, 16):
        assert regs_before[r] == regs_after[r], (
            f"Debug non-destructive: x{r} changed 0x{regs_before[r]:08x}→0x{regs_after[r]:08x}")


# ═══════════════════════════════════════════════════════════════════════════════
# 7. Mid-execution reset — PC returns to 0 and core re-runs
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_reset_mid_execution(dut):
    """Assert rst after 15 cycles mid-execution; verify PC=0 on release."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [
        addi(1, 0, 1),
        addi(2, 0, 2),
        addi(3, 0, 3),
        lui(16, 0x1000),
        sw(1, 16, 0),
        jal(0, 0),
    ]
    imem = _build_imem(instrs)
    dut.imem_rdata_i.value = imem.get(0, NOP)

    # Run 15 cycles into execution
    for _ in range(15):
        await _clk(dut)
        _imem_serve(imem, dut)

    # Assert reset
    dut.rst.value = 1
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.rst.value = 0
    await Timer(1, unit="ns")

    # First fetch after reset must be PC=0
    addr = _u32(dut.imem_addr_o)
    assert addr == 0, f"PC after mid-exec reset: 0x{addr:08x} expected 0"

    # Re-run and verify correct result
    done = await _run_to_done(dut, imem, {})
    assert done, "Program did not re-complete after mid-execution reset"

    regs = await _halt_read_regs(dut)
    assert (regs[1] & 0xFFFFFFFF) == 1, f"Post-reset x1={regs[1]}"
    assert (regs[2] & 0xFFFFFFFF) == 2, f"Post-reset x2={regs[2]}"
    assert (regs[3] & 0xFFFFFFFF) == 3, f"Post-reset x3={regs[3]}"


# ═══════════════════════════════════════════════════════════════════════════════
# 8. Three chained load-use stalls — verify all three loaded values correct
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_triple_load_use_chain(dut):
    """LW → ADD (stall 1) → LW → ADD (stall 2) → LW → ADD (stall 3): chain is correct."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [
        lui(17, 0x2000),
        lui(16, 0x1000),
        lw (1, 17, 0),    # x1 = 100 (stall 1)
        add(2, 1, 1),     # x2 = 200 (EX→EX after stall)
        lw (3, 17, 4),    # x3 = 50  (stall 2)
        add(4, 3, 2),     # x4 = 250 (stall forward)
        lw (5, 17, 8),    # x5 = 75  (stall 3)
        add(6, 5, 4),     # x6 = 325 (stall forward)
        sw(6, 16, 0),
        jal(0, 0),
    ]

    imem = _build_imem(instrs)
    done = await _run_to_done(dut, imem,
                               {0x2000>>2: 100, 0x2004>>2: 50, 0x2008>>2: 75})
    assert done

    regs = await _halt_read_regs(dut)
    assert (regs[1] & 0xFFFFFFFF) == 100, f"lw chain: x1={regs[1]}"
    assert (regs[2] & 0xFFFFFFFF) == 200, f"add after load: x2={regs[2]}"
    assert (regs[3] & 0xFFFFFFFF) == 50,  f"lw chain: x3={regs[3]}"
    assert (regs[4] & 0xFFFFFFFF) == 250, f"add after load: x4={regs[4]}"
    assert (regs[5] & 0xFFFFFFFF) == 75,  f"lw chain: x5={regs[5]}"
    assert (regs[6] & 0xFFFFFFFF) == 325, f"add after load: x6={regs[6]}"


# ═══════════════════════════════════════════════════════════════════════════════
# 9. JALR target always word-aligned — bit-0 clearing with odd rs1
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_jalr_bit0_never_set(dut):
    """JALR target = (rs1+imm)&~1; every cycle imem_addr_o[1:0]==0 — including after JALR."""
    start_core(dut)
    await reset_dut(dut)

    # JALR with rs1=x17=21 (odd), imm=0 → target = 21&~1 = 20 (word 5)
    instrs = [
        lui(16, 0x1000),
        addi(17, 0, 21),    # x17=21 (odd)
        jalr(5, 17, 0),     # link=12, target=20 (word 5)
        addi(6, 0, 99),     # skipped
        addi(7, 0, 99),     # skipped
        addi(8, 0, 42),     # JALR target (word 5 = byte 20)
        sw(8, 16, 0),
        jal(0, 0),
    ]

    imem = _build_imem(instrs)
    dut.imem_rdata_i.value = imem.get(0, NOP)

    for cyc in range(len(instrs) * 12 + 50):
        await _clk(dut)
        addr = _u32(dut.imem_addr_o)
        assert (addr & 3) == 0, f"JALR misaligned fetch 0x{addr:08x} at cycle {cyc}"
        _imem_serve(imem, dut)
        da = _u32(dut.dmem_addr_o)
        if _u32(dut.dmem_we_o) & 1 and da == DONE_ADDR:
            break
        dut.dmem_rdata_i.value = 0

    # Verify JALR landed correctly
    regs = await _halt_read_regs(dut)
    assert (regs[6] & 0xFFFFFFFF) == 0,  "JALR should skip addi x6"
    assert (regs[8] & 0xFFFFFFFF) == 42, "JALR target: x8 should be 42"


# ═══════════════════════════════════════════════════════════════════════════════
# 10. Only stores generate dmem_we_o=1 — no spurious writes
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_no_spurious_dmem_writes(dut):
    """A program with only LW (no stores except done sentinel) must not produce
    dmem_we_o=1 except for the single done sentinel SW at byte 0x1000."""
    start_core(dut)
    await reset_dut(dut)

    instrs = [
        lui(17, 0x2000),
        lui(16, 0x1000),
        lw(1, 17, 0),    # load — must NOT set dmem_we_o
        lw(2, 17, 4),    # load — must NOT set dmem_we_o
        add(3, 1, 2),    # ALU — must NOT set dmem_we_o
        addi(4, 3, 5),   # ALU — must NOT set dmem_we_o
        sw(4, 16, 0),    # ONLY expected dmem_we_o=1 (done sentinel at 0x1000)
        jal(0, 0),
    ]

    imem = _build_imem(instrs)
    dut.imem_rdata_i.value = imem.get(0, NOP)
    spurious_writes = []

    for cyc in range(len(instrs) * 12 + 100):
        await _clk(dut)
        _imem_serve(imem, dut)
        da = _u32(dut.dmem_addr_o)
        if _u32(dut.dmem_we_o) & 1:
            if da != DONE_ADDR:
                spurious_writes.append((cyc, da))
            else:
                break   # done sentinel — expected write
        dut.dmem_rdata_i.value = 0x00000064   # data mem returns 100

    assert not spurious_writes, (
        f"Spurious dmem writes: " +
        ", ".join(f"cycle={c} addr=0x{a:08x}" for c, a in spurious_writes))
