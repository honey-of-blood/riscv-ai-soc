"""
Phase 15 I-cache stress tests — hidden corner cases and edge conditions.

Coverage beyond test_icache.py:
  - AXI backpressure (arready delayed 3 cycles per word)
  - Set conflict / tag eviction (same set index, different tag)
  - All 4 word offsets return correct data after fill
  - flush_i during active FILL (abort + clean re-fill)
  - 16 consecutive unique set fills (no deadlock)
  - High-address tag extraction (addr[31:12] > 0)
  - No stall on warm cache (100 consecutive hits)
  - rvalid latency (arready immediate, rvalid arrives 3 cycles later)
  - Boundary address: last word of a line, first word of next line
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


def mem_data(addr, base=0xAB000000):
    """Deterministic word value for a given byte address."""
    return (base + (addr >> 2)) & 0xFFFFFFFF


async def axi_respond_normal(dut, addr):
    """Respond to one AXI read with immediate arready, immediate rvalid."""
    dut.m_arready.value = 1
    await RisingEdge(dut.clk)
    dut.m_arready.value = 0
    dut.m_rdata.value = mem_data(addr)
    dut.m_rvalid.value = 1
    await RisingEdge(dut.clk)
    dut.m_rvalid.value = 0


async def axi_respond_backpressure(dut, addr, delay=3):
    """Respond to one AXI read with arready delayed by `delay` cycles."""
    for _ in range(delay):
        await RisingEdge(dut.clk)
    dut.m_arready.value = 1
    await RisingEdge(dut.clk)
    dut.m_arready.value = 0
    dut.m_rdata.value = mem_data(addr)
    dut.m_rvalid.value = 1
    await RisingEdge(dut.clk)
    dut.m_rvalid.value = 0


async def axi_respond_rvalid_late(dut, addr, rdelay=3):
    """Respond to one AXI read: arready immediate, rvalid arrives `rdelay` cycles later."""
    dut.m_arready.value = 1
    await RisingEdge(dut.clk)
    dut.m_arready.value = 0
    for _ in range(rdelay):
        await RisingEdge(dut.clk)
    dut.m_rdata.value = mem_data(addr)
    dut.m_rvalid.value = 1
    await RisingEdge(dut.clk)
    dut.m_rvalid.value = 0


async def wait_for_arvalid(dut, timeout=300):
    """Wait until m_arvalid=1, return captured address."""
    for _ in range(timeout):
        await RisingEdge(dut.clk)
        if int(dut.m_arvalid.value) == 1:
            return int(dut.m_araddr.value)
    raise AssertionError("Timed out waiting for m_arvalid")


async def fill_line_normal(dut, base_addr):
    """Fill one 4-word cache line with normal (no backpressure) AXI responses."""
    for _ in range(4):
        addr = await wait_for_arvalid(dut)
        await axi_respond_normal(dut, addr)


async def fill_line_backpressure(dut, base_addr, delay=3):
    """Fill one 4-word cache line with backpressure on every arready."""
    for _ in range(4):
        addr = await wait_for_arvalid(dut)
        await axi_respond_backpressure(dut, addr, delay=delay)


async def wait_for_hit(dut, timeout=500):
    """Wait until cpu_stall_o deasserts."""
    for _ in range(timeout):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if int(dut.cpu_stall_o.value) == 0:
            return True
    return False


@cocotb.test()
async def test_axi_backpressure(dut):
    """Cache fills correctly when arready is delayed 3 cycles per word."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    target_addr = 0x00000008  # word offset 2 in line 0
    dut.cpu_addr_i.value = target_addr
    await Timer(1, unit="ns")

    assert int(dut.cpu_stall_o.value) == 1, "Expected stall on cold miss"

    fill_task = cocotb.start_soon(fill_line_backpressure(dut, 0x00000000, delay=3))
    await fill_task

    ok = await wait_for_hit(dut)
    assert ok, "Cache never came out of stall after backpressure fill"

    rdata = int(dut.cpu_rdata_o.value)
    expected = mem_data(target_addr)
    assert rdata == expected, f"Backpressure fill: rdata={rdata:#010x} expected={expected:#010x}"

    # Second access should be a hit
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert int(dut.cpu_stall_o.value) == 0, "Expected hit on repeated access after backpressure fill"


