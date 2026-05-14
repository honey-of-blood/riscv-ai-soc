"""Unit tests for cache_tag_array.sv."""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer


async def reset_dut(dut):
    dut.rst.value   = 1
    dut.we_i.value  = 0
    dut.idx_i.value = 0
    dut.tag_i.value = 0
    dut.valid_i.value = 0
    dut.dirty_i.value = 0
    await RisingEdge(dut.clk)
    dut.rst.value = 0
    await Timer(1, unit="ns")


@cocotb.test()
async def test_reset_clears_valid(dut):
    """After reset all valid bits must be 0."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    for idx in range(64):
        dut.idx_i.value = idx
        await Timer(1, unit="ns")
        assert int(dut.valid_o.value) == 0, f"idx {idx}: valid should be 0 after reset"

    dut._log.info("PASS: all 64 valid bits cleared by reset")


@cocotb.test()
async def test_write_read_tag(dut):
    """Write a tag entry and read it back from a different index."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    # Write to index 5: tag=0x1ABCDE, valid=1, dirty=0
    dut.we_i.value    = 1
    dut.idx_i.value   = 5
    dut.tag_i.value   = 0x1ABCDE
    dut.valid_i.value = 1
    dut.dirty_i.value = 0
    await RisingEdge(dut.clk)
    dut.we_i.value = 0
    await Timer(1, unit="ns")

    dut.idx_i.value = 5
    await Timer(1, unit="ns")
    assert int(dut.tag_o.value)   == 0x1ABCDE, f"tag mismatch: got 0x{int(dut.tag_o.value):06X}"
    assert int(dut.valid_o.value) == 1,         "valid should be 1"
    assert int(dut.dirty_o.value) == 0,         "dirty should be 0"

    dut._log.info("PASS: tag write/read correct")


@cocotb.test()
async def test_dirty_bit(dut):
    """Write dirty=1, read it back, then overwrite with dirty=0."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    dut.we_i.value    = 1
    dut.idx_i.value   = 10
    dut.tag_i.value   = 0x3FFFFF
    dut.valid_i.value = 1
    dut.dirty_i.value = 1
    await RisingEdge(dut.clk)
    dut.we_i.value = 0
    await Timer(1, unit="ns")

    dut.idx_i.value = 10
    await Timer(1, unit="ns")
    assert int(dut.dirty_o.value) == 1, "dirty should be 1"

    # Overwrite same index with dirty=0
    dut.we_i.value    = 1
    dut.dirty_i.value = 0
    await RisingEdge(dut.clk)
    dut.we_i.value = 0
    await Timer(1, unit="ns")

    assert int(dut.dirty_o.value) == 0, "dirty should be 0 after overwrite"
    dut._log.info("PASS: dirty bit write/overwrite correct")


@cocotb.test()
async def test_independent_entries(dut):
    """Writing one index must not affect a different index."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset_dut(dut)

    # Write index 0
    dut.we_i.value    = 1
    dut.idx_i.value   = 0
    dut.tag_i.value   = 0x2ABBCC
    dut.valid_i.value = 1
    dut.dirty_i.value = 0
    await RisingEdge(dut.clk)

    # Write index 63
    dut.idx_i.value   = 63
    dut.tag_i.value   = 0x112233
    dut.dirty_i.value = 1
    await RisingEdge(dut.clk)
    dut.we_i.value = 0

    # Check index 0 is unchanged
    dut.idx_i.value = 0
    await Timer(1, unit="ns")
    assert int(dut.tag_o.value)   == 0x2ABBCC, "index 0 tag corrupted"
    assert int(dut.dirty_o.value) == 0,         "index 0 dirty corrupted"

    # Check index 63
    dut.idx_i.value = 63
    await Timer(1, unit="ns")
    assert int(dut.tag_o.value)   == 0x112233, "index 63 tag wrong"
    assert int(dut.dirty_o.value) == 1,         "index 63 dirty wrong"

    dut._log.info("PASS: independent entries do not interfere")
