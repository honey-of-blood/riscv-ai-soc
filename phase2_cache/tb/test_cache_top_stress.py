"""
L1 data cache stress tests — corner cases NOT covered by test_cache_top.py.

Gaps targeted:
  - Consecutive dirty evictions (fill 4 sets, alias all 4 with different tags)
  - Interleaved read/write misses to different sets
  - Read-modify-write: LW + SW to same address
  - Byte-enable partial write followed by dirty eviction
  - Aliasing: same cache index, 3 different tags (2 evictions)
  - Back-to-back write misses (4 × write miss in different sets)
  - Read after dirty eviction (evicted data readable from backing memory)
  - Byte-enable merge: 4 individual byte writes produce correct word
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer


# ── AXI4 memory model (identical to test_cache_top.py) ────────────────────
class AXI4Memory:
    def __init__(self, dut):
        self.dut = dut
        self.mem = {}
        self._running = False

    def preload(self, byte_addr, value):
        self.mem[byte_addr >> 2] = value & 0xFFFF_FFFF

    def read(self, byte_addr):
        return self.mem.get(byte_addr >> 2, 0)

    async def run(self):
        self._running = True
        dut = self.dut
        dut.m_axi_awready_i.value = 0
        dut.m_axi_wready_i.value  = 0
        dut.m_axi_bvalid_i.value  = 0
        dut.m_axi_arready_i.value = 0
        dut.m_axi_rvalid_i.value  = 0
        dut.m_axi_rdata_i.value   = 0
        dut.m_axi_rlast_i.value   = 0

        while self._running:
            await RisingEdge(dut.clk)
            await Timer(1, unit="ns")

            if int(dut.m_axi_awvalid_o.value):
                aw_addr = int(dut.m_axi_awaddr_o.value)
                aw_len  = int(dut.m_axi_awlen_o.value)
                dut.m_axi_awready_i.value = 1
                await RisingEdge(dut.clk)
                await Timer(1, unit="ns")
                dut.m_axi_awready_i.value = 0
                for beat in range(aw_len + 1):
                    while not int(dut.m_axi_wvalid_o.value):
                        await RisingEdge(dut.clk)
                        await Timer(1, unit="ns")
                    dut.m_axi_wready_i.value = 1
                    wdata = int(dut.m_axi_wdata_o.value)
                    wstrb = int(dut.m_axi_wstrb_o.value)
                    waddr = aw_addr + beat * 4
                    old = self.mem.get(waddr >> 2, 0)
                    for b in range(4):
                        if (wstrb >> b) & 1:
                            old = (old & ~(0xFF<<(8*b))) | (((wdata>>(8*b))&0xFF)<<(8*b))
                    self.mem[waddr >> 2] = old
                    await RisingEdge(dut.clk)
                    await Timer(1, unit="ns")
                    dut.m_axi_wready_i.value = 0
                dut.m_axi_bvalid_i.value = 1
                await RisingEdge(dut.clk)
                await Timer(1, unit="ns")
                dut.m_axi_bvalid_i.value = 0

            elif int(dut.m_axi_arvalid_o.value):
                ar_addr = int(dut.m_axi_araddr_o.value)
                ar_len  = int(dut.m_axi_arlen_o.value)
                dut.m_axi_arready_i.value = 1
                await RisingEdge(dut.clk)
                await Timer(1, unit="ns")
                dut.m_axi_arready_i.value = 0
                for beat in range(ar_len + 1):
                    raddr = ar_addr + beat * 4
                    dut.m_axi_rdata_i.value  = self.mem.get(raddr >> 2, 0)
                    dut.m_axi_rvalid_i.value = 1
                    dut.m_axi_rlast_i.value  = 1 if beat == ar_len else 0
                    await RisingEdge(dut.clk)
                    await Timer(1, unit="ns")
                dut.m_axi_rvalid_i.value = 0
                dut.m_axi_rlast_i.value  = 0
                dut.m_axi_rdata_i.value  = 0

    def stop(self):
        self._running = False


async def reset_dut(dut):
    dut.rst.value         = 1
    dut.cpu_re_i.value    = 0
    dut.cpu_we_i.value    = 0
    dut.cpu_addr_i.value  = 0
    dut.cpu_wdata_i.value = 0
    dut.cpu_be_i.value    = 0
    for _ in range(4):
        await RisingEdge(dut.clk)
    dut.rst.value = 0
    await Timer(1, unit="ns")


async def cache_read(dut, addr, timeout=120):
    dut.cpu_re_i.value   = 1
    dut.cpu_we_i.value   = 0
    dut.cpu_addr_i.value = addr
    for _ in range(timeout):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if not int(dut.cpu_stall_o.value):
            rdata = int(dut.cpu_rdata_o.value)
            dut.cpu_re_i.value = 0
            return rdata
    dut.cpu_re_i.value = 0
    raise TimeoutError(f"cache_read 0x{addr:08X} timed out")


async def cache_write(dut, addr, data, be=0xF, timeout=120):
    dut.cpu_we_i.value    = 1
    dut.cpu_re_i.value    = 0
    dut.cpu_addr_i.value  = addr
    dut.cpu_wdata_i.value = data
    dut.cpu_be_i.value    = be
    for _ in range(timeout):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if not int(dut.cpu_stall_o.value):
            dut.cpu_we_i.value = 0
            return
    dut.cpu_we_i.value = 0
    raise TimeoutError(f"cache_write 0x{addr:08X} timed out")


# Cache address layout: tag=addr[31:10], index=addr[9:4], woff=addr[3:2]
# Set index 0: addr[9:4]=0 → all 0x0000_0000..0x0000_000F
# To alias set 0 with different tags: add multiples of 0x400 (1KB per index stride)
IDX_STRIDE = 0x400   # one tag-stride = 1KB (index field = bits[9:4] = 6 bits, tag = bits[31:10])


@cocotb.test()
async def test_consecutive_dirty_evictions(dut):
    """Write to 3 addresses that alias set 0 (same cache index, different tags).
    Each new write evicts the previous dirty line. Verify final evicted data in backing mem."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    # Three addresses all mapping to cache index 0, tag 0/1/2
    addr_tag0 = 0x00000000            # tag=0, index=0
    addr_tag1 = 0x00000400            # tag=1, index=0
    addr_tag2 = 0x00000800            # tag=2, index=0

    # Fill set 0 with tag=0, value=0xAAAA0000 (write miss → allocate)
    await cache_write(dut, addr_tag0, 0xAAAA0000)
    # Verify hit
    v = await cache_read(dut, addr_tag0)
    assert v == 0xAAAA0000, f"Write 1: expected 0xAAAA0000, got {v:#010x}"

    # Write to tag=1 same index → evicts dirty tag=0 line to backing memory
    await cache_write(dut, addr_tag1, 0xBBBB1111)
    v = await cache_read(dut, addr_tag1)
    assert v == 0xBBBB1111, f"Write 2: expected 0xBBBB1111, got {v:#010x}"

    # Write to tag=2 → evicts dirty tag=1 line
    await cache_write(dut, addr_tag2, 0xCCCC2222)
    v = await cache_read(dut, addr_tag2)
    assert v == 0xCCCC2222, f"Write 3: expected 0xCCCC2222, got {v:#010x}"

    # tag=0 was evicted to backing mem — reading it back causes a fresh fill
    v0 = await cache_read(dut, addr_tag0)
    assert v0 == 0xAAAA0000, \
        f"Evicted tag=0 should be readable from backing mem: expected 0xAAAA0000, got {v0:#010x}"


