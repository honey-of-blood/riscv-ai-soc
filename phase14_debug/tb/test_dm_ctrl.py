"""
Phase 14 — Debug Module control tests.
DUT: debug_wrap (riscv_core + dm_top + trigger_module)
"""
import cocotb
from cocotb.triggers import RisingEdge, Timer
from cocotb.clock import Clock

CLK_PERIOD = 10  # ns


# ---------------------------------------------------------------------------
# AXI4-Lite helper: single 32-bit write to DM register
# ---------------------------------------------------------------------------
async def dm_write(dut, addr, data):
    """AXI4-Lite write transaction to debug module."""
    dut.dm_awaddr.value  = addr
    dut.dm_wdata.value   = data
    dut.dm_wstrb.value   = 0xF
    dut.dm_awvalid.value = 1
    dut.dm_wvalid.value  = 1
    dut.dm_arvalid.value = 0
    await RisingEdge(dut.clk)
    dut.dm_awvalid.value = 0
    dut.dm_wvalid.value  = 0
    # Wait for bvalid
    for _ in range(10):
        await RisingEdge(dut.clk)
        if dut.dm_bvalid.value == 1:
            dut.dm_bready.value = 1
            await RisingEdge(dut.clk)
            dut.dm_bready.value = 0
            return
    raise RuntimeError(f"dm_write timeout addr=0x{addr:x}")


async def dm_read(dut, addr):
    """AXI4-Lite read transaction from debug module."""
    dut.dm_araddr.value  = addr
    dut.dm_arvalid.value = 1
    dut.dm_awvalid.value = 0
    dut.dm_wvalid.value  = 0
    dut.dm_rready.value  = 1
    await RisingEdge(dut.clk)
    dut.dm_arvalid.value = 0
    # Wait for rvalid
    for _ in range(20):
        await RisingEdge(dut.clk)
        if dut.dm_rvalid.value == 1:
            val = int(dut.dm_rdata.value)
            dut.dm_rready.value = 0
            return val
    raise RuntimeError(f"dm_read timeout addr=0x{addr:x}")


# ---------------------------------------------------------------------------
# Reset helper
# ---------------------------------------------------------------------------
async def reset_dut(dut, cycles=5):
    """Apply synchronous reset. Starts clock if not already running."""
    cocotb.start_soon(Clock(dut.clk, CLK_PERIOD, units="ns").start())
    dut.rst.value        = 1
    dut.imem_rdata.value = 0x00000013  # NOP (ADDI x0, x0, 0)
    dut.dmem_rdata.value = 0
    dut.dmem_stall.value = 0
    dut.dm_awaddr.value  = 0
    dut.dm_araddr.value  = 0
    dut.dm_awvalid.value = 0
    dut.dm_wvalid.value  = 0
    dut.dm_arvalid.value = 0
    dut.dm_wdata.value   = 0
    dut.dm_wstrb.value   = 0xF
    dut.dm_bready.value  = 1
    dut.dm_rready.value  = 1
    for _ in range(cycles):
        await RisingEdge(dut.clk)
    dut.rst.value = 0
    await RisingEdge(dut.clk)


# ---------------------------------------------------------------------------
# Test 1: Halt and resume
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_halt_resume(dut):
    """Write dmcontrol haltreq=1, verify halt, then resume."""
    cocotb.log.info("test_halt_resume start")
    await reset_dut(dut)

    # Let core run briefly
    for _ in range(10):
        await RisingEdge(dut.clk)

    # Request halt: dmcontrol[31]=1, dmactive[0]=1
    DMCONTROL = 0x40
    await dm_write(dut, DMCONTROL, 0x8000_0001)

    # Wait for core to halt (debug_mode FF takes 2 cycles after halt_req)
    halted = False
    for _ in range(20):
        await RisingEdge(dut.clk)
        if dut.dbg_halted.value == 1:
            halted = True
            break
    assert halted, "Core did not halt after haltreq"
    cocotb.log.info("Core halted OK")

    # Verify dmstatus allhalted (bit 11)
    DMSTATUS = 0x44
    status = await dm_read(dut, DMSTATUS)
    assert (status >> 11) & 1 == 1, f"allhalted not set: 0x{status:08x}"

    # Release halt + resume: dmcontrol[30]=1, [31]=0
    await dm_write(dut, DMCONTROL, 0x4000_0001)

    # Wait for resume
    resumed = False
    for _ in range(20):
        await RisingEdge(dut.clk)
        if dut.dbg_halted.value == 0:
            resumed = True
            break
    assert resumed, "Core did not resume after resumereq"
    cocotb.log.info("Core resumed OK")


