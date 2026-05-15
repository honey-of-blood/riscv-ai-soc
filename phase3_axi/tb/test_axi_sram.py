"""
cocotb unit tests for axi_sram.sv
Tests:
  1. write_then_read       – single word write + read, same address
  2. byte_enables          – partial-byte writes via wstrb
  3. multiple_addresses    – 8 unique word addresses
  4. back_to_back_writes   – consecutive writes, then verify all
  5. read_before_write     – data is X/0 on cold read (just exercises path)
  6. full_word_strobe      – wstrb=0xF writes all bytes
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer

# ─── AXI4-Lite BFM helpers ───────────────────────────────────────────────────

async def axi_write(dut, addr, data, strb=0xF):
    """Single AXI4-Lite write transaction."""
    dut.s_awaddr.value  = addr
    dut.s_awvalid.value = 1
    dut.s_wdata.value   = data
    dut.s_wstrb.value   = strb
    dut.s_wvalid.value  = 1
    dut.s_bready.value  = 1
    # Wait for AW+W handshake (AWREADY & WREADY both asserted next cycle)
    await RisingEdge(dut.clk)
    dut.s_awvalid.value = 0
    dut.s_wvalid.value  = 0
    # Wait for BVALID
    while not dut.s_bvalid.value:
        await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert dut.s_bresp.value == 0, f"Expected OKAY bresp, got {dut.s_bresp.value}"
    await RisingEdge(dut.clk)
    dut.s_bready.value = 0


async def axi_read(dut, addr) -> int:
    """Single AXI4-Lite read transaction. Returns read data."""
    dut.s_araddr.value  = addr
    dut.s_arvalid.value = 1
    dut.s_rready.value  = 1
    await RisingEdge(dut.clk)
    dut.s_arvalid.value = 0
    # Wait for RVALID
    while not dut.s_rvalid.value:
        await RisingEdge(dut.clk)
    await Timer(1, unit="ns")
    assert dut.s_rresp.value == 0, f"Expected OKAY rresp, got {dut.s_rresp.value}"
    data = int(dut.s_rdata.value)
    await RisingEdge(dut.clk)
    dut.s_rready.value = 0
    return data


async def reset(dut):
    dut.rst_n.value     = 0
    dut.s_awvalid.value = 0
    dut.s_wvalid.value  = 0
    dut.s_bready.value  = 0
    dut.s_arvalid.value = 0
    dut.s_rready.value  = 0
    dut.s_awaddr.value  = 0
    dut.s_wdata.value   = 0
    dut.s_wstrb.value   = 0
    dut.s_araddr.value  = 0
    for _ in range(3):
        await RisingEdge(dut.clk)
    dut.rst_n.value = 1
    await RisingEdge(dut.clk)


# ─── Clock ───────────────────────────────────────────────────────────────────

async def gen_clk(dut):
    while True:
        dut.clk.value = 0
        await Timer(5, unit="ns")
        dut.clk.value = 1
        await Timer(5, unit="ns")


# ─── Tests ───────────────────────────────────────────────────────────────────

@cocotb.test()
async def write_then_read(dut):
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    await axi_write(dut, addr=0x0000_0004, data=0xDEAD_BEEF)
    val = await axi_read(dut,  addr=0x0000_0004)
    assert val == 0xDEAD_BEEF, f"Expected 0xDEADBEEF, got 0x{val:08X}"


@cocotb.test()
async def byte_enables(dut):
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    # Write full word first
    await axi_write(dut, addr=0x0000_0008, data=0x0000_0000, strb=0xF)
    # Write only byte 0 (strb=0b0001)
    await axi_write(dut, addr=0x0000_0008, data=0xFF_FF_FF_AB, strb=0x1)
    val = await axi_read(dut, addr=0x0000_0008)
    assert val & 0xFF == 0xAB, f"Byte 0 wrong: 0x{val:08X}"
    assert (val >> 8) & 0xFF == 0x00, f"Byte 1 should be 0: 0x{val:08X}"
    # Write byte 3 (strb=0b1000)
    await axi_write(dut, addr=0x0000_0008, data=0xCD_00_00_00, strb=0x8)
    val = await axi_read(dut, addr=0x0000_0008)
    assert (val >> 24) & 0xFF == 0xCD, f"Byte 3 wrong: 0x{val:08X}"
    assert val & 0xFF == 0xAB, f"Byte 0 clobbered: 0x{val:08X}"


@cocotb.test()
async def multiple_addresses(dut):
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    data = {i: 0xA000_0000 | i for i in range(8)}
    for addr_idx, val in data.items():
        await axi_write(dut, addr=addr_idx * 4, data=val)
    for addr_idx, expected in data.items():
        got = await axi_read(dut, addr=addr_idx * 4)
        assert got == expected, f"addr={addr_idx*4}: expected 0x{expected:08X}, got 0x{got:08X}"


@cocotb.test()
async def back_to_back_writes(dut):
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    writes = [(0x100, 0x1111_1111), (0x104, 0x2222_2222), (0x108, 0x3333_3333)]
    for addr, val in writes:
        await axi_write(dut, addr=addr, data=val)
    for addr, expected in writes:
        got = await axi_read(dut, addr=addr)
        assert got == expected, f"addr=0x{addr:X}: expected 0x{expected:08X}, got 0x{got:08X}"


@cocotb.test()
async def full_word_strobe(dut):
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    await axi_write(dut, addr=0x200, data=0xCAFE_BABE, strb=0xF)
    val = await axi_read(dut, addr=0x200)
    assert val == 0xCAFE_BABE, f"Expected 0xCAFEBABE, got 0x{val:08X}"


@cocotb.test()
async def overwrite_preserves_other_addresses(dut):
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)
    await axi_write(dut, addr=0x300, data=0x1111_1111)
    await axi_write(dut, addr=0x304, data=0x2222_2222)
    # Overwrite first address
    await axi_write(dut, addr=0x300, data=0xAAAA_AAAA)
    val0 = await axi_read(dut, addr=0x300)
    val1 = await axi_read(dut, addr=0x304)
    assert val0 == 0xAAAA_AAAA, f"Overwrite failed: 0x{val0:08X}"
    assert val1 == 0x2222_2222, f"Neighbor clobbered: 0x{val1:08X}"