@cocotb.test()
async def test_read_modify_write(dut):
    """Read a value, modify it, write it back to same address (RMW pattern).
    Read miss → hit → write hit → verify new value persists."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    addr = 0x00001000
    mem.preload(addr, 0x00000064)  # backing memory = 100

    v = await cache_read(dut, addr)
    assert v == 100, f"RMW read: expected 100, got {v}"

    new_val = v + 1  # 101
    await cache_write(dut, addr, new_val)

    v2 = await cache_read(dut, addr)
    assert v2 == 101, f"RMW write-back: expected 101, got {v2}"


@cocotb.test()
async def test_byte_enable_partial_then_evict(dut):
    """Write individual bytes to a cache line then evict — backing memory must
    contain the merged (partially-updated) data."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    addr = 0x00002000
    # Preload backing memory with 0x11223344
    mem.preload(addr, 0x11223344)

    # Cold read to fill cache line
    v = await cache_read(dut, addr)
    assert v == 0x11223344

    # Byte-write byte 0 only (0xAA) → word becomes 0x112233AA
    await cache_write(dut, addr, 0xAA, be=0x1)
    v2 = await cache_read(dut, addr)
    assert v2 == 0x112233AA, f"Byte-enable 0x1: expected 0x112233AA, got {v2:#010x}"

    # Byte-write byte 3 only (0xBB) → word becomes 0xBB2233AA
    await cache_write(dut, addr, 0xBB000000, be=0x8)
    v3 = await cache_read(dut, addr)
    assert v3 == 0xBB2233AA, f"Byte-enable 0x8: expected 0xBB2233AA, got {v3:#010x}"

    # Force eviction by writing to aliased address (same index, different tag)
    alias_addr = addr + IDX_STRIDE  # same index, tag+1
    await cache_write(dut, alias_addr, 0xDEADBEEF)

    # Now re-read original: fills from backing mem which got the evicted dirty data
    v_back = await cache_read(dut, addr)
    assert v_back == 0xBB2233AA, \
        f"After eviction, backing mem should hold merged value 0xBB2233AA, got {v_back:#010x}"