# ---------------------------------------------------------------------------
# Test 2: Abstract command GPR read
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_abstract_gpr_read(dut):
    """Load firmware ADDI t0,x0,42; halt; read GPR5 → expect 42."""
    cocotb.log.info("test_abstract_gpr_read start")

    # Firmware: ADDI t0 (x5), x0, 42  = 0x02a00293
    # Followed by infinite loop: JAL x0, 0 = 0x0000006F
    ADDI_T0_42  = 0x02A00293  # addi x5, x0, 42
    JAL_LOOP    = 0x0000006F  # jal x0, 0

    imem = {0: ADDI_T0_42, 4: JAL_LOOP}

    async def imem_model(dut):
        while True:
            await RisingEdge(dut.clk)
            try:
                addr = int(dut.imem_addr.value)
                dut.imem_rdata.value = imem.get(addr, 0x0000006F)
            except ValueError:
                dut.imem_rdata.value = 0x0000006F

    cocotb.start_soon(imem_model(dut))

    await reset_dut(dut)

    # Let core execute a few cycles so ADDI reaches WB
    for _ in range(20):
        await RisingEdge(dut.clk)

    # Halt
    DMCONTROL = 0x40
    await dm_write(dut, DMCONTROL, 0x8000_0001)

    halted = False
    for _ in range(20):
        await RisingEdge(dut.clk)
        if dut.dbg_halted.value == 1:
            halted = True
            break
    assert halted, "Core did not halt"

    # Issue abstract command: read GPR5 (t0)
    # command: cmdtype=0, aarsize=2(=32-bit), transfer=1, write=0, regno=0x1005
    # [31:24]=0, [22:20]=010, [19]=0, [18]=0, [17]=1, [16]=0, [15:0]=0x1005
    CMD_READ_GPR5 = (0 << 24) | (2 << 20) | (0 << 19) | (0 << 18) | (1 << 17) | (0 << 16) | 0x1005
    COMMAND = 0x5C
    DATA0   = 0x10

    await dm_write(dut, COMMAND, CMD_READ_GPR5)

    # Wait for command to complete (abstractcs.busy goes low)
    ABSTRACTCS = 0x58
    for _ in range(30):
        await RisingEdge(dut.clk)
        acs = await dm_read(dut, ABSTRACTCS)
        if (acs >> 12) & 1 == 0:  # busy=0
            break

    # Check cmderr
    acs = await dm_read(dut, ABSTRACTCS)
    cmderr = (acs >> 8) & 0x7
    assert cmderr == 0, f"cmderr={cmderr}, abstractcs=0x{acs:08x}"

    # Read data0
    data0 = await dm_read(dut, DATA0)
    cocotb.log.info(f"GPR5 = 0x{data0:08x} (expected 0x2A=42)")
    assert data0 == 42, f"Expected GPR5=42, got {data0}"
    cocotb.log.info("test_abstract_gpr_read PASS")


