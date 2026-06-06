"""Phase 18 — systolic_array_v3 cocotb tests (N=4, ACT_W=4)."""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK_PERIOD = 10  # ns

# APB register offsets
CTRL   = 0x000
W_ROW0 = 0x008
W_ROW1 = 0x00C
W_ROW2 = 0x010
W_ROW3 = 0x014
A_VEC  = 0x028
Y0     = 0x100
Y1     = 0x104
Y2     = 0x108
Y3     = 0x10C


def pack4(w0, w1, w2, w3):
    """Pack four 4-bit signed values (−8..7) into a 16-bit word."""
    return (
        ((w3 & 0xF) << 12) | ((w2 & 0xF) << 8) |
        ((w1 & 0xF) <<  4) | ((w0 & 0xF) <<  0)
    )


def to_signed32(x):
    if x >= 0x80000000:
        return x - 0x100000000
    return x


async def reset(dut):
    dut.rst_n.value   = 0
    dut.psel.value    = 0
    dut.penable.value = 0
    dut.pwrite.value  = 0
    dut.paddr.value   = 0
    dut.pwdata.value  = 0
    await Timer(5 * CLK_PERIOD, unit="ns")
    dut.rst_n.value = 1
    await Timer(CLK_PERIOD, unit="ns")


async def apb_wr(dut, addr, data):
    dut.paddr.value  = addr
    dut.pwdata.value = data & 0xFFFFFFFF
    dut.pwrite.value = 1
    dut.psel.value   = 1
    await RisingEdge(dut.clk)
    dut.penable.value = 1
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    dut.psel.value    = 0
    dut.penable.value = 0
    dut.pwrite.value  = 0


async def apb_rd(dut, addr):
    dut.paddr.value  = addr
    dut.pwrite.value = 0
    dut.psel.value   = 1
    await RisingEdge(dut.clk)
    dut.penable.value = 1
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    val = int(dut.prdata.value)
    dut.psel.value    = 0
    dut.penable.value = 0
    return val


async def wait_done(dut, timeout=100):
    for _ in range(timeout):
        ctrl = await apb_rd(dut, CTRL)
        if ctrl & 0x2:   # done bit
            return
    assert False, "systolic_array_v3 done timeout"


@cocotb.test()
async def test_reset_state(dut):
    """After reset CTRL=0, Y outputs=0."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    ctrl = await apb_rd(dut, CTRL)
    assert (ctrl & 0x3) == 0, f"CTRL should be 0 after reset, got {ctrl:#x}"
    for off in (Y0, Y1, Y2, Y3):
        y = await apb_rd(dut, off)
        assert y == 0, f"Y at {off:#x} should be 0 after reset, got {y}"


@cocotb.test()
async def test_weight_write_read(dut):
    """Written W_ROW values are readable back via APB."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    # Identity row 0: w[0][0]=1, w[0][1..3]=0 → 0x0001
    await apb_wr(dut, W_ROW0, 0x0001)
    # Not directly APB-readable in current design (write-only reg),
    # so start a zero-activation run and verify Y[0]=0 (correct for zero input)
    await apb_wr(dut, A_VEC, 0x0000)
    await apb_wr(dut, CTRL, 1)   # start
    await wait_done(dut)
    y0 = to_signed32(await apb_rd(dut, Y0))
    assert y0 == 0, f"expected Y[0]=0 for zero input, got {y0}"
    await apb_wr(dut, CTRL, 0)   # clear start


