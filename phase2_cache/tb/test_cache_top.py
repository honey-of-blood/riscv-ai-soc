"""
Integration tests for cache_top.sv (cache controller + tag/data arrays).

Memory model:
  AXI4 burst read  (FILL):       serve 4 words from a Python dict on each AR request.
  AXI4 burst write (WRITE_BACK): capture 4 words from W channel into the Python dict.

Address map (matches cache_controller.sv):
  addr[31:10] tag  (22 bits)
  addr[ 9: 4] index (6 bits)
  addr[ 3: 2] word offset (2 bits → 4 words)
  addr[ 1: 0] byte offset (ignored by cache)
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer
import random

# ---------------------------------------------------------------------------
# AXI4 memory model
# ---------------------------------------------------------------------------
class AXI4Memory:
    """Behavioural AXI4 slave: responds to burst reads/writes from the cache."""

    def __init__(self, dut):
        self.dut  = dut
        self.mem  = {}          # word_address (byte_addr >> 2) → 32-bit value
        self._running = False

    def preload(self, byte_addr, value):
        self.mem[byte_addr >> 2] = value & 0xFFFF_FFFF

    def read(self, byte_addr):
        return self.mem.get(byte_addr >> 2, 0)

    async def run(self):
        """Co-routine: drive AXI4 slave signals in response to master requests."""
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
            await Timer(1, unit="ns")   # let combinational outputs settle

            # ── Handle write-address channel ──────────────────────────────
            if int(dut.m_axi_awvalid_o.value):
                aw_addr = int(dut.m_axi_awaddr_o.value)
                aw_len  = int(dut.m_axi_awlen_o.value)   # should be 3
                dut.m_axi_awready_i.value = 1
                await RisingEdge(dut.clk)
                await Timer(1, unit="ns")
                dut.m_axi_awready_i.value = 0

                # Accept write data beats
                beats = aw_len + 1
                for beat in range(beats):
                    while not int(dut.m_axi_wvalid_o.value):
                        await RisingEdge(dut.clk)
                        await Timer(1, unit="ns")
                    dut.m_axi_wready_i.value = 1
                    wdata = int(dut.m_axi_wdata_o.value)
                    wstrb = int(dut.m_axi_wstrb_o.value)
                    waddr = aw_addr + beat * 4
                    # Apply byte strobes
                    old = self.mem.get(waddr >> 2, 0)
                    for b in range(4):
                        if (wstrb >> b) & 1:
                            old = (old & ~(0xFF << (8*b))) | (((wdata >> (8*b)) & 0xFF) << (8*b))
                    self.mem[waddr >> 2] = old
                    await RisingEdge(dut.clk)
                    await Timer(1, unit="ns")
                    dut.m_axi_wready_i.value = 0

                # Send write response
                dut.m_axi_bvalid_i.value = 1
                await RisingEdge(dut.clk)
                await Timer(1, unit="ns")
                dut.m_axi_bvalid_i.value = 0

            # ── Handle read-address channel ───────────────────────────────
            elif int(dut.m_axi_arvalid_o.value):
                ar_addr = int(dut.m_axi_araddr_o.value)
                ar_len  = int(dut.m_axi_arlen_o.value)   # should be 3
                dut.m_axi_arready_i.value = 1
                await RisingEdge(dut.clk)
                await Timer(1, unit="ns")
                dut.m_axi_arready_i.value = 0

                beats = ar_len + 1
                for beat in range(beats):
                    raddr = ar_addr + beat * 4
                    rdata = self.mem.get(raddr >> 2, 0)
                    dut.m_axi_rdata_i.value  = rdata
                    dut.m_axi_rvalid_i.value = 1
                    dut.m_axi_rlast_i.value  = 1 if beat == beats - 1 else 0
                    await RisingEdge(dut.clk)
                    await Timer(1, unit="ns")

                dut.m_axi_rvalid_i.value = 0
                dut.m_axi_rlast_i.value  = 0
                dut.m_axi_rdata_i.value  = 0

    def stop(self):
        self._running = False


# ---------------------------------------------------------------------------
# Simulation helpers
# ---------------------------------------------------------------------------
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


async def cache_read(dut, addr, timeout=80):
    """
    Issue a cache read.  Hold cpu_re_i=1 until stall de-asserts (the standard
    cache protocol: CPU must keep its request stable while stall=1).
    Returns read data when stall falls.
    """
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
    raise TimeoutError(f"cache_read addr=0x{addr:08X} timed out after {timeout} cycles")


async def cache_write(dut, addr, data, be=0xF, timeout=80):
    """
    Issue a cache write.  Hold cpu_we_i=1 until stall de-asserts.
    """
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
    raise TimeoutError(f"cache_write addr=0x{addr:08X} timed out after {timeout} cycles")


# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------

@cocotb.test()
async def test_cold_miss_then_hit(dut):
    """
    Cold miss: first read misses (fetches from memory), second read hits (1 cycle).

    Pre-load memory address 0x1000 with value 0xDEADBEEF.
    Read[1]: miss → FILL → returns 0xDEADBEEF.
    Read[2]: hit  → returns 0xDEADBEEF in 0 stall cycles.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())

    await reset_dut(dut)

    # Pre-load the 4-word cache line containing 0x1000
    mem.preload(0x1000, 0xDEADBEEF)   # word 0 of the line
    mem.preload(0x1004, 0x00000001)
    mem.preload(0x1008, 0x00000002)
    mem.preload(0x100C, 0x00000003)

    val1 = await cache_read(dut, 0x1000)
    assert val1 == 0xDEADBEEF, f"cold miss: expected 0xDEADBEEF, got 0x{val1:08X}"
    dut._log.info("cold miss returned correct value")

    val2 = await cache_read(dut, 0x1000)
    assert val2 == 0xDEADBEEF, f"second read (hit): expected 0xDEADBEEF, got 0x{val2:08X}"
    dut._log.info("PASS: cold miss then hit — both return correct data")


