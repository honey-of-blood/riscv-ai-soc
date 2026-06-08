"""Phase 21 stress — extended ISS-vs-DUT comparison tests.

Covers gaps left by the base test_iss_compare.py:
  • Larger programs (n_body 40-70) that stress forwarding paths more
  • Full M-extension pool including DIV/DIVU/REM/REMU
  • div_frac > 0: div-by-zero edge cases verified via spec-correct ISS
  • Dense branches (branch_frac 0.20-0.30)
  • Mixed everything at once
  • Large load/store programs
  • AUIPC in the random instruction pool (added to gen_program's ALU set)
  • SLTI/SLTIU (previously only SLT/SLTU R-type tested)
  • Shift-by-0 / shift-by-31 (sh range now 0..31)

All tests: ISS is the golden reference; register x1-x16 compared after done sentinel.
"""
import sys, os
sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))
sys.path.insert(0, os.path.dirname(__file__))

import cocotb
from core_helpers import start_core, reset_dut, run_program, read_registers, DONE_ADDR
from prog_gen import gen_program, gen_load_store_program
from iss.rv32imac_iss import RV32IMISS

CHECK_REGS = list(range(1, 17))


async def _cmp(dut, seed, n_body=40, m_ext_frac=0.0, branch_frac=0.0, div_frac=0.0):
    """ISS-vs-DUT comparison helper with generous timeout for DIV stalls."""
    start_core(dut)
    await reset_dut(dut)

    instrs, iss_steps, _ = gen_program(
        n_body=n_body, seed=seed,
        m_ext_frac=m_ext_frac, branch_frac=branch_frac, div_frac=div_frac)

    iss = RV32IMISS()
    iss.load(instrs)
    iss_regs = iss.run_n(iss_steps)

    imem = {i: instrs[i] for i in range(len(instrs))}
    dmem = {}
    # 45 cycles/instr base; handles 32-cycle DIV stalls generously
    timeout = len(instrs) * 45 + 250

    done = await run_program(dut, imem, dmem, cycles=timeout, stop_on_done=True)
    assert done, f"Done sentinel not seen within {timeout} cycles (seed={seed})"

    dut_regs = await read_registers(dut)

    mismatches = []
    for r in CHECK_REGS:
        iv = iss_regs[r] & 0xFFFFFFFF
        dv = dut_regs[r] & 0xFFFFFFFF
        if iv != dv:
            mismatches.append(f"  x{r:02d}: ISS=0x{iv:08x}  DUT=0x{dv:08x}")

    assert not mismatches, (
        f"Register mismatch seed={seed} n_body={n_body}:\n" + "\n".join(mismatches))


async def _cmp_ls(dut, seed, n_body=25):
    """Load/store variant with larger timeout."""
    start_core(dut)
    await reset_dut(dut)

    instrs, iss_steps, _, data_mem = gen_load_store_program(n_body=n_body, seed=seed)

    iss = RV32IMISS()
    iss.load(instrs)
    iss.mem.update(data_mem)
    iss_regs = iss.run_n(iss_steps)

    imem = {i: instrs[i] for i in range(len(instrs))}
    dmem = dict(data_mem)
    timeout = len(instrs) * 45 + 250

    done = await run_program(dut, imem, dmem, cycles=timeout, stop_on_done=True)
    assert done, f"Done sentinel not seen within {timeout} cycles (seed={seed})"

    dut_regs = await read_registers(dut)

    mismatches = []
    for r in range(1, 15):
        iv = iss_regs[r] & 0xFFFFFFFF
        dv = dut_regs[r] & 0xFFFFFFFF
        if iv != dv:
            mismatches.append(f"  x{r:02d}: ISS=0x{iv:08x}  DUT=0x{dv:08x}")

    assert not mismatches, "\n".join(mismatches)


# ═══════════════════════════════════════════════════════════════════════════════
# Long pure-arithmetic programs (n_body 40-70)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_arith_long_seed17(dut):
    """40-instr pure arith — stresses all forwarding paths more deeply."""
    await _cmp(dut, seed=17, n_body=40)

@cocotb.test()
async def test_arith_long_seed18(dut):
    """50-instr pure arith + AUIPC/SLTI/SLTIU in pool."""
    await _cmp(dut, seed=18, n_body=50)

@cocotb.test()
async def test_arith_long_seed19(dut):
    """60-instr — forwarding chain with shift-by-0 and shift-by-31 variants."""
    await _cmp(dut, seed=19, n_body=60)

@cocotb.test()
async def test_arith_long_seed20(dut):
    """45-instr, seed=20."""
    await _cmp(dut, seed=20, n_body=45)