@cocotb.test()
async def test_aliasing_three_tags(dut):
    """Same cache index, 3 tags: access pattern A→B→C→A→B→C.
    Each tag miss evicts the previous. Verifies eviction chain is lossless."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    # Use set index 5 (addr bit[9:4]=5 → addr[9:4]=5 → addr base = 5<<4 = 0x50)
    base = 0x00000050
    addrs = [base, base + IDX_STRIDE, base + 2*IDX_STRIDE]
    vals  = [0xAA000000, 0xBB000000, 0xCC000000]

    for addr, val in zip(addrs, vals):
        mem.preload(addr, val)

    # Read all three in sequence (each evicts previous)
    for i, (addr, val) in enumerate(zip(addrs, vals)):
        v = await cache_read(dut, addr)
        assert v == val, f"Tag {i}: expected {val:#010x}, got {v:#010x}"

    # Re-read first: must fill from backing mem (was evicted by B then C reads)
    v0 = await cache_read(dut, addrs[0])
    assert v0 == vals[0], \
        f"Re-read tag0 after 2 evictions: expected {vals[0]:#010x}, got {v0:#010x}"


@cocotb.test()
async def test_back_to_back_write_misses(dut):
    """4 consecutive write misses to 4 different cache sets — verifies the cache
    handles allocate-on-write (or write-no-allocate) without getting stuck."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    # 4 unique sets: index bits vary with addr[9:4]
    addrs = [0x00000000, 0x00000010, 0x00000020, 0x00000030]
    vals  = [0x11111111, 0x22222222, 0x33333333, 0x44444444]

    for addr, val in zip(addrs, vals):
        await cache_write(dut, addr, val)

    for addr, val in zip(addrs, vals):
        v = await cache_read(dut, addr)
        assert v == val, f"Back-to-back write miss addr={addr:#010x}: expected {val:#010x}, got {v:#010x}"


@cocotb.test()
async def test_interleaved_read_write_misses(dut):
    """Alternate read-miss and write-miss to different sets.
    Verifies FSM transitions cleanly between FILL and WRITE_BACK paths."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    r_addr = 0x00003000
    w_addr = 0x00004000
    mem.preload(r_addr, 0xFEEDFACE)

    # Read miss
    v = await cache_read(dut, r_addr)
    assert v == 0xFEEDFACE, f"Read miss: expected 0xFEEDFACE, got {v:#010x}"

    # Write miss (different set)
    await cache_write(dut, w_addr, 0xC0FFEE00)

    # Read hit (r_addr still in cache — different set from w_addr)
    v2 = await cache_read(dut, r_addr)
    assert v2 == 0xFEEDFACE, f"Read hit after write miss: expected 0xFEEDFACE, got {v2:#010x}"

    # Read the write-miss address
    v3 = await cache_read(dut, w_addr)
    assert v3 == 0xC0FFEE00, f"Write miss verify: expected 0xC0FFEE00, got {v3:#010x}"


@cocotb.test()
async def test_byte_enable_merge_full_word(dut):
    """Write 4 individual bytes to the same address; final read must return the merged word."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    addr = 0x00005000
    # Cold read to allocate line (backing mem = 0)
    v = await cache_read(dut, addr)
    assert v == 0

    # Write bytes one at a time: byte0=0xAA, byte1=0xBB, byte2=0xCC, byte3=0xDD
    await cache_write(dut, addr, 0x000000AA, be=0x1)
    await cache_write(dut, addr, 0x0000BB00, be=0x2)
    await cache_write(dut, addr, 0x00CC0000, be=0x4)
    await cache_write(dut, addr, 0xDD000000, be=0x8)

    v = await cache_read(dut, addr)
    assert v == 0xDDCCBBAA, f"Byte-merge: expected 0xDDCCBBAA, got {v:#010x}"
