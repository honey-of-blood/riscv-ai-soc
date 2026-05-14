"""Unit tests for cache_data_array.sv."""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer


async def write_word(dut, idx, word, data, be=0xF):
    dut.we_i.value    = 1
    dut.idx_i.value   = idx
    dut.word_i.value  = word
    dut.wdata_i.value = data
    dut.be_i.value    = be
    await RisingEdge(dut.clk)
    dut.we_i.value = 0
    await Timer(1, unit="ns")


def read_word(dut, word):
    sigs = [dut.word0_o, dut.word1_o, dut.word2_o, dut.word3_o]
    return int(sigs[word].value)


@cocotb.test()
async def test_write_read_all_words(dut):
    """Write all 4 words of a cache line and read them back."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    dut.we_i.value = 0
    await RisingEdge(dut.clk)

    values = [0xDEADBEEF, 0xCAFEBABE, 0x12345678, 0xABCD0000]
    for w, v in enumerate(values):
        await write_word(dut, idx=7, word=w, data=v)

    dut.idx_i.value = 7
    await Timer(1, unit="ns")

    for w, v in enumerate(values):
        got = read_word(dut, w)
        assert got == v, f"word{w}: expected 0x{v:08X}, got 0x{got:08X}"

    dut._log.info("PASS: all 4 words of cache line written/read correctly")


@cocotb.test()
async def test_byte_enable_write(dut):
    """Byte enables: only specified bytes should be updated."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    dut.we_i.value = 0
    await RisingEdge(dut.clk)

    # Write 0xFFFFFFFF to word 0 of set 3
    await write_word(dut, idx=3, word=0, data=0xFFFFFFFF, be=0xF)

    # Overwrite only byte 0 with 0x42 (be=0001)
    await write_word(dut, idx=3, word=0, data=0x00000042, be=0x1)

    dut.idx_i.value = 3
    await Timer(1, unit="ns")
    got = read_word(dut, 0)
    assert got == 0xFFFFFF42, f"BE write: expected 0xFFFFFF42, got 0x{got:08X}"

    # Overwrite bytes 2-3 with 0x1234
    await write_word(dut, idx=3, word=0, data=0x12340000, be=0xC)  # be=1100 → bytes 2,3
    dut.idx_i.value = 3
    await Timer(1, unit="ns")
    got = read_word(dut, 0)
    assert got == 0x1234FF42, f"BE write (high): expected 0x1234FF42, got 0x{got:08X}"

    dut._log.info("PASS: byte enable writes correct")


@cocotb.test()
async def test_independent_sets(dut):
    """Writing to set N must not affect set M."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    dut.we_i.value = 0
    await RisingEdge(dut.clk)

    await write_word(dut, idx=0,  word=2, data=0x11111111)
    await write_word(dut, idx=63, word=2, data=0x22222222)

    dut.idx_i.value = 0
    await Timer(1, unit="ns")
    assert read_word(dut, 2) == 0x11111111, "set 0 word 2 corrupted"

    dut.idx_i.value = 63
    await Timer(1, unit="ns")
    assert read_word(dut, 2) == 0x22222222, "set 63 word 2 wrong"

    dut._log.info("PASS: independent sets do not interfere")
