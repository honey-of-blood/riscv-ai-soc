"""Phase 18 — pe_int4 cocotb tests (ACT_W=4, ACCW=32)."""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK_PERIOD = 10  # ns


async def reset(dut):
    dut.rst_n.value = 0
    dut.a_i.value   = 0
    dut.b_i.value   = 0
    dut.c_i.value   = 0
    await Timer(5 * CLK_PERIOD, unit="ns")
    dut.rst_n.value = 1
    await Timer(CLK_PERIOD, unit="ns")


def to_signed4(x):
    """Convert unsigned 4-bit value to signed Python int."""
    if x >= 8:
        return x - 16
    return x


def to_signed32(x):
    """Convert unsigned 32-bit value to signed Python int."""
    if x >= 0x80000000:
        return x - 0x100000000
    return x


@cocotb.test()
async def test_reset_state(dut):
    """After reset all outputs are zero."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert int(dut.c_o.value) == 0, f"c_o should be 0 after reset, got {dut.c_o.value}"
    assert int(dut.a_o.value) == 0
    assert int(dut.b_o.value) == 0


@cocotb.test()
async def test_basic_int4_multiply(dut):
    """a_i=3, b_i=2, c_i=0 → c_o=6 after one cycle."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    dut.a_i.value = 3
    dut.b_i.value = 2
    dut.c_i.value = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    c_o = to_signed32(int(dut.c_o.value))
    assert c_o == 6, f"expected 6, got {c_o}"


@cocotb.test()
async def test_accumulate(dut):
    """Feed same inputs for 3 cycles with c_i chaining: c_o should be 6*N."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    # Cycle 1: a=3, b=2, c_i=0 → c_o=6
    dut.a_i.value = 3
    dut.b_i.value = 2
    dut.c_i.value = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    c1 = to_signed32(int(dut.c_o.value))
    assert c1 == 6

    # Cycle 2: feed c_o of cycle 1 back as c_i
    dut.c_i.value = c1 & 0xFFFFFFFF
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    c2 = to_signed32(int(dut.c_o.value))
    assert c2 == 12

    # Cycle 3
    dut.c_i.value = c2 & 0xFFFFFFFF
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    c3 = to_signed32(int(dut.c_o.value))
    assert c3 == 18


@cocotb.test()
async def test_passthrough(dut):
    """a_o == a_i and b_o == b_i (both delayed by one cycle)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    dut.a_i.value = 5
    dut.b_i.value = 3
    dut.c_i.value = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    a_o = int(dut.a_o.value) & 0xF
    b_o = int(dut.b_o.value) & 0xF
    assert to_signed4(a_o) == 5, f"a_o expected 5, got {to_signed4(a_o)}"
    assert to_signed4(b_o) == 3, f"b_o expected 3, got {to_signed4(b_o)}"


@cocotb.test()
async def test_signed_negative(dut):
    """a_i=-3 (0xD), b_i=2 → c_o=-6 (sign-extended)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    dut.a_i.value = 0xD  # -3 in 4-bit 2's complement
    dut.b_i.value = 2
    dut.c_i.value = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    c_o = to_signed32(int(dut.c_o.value))
    assert c_o == -6, f"expected -6, got {c_o}"


@cocotb.test()
async def test_max_int4_product(dut):
    """a_i=7, b_i=7 → c_o=49 (max INT4 × INT4 product)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    dut.a_i.value = 7
    dut.b_i.value = 7
    dut.c_i.value = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    c_o = to_signed32(int(dut.c_o.value))
    assert c_o == 49, f"expected 49, got {c_o}"
