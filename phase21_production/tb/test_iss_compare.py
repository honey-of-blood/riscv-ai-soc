"""Phase 21 — ISS-vs-DUT comparison tests.

Each test generates a random RV32IM program, executes it on:
  1. The Python ISS (golden reference — rv32imac_iss.py)
  2. The RTL DUT (riscv_core.sv) via cocotb

Then compares all registers x1-x15 (and x16 for the LUI'd done-address).
A mismatch flags an RTL bug that unit tests would have missed.

Test matrix (seed → program type):
  Seeds 0-4  : pure arithmetic (all R/I-type, no memory, no M-ext)
  Seeds 5-9  : arithmetic with M-extension (MUL/MULH/DIV/REM)
  Seeds 10-13: arithmetic with forward branches (BEQ/BNE/BLT etc.)
  Seeds 14-16: load + store + arithmetic (data memory exercised)
"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
sys.path.insert(0, os.path.dirname(__file__))

import cocotb
from core_helpers import start_core, reset_dut, run_program, read_registers, DONE_ADDR
from prog_gen import gen_program, gen_load_store_program, NOP
from iss.rv32imac_iss import RV32IMISS

# Registers to compare after execution (x1-x15 are the random-program working regs)
CHECK_REGS = list(range(1, 17))   # x1-x16 (x16 = done-addr reg, always 0x1000)


async def _iss_vs_dut(dut, seed, n_body=20, m_ext_frac=0.0, branch_frac=0.0):
    """Core comparison helper used by every test."""
    start_core(dut)
    await reset_dut(dut)

    instrs, iss_steps, _ = gen_program(
        n_body=n_body, seed=seed,
        m_ext_frac=m_ext_frac, branch_frac=branch_frac)

    # ── ISS execution ─────────────────────────────────────────────────────────
    iss = RV32IMISS()
    iss.load(instrs)
    iss_regs = iss.run_n(iss_steps)

    # ── DUT execution ─────────────────────────────────────────────────────────
    imem = {i: instrs[i] for i in range(len(instrs))}
    dmem = {}
    timeout_cycles = len(instrs) * 8 + 80

    done = await run_program(dut, imem, dmem, cycles=timeout_cycles, stop_on_done=True)
    assert done, (f"DUT did not write to DONE_ADDR (0x{DONE_ADDR:08x}) "
                  f"within {timeout_cycles} cycles (seed={seed})")

    dut_regs = await read_registers(dut)

    # ── Comparison ────────────────────────────────────────────────────────────
    mismatches = []
    for r in CHECK_REGS:
        iss_v = iss_regs[r] & 0xFFFFFFFF
        dut_v = dut_regs[r] & 0xFFFFFFFF
        if iss_v != dut_v:
            mismatches.append(f"  x{r:02d}: ISS=0x{iss_v:08x}  DUT=0x{dut_v:08x}")

    assert not mismatches, (
        f"Register mismatch (seed={seed}, n_body={n_body}):\n" +
        "\n".join(mismatches))


async def _iss_vs_dut_ls(dut, seed, n_body=15):
    """Load/store variant: pre-initialises data memory in both ISS and DUT."""
    start_core(dut)
    await reset_dut(dut)

    instrs, iss_steps, _, data_mem = gen_load_store_program(n_body=n_body, seed=seed)

    iss = RV32IMISS()
    iss.load(instrs)
    iss.mem.update(data_mem)    # same pre-init in ISS

    iss_regs = iss.run_n(iss_steps)

    imem = {i: instrs[i] for i in range(len(instrs))}
    dmem = dict(data_mem)       # same pre-init in DUT-side Python dmem
    timeout_cycles = len(instrs) * 8 + 80

    done = await run_program(dut, imem, dmem, cycles=timeout_cycles, stop_on_done=True)
    assert done, f"DUT done sentinel not seen (seed={seed})"

    dut_regs = await read_registers(dut)

    mismatches = []
    for r in range(1, 15):     # x1-x14 (x15 is base pointer, x16 is done addr)
        iss_v = iss_regs[r] & 0xFFFFFFFF
        dut_v = dut_regs[r] & 0xFFFFFFFF
        if iss_v != dut_v:
            mismatches.append(f"  x{r:02d}: ISS=0x{iss_v:08x}  DUT=0x{dut_v:08x}")

    assert not mismatches, "\n".join(mismatches)


# ═══════════════════════════════════════════════════════════════════════════════
# Seeds 0-4: Pure arithmetic (R-type + I-type, no M-ext, no branches)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_arith_seed0(dut):
    """20 random R/I-type instructions, seed=0."""
    await _iss_vs_dut(dut, seed=0, n_body=20)

@cocotb.test()
async def test_arith_seed1(dut):
    """20 random R/I-type instructions, seed=1 — different register init."""
    await _iss_vs_dut(dut, seed=1, n_body=20)

@cocotb.test()
async def test_arith_seed2(dut):
    """30 instructions — longer chain stresses forwarding more."""
    await _iss_vs_dut(dut, seed=2, n_body=30)

@cocotb.test()
async def test_arith_seed3(dut):
    """20 instructions, seed=3 — shift-heavy: exercises SLL/SRL/SRA/SLLI/SRLI/SRAI."""
    await _iss_vs_dut(dut, seed=3, n_body=20)

@cocotb.test()
async def test_arith_seed4(dut):
    """25 instructions, seed=4 — SLT/SLTU/SLTI/SLTIU comparison coverage."""
    await _iss_vs_dut(dut, seed=4, n_body=25)

# ═══════════════════════════════════════════════════════════════════════════════
# Seeds 5-9: M-extension arithmetic (MUL/MULH/MULHU/MULHSU)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_mext_seed5(dut):
    """20 instructions, ~15% M-ext: MUL/MULH/MULHU/MULHSU."""
    await _iss_vs_dut(dut, seed=5, n_body=20, m_ext_frac=0.15)

@cocotb.test()
async def test_mext_seed6(dut):
    """30 instructions, ~25% M-ext — heavier M-extension coverage."""
    await _iss_vs_dut(dut, seed=6, n_body=30, m_ext_frac=0.25)

@cocotb.test()
async def test_mext_seed7(dut):
    """20 instructions, seed=7, M-ext heavy."""
    await _iss_vs_dut(dut, seed=7, n_body=20, m_ext_frac=0.20)

@cocotb.test()
async def test_mext_seed8(dut):
    """25 instructions, seed=8."""
    await _iss_vs_dut(dut, seed=8, n_body=25, m_ext_frac=0.20)

@cocotb.test()
async def test_mext_seed9(dut):
    """30 instructions, seed=9, mixed M-ext + shift-heavy."""
    await _iss_vs_dut(dut, seed=9, n_body=30, m_ext_frac=0.15)

# ═══════════════════════════════════════════════════════════════════════════════
# Seeds 10-13: Forward branches (BEQ/BNE/BLT/BGE/BLTU/BGEU)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_branch_seed10(dut):
    """20 instructions with ~10% forward branches — tests branch-flush path."""
    await _iss_vs_dut(dut, seed=10, n_body=20, branch_frac=0.10)

@cocotb.test()
async def test_branch_seed11(dut):
    """30 instructions, ~15% branches — more branch-not-taken / taken coverage."""
    await _iss_vs_dut(dut, seed=11, n_body=30, branch_frac=0.15)

@cocotb.test()
async def test_branch_seed12(dut):
    """25 instructions, seed=12, mixed branches + M-ext."""
    await _iss_vs_dut(dut, seed=12, n_body=25, branch_frac=0.10, m_ext_frac=0.10)

@cocotb.test()
async def test_branch_seed13(dut):
    """35 instructions, seed=13, all features."""
    await _iss_vs_dut(dut, seed=13, n_body=35, branch_frac=0.12, m_ext_frac=0.12)

# ═══════════════════════════════════════════════════════════════════════════════
# Seeds 14-16: Load + Store programs (data memory exercised)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_load_store_seed14(dut):
    """15 instructions with LW/SW/ADD — data memory routing verified."""
    await _iss_vs_dut_ls(dut, seed=14, n_body=15)

@cocotb.test()
async def test_load_store_seed15(dut):
    """20 instructions, seed=15 — more load-after-store chains (stall path)."""
    await _iss_vs_dut_ls(dut, seed=15, n_body=20)

@cocotb.test()
async def test_load_store_seed16(dut):
    """25 instructions, seed=16 — load-use stall exercised by store-then-load."""
    await _iss_vs_dut_ls(dut, seed=16, n_body=25)
