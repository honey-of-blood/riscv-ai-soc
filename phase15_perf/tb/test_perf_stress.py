"""
Phase 15 integration stress tests — full pipeline with icache + branch predictor.

Programs are hand-assembled RV32I/M instructions (little-endian word arrays).

Termination: all programs write their result to a specific dmem address and then
halt. run_program() terminates on that dmem write, avoiding the speculative-fetch
false-positive that would occur when checking imem_addr (pc_obs) for EBREAK.

Coverage beyond test_perf.py:
  - Nested loop (10×10 = 100 increments) with correct final value
  - Load-use hazard immediately before MUL instruction
  - 1000-iteration loop (icache warmup + BP training)
  - Fibonacci(10) spanning 3 cache lines — verifies cross-line branch redirect
  - Sum 1..5 via loop (tests BNE misprediction recovery + correct result)
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer
from cocotb.clock import Clock


# ---------------------------------------------------------------------------
# Instruction encodings (RV32I/M, all verified by hand)
# ---------------------------------------------------------------------------

def _addi(rd, rs1, imm):
    imm &= 0xFFF
    return (imm << 20) | (rs1 << 15) | (0 << 12) | (rd << 7) | 0x13


def _add(rd, rs1, rs2):
    return (rs2 << 20) | (rs1 << 15) | (0 << 12) | (rd << 7) | 0x33


def _bne(rs1, rs2, offset):
    o = offset & 0x1FFF
    imm12   = (o >> 12) & 1
    imm11   = (o >> 11) & 1
    imm10_5 = (o >> 5) & 0x3F
    imm4_1  = (o >> 1) & 0xF
    return (imm12 << 31) | (imm10_5 << 25) | (rs2 << 20) | (rs1 << 15) | \
           (1 << 12) | (imm4_1 << 8) | (imm11 << 7) | 0x63


def _lw(rd, rs1, imm):
    imm &= 0xFFF
    return (imm << 20) | (rs1 << 15) | (2 << 12) | (rd << 7) | 0x03


def _sw(rs2, rs1, imm):
    imm &= 0xFFF
    imm11_5 = (imm >> 5) & 0x7F
    imm4_0  = imm & 0x1F
    return (imm11_5 << 25) | (rs2 << 20) | (rs1 << 15) | (2 << 12) | (imm4_0 << 7) | 0x23


def _mul(rd, rs1, rs2):
    return (1 << 25) | (rs2 << 20) | (rs1 << 15) | (0 << 12) | (rd << 7) | 0x33


NOP = 0x00000013

# Registers
x0, ra, sp = 0, 1, 2
t0, t1, t2 = 5, 6, 7
a0, a1, a2 = 10, 11, 12

# ---------------------------------------------------------------------------
# Programs
# Termination condition: SW to result_addr. All programs end with:
#   SW <result>, result_addr(x0)
#   (EBREAK or tight loop — not used for detection)
# ---------------------------------------------------------------------------

# Nested loop 10×10: sum stored to dmem[0] via SW; expected = 100
# result_addr = 0
NESTED_LOOP = [
    _addi(t0, x0, 10),    # 0x00: outer = 10
    _addi(t1, x0, 10),    # 0x04: inner = 10   ← outer_loop
    _addi(a0, a0, 1),     # 0x08: sum++         ← inner_loop
    _addi(t1, t1, -1),    # 0x0C: inner--
    _bne(t1, x0, -8),     # 0x10: if inner!=0 → 0x08
    _addi(t0, t0, -1),    # 0x14: outer--
    _bne(t0, x0, -20),    # 0x18: if outer!=0 → 0x04
    _sw(a0, x0, 0),       # 0x1C: dmem[0] = sum (TERMINATION WRITE)
    NOP, NOP, NOP, NOP,   # padding to keep in same cache line (0x1C is line 1)
]
NESTED_LOOP_RESULT_ADDR = 0

# Load-use hazard then MUL: dmem[0]=7, computes 7×7=49, stores to dmem[4]
# result_addr = 4
LOAD_USE_MUL = [
    _lw(t0, x0, 0),       # 0x00: t0 = dmem[0] = 7
    _mul(t1, t0, t0),     # 0x04: t1 = t0*t0 (load-use: t0 used immediately)
    _sw(t1, x0, 4),       # 0x08: dmem[4] = t1  (TERMINATION WRITE)
    NOP,                  # 0x0C: padding
]
LOAD_USE_MUL_RESULT_ADDR = 4

# 1000-iteration countdown loop — writes 0 to dmem[4] when done
# result_addr = 4  (store of x0=0 signals completion)
LOOP_1000 = [
    _addi(t0, x0, 1000 & 0xFFF),   # 0x00: t0 = 1000
    _addi(t0, t0, -1),              # 0x04: t0--   ← loop
    _bne(t0, x0, -4),               # 0x08: if t0!=0 → 0x04
    _sw(x0, x0, 4),                 # 0x0C: dmem[4] = 0  (TERMINATION WRITE)
    NOP,                            # 0x10: padding
]
LOOP_1000_RESULT_ADDR = 4

# Fibonacci(10) across 3 cache lines:
#   Line 0 (0x00-0x0F): init a0=0, a1=1, t0=9, last word = ADD
#   Line 1 (0x10-0x1F): loop body ADDI×2 + ADDI(-1) + BNE(-16 → 0x0C)
#   Line 2 (0x20-0x2F): SW a1, EBREAK
# result_addr = 0
FIBONACCI = [
    _addi(a0, x0, 0),     # 0x00: f(n-2) = 0
    _addi(a1, x0, 1),     # 0x04: f(n-1) = 1
    _addi(t0, x0, 9),     # 0x08: count = 9 iterations → f(10) = 55
    _add(t1, a0, a1),     # 0x0C: t1 = f(n-1)+f(n-2)  ← last word line 0
    _addi(a0, a1, 0),     # 0x10: a0 = a1
    _addi(a1, t1, 0),     # 0x14: a1 = t1
    _addi(t0, t0, -1),    # 0x18: count--
    _bne(t0, x0, -16),    # 0x1C: if count!=0 → 0x0C  (cross-line branch)
    _sw(a1, x0, 0),       # 0x20: dmem[0] = f(10) = 55  (TERMINATION WRITE)
    NOP, NOP, NOP,        # 0x24-0x2C: padding (line 2)
]
FIBONACCI_RESULT_ADDR = 0

# Sum 1..5: a0 = 5+4+3+2+1 = 15, stored to dmem[0]
# result_addr = 0
SUM_1_TO_5 = [
    _addi(t0, x0, 5),     # 0x00: counter = 5
    _addi(a0, x0, 0),     # 0x04: sum = 0
    _add(a0, a0, t0),     # 0x08: sum += t0  ← loop
    _addi(t0, t0, -1),    # 0x0C: t0--
    _bne(t0, x0, -8),     # 0x10: if t0!=0 → 0x08
    _sw(a0, x0, 0),       # 0x14: dmem[0] = sum  (TERMINATION WRITE)
    NOP, NOP,             # 0x18-0x1C: padding
]
SUM_1_TO_5_RESULT_ADDR = 0


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

async def axi_slave(dut, mem):
    """Continuously serve AXI4-Lite icache reads from mem[]."""
    while True:
        await RisingEdge(dut.clk)
        if int(dut.ic_arvalid.value) == 1 and int(dut.ic_arready.value) == 0:
            dut.ic_arready.value = 1
        elif int(dut.ic_arready.value) == 1:
            addr = int(dut.ic_araddr.value)
            dut.ic_arready.value = 0
            idx = (addr >> 2) & 0xFF
            dut.ic_rdata.value = mem[idx] if idx < len(mem) else NOP
            dut.ic_rvalid.value = 1
        if int(dut.ic_rvalid.value) == 1:
            dut.ic_rvalid.value = 0


async def run_program(dut, prog, result_addr, dmem_init=None, timeout=50000):
    """Load prog into AXI slave; run until a write to result_addr is observed
    (true program completion) or timeout. Returns (cycles, dmem_writes, done).

    NOTE: termination is on the SW write to result_addr, NOT on pc_obs==EBREAK.
    pc_obs is the speculative IF-stage address; a branch predictor defaulting
    to not-taken would speculatively fetch EBREAK before the loop actually ends,
    causing false-positive detection.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    dut.ic_rdata.value = 0
    dut.ic_rvalid.value = 0
    dut.ic_arready.value = 0
    dut.dmem_rdata.value = 0
    dut.dmem_stall.value = 0

    dut.rst_n.value = 0
    await Timer(30, unit="ns")
    await RisingEdge(dut.clk)
    dut.rst_n.value = 1

    cocotb.start_soon(axi_slave(dut, prog))

    dmem = dict(dmem_init or {})
    dmem_writes = {}
    done = False
    cycles = 0

    for cycles in range(timeout):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")

        # Serve dmem reads
        if int(dut.dmem_re.value):
            addr = int(dut.dmem_addr.value)
            dut.dmem_rdata.value = dmem.get(addr, 0)

        # Capture dmem writes
        if int(dut.dmem_we.value):
            addr = int(dut.dmem_addr.value)
            wdata = int(dut.dmem_wdata.value)
            dmem_writes[addr] = wdata
            if addr == result_addr:
                done = True
                break  # program completed its result store

    return cycles, dmem_writes, done


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------