@cocotb.test()
async def test_arith_long_seed21(dut):
    """55-instr, seed=21 — exercises SLTI/SLTIU signed/unsigned comparisons."""
    await _cmp(dut, seed=21, n_body=55)

# ═══════════════════════════════════════════════════════════════════════════════
# Heavy MUL-family (25-30% of body instructions)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_mext_heavy_seed22(dut):
    """30-instr, 30% MUL-family — heavy multiplier path."""
    await _cmp(dut, seed=22, n_body=30, m_ext_frac=0.30)

@cocotb.test()
async def test_mext_heavy_seed23(dut):
    """40-instr, 25% MUL-family."""
    await _cmp(dut, seed=23, n_body=40, m_ext_frac=0.25)

@cocotb.test()
async def test_mext_heavy_seed24(dut):
    """50-instr, 20% MUL-family."""
    await _cmp(dut, seed=24, n_body=50, m_ext_frac=0.20)

# ═══════════════════════════════════════════════════════════════════════════════
# DIV/REM family (includes div-by-zero cases — ISS+DUT must agree on semantics)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_div_seed25(dut):
    """20-instr, 10% DIV/REM — exercises 32-cycle divider and spec-defined results."""
    await _cmp(dut, seed=25, n_body=20, div_frac=0.10)

@cocotb.test()
async def test_div_seed26(dut):
    """25-instr, 15% DIV/REM."""
    await _cmp(dut, seed=26, n_body=25, div_frac=0.15)

@cocotb.test()
async def test_div_seed27(dut):
    """30-instr, 12% DIV/REM + 10% MUL — mixed M-extension."""
    await _cmp(dut, seed=27, n_body=30, div_frac=0.12, m_ext_frac=0.10)

@cocotb.test()
async def test_div_seed28(dut):
    """35-instr, 10% DIV/REM + 10% MUL + 10% branches — full M-ext mix."""
    await _cmp(dut, seed=28, n_body=35, div_frac=0.10, m_ext_frac=0.10, branch_frac=0.10)

# ═══════════════════════════════════════════════════════════════════════════════
# Dense branches (20-30% of body)
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_branch_dense_seed29(dut):
    """25-instr, 25% branches — heavy branch-flush path exercise."""
    await _cmp(dut, seed=29, n_body=25, branch_frac=0.25)

@cocotb.test()
async def test_branch_dense_seed30(dut):
    """35-instr, 20% branches."""
    await _cmp(dut, seed=30, n_body=35, branch_frac=0.20)

@cocotb.test()
async def test_branch_dense_seed31(dut):
    """40-instr, 20% branches + 10% MUL."""
    await _cmp(dut, seed=31, n_body=40, branch_frac=0.20, m_ext_frac=0.10)

@cocotb.test()
async def test_branch_dense_seed32(dut):
    """50-instr, 18% branches — tests branch predictor recovery across many flushes."""
    await _cmp(dut, seed=32, n_body=50, branch_frac=0.18)

# ═══════════════════════════════════════════════════════════════════════════════
# Mixed-everything
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_mixed_seed33(dut):
    """35-instr: arith + MUL + DIV + branches — all features simultaneously."""
    await _cmp(dut, seed=33, n_body=35, m_ext_frac=0.10, branch_frac=0.10, div_frac=0.05)

@cocotb.test()
async def test_mixed_seed34(dut):
    """40-instr mixed."""
    await _cmp(dut, seed=34, n_body=40, m_ext_frac=0.12, branch_frac=0.12, div_frac=0.06)

@cocotb.test()
async def test_long_mixed_seed35(dut):
    """60-instr, all feature flags — longest mixed program."""
    await _cmp(dut, seed=35, n_body=60, m_ext_frac=0.10, branch_frac=0.10, div_frac=0.05)

@cocotb.test()
async def test_long_branch_seed36(dut):
    """70-instr, branch-heavy long program."""
    await _cmp(dut, seed=36, n_body=70, branch_frac=0.10)

# ═══════════════════════════════════════════════════════════════════════════════
# Extended load/store programs
# ═══════════════════════════════════════════════════════════════════════════════

@cocotb.test()
async def test_ls_stress_seed37(dut):
    """30-instr load/store — more store-load chains, more load-use stalls."""
    await _cmp_ls(dut, seed=37, n_body=30)

@cocotb.test()
async def test_ls_stress_seed38(dut):
    """35-instr load/store — stress byte-lane routing."""
    await _cmp_ls(dut, seed=38, n_body=35)

@cocotb.test()
async def test_ls_stress_seed39(dut):
    """40-instr load/store, seed=39."""
    await _cmp_ls(dut, seed=39, n_body=40)