@cocotb.test()
async def test_set_conflict_eviction(dut):
    """Two addresses in the same cache set (same index, different tag) cause eviction.
    After evicting line A with line B, re-accessing A should miss again.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    # Cache index = addr[11:4]; tag = addr[31:12]
    # Line A: addr=0x00000000, index=0, tag=0x00000
    # Line B: addr=0x00001000, index=0, tag=0x00001  (same index, different tag)
    addr_a = 0x00000000
    addr_b = 0x00001000

    # Step 1: Fill line A
    dut.cpu_addr_i.value = addr_a
    fill_task = cocotb.start_soon(fill_line_normal(dut, addr_a))
    await fill_task
    ok = await wait_for_hit(dut)
    assert ok, "Line A fill never completed"

    # Confirm A is a hit
    dut.cpu_addr_i.value = addr_a
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert int(dut.cpu_stall_o.value) == 0, "Line A should be a hit"
    rdata_a = int(dut.cpu_rdata_o.value)
    assert rdata_a == mem_data(addr_a), f"Line A data wrong: {rdata_a:#010x}"

    # Step 2: Fill line B (evicts line A from set 0)
    dut.cpu_addr_i.value = addr_b
    await Timer(1, unit="ns")
    assert int(dut.cpu_stall_o.value) == 1, "Line B should miss (cold)"

    fill_task = cocotb.start_soon(fill_line_normal(dut, addr_b))
    await fill_task
    ok = await wait_for_hit(dut)
    assert ok, "Line B fill never completed"

    # Confirm B is a hit
    dut.cpu_addr_i.value = addr_b
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert int(dut.cpu_stall_o.value) == 0, "Line B should be a hit after fill"

    # Step 3: Re-access A — should be a miss (evicted)
    dut.cpu_addr_i.value = addr_a
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert int(dut.cpu_stall_o.value) == 1, "Line A should miss after eviction by line B"


@cocotb.test()
async def test_all_4_word_offsets(dut):
    """Fill a cache line and read all 4 word offsets; each must return correct data.
    Uses line 0 (addr 0x000-0x00C) so the fill triggered by reset is reused."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    # After reset cpu_addr_i=0 so the cache immediately starts filling line 0.
    # Keep cpu_addr_i=0 so req_idx/req_tag remain stable during fill.
    base = 0x00000000
    dut.cpu_addr_i.value = base

    # Serve the fill that was already triggered by post-reset miss on addr 0
    fill_task = cocotb.start_soon(fill_line_normal(dut, base))
    await fill_task
    ok = await wait_for_hit(dut)
    assert ok, "Fill never completed"

    # Read each of the 4 word offsets
    for off in range(4):
        addr = base + off * 4
        dut.cpu_addr_i.value = addr
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        assert int(dut.cpu_stall_o.value) == 0, f"Expected hit for offset {off}, got stall"
        rdata = int(dut.cpu_rdata_o.value)
        expected = mem_data(addr)
        assert rdata == expected, \
            f"Offset {off}: expected {expected:#010x}, got {rdata:#010x}"


@cocotb.test()
async def test_flush_during_fill(dut):
    """Assert flush_i after 2 words received in FILL state. Cache must
    cleanly abort, return to LOOKUP, then re-fill correctly on next access."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    target_addr = 0x00000300
    dut.cpu_addr_i.value = target_addr
    await Timer(1, unit="ns")
    assert int(dut.cpu_stall_o.value) == 1, "Should stall on cold miss"

    # Serve first 2 AXI words normally, then assert flush mid-fill
    for i in range(2):
        addr = await wait_for_arvalid(dut)
        await axi_respond_normal(dut, addr)

    # Flush while still in FILL (after 2 words, before 3rd arvalid)
    await RisingEdge(dut.clk)
    dut.flush_i.value = 1
    await RisingEdge(dut.clk)
    dut.flush_i.value = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    # After flush the cache is back in LOOKUP with valid[] cleared
    # The line is not complete so access must miss again
    stall = int(dut.cpu_stall_o.value)
    assert stall == 1, f"Expected miss after flush-during-fill, got stall={stall}"

    # Now serve a fresh complete fill
    fill_task = cocotb.start_soon(fill_line_normal(dut, target_addr))
    await fill_task
    ok = await wait_for_hit(dut)
    assert ok, "Re-fill after flush-during-fill never completed"

    # Verify data is correct
    rdata = int(dut.cpu_rdata_o.value)
    expected = mem_data(target_addr)
    assert rdata == expected, f"Post-flush-refill: {rdata:#010x} != {expected:#010x}"


@cocotb.test()
async def test_16_consecutive_sets(dut):
    """Fill 16 unique cache lines (all different sets); verify no deadlock
    and all hit on second access."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    # Each line is 16 bytes; 16 lines × 16 bytes = 256 bytes, indices 0..15
    line_addrs = [i * 16 for i in range(16)]

    for addr in line_addrs:
        dut.cpu_addr_i.value = addr
        await Timer(1, unit="ns")
        fill_task = cocotb.start_soon(fill_line_normal(dut, addr))
        await fill_task
        ok = await wait_for_hit(dut)
        assert ok, f"Fill never completed for addr {addr:#010x}"

    # Second pass — all must be hits
    for addr in line_addrs:
        dut.cpu_addr_i.value = addr
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        assert int(dut.cpu_stall_o.value) == 0, \
            f"Expected hit on second access to {addr:#010x}"
        rdata = int(dut.cpu_rdata_o.value)
        assert rdata == mem_data(addr), \
            f"Data mismatch at {addr:#010x}: {rdata:#010x} vs {mem_data(addr):#010x}"