@cocotb.test()
async def test_nested_loop_correctness(dut):
    """10×10 nested loop must produce sum=100 stored at dmem[0]."""
    cycles, writes, ok = await run_program(
        dut, NESTED_LOOP, NESTED_LOOP_RESULT_ADDR
    )
    assert ok, f"Nested loop did not complete: no write to dmem[0] in {cycles} cycles"
    result = writes.get(0, None)
    assert result == 100, f"Nested loop: expected sum=100 at dmem[0], got {result}"
    assert cycles < 20000, f"Nested loop took too long: {cycles} cycles"
    cocotb.log.info(f"Nested loop (10×10): {cycles} cycles, sum={result}")


@cocotb.test()
async def test_load_use_before_mul(dut):
    """LW immediately followed by MUL using loaded value: 7×7=49 at dmem[4]."""
    cycles, writes, ok = await run_program(
        dut, LOAD_USE_MUL, LOAD_USE_MUL_RESULT_ADDR, dmem_init={0: 7}
    )
    assert ok, f"Load-use+MUL did not complete in {cycles} cycles"
    result = writes.get(4, None)
    assert result == 49, f"Load-use+MUL: expected 49 at dmem[4], got {result}"
    cocotb.log.info(f"Load-use+MUL: {cycles} cycles, result={result}")


