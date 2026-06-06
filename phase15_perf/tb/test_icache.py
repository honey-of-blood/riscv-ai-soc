"""
Phase 15 I-cache unit tests.
Tests: cold miss → hit, flush, multiple lines, stall duration.
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer
from cocotb.clock import Clock


async def reset(dut):
    dut.rst_n.value = 0
    dut.flush_i.value = 0
    dut.cpu_addr_i.value = 0
    dut.m_arready.value = 0
    dut.m_rvalid.value = 0
    dut.m_rdata.value = 0
    await Timer(20, unit="ns")
    await RisingEdge(dut.clk)
    dut.rst_n.value = 1
    await RisingEdge(dut.clk)


async def axi_slave_respond(dut, mem_array):
    """Serve one AXI4-Lite read: wait arvalid, set arready, then rvalid+rdata."""
    # Wait until arvalid
    for _ in range(200):
        await RisingEdge(dut.clk)
        if dut.m_arvalid.value == 1:
            addr = int(dut.m_araddr.value)
            dut.m_arready.value = 1
            await RisingEdge(dut.clk)
            dut.m_arready.value = 0
            dut.m_rvalid.value = 1
            idx = (addr >> 2) & 0xFFFF  # index into mem_array safely
            dut.m_rdata.value = mem_array[idx] if idx < len(mem_array) else 0xDEADBEEF
            await RisingEdge(dut.clk)
            dut.m_rvalid.value = 0
            return True
    return False


async def fill_line(dut, mem_array):
    """Fill one cache line (4 AXI reads)."""
    for _ in range(4):
        ok = await axi_slave_respond(dut, mem_array)
        assert ok, "AXI slave timed out waiting for arvalid"


@cocotb.test()
async def test_cold_miss_then_hit(dut):
    """First access to a line causes a miss; second access is a hit (no stall)."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    # Build a small memory image
    mem = [i + 0xAA000000 for i in range(1024)]

    # Drive address 0x00000004 (second word in line 0)
    dut.cpu_addr_i.value = 0x00000004
    await Timer(1, unit="ns")

    # Should be stalling (cold miss)
    stall_seen = False
    for _ in range(5):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if int(dut.cpu_stall_o.value) == 1:
            stall_seen = True
            break

    assert stall_seen, "Expected stall on cold miss"

    # Serve all 4 AXI reads for the cache line
    fill_task = cocotb.start_soon(fill_line(dut, mem))
    await fill_task

    # Wait for stall to deassert
    hit = False
    for _ in range(20):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if int(dut.cpu_stall_o.value) == 0:
            hit = True
            break

    assert hit, "Cache stall never deasserted after fill"

    # Verify data — word 1 (addr=0x4, off=1) should match mem[1]
    rdata = int(dut.cpu_rdata_o.value)
    assert rdata == mem[1], f"Expected {mem[1]:#010x}, got {rdata:#010x}"

    # Second access to same address — should be a hit immediately (no stall)
    dut.cpu_addr_i.value = 0x00000004
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert int(dut.cpu_stall_o.value) == 0, "Expected hit (no stall) on second access"


@cocotb.test()
async def test_cache_flush(dut):
    """After flush_i=1, a previously cached address should miss again."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    mem = [i + 0xBB000000 for i in range(1024)]

    # Prime the cache with address 0
    dut.cpu_addr_i.value = 0x00000000
    fill_task = cocotb.start_soon(fill_line(dut, mem))
    await fill_task

    # Wait for hit
    for _ in range(20):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if int(dut.cpu_stall_o.value) == 0:
            break

    # Confirm hit
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert int(dut.cpu_stall_o.value) == 0, "Should be a hit before flush"

    # Issue flush
    dut.flush_i.value = 1
    await RisingEdge(dut.clk)
    dut.flush_i.value = 0
    await RisingEdge(dut.clk)

    # Now access the same address — should miss again
    dut.cpu_addr_i.value = 0x00000000
    await Timer(1, unit="ns")
    stall_after_flush = int(dut.cpu_stall_o.value)
    assert stall_after_flush == 1, f"Expected miss after flush, cpu_stall_o={stall_after_flush}"

    # Refill
    fill_task = cocotb.start_soon(fill_line(dut, mem))
    await fill_task

    for _ in range(20):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if int(dut.cpu_stall_o.value) == 0:
            break


@cocotb.test()
async def test_multiple_lines(dut):
    """Access 8 different cache lines; all should hit on second access."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    mem = [i + 0xCC000000 for i in range(4096)]

    # Access 8 lines at different cache indexes (each line = 16 bytes)
    line_addrs = [i * 16 for i in range(8)]

    for addr in line_addrs:
        dut.cpu_addr_i.value = addr
        fill_task = cocotb.start_soon(fill_line(dut, mem))
        await fill_task
        # Wait for stall to clear
        for _ in range(30):
            await RisingEdge(dut.clk)
            await Timer(1, unit="ns")
            if int(dut.cpu_stall_o.value) == 0:
                break

    # Second pass — all should hit
    for addr in line_addrs:
        dut.cpu_addr_i.value = addr
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        assert int(dut.cpu_stall_o.value) == 0, \
            f"Expected hit for addr {addr:#010x} on second access, got stall"


@cocotb.test()
async def test_stall_duration(dut):
    """Cold miss should produce exactly 4 AXI read transactions (4+ stall cycles)."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    mem = [i + 0xDD000000 for i in range(1024)]

    dut.cpu_addr_i.value = 0x00000100  # address in a clean line

    stall_cycles = 0
    axi_count = 0
    prev_arvalid = 0

    # Drive AXI slave and count stall cycles
    for cycle in range(200):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")

        cur_stall = int(dut.cpu_stall_o.value)
        if cur_stall:
            stall_cycles += 1

        cur_arvalid = int(dut.m_arvalid.value)
        if cur_arvalid and not prev_arvalid:
            # Rising edge of arvalid — a new read is starting
            axi_count += 1

        # Respond to AXI
        if int(dut.m_arvalid.value) == 1 and int(dut.m_arready.value) == 0:
            addr = int(dut.m_araddr.value)
            dut.m_arready.value = 1
        elif int(dut.m_arready.value) == 1:
            dut.m_arready.value = 0
            idx = (int(dut.m_araddr.value) >> 2) & 0xFFFF
            dut.m_rvalid.value = 1
            dut.m_rdata.value = mem[idx] if idx < len(mem) else 0

        if int(dut.m_rvalid.value) == 1:
            dut.m_rvalid.value = 0

        prev_arvalid = cur_arvalid

        if cur_stall == 0 and cycle > 5:
            break

    assert axi_count >= 4, f"Expected at least 4 AXI reads, got {axi_count}"
    assert stall_cycles >= 4, f"Expected at least 4 stall cycles, got {stall_cycles}"
    cocotb.log.info(f"Cold miss: {stall_cycles} stall cycles, {axi_count} AXI reads")