# ---------------------------------------------------------------------------
# Test 3: Abstract command GPR write
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_abstract_gpr_write(dut):
    """Halt, write GPR6=0xDEAD, verify read-back."""
    cocotb.log.info("test_abstract_gpr_write start")
    await reset_dut(dut)

    for _ in range(5):
        await RisingEdge(dut.clk)

    # Halt
    DMCONTROL = 0x40
    await dm_write(dut, DMCONTROL, 0x8000_0001)

    halted = False
    for _ in range(20):
        await RisingEdge(dut.clk)
        if dut.dbg_halted.value == 1:
            halted = True
            break
    assert halted, "Core did not halt"

    DATA0   = 0x10
    COMMAND = 0x5C

    # Write 0xDEAD to data0
    await dm_write(dut, DATA0, 0xDEAD)

    # Issue write GPR6 command: cmdtype=0, aarsize=2, transfer=1, write=1, regno=0x1006
    CMD_WRITE_GPR6 = (0 << 24) | (2 << 20) | (0 << 19) | (0 << 18) | (1 << 17) | (1 << 16) | 0x1006
    await dm_write(dut, COMMAND, CMD_WRITE_GPR6)

    # Wait for completion
    ABSTRACTCS = 0x58
    for _ in range(30):
        await RisingEdge(dut.clk)
        acs = await dm_read(dut, ABSTRACTCS)
        if (acs >> 12) & 1 == 0:
            break

    acs = await dm_read(dut, ABSTRACTCS)
    cmderr = (acs >> 8) & 0x7
    assert cmderr == 0, f"cmderr={cmderr}"

    # Now read back GPR6
    CMD_READ_GPR6 = (0 << 24) | (2 << 20) | (0 << 19) | (0 << 18) | (1 << 17) | (0 << 16) | 0x1006
    await dm_write(dut, COMMAND, CMD_READ_GPR6)

    for _ in range(30):
        await RisingEdge(dut.clk)
        acs = await dm_read(dut, ABSTRACTCS)
        if (acs >> 12) & 1 == 0:
            break

    data0 = await dm_read(dut, DATA0)
    cocotb.log.info(f"GPR6 readback = 0x{data0:08x}")
    assert data0 == 0xDEAD, f"Expected 0xDEAD, got 0x{data0:08x}"
    cocotb.log.info("test_abstract_gpr_write PASS")


# ---------------------------------------------------------------------------
# Test 4: dmstatus reflects core state
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_dmstatus(dut):
    """Verify allhalted/allrunning bits match core state."""
    cocotb.log.info("test_dmstatus start")
    await reset_dut(dut)

    DMSTATUS  = 0x44
    DMCONTROL = 0x40

    for _ in range(5):
        await RisingEdge(dut.clk)

    # Check running initially
    status = await dm_read(dut, DMSTATUS)
    allrunning  = (status >> 9) & 1  # bit[9]
    anyrunning  = (status >> 8) & 1  # bit[8] — wait: re-check encoding
    # Per spec: [11]=allhalted, [10]=anyhalted, [9]=allrunning, [8]=anyrunning
    allhalted   = (status >> 11) & 1
    anyhalted   = (status >> 10) & 1
    allrunning2 = (status >> 9)  & 1
    anyrunning2 = (status >> 8)  & 1
    cocotb.log.info(f"dmstatus=0x{status:08x} allhalted={allhalted} allrunning={allrunning2}")
    assert allhalted == 0,  "Core should be running initially"
    assert allrunning2 == 1, "Core should be running initially"

    # Halt
    await dm_write(dut, DMCONTROL, 0x8000_0001)

    halted = False
    for _ in range(20):
        await RisingEdge(dut.clk)
        if dut.dbg_halted.value == 1:
            halted = True
            break
    assert halted

    status = await dm_read(dut, DMSTATUS)
    allhalted  = (status >> 11) & 1
    anyhalted  = (status >> 10) & 1
    allrunning = (status >> 9)  & 1
    cocotb.log.info(f"dmstatus=0x{status:08x} allhalted={allhalted}")
    assert allhalted == 1, "allhalted should be 1 when halted"
    assert allrunning == 0, "allrunning should be 0 when halted"
    cocotb.log.info("test_dmstatus PASS")


# ---------------------------------------------------------------------------
# Test 5: abstractcs datacount and progbufsize
# ---------------------------------------------------------------------------
@cocotb.test()
async def test_abstractcs_datacount(dut):
    """Verify datacount=1, progbufsize=4 in abstractcs."""
    cocotb.log.info("test_abstractcs_datacount start")
    await reset_dut(dut)

    for _ in range(5):
        await RisingEdge(dut.clk)

    ABSTRACTCS = 0x58
    acs = await dm_read(dut, ABSTRACTCS)
    cocotb.log.info(f"abstractcs=0x{acs:08x}")
    datacount   = acs & 0xF
    progbufsize = (acs >> 24) & 0x1F
    assert datacount == 1,   f"datacount={datacount}, expected 1"
    assert progbufsize == 4, f"progbufsize={progbufsize}, expected 4"
    cocotb.log.info("test_abstractcs_datacount PASS")
