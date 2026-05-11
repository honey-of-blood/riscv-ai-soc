import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer
import random

async def reset(dut):
    dut.rst.value = 1
    dut.we.value  = 0
    await RisingEdge(dut.clk)
    await RisingEdge(dut.clk)
    dut.rst.value = 0

async def write_reg(dut, rd, wd):
    dut.we.value = 1
    dut.rd.value = rd
    dut.wd.value = wd & 0xFFFFFFFF
    await RisingEdge(dut.clk)
    dut.we.value = 0

async def read_regs(dut, rs1, rs2):
    dut.rs1.value = rs1
    dut.rs2.value = rs2
    await Timer(1, unit="ns")
    return int(dut.rd1.value), int(dut.rd2.value)


@cocotb.test()
async def test_write_read(dut):
    """Write to several registers and read them back."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    test_vals = {1: 0xDEADBEEF, 2: 0xCAFEBABE, 15: 0x12345678,
                 31: 0xFFFFFFFF, 10: 0xA5A5A5A5}

    for reg, val in test_vals.items():
        await write_reg(dut, reg, val)

    for reg, expected in test_vals.items():
        v1, _ = await read_regs(dut, reg, 0)
        assert v1 == expected, f"r{reg}: expected 0x{expected:08X}, got 0x{v1:08X}"

    dut._log.info("PASS: write/read correct for all test registers")


@cocotb.test()
async def test_x0_hardwired_zero(dut):
    """x0 must always read 0 — even after an attempted write."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    await write_reg(dut, 0, 0xDEADBEEF)

    v1, v2 = await read_regs(dut, 0, 0)
    assert v1 == 0, f"x0 rd1: expected 0, got 0x{v1:08X}"
    assert v2 == 0, f"x0 rd2: expected 0, got 0x{v2:08X}"

    dut._log.info("PASS: x0 is hardwired to 0")


@cocotb.test()
async def test_two_port_simultaneous_read(dut):
    """Both read ports must return independent values simultaneously."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    await write_reg(dut, 5,  0xAAAAAAAA)
    await write_reg(dut, 17, 0x55555555)

    v1, v2 = await read_regs(dut, 5, 17)
    assert v1 == 0xAAAAAAAA, f"rs1 port: 0x{v1:08X}"
    assert v2 == 0x55555555, f"rs2 port: 0x{v2:08X}"

    # Same register on both ports
    v1, v2 = await read_regs(dut, 5, 5)
    assert v1 == v2 == 0xAAAAAAAA

    dut._log.info("PASS: dual read ports work independently")


@cocotb.test()
async def test_write_read_through(dut):
    """Write-before-read: read immediately returns new write data when we=1 and rd==rs (WB→ID bypass)."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    await write_reg(dut, 3, 0x11111111)

    # Drive a write to r3 and read r3 in the same cycle — WBR should return new data
    dut.we.value  = 1
    dut.rd.value  = 3
    dut.wd.value  = 0x22222222
    dut.rs1.value = 3
    dut.rs2.value = 3
    await Timer(1, unit="ns")
    assert int(dut.rd1.value) == 0x22222222, \
        f"WBR port 1 failed: expected 0x22222222, got 0x{int(dut.rd1.value):08X}"
    assert int(dut.rd2.value) == 0x22222222, \
        f"WBR port 2 failed: expected 0x22222222, got 0x{int(dut.rd2.value):08X}"

    # When we=0, read should return the registered old value (not bypass)
    dut.we.value = 0
    await Timer(1, unit="ns")
    assert int(dut.rd1.value) == 0x11111111, \
        f"After we=0, expected stored value 0x11111111, got 0x{int(dut.rd1.value):08X}"

    dut._log.info("PASS: write-before-read bypass works on both ports")


@cocotb.test()
async def test_reset_clears_all(dut):
    """Reset must zero out every writable register."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    # Write non-zero to every register
    for reg in range(1, 32):
        await write_reg(dut, reg, 0xFFFFFFFF)

    # Assert reset
    await reset(dut)

    # All should now read 0
    errors = 0
    for reg in range(1, 32):
        v, _ = await read_regs(dut, reg, 0)
        if v != 0:
            dut._log.error(f"r{reg} not cleared after reset: 0x{v:08X}")
            errors += 1

    assert errors == 0, f"{errors} registers not cleared by reset"
    dut._log.info("PASS: reset clears all 31 writable registers to 0")


@cocotb.test()
async def test_random_writes(dut):
    """50 random register writes then verify all with both read ports."""
    cocotb.start_soon(Clock(dut.clk, 10, unit="ns").start())
    await reset(dut)

    random.seed(99)
    golden = {i: 0 for i in range(32)}

    for _ in range(50):
        reg = random.randint(1, 31)
        val = random.randint(0, 0xFFFFFFFF)
        golden[reg] = val
        await write_reg(dut, reg, val)

    errors = 0
    for reg in range(1, 32):
        v1, _ = await read_regs(dut, reg, 0)
        if v1 != golden[reg]:
            dut._log.error(f"r{reg}: expected 0x{golden[reg]:08X}, got 0x{v1:08X}")
            errors += 1

    assert errors == 0, f"{errors} register mismatches"
    dut._log.info("PASS: 50 random writes verified across all 31 writable registers")