@cocotb.test()
async def test_high_address_tag(dut):
    """Access address with tag = 0xFFF00 (high bits set) — verify correct
    tag extraction and fill."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    # addr = 0xFFF00010: tag=0xFFF00, index=1, word_off=0
    target_addr = 0xFFF00010
    dut.cpu_addr_i.value = target_addr
    await Timer(1, unit="ns")
    assert int(dut.cpu_stall_o.value) == 1, "Should stall on cold miss for high address"

    fill_task = cocotb.start_soon(fill_line_normal(dut, target_addr))
    await fill_task
    ok = await wait_for_hit(dut)
    assert ok, "Fill never completed for high address"

    # Confirm it's a hit now
    dut.cpu_addr_i.value = target_addr
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert int(dut.cpu_stall_o.value) == 0, "Expected hit for high-address line on second access"

    # Verify tag uniqueness: 0x00000010 (same index, different tag) should miss
    low_addr = 0x00000010
    dut.cpu_addr_i.value = low_addr
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert int(dut.cpu_stall_o.value) == 1, \
        "Low-tag address should miss even though index matches high-tag line"


@cocotb.test()
async def test_no_stall_warm_cache(dut):
    """After warming up 4 cache lines, 100 consecutive reads to those lines
    must never assert cpu_stall_o."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    warm_addrs = [i * 16 for i in range(4)]  # 4 unique lines

    # Warm up
    for addr in warm_addrs:
        dut.cpu_addr_i.value = addr
        fill_task = cocotb.start_soon(fill_line_normal(dut, addr))
        await fill_task
        ok = await wait_for_hit(dut)
        assert ok, f"Warm-up fill failed for {addr:#010x}"

    # 100 random hits across those 4 lines (simple round-robin)
    stall_count = 0
    addrs = warm_addrs * 25  # 100 accesses
    for addr in addrs:
        dut.cpu_addr_i.value = addr
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if int(dut.cpu_stall_o.value) == 1:
            stall_count += 1

    assert stall_count == 0, f"Warm cache produced {stall_count} unexpected stall cycles"


@cocotb.test()
async def test_rvalid_latency(dut):
    """arready is immediate but rvalid arrives 3 cycles later. Cache must wait
    and capture correct data. Uses line 0 (addr 0) so reset fill is reused."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    # Keep cpu_addr_i=0 (same as reset default) so the post-reset fill uses
    # correct req_idx/req_tag and we can validate the rdata.
    target_addr = 0x00000000
    dut.cpu_addr_i.value = target_addr
    await Timer(1, unit="ns")
    assert int(dut.cpu_stall_o.value) == 1, "Should stall on cold miss"

    # Serve 4 words with late rvalid (arready immediate, rvalid arrives 3 cycles later)
    for _ in range(4):
        addr = await wait_for_arvalid(dut)
        await axi_respond_rvalid_late(dut, addr, rdelay=3)

    ok = await wait_for_hit(dut)
    assert ok, "Cache never came out of stall with late-rvalid pattern"

    rdata = int(dut.cpu_rdata_o.value)
    expected = mem_data(target_addr)
    assert rdata == expected, f"Late-rvalid fill: {rdata:#010x} != {expected:#010x}"


@cocotb.test()
async def test_boundary_addresses(dut):
    """Access the last word of one line and the first word of the next line;
    both should be served from different cache lines."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    # Line 0: 0x00 - 0x0F  (index=0)
    # Line 1: 0x10 - 0x1F  (index=1)
    last_word_line0  = 0x0000000C  # word offset 3 of line 0
    first_word_line1 = 0x00000010  # word offset 0 of line 1

    # Access last word of line 0
    dut.cpu_addr_i.value = last_word_line0
    fill_task = cocotb.start_soon(fill_line_normal(dut, 0x00000000))
    await fill_task
    ok = await wait_for_hit(dut)
    assert ok, "Line 0 fill failed"
    rdata = int(dut.cpu_rdata_o.value)
    assert rdata == mem_data(last_word_line0), \
        f"Last word line 0: {rdata:#010x} != {mem_data(last_word_line0):#010x}"

    # Access first word of line 1 — should trigger a new miss
    dut.cpu_addr_i.value = first_word_line1
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert int(dut.cpu_stall_o.value) == 1, "First word of line 1 should miss"

    fill_task = cocotb.start_soon(fill_line_normal(dut, 0x00000010))
    await fill_task
    ok = await wait_for_hit(dut)
    assert ok, "Line 1 fill failed"
    rdata = int(dut.cpu_rdata_o.value)
    assert rdata == mem_data(first_word_line1), \
        f"First word line 1: {rdata:#010x} != {mem_data(first_word_line1):#010x}"
