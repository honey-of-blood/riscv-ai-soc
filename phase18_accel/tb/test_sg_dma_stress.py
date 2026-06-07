"""Phase 18 stress tests — sg_dma.

Exercises 4-descriptor chains, byte_count=0 null descriptors, minimum/large
transfers, fixed-address scatter/gather, sequential runs, abort during fetch,
and IRQ-mask suppression.
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK_PERIOD = 10  # ns

DESC_ADDR = 0x00
CTRL_R    = 0x04
STATUS_R  = 0x08
IRQ_MASK  = 0x0C

ST_BUSY  = 0x1
ST_DONE  = 0x2
ST_ERROR = 0x4
CTRL_START = 0x1
CTRL_ABORT = 0x2


async def reset(dut):
    dut.rst_n.value     = 0
    dut.psel.value      = 0
    dut.penable.value   = 0
    dut.pwrite.value    = 0
    dut.paddr.value     = 0
    dut.pwdata.value    = 0
    dut.mem_rdata_i.value = 0
    dut.mem_ack_i.value = 0
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


def mem_model_coro(dut, mem: dict):
    async def _run():
        while True:
            await RisingEdge(dut.clk)
            await Timer(1, unit="ns")
            if int(dut.mem_req_o.value):
                addr = int(dut.mem_addr_o.value)
                if int(dut.mem_wr_o.value):
                    mem[addr] = int(dut.mem_wdata_o.value)
                else:
                    dut.mem_rdata_i.value = mem.get(addr, 0)
                dut.mem_ack_i.value = 1
            else:
                dut.mem_ack_i.value = 0
    return _run()


def build_desc(mem, base, src, dst, count, nxt, flags):
    mem[base + 0x00] = src
    mem[base + 0x04] = dst
    mem[base + 0x08] = count
    mem[base + 0x0C] = nxt
    mem[base + 0x10] = flags


async def wait_done(dut, timeout=500):
    for _ in range(timeout):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        st = await apb_rd(dut, STATUS_R)
        if st & ST_DONE:
            return
    assert False, "sg_dma done timeout"


async def clear_and_idle(dut):
    """Clear ctrl_start/abort and wait for FSM to return to IDLE."""
    await apb_wr(dut, CTRL_R, 0)
    await Timer(4 * CLK_PERIOD, unit="ns")


@cocotb.test()
async def test_four_descriptor_chain(dut):
    """Four chained descriptors each copying 2 words; all copies verified."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    mem = {}
    cocotb.start_soon(mem_model_coro(dut, mem))

    # Descriptor chain: 0x1000 → 0x1100 → 0x1200 → 0x1300 → end
    build_desc(mem, 0x1000, 0x2000, 0x3000, 8, 0x1100, 0b110)
    build_desc(mem, 0x1100, 0x4000, 0x5000, 8, 0x1200, 0b110)
    build_desc(mem, 0x1200, 0x6000, 0x7000, 8, 0x1300, 0b110)
    build_desc(mem, 0x1300, 0x8000, 0x9000, 8, 0x0000, 0b110)

    for base, data in [(0x2000, 0xAAAA0000), (0x4000, 0xBBBB0000),
                       (0x6000, 0xCCCC0000), (0x8000, 0xDDDD0000)]:
        mem[base]     = data | 0
        mem[base + 4] = data | 1

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)
    await wait_done(dut)

    for base, dst, expect in [
        (0x2000, 0x3000, 0xAAAA0000),
        (0x4000, 0x5000, 0xBBBB0000),
        (0x6000, 0x7000, 0xCCCC0000),
        (0x8000, 0x9000, 0xDDDD0000),
    ]:
        assert mem.get(dst)     == expect | 0
        assert mem.get(dst + 4) == expect | 1

    await clear_and_idle(dut)


@cocotb.test()
async def test_byte_count_zero(dut):
    """Null descriptor (byte_count=0) skips transfer and chains correctly."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    mem = {}
    cocotb.start_soon(mem_model_coro(dut, mem))

    # desc1: byte_count=0, chains to desc2
    build_desc(mem, 0x1000, 0x2000, 0x3000, 0, 0x1100, 0b110)
    # desc2: copies 1 word
    build_desc(mem, 0x1100, 0x4000, 0x5000, 4, 0x0000, 0b110)
    mem[0x4000] = 0xFACEFACE

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)
    await wait_done(dut)

    # dst of desc1 must NOT be written
    assert mem.get(0x3000) is None, "desc1 (byte_count=0) wrote to dst!"
    # dst of desc2 must be written
    assert mem.get(0x5000) == 0xFACEFACE, "desc2 copy failed"

    await clear_and_idle(dut)


@cocotb.test()
async def test_minimum_transfer(dut):
    """byte_count=4 (single word) copies exactly one word."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    mem = {}
    cocotb.start_soon(mem_model_coro(dut, mem))

    build_desc(mem, 0x1000, 0x2000, 0x3000, 4, 0, 0b110)
    mem[0x2000] = 0x600DC0DE

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)
    await wait_done(dut)

    assert mem.get(0x3000) == 0x600DC0DE
    # Dst+4 must NOT be written (only 1 word)
    assert mem.get(0x3004) is None, "extra word written for byte_count=4"

    await clear_and_idle(dut)


