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


@cocotb.test()
async def test_write_miss_allocate(dut):
    """
    Write to an uncached address (write miss → write-allocate).
    Tests the RESPOND && req_we path in cache_controller output logic.

    Expected behaviour:
      - Cache fills the line from memory (FILL state).
      - In RESPOND, applies the CPU write and marks the line dirty.
      - Memory is NOT updated (write-back policy).
      - A subsequent read returns the written value (dirty hit).
      - Evicting the dirty line sends the written value to memory.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    # addr=0x5000 → tag=20, index=0
    addr     = 0x5000
    conflict = addr + 0x400   # tag=21, index=0

    for w in range(4):
        mem.preload(addr     + w * 4, 0xAA000000 | w)
        mem.preload(conflict + w * 4, 0xBB000000 | w)

    # Write to word 2 of an uncached line — write miss, no prior fill
    await cache_write(dut, addr + 8, 0xDEADBEEF)

    # Memory must NOT be updated (write-back)
    assert mem.read(addr + 8) == 0xAA000002, \
        f"write-back violated before eviction: got 0x{mem.read(addr + 8):08X}"

    # Read back the written word — must be dirty hit
    v = await cache_read(dut, addr + 8)
    assert v == 0xDEADBEEF, f"write-miss readback: expected 0xDEADBEEF, got 0x{v:08X}"

    # Other words in the line come from the fill and must be unchanged
    v0 = await cache_read(dut, addr)
    assert v0 == 0xAA000000, f"word0 corrupted: expected 0xAA000000, got 0x{v0:08X}"

    # Trigger eviction — conflict address maps to the same index
    await cache_read(dut, conflict)

    # Now memory must have the written value for the evicted word
    assert mem.read(addr + 8) == 0xDEADBEEF, \
        f"eviction: addr+8 expected 0xDEADBEEF, got 0x{mem.read(addr + 8):08X}"
    # Other words of the evicted line must also be in memory unchanged
    assert mem.read(addr)     == 0xAA000000, "eviction: word0 wrong in memory"
    assert mem.read(addr + 4) == 0xAA000001, "eviction: word1 wrong in memory"

    dut._log.info("PASS: write-miss allocates, marks dirty, evicts correct data")


@cocotb.test()
async def test_write_miss_dirty_eviction(dut):
    """
    Write miss into a set whose resident line is already dirty.
    Full path: TAG_CHECK → WRITE_BACK → FILL → RESPOND(req_we).

    1. Cold read of line A → fill (clean).
    2. Write to line A → dirty.
    3. Write to line B (same index, different tag) → write miss triggers
       dirty eviction of A, fills B, then applies write in RESPOND.

    Verify: A written back to memory; B's written value in cache; B not yet
    in memory (write-back still pending).
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    # addr_A=0x40 → tag=0, index=4;  addr_B=0x440 → tag=1, index=4
    addr_A = 0x00000040
    addr_B = addr_A + 0x400

    for w in range(4):
        mem.preload(addr_A + w * 4, 0xAAAA0000 | w)
        mem.preload(addr_B + w * 4, 0xBBBB0000 | w)

    # Step 1: read A → cold miss → fill (clean, valid, dirty=0)
    await cache_read(dut, addr_A)

    # Step 2: write A word 1 → write hit → dirty=1
    await cache_write(dut, addr_A + 4, 0xCAFEBABE)
    assert mem.read(addr_A + 4) == 0xAAAA0001, \
        "premature writeback of A before eviction"

    # Step 3: write B word 0 → write miss → evict dirty A → fill B → apply write
    await cache_write(dut, addr_B, 0xDEAD1234)

    # A must now be in memory with the modified word 1
    assert mem.read(addr_A + 4) == 0xCAFEBABE, \
        f"A word1 not written back: expected 0xCAFEBABE, got 0x{mem.read(addr_A + 4):08X}"
    # A's unmodified words must also be correct in memory
    assert mem.read(addr_A)     == 0xAAAA0000, "A word0 wrong in memory after eviction"
    assert mem.read(addr_A + 8) == 0xAAAA0002, "A word2 wrong in memory after eviction"

    # B's written value must be readable from cache (dirty hit)
    v = await cache_read(dut, addr_B)
    assert v == 0xDEAD1234, \
        f"B word0 readback: expected 0xDEAD1234, got 0x{v:08X}"

    # B's memory must be unchanged (write-back, not write-through)
    assert mem.read(addr_B) == 0xBBBB0000, \
        f"B's memory updated too early: got 0x{mem.read(addr_B):08X}"

    dut._log.info("PASS: write-miss + dirty eviction → WRITE_BACK → FILL → RESPOND(write)")


