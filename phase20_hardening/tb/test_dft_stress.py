"""Phase 20 — dft_top.sv aggressive stress tests.

Scan chain topology (SCAN_DEPTH=16):
  scan_in → FF[15] → FF[14] → ... → FF[0] → scan_out
  shift_in LSB→FF[15] (MSB of pattern enters first), scan_out = FF[0] (LSB exits first).

After shifting DEPTH bits MSB-first, FF[0] holds bits_in[0] (MSB of pattern).
Shift-out phase emits FF[0], FF[1], ..., FF[15] — i.e. MSB-first.
Reconstruction: (b0<<15)|(b1<<14)|...|(b15<<0) = original pattern.
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK_NS   = 10
SCAN_CLK = 10
DEPTH    = 16


async def reset_dut(dut):
    dut.rst_n.value      = 0
    dut.scan_en_i.value  = 0
    dut.scan_clk_i.value = 0
    dut.scan_in_i.value  = 0
    dut.d_i.value        = 0
    await Timer(5 * CLK_NS, unit="ns")
    dut.rst_n.value = 1
    await Timer(CLK_NS, unit="ns")


async def scan_clock_pulse(dut):
    dut.scan_clk_i.value = 1
    await Timer(SCAN_CLK // 2, unit="ns")
    dut.scan_clk_i.value = 0
    await Timer(SCAN_CLK // 2, unit="ns")


async def shift_in_pattern(dut, pattern):
    """Shift DEPTH bits of pattern MSB-first into the scan chain."""
    bits = [(pattern >> (DEPTH - 1 - i)) & 1 for i in range(DEPTH)]
    for bit in bits:
        dut.scan_in_i.value = bit
        await scan_clock_pulse(dut)


async def shift_out_pattern(dut):
    """Shift out DEPTH bits and reconstruct the pattern (MSB-first)."""
    result = 0
    for _ in range(DEPTH):
        result = (result << 1) | int(dut.scan_out_o.value)
        await scan_clock_pulse(dut)
    return result & 0xFFFF


async def scan_shift_and_verify(dut, pattern):
    """Shift pattern in, shift it out, and return the reconstructed value."""
    dut.scan_en_i.value = 1
    await Timer(1, unit="ns")
    await shift_in_pattern(dut, pattern)
    result = await shift_out_pattern(dut)
    return result


# ── Tests ──────────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_four_patterns_sequential(dut):
    """Shift 0xDEAD, 0xBEEF, 0x5A5A, 0xA5A5 through the chain in sequence.
    Each pattern enters and exits correctly; chain state does not bleed."""
    cocotb.start_soon(Clock(dut.clk_i, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    patterns = [0xDEAD, 0xBEEF, 0x5A5A, 0xA5A5]
    for pat in patterns:
        # Reset chain between each pattern
        dut.rst_n.value = 0
        await Timer(1, unit="ns")
        dut.rst_n.value = 1
        await Timer(1, unit="ns")

        result = await scan_shift_and_verify(dut, pat)
        assert result == pat, f"pattern {pat:#06x}: shifted out {result:#06x}"


@cocotb.test()
async def test_walking_ones_all_positions(dut):
    """Walk a single 1-bit through all 16 positions; verify it exits at the correct bit."""
    cocotb.start_soon(Clock(dut.clk_i, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    for pos in range(DEPTH):
        pattern = 1 << pos

        dut.rst_n.value = 0
        await Timer(1, unit="ns")
        dut.rst_n.value = 1
        await Timer(1, unit="ns")

        result = await scan_shift_and_verify(dut, pattern)
        assert result == pattern, \
            f"walking-one at bit {pos}: in={pattern:#06x} out={result:#06x}"


@cocotb.test()
async def test_walking_zeros_all_positions(dut):
    """Walk a single 0-bit through all 16 positions (all-ones background)."""
    cocotb.start_soon(Clock(dut.clk_i, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    for pos in range(DEPTH):
        pattern = 0xFFFF ^ (1 << pos)  # all-ones with one zero

        dut.rst_n.value = 0
        await Timer(1, unit="ns")
        dut.rst_n.value = 1
        await Timer(1, unit="ns")

        result = await scan_shift_and_verify(dut, pattern)
        assert result == pattern, \
            f"walking-zero at bit {pos}: in={pattern:#06x} out={result:#06x}"


@cocotb.test()
async def test_reset_clears_mid_scan(dut):
    """Assert reset after shifting in 8 bits; verify all FFs cleared to 0."""
    cocotb.start_soon(Clock(dut.clk_i, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    dut.scan_en_i.value = 1
    await Timer(1, unit="ns")

    # Shift in the first 8 bits of 0xDEAD (MSB first = 1101 1110)
    half_pattern = [(0xDEAD >> (DEPTH - 1 - i)) & 1 for i in range(DEPTH // 2)]
    for bit in half_pattern:
        dut.scan_in_i.value = bit
        await scan_clock_pulse(dut)

    # Assert reset mid-shift
    dut.rst_n.value = 0
    await Timer(1, unit="ns")

    # All FFs must be 0 immediately on rst_n=0 (async clear)
    assert int(dut.q_o.value) == 0, \
        f"q_o not 0 after mid-scan reset: {int(dut.q_o.value):#06x}"
    assert int(dut.scan_out_o.value) == 0, "scan_out_o not 0 after mid-scan reset"

    # Release reset and shift out — should get all zeros
    dut.rst_n.value = 1
    await Timer(1, unit="ns")
    result = await shift_out_pattern(dut)
    assert result == 0, f"post-reset shift-out expected 0x0000, got {result:#06x}"


@cocotb.test()
async def test_scan_functional_interleave(dut):
    """Three rounds of: functional capture → scan shift-out → verify.
    Ensures mode switching does not corrupt the chain."""
    cocotb.start_soon(Clock(dut.clk_i, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    func_patterns = [0x1234, 0xABCD, 0xF00F]

    for pat in func_patterns:
        # Functional capture
        dut.scan_en_i.value = 0
        dut.d_i.value = pat
        await RisingEdge(dut.clk_i)
        await Timer(1, unit="ns")
        assert int(dut.q_o.value) == pat, \
            f"functional capture: expected {pat:#06x}, got {int(dut.q_o.value):#06x}"

        # Switch to scan mode and shift out; bits exit LSB-first from FF[0]
        dut.scan_en_i.value = 1
        dut.scan_in_i.value = 0
        await Timer(1, unit="ns")

        # FF[0] = q_o[0]. After DEPTH shift clocks, we collect scan_out LSB-first.
        shifted = 0
        for _ in range(DEPTH):
            shifted = (shifted << 1) | int(dut.scan_out_o.value)
            await scan_clock_pulse(dut)

        # Bits came out FF[0]..FF[15] (LSB first); reverse to reconstruct
        reconstructed = 0
        for i in range(DEPTH):
            reconstructed = (reconstructed << 1) | ((shifted >> i) & 1)
        reconstructed &= 0xFFFF
        assert reconstructed == pat, \
            f"scan shift-out after functional {pat:#06x}: got {reconstructed:#06x}"

        # Switch back to functional for next iteration
        dut.scan_en_i.value = 0


@cocotb.test()
async def test_all_zeros_and_all_ones(dut):
    """Edge patterns: 0x0000 (all-zeros) and 0xFFFF (all-ones)."""
    cocotb.start_soon(Clock(dut.clk_i, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    for pat in [0x0000, 0xFFFF]:
        dut.rst_n.value = 0
        await Timer(1, unit="ns")
        dut.rst_n.value = 1
        await Timer(1, unit="ns")

        result = await scan_shift_and_verify(dut, pat)
        assert result == pat, f"pattern {pat:#06x}: got {result:#06x}"


@cocotb.test()
async def test_multiple_sequential_scans_no_reset(dut):
    """Four scan operations back-to-back without intermediate reset.
    Each new shift-in overwrites the chain; shift-out must reflect the latest input."""
    cocotb.start_soon(Clock(dut.clk_i, CLK_NS, unit="ns").start())
    await reset_dut(dut)

    dut.scan_en_i.value = 1
    await Timer(1, unit="ns")

    sequences = [0x1357, 0x2468, 0x9ABC, 0xEF01]
    for pat in sequences:
        # Shift in new pattern (overwrites whatever is in the chain)
        await shift_in_pattern(dut, pat)
        # Immediately shift out — must equal pat
        result = await shift_out_pattern(dut)
        assert result == pat, \
            f"sequential scan {pat:#06x}: shifted out {result:#06x}"
