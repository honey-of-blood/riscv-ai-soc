"""
cocotb tests for instr_bram.sv — 64 KB true dual-port instruction BRAM.

Port A: combinational instruction fetch  (pa_addr_i → pa_rdata_o, no clock)
Port B: synchronous bootloader write/read (pb_en_i/pb_we_i → clk edge)

Tests:
  1. test_single_word_write_read      — write word via Port B, read via Port A
  2. test_overwrite_same_address      — two writes, verify latest value wins
  3. test_sequential_16_words         — fill 16 consecutive words, read all via A
  4. test_first_word_address          — boundary: address 0x00000000
  5. test_last_word_address           — boundary: address 0x0000FFFC (word 16383)
  6. test_portb_readback              — write via B, read back via B (registered)
  7. test_porta_portb_independent_addrs — simultaneous access to different addrs
  8. test_bootloader_1kb_pattern      — write 256 words (1 KB), verify all via Port A
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer


async def gen_clock(dut):
    while True:
        dut.clk.value = 0
        await Timer(5, unit="ns")
        dut.clk.value = 1
        await Timer(5, unit="ns")


async def init_dut(dut):
    cocotb.start_soon(gen_clock(dut))
    dut.pa_addr_i.value  = 0
    dut.pb_en_i.value    = 0
    dut.pb_we_i.value    = 0
    dut.pb_addr_i.value  = 0
    dut.pb_wdata_i.value = 0
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")


async def write_b(dut, addr: int, data: int):
    """Write one word via Port B (sync on posedge clk)."""
    dut.pb_en_i.value    = 1
    dut.pb_we_i.value    = 1
    dut.pb_addr_i.value  = addr
    dut.pb_wdata_i.value = data & 0xFFFFFFFF
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    dut.pb_en_i.value = 0
    dut.pb_we_i.value = 0


async def read_b(dut, addr: int) -> int:
    """Read one word via Port B (registered — result valid after clock edge)."""
    dut.pb_en_i.value   = 1
    dut.pb_we_i.value   = 0
    dut.pb_addr_i.value = addr
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    val = int(dut.pb_rdata_o.value)
    dut.pb_en_i.value = 0
    return val


def read_a(dut, addr: int) -> int:
    """Read one word via Port A (combinational — valid after addr settles)."""
    dut.pa_addr_i.value = addr
    # Combinational output — no clock needed, but allow 1 delta for simulator
    return int(dut.pa_rdata_o.value)


# ─────────────────────────────────────────────────────────────────────────────

@cocotb.test()
async def test_single_word_write_read(dut):
    """Write 0xDEADBEEF to byte address 4 via Port B; read back via Port A."""
    await init_dut(dut)
    await write_b(dut, addr=0x04, data=0xDEADBEEF)
    # Port A async read — settle the address then sample
    dut.pa_addr_i.value = 0x04
    await Timer(1, unit="ns")
    assert int(dut.pa_rdata_o.value) == 0xDEADBEEF, \
        f"Expected 0xDEADBEEF, got {int(dut.pa_rdata_o.value):#010x}"


@cocotb.test()
async def test_overwrite_same_address(dut):
    """Two writes to the same address; verify the latest value is returned."""
    await init_dut(dut)
    await write_b(dut, addr=0x08, data=0xAAAAAAAA)
    await write_b(dut, addr=0x08, data=0x55555555)
    dut.pa_addr_i.value = 0x08
    await Timer(1, unit="ns")
    assert int(dut.pa_rdata_o.value) == 0x55555555, \
        f"Overwrite failed: got {int(dut.pa_rdata_o.value):#010x}"


@cocotb.test()
async def test_sequential_16_words(dut):
    """Fill 16 consecutive words via Port B; read all via Port A."""
    await init_dut(dut)
    base = 0x100   # byte address 0x100 = word index 64

    # Write 16 words
    for i in range(16):
        await write_b(dut, addr=base + i * 4, data=0xC0DE0000 + i)

    # Read back via Port A
    for i in range(16):
        dut.pa_addr_i.value = base + i * 4
        await Timer(1, unit="ns")
        expected = 0xC0DE0000 + i
        got      = int(dut.pa_rdata_o.value)
        assert got == expected, \
            f"Word {i}: expected {expected:#010x}, got {got:#010x}"


@cocotb.test()
async def test_first_word_address(dut):
    """Boundary: byte address 0x00000000 (word 0)."""
    await init_dut(dut)
    await write_b(dut, addr=0x00000000, data=0x13131313)   # NOP instruction
    dut.pa_addr_i.value = 0x00000000
    await Timer(1, unit="ns")
    assert int(dut.pa_rdata_o.value) == 0x13131313


@cocotb.test()
async def test_last_word_address(dut):
    """Boundary: byte address 0x0000FFFC (word 16383, last in 64 KB BRAM)."""
    await init_dut(dut)
    last_addr = (16384 - 1) * 4   # 0x0000FFFC
    await write_b(dut, addr=last_addr, data=0xCAFEBABE)
    dut.pa_addr_i.value = last_addr
    await Timer(1, unit="ns")
    assert int(dut.pa_rdata_o.value) == 0xCAFEBABE, \
        f"Last word: expected 0xCAFEBABE, got {int(dut.pa_rdata_o.value):#010x}"


@cocotb.test()
async def test_portb_readback(dut):
    """Write via Port B; read back via Port B (registered output pb_rdata_o)."""
    await init_dut(dut)
    await write_b(dut, addr=0x20, data=0x12345678)
    val = await read_b(dut, addr=0x20)
    assert val == 0x12345678, f"Port B readback: expected 0x12345678, got {val:#010x}"


@cocotb.test()
async def test_porta_portb_independent_addrs(dut):
    """Write two words at different addresses; read both simultaneously."""
    await init_dut(dut)
    await write_b(dut, addr=0x40, data=0x11111111)
    await write_b(dut, addr=0x44, data=0x22222222)

    # Port A samples addr 0x40
    dut.pa_addr_i.value = 0x40
    await Timer(1, unit="ns")
    a_val = int(dut.pa_rdata_o.value)

    # Port B reads addr 0x44
    b_val = await read_b(dut, addr=0x44)

    assert a_val == 0x11111111, f"Port A: expected 0x11111111, got {a_val:#010x}"
    assert b_val == 0x22222222, f"Port B: expected 0x22222222, got {b_val:#010x}"


@cocotb.test()
async def test_bootloader_1kb_pattern(dut):
    """Write 256 words (1 KB) simulating a bootloader image; read all via Port A."""
    await init_dut(dut)
    n = 256
    # Generate a pattern that exercises all bits of the data bus
    words = [(0xB007_0000 + i) & 0xFFFFFFFF for i in range(n)]

    for i, w in enumerate(words):
        await write_b(dut, addr=i * 4, data=w)

    for i, expected in enumerate(words):
        dut.pa_addr_i.value = i * 4
        await Timer(1, unit="ns")
        got = int(dut.pa_rdata_o.value)
        assert got == expected, \
            f"Word {i}: expected {expected:#010x}, got {got:#010x}"
