"""Phase 18 — sg_dma cocotb tests."""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

CLK_PERIOD = 10  # ns

# APB register offsets
DESC_ADDR = 0x00
CTRL_R    = 0x04
STATUS_R  = 0x08
IRQ_MASK  = 0x0C

# CTRL bits
CTRL_START = 0x1
CTRL_ABORT = 0x2

# STATUS bits
ST_BUSY  = 0x1
ST_DONE  = 0x2
ST_ERROR = 0x4


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
    """Returns a coroutine that drives the memory bus from a Python dict."""
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


def build_descriptor(mem, base, src, dst, count, nxt, flags):
    """Write a 5-word descriptor into mem at base address."""
    mem[base + 0x00] = src
    mem[base + 0x04] = dst
    mem[base + 0x08] = count
    mem[base + 0x0C] = nxt
    mem[base + 0x10] = flags


async def wait_done(dut, timeout=300):
    for _ in range(timeout):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        st = await apb_rd(dut, STATUS_R)
        if st & ST_DONE:
            return
    assert False, "sg_dma done timeout"


@cocotb.test()
async def test_reset_state(dut):
    """After reset STATUS=0, irq_o=0."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)
    st = await apb_rd(dut, STATUS_R)
    assert st == 0, f"STATUS should be 0 after reset, got {st:#x}"
    assert int(dut.irq_o.value) == 0, "irq_o should be 0 after reset"
    assert int(dut.mem_req_o.value) == 0, "mem_req_o should be 0 after reset"


@cocotb.test()
async def test_single_descriptor_copy(dut):
    """Single descriptor: copy 4 words from src to dst."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    mem = {}
    cocotb.start_soon(mem_model_coro(dut, mem))

    # Build descriptor at 0x1000
    build_descriptor(mem, 0x1000,
                     src=0x2000, dst=0x3000, count=16,
                     nxt=0, flags=0b110)   # src_inc=1, dst_inc=1
    # Source data
    for i in range(4):
        mem[0x2000 + i*4] = 0xDEAD0000 + i

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)
    await wait_done(dut)

    for i in range(4):
        assert mem.get(0x3000 + i*4) == 0xDEAD0000 + i, \
            f"dst[{i}] mismatch: {mem.get(0x3000+i*4):#x}"

    await apb_wr(dut, CTRL_R, 0)  # clear start


@cocotb.test()
async def test_chain_two_descriptors(dut):
    """Two chained descriptors each copy 2 words."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    mem = {}
    cocotb.start_soon(mem_model_coro(dut, mem))

    # Descriptor 1 at 0x1000: src=0x2000, dst=0x3000, 8 bytes, next=0x1100
    build_descriptor(mem, 0x1000,
                     src=0x2000, dst=0x3000, count=8,
                     nxt=0x1100, flags=0b110)
    # Descriptor 2 at 0x1100: src=0x4000, dst=0x5000, 8 bytes, next=0
    build_descriptor(mem, 0x1100,
                     src=0x4000, dst=0x5000, count=8,
                     nxt=0, flags=0b110)
    mem[0x2000] = 0xAAAAAAAA
    mem[0x2004] = 0xBBBBBBBB
    mem[0x4000] = 0xCCCCCCCC
    mem[0x4004] = 0xDDDDDDDD

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)
    await wait_done(dut)

    assert mem.get(0x3000) == 0xAAAAAAAA
    assert mem.get(0x3004) == 0xBBBBBBBB
    assert mem.get(0x5000) == 0xCCCCCCCC
    assert mem.get(0x5004) == 0xDDDDDDDD

    await apb_wr(dut, CTRL_R, 0)


@cocotb.test()
async def test_irq_fires_when_done(dut):
    """irq_o asserts when done and irq_mask=1 (default)."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    mem = {}
    cocotb.start_soon(mem_model_coro(dut, mem))

    build_descriptor(mem, 0x1000,
                     src=0x2000, dst=0x3000, count=4,
                     nxt=0, flags=0b110)
    mem[0x2000] = 0x12345678

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)
    await wait_done(dut)

    assert int(dut.irq_o.value) == 1, "irq_o should be 1 when done"
    await apb_wr(dut, CTRL_R, 0)


@cocotb.test()
async def test_no_src_increment(dut):
    """src_inc=0: DMA reads same source address for every word."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    mem = {}
    cocotb.start_soon(mem_model_coro(dut, mem))

    # flags: src_inc=0 [bit1=0], dst_inc=1 [bit2=1] → 0b100
    build_descriptor(mem, 0x1000,
                     src=0x2000, dst=0x3000, count=8,
                     nxt=0, flags=0b100)
    mem[0x2000] = 0xFEEDFACE

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)
    await wait_done(dut)

    # Both destination words should equal the single source word
    assert mem.get(0x3000) == 0xFEEDFACE
    assert mem.get(0x3004) == 0xFEEDFACE

    await apb_wr(dut, CTRL_R, 0)


@cocotb.test()
async def test_abort(dut):
    """Writing CTRL[abort]=1 mid-transfer sets STATUS[error]."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    await reset(dut)

    mem = {}
    cocotb.start_soon(mem_model_coro(dut, mem))

    # Large transfer so there's time to abort
    build_descriptor(mem, 0x1000,
                     src=0x2000, dst=0x3000, count=64,
                     nxt=0, flags=0b110)
    for i in range(16):
        mem[0x2000 + i*4] = i

    await apb_wr(dut, DESC_ADDR, 0x1000)
    await apb_wr(dut, CTRL_R, CTRL_START)

    # Wait a few cycles then abort
    for _ in range(20):
        await RisingEdge(dut.clk)

    await apb_wr(dut, CTRL_R, CTRL_ABORT)
    await Timer(5 * CLK_PERIOD, unit="ns")

    st = await apb_rd(dut, STATUS_R)
    assert not (st & ST_BUSY),  f"DMA should not be busy after abort: {st:#x}"
    assert     (st & ST_ERROR), f"ERROR bit should be set after abort: {st:#x}"
