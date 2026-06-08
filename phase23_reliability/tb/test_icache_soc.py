"""test_icache_soc.py — Phase 23.1: icache module connectivity tests.

Tests:
  test_icache_miss_stall      — stall asserted on first fetch to new line
  test_icache_hit_no_stall    — second fetch to same line: no stall
  test_icache_4beat_fill      — 4 consecutive words filled in one miss
  test_icache_flush           — flush_i invalidates all lines
  test_icache_stall_wired     — icache stall_o == 0 after hit (icache_stall_i port test)

DUT: icache
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer


async def reset_ic(dut):
    dut.rst_n.value    = 0
    dut.flush_i.value  = 0
    dut.cpu_addr_i.value = 0
    dut.m_arready.value = 0
    dut.m_rvalid.value  = 0
    dut.m_rdata.value   = 0
    await Timer(20, unit="ns")
    dut.rst_n.value = 1
    await Timer(10, unit="ns")


async def serve_refill(dut, words):
    """Reply to one icache AXI request with `words` (list of 4 ints)."""
    # Wait for arvalid
    for _ in range(100):
        await RisingEdge(dut.clk)
        if dut.m_arvalid.value:
            break
    dut.m_arready.value = 1
    await RisingEdge(dut.clk)
    dut.m_arready.value = 0

    for w in words:
        dut.m_rdata.value  = w
        dut.m_rvalid.value = 1
        await RisingEdge(dut.clk)
        while not dut.m_rready.value:
            await RisingEdge(dut.clk)
    dut.m_rvalid.value = 0


@cocotb.test()
async def test_icache_miss_stall(dut):
    """stall_o asserted during miss until fill completes."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_ic(dut)

    dut.cpu_addr_i.value = 0x1000

    # Stall must be asserted immediately (miss on empty cache)
    await Timer(1, unit="ns")
    assert dut.cpu_stall_o.value, "stall not asserted on cold miss"

    # Serve refill
    words = [0x11111111, 0x22222222, 0x33333333, 0x44444444]
    cocotb.start_soon(serve_refill(dut, words))

    # Wait for stall to clear
    for _ in range(50):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if not dut.cpu_stall_o.value:
            break
    else:
        raise AssertionError("stall never cleared after refill")

    assert int(dut.cpu_rdata_o.value) == words[0], \
        f"wrong rdata: 0x{int(dut.cpu_rdata_o.value):08x}"


@cocotb.test()
async def test_icache_hit_no_stall(dut):
    """Second access to the same cache line: stall_o must be 0."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_ic(dut)

    words = [0xAAAA1111, 0xAAAA2222, 0xAAAA3333, 0xAAAA4444]
    dut.cpu_addr_i.value = 0x2000
    cocotb.start_soon(serve_refill(dut, words))

    # Wait for first miss to resolve
    for _ in range(50):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if not dut.cpu_stall_o.value:
            break
    else:
        raise AssertionError("first miss never resolved")

    # Now read word[0] again — must hit immediately
    dut.cpu_addr_i.value = 0x2000
    await Timer(1, unit="ns")
    assert not dut.cpu_stall_o.value, "stall asserted on cache hit"
    assert int(dut.cpu_rdata_o.value) == words[0]


@cocotb.test()
async def test_icache_4beat_fill(dut):
    """All 4 words of a cache line are accessible after one miss."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_ic(dut)

    base = 0x3000
    words = [0xBEEF0000, 0xBEEF0001, 0xBEEF0002, 0xBEEF0003]

    dut.cpu_addr_i.value = base
    cocotb.start_soon(serve_refill(dut, words))

    for _ in range(50):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if not dut.cpu_stall_o.value:
            break

    # Read each word in the line
    for i, exp in enumerate(words):
        dut.cpu_addr_i.value = base + i * 4
        await Timer(1, unit="ns")
        assert not dut.cpu_stall_o.value, f"stall on hit for word {i}"
        got = int(dut.cpu_rdata_o.value)
        assert got == exp, f"word {i}: got 0x{got:08x} expected 0x{exp:08x}"
        await RisingEdge(dut.clk)


@cocotb.test()
async def test_icache_flush(dut):
    """flush_i invalidates all lines; next access must miss again."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_ic(dut)

    words = [0xCAFE0001, 0xCAFE0002, 0xCAFE0003, 0xCAFE0004]
    dut.cpu_addr_i.value = 0x4000
    cocotb.start_soon(serve_refill(dut, words))

    for _ in range(50):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if not dut.cpu_stall_o.value:
            break

    # Assert flush
    dut.flush_i.value = 1
    await RisingEdge(dut.clk)
    dut.flush_i.value = 0

    # Cache must be invalid now — stall should re-assert
    dut.cpu_addr_i.value = 0x4000
    await Timer(1, unit="ns")
    assert dut.cpu_stall_o.value, "stall not re-asserted after flush"


@cocotb.test()
async def test_icache_stall_wired(dut):
    """After hit, cpu_stall_o=0. This models the soc_top icache_stall_i connection."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_ic(dut)

    words = [0x13572468] * 4
    dut.cpu_addr_i.value = 0x5000
    cocotb.start_soon(serve_refill(dut, words))

    for _ in range(50):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if not dut.cpu_stall_o.value:
            break

    # cpu_stall_o drives icache_stall_i in soc_top; must be 0 on hit
    stall_val = int(dut.cpu_stall_o.value)
    assert stall_val == 0, f"icache_stall_i would be {stall_val} on hit — wiring incorrect"