@cocotb.test()
async def test_large_transfer_32_words(dut):
    """byte_count=128 (32 words) copies all words correctly."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    mem = {}
    cocotb.start_soon(mem_model_coro(dut, mem))

    build_desc(mem, 0x1000, 0x2000, 0x3000, 128, 0, 0b110)
    for i in range(32):
        mem[0x2000 + i*4] = 0x10000000 + i

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)
    await wait_done(dut, timeout=1000)

    for i in range(32):
        got = mem.get(0x3000 + i*4)
        assert got == 0x10000000 + i, f"word[{i}]: expected {0x10000000+i:#x}, got {got:#x}"

    await clear_and_idle(dut)


@cocotb.test()
async def test_fixed_src_incrementing_dst(dut):
    """src_inc=0 (fixed source): all N destination words get the same value."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    mem = {}
    cocotb.start_soon(mem_model_coro(dut, mem))

    # flags: src_inc=0 [bit1=0], dst_inc=1 [bit2=1] → 0b100
    build_desc(mem, 0x1000, 0x2000, 0x3000, 16, 0, 0b100)
    mem[0x2000] = 0xA5A5A5A5   # source (fixed)

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)
    await wait_done(dut)

    for i in range(4):
        got = mem.get(0x3000 + i*4)
        assert got == 0xA5A5A5A5, f"dst[{i}]={got:#x} should be 0xA5A5A5A5"

    await clear_and_idle(dut)


@cocotb.test()
async def test_sequential_runs_without_reset(dut):
    """Two consecutive runs between hardware resets, results verified separately."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    mem = {}
    cocotb.start_soon(mem_model_coro(dut, mem))

    # Run 1
    build_desc(mem, 0x1000, 0x2000, 0x3000, 8, 0, 0b110)
    mem[0x2000] = 0x11111111
    mem[0x2004] = 0x22222222

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)
    await wait_done(dut)
    assert mem.get(0x3000) == 0x11111111
    assert mem.get(0x3004) == 0x22222222

    # Clear and wait for IDLE
    await clear_and_idle(dut)
    st = await apb_rd(dut, STATUS_R)
    assert not (st & ST_BUSY),  "Should not be busy after clearing start"
    assert not (st & ST_DONE),  "Done should clear after ctrl_start deasserted"

    # Run 2 with different data
    build_desc(mem, 0x1000, 0x4000, 0x5000, 8, 0, 0b110)
    mem[0x4000] = 0x33333333
    mem[0x4004] = 0x44444444

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)
    await wait_done(dut)
    assert mem.get(0x5000) == 0x33333333
    assert mem.get(0x5004) == 0x44444444

    await clear_and_idle(dut)


@cocotb.test()
async def test_abort_during_fetch_phase(dut):
    """Abort issued immediately after start hits the FETCH state."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    # No memory model — stall the DMA in FETCH (mem_ack never fires)
    dut.mem_ack_i.value = 0
    dut.mem_rdata_i.value = 0

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)

    # One or two cycles: DMA is in FETCH, waiting for ack
    await Timer(3 * CLK_PERIOD, unit="ns")

    # Abort
    await apb_wr(dut, CTRL_R, CTRL_ABORT)
    await Timer(3 * CLK_PERIOD, unit="ns")

    st = await apb_rd(dut, STATUS_R)
    assert not (st & ST_BUSY),  f"busy should be 0 after abort: {st:#x}"
    assert     (st & ST_ERROR), f"error should be 1 after abort: {st:#x}"
    assert not (st & ST_DONE),  f"done should be 0 after abort: {st:#x}"


@cocotb.test()
async def test_irq_mask_disabled(dut):
    """With irq_mask=0, irq_o stays 0 even when DMA completes."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    mem = {}
    cocotb.start_soon(mem_model_coro(dut, mem))

    # Disable IRQ mask
    await apb_wr(dut, IRQ_MASK, 0)

    build_desc(mem, 0x1000, 0x2000, 0x3000, 4, 0, 0b110)
    mem[0x2000] = 0xABCD1234

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)
    await wait_done(dut)

    assert int(dut.irq_o.value) == 0, "irq_o should be masked (0) when irq_mask=0"
    assert mem.get(0x3000) == 0xABCD1234, "transfer should still complete"

    await clear_and_idle(dut)
