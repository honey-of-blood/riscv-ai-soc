"""Phase 18 stress tests — systolic_array_v3 (N=4, ACT_W=4).

Covers non-trivial matrix multiplies, negative weights, max/min INT4 values,
four consecutive runs, zero activation, ReLU boundary, and a pseudo-random
reference comparison against a Python golden model.
"""
import random
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK_PERIOD = 10  # ns
N = 4

CTRL   = 0x000
W_ROW  = [0x008, 0x00C, 0x010, 0x014]
A_VEC  = 0x028
Y_REGS = [0x100, 0x104, 0x108, 0x10C]


def pack4(w0, w1, w2, w3):
    return ((w3 & 0xF) << 12) | ((w2 & 0xF) << 8) | ((w1 & 0xF) << 4) | (w0 & 0xF)


def to_signed32(x):
    v = int(x) & 0xFFFFFFFF
    return v - 0x100000000 if v >= 0x80000000 else v


def ref_matmul(W_rows, a_vec):
    """Y[c] = Σ_r W_rows[r][c] * a_vec[r]  (Python golden)."""
    return [sum(W_rows[r][c] * a_vec[r] for r in range(N)) for c in range(N)]


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
        if ctrl & 0x2:
            return
    assert False, "systolic_array_v3 done timeout"


async def run_matmul(dut, W_rows, a_vec, relu=False):
    """Load weights and activation, run array, return Y[0..N-1]."""
    for r in range(N):
        await apb_wr(dut, W_ROW[r], pack4(*W_rows[r]))
    await apb_wr(dut, A_VEC, pack4(*a_vec))
    ctrl_val = 0x1 | (0x4 if relu else 0)
    await apb_wr(dut, CTRL, ctrl_val)
    await wait_done(dut)
    Y = [to_signed32(await apb_rd(dut, Y_REGS[c])) for c in range(N)]
    await apb_wr(dut, CTRL, 0)   # clear start → FSM returns to IDLE
    await RisingEdge(dut.clk)
    await RisingEdge(dut.clk)    # wait for DONE→IDLE transition
    await Timer(1, unit="ns")
    return Y


@cocotb.test()
async def test_nontrivial_matmul(dut):
    """W rows=[1,2,3,4]/[2,3,4,5]/[3,4,5,6]/[4,5,6,7], A=[1,1,1,1] vs Python ref."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    W = [[1,2,3,4],[2,3,4,5],[3,4,5,6],[4,5,6,7]]
    a = [1,1,1,1]
    expected = ref_matmul(W, a)   # [10, 14, 18, 22]
    Y = await run_matmul(dut, W, a)
    assert Y == expected, f"expected {expected}, got {Y}"


@cocotb.test()
async def test_scaled_diagonal(dut):
    """W = diag(1,2,3,4), A=[2,3,4,5] → Y=[2,6,12,20]."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    W = [[1,0,0,0],[0,2,0,0],[0,0,3,0],[0,0,0,4]]
    a = [2,3,4,5]
    expected = ref_matmul(W, a)  # [2, 6, 12, 20]
    Y = await run_matmul(dut, W, a)
    assert Y == expected, f"expected {expected}, got {Y}"


@cocotb.test()
async def test_negative_weights_no_relu(dut):
    """W = -I, A=[1,2,3,4] → Y=[-1,-2,-3,-4] without ReLU."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    W = [[-1,0,0,0],[0,-1,0,0],[0,0,-1,0],[0,0,0,-1]]
    a = [1,2,3,4]
    expected = ref_matmul(W, a)   # [-1, -2, -3, -4]
    Y = await run_matmul(dut, W, a, relu=False)
    assert Y == expected, f"expected {expected}, got {Y}"


@cocotb.test()
async def test_negative_weights_with_relu(dut):
    """W = -I, A=[1,2,3,4] with ReLU → all outputs clipped to 0."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    W = [[-1,0,0,0],[0,-1,0,0],[0,0,-1,0],[0,0,0,-1]]
    a = [1,2,3,4]
    Y = await run_matmul(dut, W, a, relu=True)
    assert Y == [0,0,0,0], f"ReLU should clip to 0, got {Y}"


@cocotb.test()
async def test_max_int4_values(dut):
    """W=all-7, A=[7,7,7,7] → Y = N*7*7 = 4*49 = 196 per column."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    W = [[7]*N for _ in range(N)]
    a = [7]*N
    expected = ref_matmul(W, a)  # [196]*4
    Y = await run_matmul(dut, W, a)
    assert Y == expected, f"expected {expected}, got {Y}"


@cocotb.test()
async def test_min_int4_values(dut):
    """W=all-(-8), A=all-1 → Y = N*(-8)*1 = -32 per column."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    W = [[-8]*N for _ in range(N)]
    a = [1]*N
    expected = ref_matmul(W, a)   # [-32]*4
    Y = await run_matmul(dut, W, a)
    assert Y == expected, f"expected {expected}, got {Y}"


@cocotb.test()
async def test_four_consecutive_runs(dut):
    """Four sequential runs with different W/A, each compared against Python ref."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    rng = random.Random(0xCAFE)
    for run_idx in range(4):
        W = [[rng.randint(-4, 4) for _ in range(N)] for _ in range(N)]
        a = [rng.randint(-4, 4) for _ in range(N)]
        expected = ref_matmul(W, a)
        Y = await run_matmul(dut, W, a)
        assert Y == expected, f"run {run_idx}: W={W}, a={a}: expected {expected}, got {Y}"


@cocotb.test()
async def test_zero_activation(dut):
    """Any weight matrix, A=all-zeros → Y=all-zeros."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    W = [[7]*N for _ in range(N)]  # max weights
    a = [0]*N
    Y = await run_matmul(dut, W, a)
    assert Y == [0]*N, f"expected zeros, got {Y}"


@cocotb.test()
async def test_random_reference_sweep(dut):
    """6 pseudo-random INT4 matrices compared against Python golden model."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    rng = random.Random(0xBEEF_1234)
    errors = []
    for i in range(6):
        # Use -7..7 to avoid edge overflow concerns
        W = [[rng.randint(-7, 7) for _ in range(N)] for _ in range(N)]
        a = [rng.randint(-7, 7) for _ in range(N)]
        expected = ref_matmul(W, a)
        Y = await run_matmul(dut, W, a)
        if Y != expected:
            errors.append(f"iter {i}: W={W}, a={a}: expected {expected}, got {Y}")
    assert not errors, "\n".join(errors)