@cocotb.test()
async def test_read_different_words_in_line(dut):
    """
    After a fill, reading different word offsets within the same line all hit.

    Line base = 0x2000, words at 0x2000/0x2004/0x2008/0x200C.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    line_vals = [0x11111111, 0x22222222, 0x33333333, 0x44444444]
    for w, v in enumerate(line_vals):
        mem.preload(0x2000 + w * 4, v)

    # First read triggers fill
    v0 = await cache_read(dut, 0x2000)
    assert v0 == line_vals[0], f"word0: expected 0x{line_vals[0]:08X}, got 0x{v0:08X}"

    # Remaining reads hit
    for w in range(1, 4):
        v = await cache_read(dut, 0x2000 + w * 4)
        assert v == line_vals[w], f"word{w}: expected 0x{line_vals[w]:08X}, got 0x{v:08X}"

    dut._log.info("PASS: all 4 words of a filled line read correctly")


@cocotb.test()
async def test_write_hit_read_back(dut):
    """
    Fill a line from memory, write to it (hit), read back the new value.
    Dirty bit must be set; memory must NOT be updated yet (write-back).
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    mem.preload(0x3000, 0xAAAAAAAA)
    mem.preload(0x3004, 0xBBBBBBBB)
    mem.preload(0x3008, 0xCCCCCCCC)
    mem.preload(0x300C, 0xDDDDDDDD)

    # Fill the line
    await cache_read(dut, 0x3000)

    # Write new value to word 1
    await cache_write(dut, 0x3004, 0x12345678)

    # Read back — should be updated value
    v = await cache_read(dut, 0x3004)
    assert v == 0x12345678, f"write-hit readback: expected 0x12345678, got 0x{v:08X}"

    # Memory should still have old value (write-back, not write-through)
    assert mem.read(0x3004) == 0xBBBBBBBB, \
        f"write-back: memory updated too early (got 0x{mem.read(0x3004):08X})"

    dut._log.info("PASS: write hit updated cache, memory unchanged (write-back)")