@cocotb.test()
async def test_byte_enable_store_end_to_end(dut):
    """
    Sub-word byte-enable stores through the full cache stack.
    Exercises data_be_o = req_be wiring in cache_controller output logic.

    Sequence:
      1. Fill a line with a known pattern.
      2. Store individual bytes and a halfword using sub-word byte enables.
      3. Read back and verify only the targeted bytes changed.
      4. Evict the dirty line and verify all 4 words land in memory correctly
         (tests the wb_wdata mux sends the BE-modified data, not the original).
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    # addr=0x6000 → tag=24, index=0
    addr     = 0x6000
    conflict = addr + 0x400   # tag=25, index=0

    mem.preload(addr,        0xAABBCCDD)
    mem.preload(addr + 0x4,  0x11223344)
    mem.preload(addr + 0x8,  0x55667788)
    mem.preload(addr + 0xC,  0x99AABBCC)
    for w in range(4):
        mem.preload(conflict + w * 4, 0xCC000000 | w)

    # Fill the line via a cold read
    await cache_read(dut, addr)

    # ── be=0001: byte 0 only ───────────────────────────────────────────────
    await cache_write(dut, addr, 0x000000FF, be=0x1)
    v = await cache_read(dut, addr)
    assert v == 0xAABBCCFF, f"be=0x1: expected 0xAABBCCFF, got 0x{v:08X}"

    # ── be=1100: bytes 2-3 only ────────────────────────────────────────────
    await cache_write(dut, addr, 0x12340000, be=0xC)
    v = await cache_read(dut, addr)
    assert v == 0x1234CCFF, f"be=0xC: expected 0x1234CCFF, got 0x{v:08X}"

    # ── be=0011: low halfword of word 1 ───────────────────────────────────
    await cache_write(dut, addr + 4, 0x0000BEEF, be=0x3)
    v = await cache_read(dut, addr + 4)
    assert v == 0x1122BEEF, f"be=0x3: expected 0x1122BEEF, got 0x{v:08X}"

    # Evict the dirty line; all 4 words must reach memory with correct values
    await cache_read(dut, conflict)

    assert mem.read(addr)        == 0x1234CCFF, f"evict word0: got 0x{mem.read(addr):08X}"
    assert mem.read(addr + 0x4)  == 0x1122BEEF, f"evict word1: got 0x{mem.read(addr + 0x4):08X}"
    assert mem.read(addr + 0x8)  == 0x55667788, f"evict word2: got 0x{mem.read(addr + 0x8):08X}"
    assert mem.read(addr + 0xC)  == 0x99AABBCC, f"evict word3: got 0x{mem.read(addr + 0xC):08X}"

    dut._log.info("PASS: byte-enable stores end-to-end, all 4 words correct on eviction")


@cocotb.test()
async def test_eviction_writes_all_four_words(dut):
    """
    Write all 4 words of a cache line (each a write hit) then evict.
    Verifies the wb_wdata mux in cache_controller correctly cycles through
    burst_cnt=0..3 and sends all four dirty words to memory.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    # base=0x7000 → tag=28, index=0
    base     = 0x7000
    conflict = base + 0x400   # tag=29, index=0

    for w in range(4):
        mem.preload(base     + w * 4, 0x10000000 | w)
        mem.preload(conflict + w * 4, 0x20000000 | w)

    # Cold read → fill
    await cache_read(dut, base)

    # Write all 4 words (write hits → dirty=1 after first write)
    dirty_vals = [0xDEAD0000, 0xDEAD0001, 0xDEAD0002, 0xDEAD0003]
    for w, v in enumerate(dirty_vals):
        await cache_write(dut, base + w * 4, v)

    # Verify in-cache reads before eviction
    for w, v in enumerate(dirty_vals):
        got = await cache_read(dut, base + w * 4)
        assert got == v, f"pre-evict word{w}: expected 0x{v:08X}, got 0x{got:08X}"

    # Trigger eviction
    await cache_read(dut, conflict)

    # All 4 words must be in memory with the dirty values
    for w, v in enumerate(dirty_vals):
        got = mem.read(base + w * 4)
        assert got == v, \
            f"evict word{w}: expected 0x{v:08X}, got 0x{got:08X}"

    dut._log.info("PASS: all 4 dirty words correctly sent to memory on eviction")


@cocotb.test()
async def test_hit_latency(dut):
    """
    A cache hit must release stall after exactly 1 stall cycle
    (IDLE→TAG_CHECK stalls; HIT de-asserts stall).
    Measures actual rising-edge count so a slow FSM transition would fail.
    """
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    mem = AXI4Memory(dut)
    cocotb.start_soon(mem.run())
    await reset_dut(dut)

    addr = 0x8000
    mem.preload(addr,       0x11111111)
    mem.preload(addr + 0x4, 0x22222222)
    mem.preload(addr + 0x8, 0x33333333)
    mem.preload(addr + 0xC, 0x44444444)

    # Warm the cache — cold miss is expected and not measured here
    await cache_read(dut, addr)
    # cache_read() returns while FSM is still in HIT state (stall just de-asserted).
    # Wait one more edge so HIT→IDLE completes before we start measuring.
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")

    # Present a new request and count stall cycles until de-assertion
    dut.cpu_re_i.value   = 1
    dut.cpu_we_i.value   = 0
    dut.cpu_addr_i.value = addr

    stall_cycles = 0
    for _ in range(10):
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        if not int(dut.cpu_stall_o.value):
            break
        stall_cycles += 1

    rdata = int(dut.cpu_rdata_o.value)
    dut.cpu_re_i.value = 0

    assert stall_cycles == 1, \
        f"hit latency: expected 1 stall cycle (TAG_CHECK), got {stall_cycles}"
    assert rdata == 0x11111111, \
        f"hit rdata: expected 0x11111111, got 0x{rdata:08X}"

    dut._log.info(f"PASS: cache hit releases stall after exactly {stall_cycles} stall cycle")
