import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer

# Simple instruction memory model: addr/4 → instruction word
def imem(addr):
    """Return a unique word for each word-aligned address (for easy checking)."""
    return (addr >> 2) + 0xDEAD_0000

async def setup(dut):
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    dut.rst.value          = 1
    dut.stall_i.value      = 0
    dut.branch_taken_i.value = 0
    dut.branch_target_i.value = 0
    dut.imem_rdata_i.value = 0
    await RisingEdge(dut.clk)
    await RisingEdge(dut.clk)
    dut.rst.value = 0

async def tick(dut):
    """Advance one cycle, driving imem with whatever PC the fetch stage requests."""
    dut.imem_rdata_i.value = imem(int(dut.imem_addr_o.value))
    await RisingEdge(dut.clk)
    await Timer(1, unit="ns")  # settle combinational outputs


@cocotb.test()
async def test_sequential_fetch(dut):
    """PC must advance PC+4 each cycle and imem_addr must track it."""
    await setup(dut)

    for expected_pc in range(0, 10 * 4, 4):
        assert int(dut.imem_addr_o.value) == expected_pc, \
            f"imem_addr: expected 0x{expected_pc:08X}, got 0x{int(dut.imem_addr_o.value):08X}"
        await tick(dut)

    dut._log.info("PASS: PC increments by 4 each cycle, imem_addr tracks PC")


@cocotb.test()
async def test_reset(dut):
    """Reset must drive PC back to 0."""
    await setup(dut)

    # Advance several cycles
    for _ in range(5):
        await tick(dut)

    pc_before = int(dut.imem_addr_o.value)
    assert pc_before == 20, f"Expected PC=20 after 5 cycles, got {pc_before}"

    # Assert reset mid-run
    dut.rst.value = 1
    await RisingEdge(dut.clk)
    dut.rst.value = 0
    await Timer(1, unit="ns")

    assert int(dut.imem_addr_o.value) == 0, \
        f"PC not reset to 0, got {int(dut.imem_addr_o.value)}"
    dut._log.info("PASS: reset drives PC to 0")


@cocotb.test()
async def test_stall(dut):
    """Stall must freeze PC — same address presented to imem for multiple cycles."""
    await setup(dut)

    # Let it run to PC=8
    for _ in range(2):
        await tick(dut)

    pc_before_stall = int(dut.imem_addr_o.value)
    assert pc_before_stall == 8

    # Stall for 3 cycles
    dut.stall_i.value = 1
    for _ in range(3):
        dut.imem_rdata_i.value = imem(int(dut.imem_addr_o.value))
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        assert int(dut.imem_addr_o.value) == pc_before_stall, \
            f"PC advanced during stall: got 0x{int(dut.imem_addr_o.value):08X}"

    # Release stall — PC resumes
    dut.stall_i.value = 0
    await tick(dut)
    assert int(dut.imem_addr_o.value) == pc_before_stall + 4, \
        f"PC didn't resume after stall release"

    dut._log.info("PASS: stall freezes PC for 3 cycles, resumes correctly")


@cocotb.test()
async def test_branch_taken(dut):
    """Branch redirect must load branch_target into PC next cycle."""
    await setup(dut)

    # Run to PC=12
    for _ in range(3):
        await tick(dut)
    assert int(dut.imem_addr_o.value) == 12

    # Signal branch taken to address 0x100
    dut.branch_taken_i.value  = 1
    dut.branch_target_i.value = 0x100
    dut.imem_rdata_i.value    = imem(int(dut.imem_addr_o.value))
    await RisingEdge(dut.clk)
    dut.branch_taken_i.value  = 0
    await Timer(1, unit="ns")

    assert int(dut.imem_addr_o.value) == 0x100, \
        f"Expected PC=0x100 after branch, got 0x{int(dut.imem_addr_o.value):08X}"

    # Should continue sequentially from 0x100
    await tick(dut)
    assert int(dut.imem_addr_o.value) == 0x104

    dut._log.info("PASS: branch redirect loads target PC, sequential fetch resumes")


@cocotb.test()
async def test_pipeline_reg_advances(dut):
    """IF/ID pipeline register must capture {PC, instr} on each rising edge.

    Non-blocking assignment semantics: at the rising edge, the pipeline register
    captures the CURRENT value of PC (before PC increments). So after edge N
    (0-indexed), pc_id == N*4 and instr_id == imem(N*4).
    """
    await setup(dut)

    for cycle in range(4):
        pc_in_if = cycle * 4                 # PC value sitting in IF at this edge
        dut.imem_rdata_i.value = imem(pc_in_if)
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        assert int(dut.pc_id_o.value) == pc_in_if, \
            f"cycle {cycle}: pc_id expected {pc_in_if}, got {int(dut.pc_id_o.value)}"
        assert int(dut.instr_id_o.value) == imem(pc_in_if), \
            f"cycle {cycle}: instr_id expected 0x{imem(pc_in_if):08X}, " \
            f"got 0x{int(dut.instr_id_o.value):08X}"

    dut._log.info("PASS: IF/ID pipeline register captures PC and instruction correctly")


@cocotb.test()
async def test_pipeline_reg_flush(dut):
    """Flush must insert NOP (0x00000013) into IF/ID regardless of fetched instruction."""
    await setup(dut)

    # Fetch one real instruction
    dut.imem_rdata_i.value = 0xDEADBEEF
    await tick(dut)

    # Now assert flush
    dut.flush_i.value      = 1
    dut.imem_rdata_i.value = 0xDEADBEEF  # memory still returns junk
    await RisingEdge(dut.clk)
    dut.flush_i.value = 0
    await Timer(1, unit="ns")

    nop = int(dut.instr_id_o.value)
    assert nop == 0x00000013, \
        f"Expected NOP 0x00000013 after flush, got 0x{nop:08X}"

    dut._log.info("PASS: flush inserts NOP into IF/ID pipeline register")


@cocotb.test()
async def test_pipeline_reg_stall(dut):
    """Stall must hold IF/ID register contents — no overwrite."""
    await setup(dut)

    # Load a known instruction into IF/ID
    dut.imem_rdata_i.value = 0xABCD1234
    await tick(dut)   # IF/ID now holds PC=0, instr=0xABCD1234 (from cycle 0)

    # Stall for 3 cycles
    dut.stall_i.value = 1
    saved_pc    = int(dut.pc_id_o.value)
    saved_instr = int(dut.instr_id_o.value)

    for _ in range(3):
        dut.imem_rdata_i.value = 0xDEADBEEF  # different data on bus
        await RisingEdge(dut.clk)
        await Timer(1, unit="ns")
        assert int(dut.pc_id_o.value)    == saved_pc,    "pc_id changed during stall"
        assert int(dut.instr_id_o.value) == saved_instr, "instr_id changed during stall"

    dut.stall_i.value = 0
    dut._log.info("PASS: stall holds IF/ID register contents for 3 cycles")
