"""
Phase 15 integration performance test using perf_wrap.
Runs a tight loop through the I-cache and measures cycle count.

Program (assembled, starting at address 0):
  0x000: ADDI t0, x0, 100    (0x06400293)  ; t0 = 100
  0x004: ADDI t0, t0, -1     (0xFFF28293)  ; t0--           <- loop target
  0x008: BNE  t0, x0, -4     (0xFE029EE3)  ; if t0 != 0 goto 0x004
  0x00C: EBREAK              (0x00100073)  ; halt
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer
from cocotb.clock import Clock


# Instruction memory: word-indexed
IMEM = [
    0x06400293,  # 0x000: ADDI t0, x0, 100
    0xFFF28293,  # 0x004: ADDI t0, t0, -1
    0xFE029EE3,  # 0x008: BNE t0, x0, -4
    0x00100073,  # 0x00C: EBREAK
]

EBREAK_ADDR = 0x0000000C


async def axi_slave(dut, mem):
    """Continuously serve AXI4-Lite read requests from mem."""
    while True:
        await RisingEdge(dut.clk)
        if int(dut.ic_arvalid.value) == 1 and int(dut.ic_arready.value) == 0:
            addr = int(dut.ic_araddr.value)
            dut.ic_arready.value = 1
        elif int(dut.ic_arready.value) == 1:
            addr = int(dut.ic_araddr.value)
            dut.ic_arready.value = 0
            idx = (addr >> 2) & 0xFF
            data = mem[idx] if idx < len(mem) else 0x00000013  # NOP
            dut.ic_rdata.value = data
            dut.ic_rvalid.value = 1

        if int(dut.ic_rvalid.value) == 1:
            dut.ic_rvalid.value = 0


@cocotb.test()
async def test_loop_benchmark(dut):
    """Run a 100-iteration loop and verify it completes in reasonable time."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())

    # Initialize
    dut.ic_rdata.value = 0
    dut.ic_rvalid.value = 0
    dut.ic_arready.value = 0
    dut.dmem_rdata.value = 0
    dut.dmem_stall.value = 0

    # Reset
    dut.rst_n.value = 0
    await Timer(30, unit="ns")
    await RisingEdge(dut.clk)
    dut.rst_n.value = 1

    # Start AXI slave in background
    cocotb.start_soon(axi_slave(dut, IMEM))

    # Run until EBREAK or timeout
    cycles = 0
    max_cycles = 5000
    ebreak_seen = False

    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    while cycles < max_cycles:
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        cycles += 1

        pc = int(dut.pc_obs.value)
        if pc == EBREAK_ADDR:
            # Give pipeline a few more cycles to reach EBREAK in EX
            for _ in range(5):
                await RisingEdge(dut.clk)
            ebreak_seen = True
            break

    assert ebreak_seen, f"Program did not reach EBREAK within {max_cycles} cycles (last PC={pc:#010x})"
    cocotb.log.info(f"Loop completed in {cycles} cycles")

    # After cache warmup (first pass ~4 AXI reads per line × number of lines),
    # the loop body (3 instructions in 1 cache line) should be cached.
    # With 100 iterations and ~3 pipeline stages, expect << 2000 cycles.
    assert cycles < 3000, f"Too many cycles: {cycles} (possible cache issue)"


@cocotb.test()
async def test_no_stores(dut):
    """Verify dmem_we is never asserted during the loop program."""
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

    cocotb.start_soon(axi_slave(dut, IMEM))

    max_cycles = 5000
    store_seen = False
    ebreak_seen = False

    await RisingEdge(dut.clk)

    for _ in range(max_cycles):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")

        if int(dut.dmem_we.value) == 1:
            store_seen = True

        pc = int(dut.pc_obs.value)
        if pc == EBREAK_ADDR:
            ebreak_seen = True
            break

    assert ebreak_seen, "Program did not reach EBREAK"
    assert not store_seen, "Unexpected store (dmem_we=1) during loop program"