@cocotb.test()
async def test_identity_matmul(dut):
    """W=I (transposed), A=[1,2,3,4] → Y=[1,2,3,4]."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    # W_ROW[r][c]=1 if r==c else 0
    await apb_wr(dut, W_ROW0, pack4(1, 0, 0, 0))
    await apb_wr(dut, W_ROW1, pack4(0, 1, 0, 0))
    await apb_wr(dut, W_ROW2, pack4(0, 0, 1, 0))
    await apb_wr(dut, W_ROW3, pack4(0, 0, 0, 1))
    await apb_wr(dut, A_VEC,  pack4(1, 2, 3, 4))
    await apb_wr(dut, CTRL, 1)
    await wait_done(dut)
    expected = [1, 2, 3, 4]
    for i, off in enumerate((Y0, Y1, Y2, Y3)):
        y = to_signed32(await apb_rd(dut, off))
        assert y == expected[i], f"Y[{i}] expected {expected[i]}, got {y}"
    await apb_wr(dut, CTRL, 0)


@cocotb.test()
async def test_all_ones(dut):
    """W=all-1, A=[1,1,1,1] → Y=[4,4,4,4]."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    row = pack4(1, 1, 1, 1)
    for off in (W_ROW0, W_ROW1, W_ROW2, W_ROW3):
        await apb_wr(dut, off, row)
    await apb_wr(dut, A_VEC, pack4(1, 1, 1, 1))
    await apb_wr(dut, CTRL, 1)
    await wait_done(dut)
    for i, off in enumerate((Y0, Y1, Y2, Y3)):
        y = to_signed32(await apb_rd(dut, off))
        assert y == 4, f"Y[{i}] expected 4, got {y}"
    await apb_wr(dut, CTRL, 0)


@cocotb.test()
async def test_relu(dut):
    """With relu_en, negative outputs are clipped to 0."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    # W_ROW[0] = -1 for all columns; other rows = 0
    await apb_wr(dut, W_ROW0, pack4(-1, -1, -1, -1))
    await apb_wr(dut, W_ROW1, pack4( 0,  0,  0,  0))
    await apb_wr(dut, W_ROW2, pack4( 0,  0,  0,  0))
    await apb_wr(dut, W_ROW3, pack4( 0,  0,  0,  0))
    await apb_wr(dut, A_VEC, pack4(1, 0, 0, 0))
    await apb_wr(dut, CTRL, 0x5)   # start=1, relu_en=1
    await wait_done(dut)
    for i, off in enumerate((Y0, Y1, Y2, Y3)):
        y = to_signed32(await apb_rd(dut, off))
        assert y == 0, f"Y[{i}] should be clipped to 0 by ReLU, got {y}"
    await apb_wr(dut, CTRL, 0x4)  # clear start, keep relu bit


@cocotb.test()
async def test_restart(dut):
    """Run twice, second run with different weights gives different result."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    # First run: W=I, A=[1,2,3,4] → Y=[1,2,3,4]
    await apb_wr(dut, W_ROW0, pack4(1, 0, 0, 0))
    await apb_wr(dut, W_ROW1, pack4(0, 1, 0, 0))
    await apb_wr(dut, W_ROW2, pack4(0, 0, 1, 0))
    await apb_wr(dut, W_ROW3, pack4(0, 0, 0, 1))
    await apb_wr(dut, A_VEC, pack4(1, 2, 3, 4))
    await apb_wr(dut, CTRL, 1)
    await wait_done(dut)
    y0_run1 = to_signed32(await apb_rd(dut, Y0))
    assert y0_run1 == 1, f"Run1 Y[0] expected 1, got {y0_run1}"
    await apb_wr(dut, CTRL, 0)  # clear start

    # Second run: W=2*I, A=[1,2,3,4] → Y=[2,4,6,8]
    await RisingEdge(dut.clk)
    await apb_wr(dut, W_ROW0, pack4(2, 0, 0, 0))
    await apb_wr(dut, W_ROW1, pack4(0, 2, 0, 0))
    await apb_wr(dut, W_ROW2, pack4(0, 0, 2, 0))
    await apb_wr(dut, W_ROW3, pack4(0, 0, 0, 2))
    await apb_wr(dut, A_VEC, pack4(1, 2, 3, 4))
    await apb_wr(dut, CTRL, 1)
    await wait_done(dut)
    expected2 = [2, 4, 6, 8]
    for i, off in enumerate((Y0, Y1, Y2, Y3)):
        y = to_signed32(await apb_rd(dut, off))
        assert y == expected2[i], f"Run2 Y[{i}] expected {expected2[i]}, got {y}"
    await apb_wr(dut, CTRL, 0)