@cocotb.test()
async def test_1000_iter_loop(dut):
    """1000-iteration loop must complete and verify icache warmup is effective."""
    cycles, writes, ok = await run_program(
        dut, LOOP_1000, LOOP_1000_RESULT_ADDR, timeout=100000
    )
    assert ok, f"1000-iter loop did not complete: no write to dmem[4] in {cycles} cycles"
    # After warmup, 2 instr/iteration × 1000 ≈ 2000 core cycles + ~50 fill cycles
    assert cycles < 10000, f"1000-iter loop too slow: {cycles} cycles (cache stall suspected)"
    cocotb.log.info(f"1000-iter loop: {cycles} cycles")


@cocotb.test()
async def test_fibonacci_cross_line(dut):
    """Fibonacci(10) = 55. Loop body spans two cache lines; cross-line BNE
    must redirect cleanly every iteration."""
    cycles, writes, ok = await run_program(
        dut, FIBONACCI, FIBONACCI_RESULT_ADDR
    )
    assert ok, f"Fibonacci program did not complete in {cycles} cycles"
    result = writes.get(0, None)
    assert result == 55, f"Fibonacci(10): expected 55, got {result}"
    cocotb.log.info(f"Fibonacci(10) cross-line: {cycles} cycles, result={result}")


@cocotb.test()
async def test_sum_mispred_recovery(dut):
    """Sum 1+2+3+4+5=15 via BNE loop. The first few iterations trigger branch
    mispredictions (BP not-taken vs actual taken); pipeline must recover correctly."""
    cycles, writes, ok = await run_program(
        dut, SUM_1_TO_5, SUM_1_TO_5_RESULT_ADDR
    )
    assert ok, f"Sum 1..5 program did not complete in {cycles} cycles"
    result = writes.get(0, None)
    assert result == 15, f"Sum 1..5: expected 15 at dmem[0], got {result}"
    cocotb.log.info(f"Sum 1..5 (mispred recovery): {cycles} cycles, result={result}")