@cocotb.test()
async def test_dirty_eviction(dut):
    """
    Write to a line (makes it dirty), then access a conflicting address
    (same index, different tag) → cache must write back the dirty line before fill.

    Two addresses map to the same cache set (index bits match):
      addr_A = 0x0000_0000  (tag=0x0000000, index=0)
      addr_B = 0x0000_0400  (tag=0x0000001, index=0)  [tag differs, index same]
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    # addr_A line: index=0, tag=0
    addr_A = 0x00000000
    # addr_B line: same index (bits[9:4]=0), different tag (bit 10 set)
    addr_B = 0x00000400   # tag=1, index=0

    # Pre-fill memory for both lines
    for w in range(4):
        mem.preload(addr_A + w * 4, 0xAAAA0000 | w)
        mem.preload(addr_B + w * 4, 0xBBBB0000 | w)

    # Load addr_A into cache (cold miss)
    await cache_read(dut, addr_A)

    # Write to addr_A word 0 → line becomes dirty, cache holds 0xDEAD_1234
    await cache_write(dut, addr_A, 0xDEAD1234)
    assert mem.read(addr_A) == 0xAAAA0000, \
        "memory updated before eviction — write-back violated"

    # Access addr_B (same index) → triggers dirty eviction of addr_A line
    val_B = await cache_read(dut, addr_B)
    assert val_B == 0xBBBB0000, f"addr_B read: expected 0xBBBB0000, got 0x{val_B:08X}"

    # Now memory must have the written-back dirty value for addr_A
    assert mem.read(addr_A) == 0xDEAD1234, \
        f"write-back: memory[addr_A] should be 0xDEAD1234, got 0x{mem.read(addr_A):08X}"

    dut._log.info("PASS: dirty eviction writes back correct data before fill")


@cocotb.test()
async def test_golden_model(dut):
    """
    100 random read/write operations compared against a Python cache model.
    Zero mismatches required.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    # ── Python golden model ──────────────────────────────────────────────
    NUM_SETS = 64
    WORDS    = 4

    class CacheModel:
        def __init__(self):
            # sets[idx] = (tag, [word0, word1, word2, word3], valid, dirty)
            self.sets   = [None] * NUM_SETS
            self.memory = {}   # word_addr → value

        def _decode(self, addr):
            tag  = addr >> 10
            idx  = (addr >> 4) & 0x3F
            woff = (addr >> 2) & 0x3
            return tag, idx, woff

        def read(self, addr):
            tag, idx, woff = self._decode(addr)
            entry = self.sets[idx]
            if entry and entry[2] and entry[0] == tag:   # hit
                return entry[1][woff]
            # miss — write back if dirty, then fill
            if entry and entry[2] and entry[3]:           # dirty eviction
                base = (entry[0] << 10) | (idx << 4)
                for w in range(WORDS):
                    self.memory[(base >> 2) + w] = entry[1][w]
            # fill from memory
            base = (tag << 10) | (idx << 4)
            line = [self.memory.get((base >> 2) + w, 0) for w in range(WORDS)]
            self.sets[idx] = (tag, line, True, False)
            return line[woff]

        def write(self, addr, data):
            tag, idx, woff = self._decode(addr)
            entry = self.sets[idx]
            if not (entry and entry[2] and entry[0] == tag):   # miss → allocate
                self.read(addr)   # fills the line
                entry = self.sets[idx]
            line       = list(entry[1])
            line[woff] = data
            self.sets[idx] = (tag, line, True, True)   # dirty

    model = CacheModel()

    # Pre-populate backing memory with known values so model and DUT agree
    random.seed(0xC0FFEE)
    addrs = [random.randint(0, 0x3FF) << 4 for _ in range(20)]   # 20 distinct lines
    for a in addrs:
        for w in range(WORDS):
            val = random.randint(0, 0xFFFF_FFFF)
            byte_addr = a + w * 4
            mem.preload(byte_addr, val)
            model.memory[byte_addr >> 2] = val

    errors = 0
    for op_num in range(100):
        addr   = random.choice(addrs) + random.randint(0, 3) * 4   # word-aligned
        is_write = random.random() < 0.4

        if is_write:
            val = random.randint(0, 0xFFFF_FFFF)
            model.write(addr, val)
            await cache_write(dut, addr, val)
        else:
            expected = model.read(addr)
            got      = await cache_read(dut, addr)
            if got != expected:
                dut._log.error(
                    f"op {op_num}: READ addr=0x{addr:08X} "
                    f"expected=0x{expected:08X} got=0x{got:08X}"
                )
                errors += 1

    assert errors == 0, f"{errors}/100 operations failed golden model check"
    dut._log.info("PASS: 100 random ops match golden model — zero mismatches")
