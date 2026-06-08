"""test_cdc.py — Phase 23.5: cdc_sync2 module tests.

Tests:
  test_cdc_two_cycle_delay    — output lags input by exactly 2 clock cycles
  test_cdc_width_8            — 8-bit parameterization works
  test_cdc_stable_output      — no glitch on stable input
  test_cdc_async_reg_attr     — RTL contains ASYNC_REG="TRUE" attribute
  test_cdc_soc_wiring         — soc_top RTL wires cdc_sync2 on uart_rx and gpio_in

DUT: cdc_sync2
"""
import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, Timer
from pathlib import Path


@cocotb.test()
async def test_cdc_two_cycle_delay(dut):
    """Input applied at cycle 0 appears at output at cycle 2."""
    cocotb.start_soon(Clock(dut.clk_dst, 10, unit="ns").start())
    dut.d.value = 0
    await Timer(5, unit="ns")

    # Apply input on first rising edge
    await RisingEdge(dut.clk_dst)
    dut.d.value = 1

    # After 1 cycle: ff1 has captured 1, ff2 still 0
    await RisingEdge(dut.clk_dst)
    await Timer(1, unit="ns")
    assert int(dut.q.value) == 0, "q changed after only 1 cycle"

    # After 2 cycles: ff2 captures 1
    await RisingEdge(dut.clk_dst)
    await Timer(1, unit="ns")
    assert int(dut.q.value) == 1, f"q not 1 after 2 cycles; got {dut.q.value}"


@cocotb.test()
async def test_cdc_width_8(dut):
    """8-bit synchronizer passes all bits."""
    cocotb.start_soon(Clock(dut.clk_dst, 10, unit="ns").start())
    dut.d.value = 0
    await Timer(5, unit="ns")

    test_val = 0b10110101
    await RisingEdge(dut.clk_dst)
    dut.d.value = test_val

    # Wait 2 cycles
    await RisingEdge(dut.clk_dst)
    await RisingEdge(dut.clk_dst)
    await Timer(1, unit="ns")
    assert int(dut.q.value) == test_val, \
        f"8-bit sync failed: got 0b{int(dut.q.value):08b} expected 0b{test_val:08b}"


@cocotb.test()
async def test_cdc_stable_output(dut):
    """Stable input → stable output (no glitch after settling)."""
    cocotb.start_soon(Clock(dut.clk_dst, 10, unit="ns").start())
    dut.d.value = 0
    await Timer(5, unit="ns")

    dut.d.value = 0xA5
    # Wait 5 cycles for settling
    for _ in range(5):
        await RisingEdge(dut.clk_dst)
    await Timer(1, unit="ns")

    first = int(dut.q.value)
    for _ in range(10):
        await RisingEdge(dut.clk_dst)
        await Timer(1, unit="ns")
        assert int(dut.q.value) == first, "output glitched on stable input"


@cocotb.test()
async def test_cdc_async_reg_attr(dut):
    """RTL source contains ASYNC_REG=\"TRUE\" on ff1 and ff2."""
    src_path = Path(__file__).resolve().parents[2] / "phase23_reliability" / "rtl" / "cdc_sync2.sv"
    src = src_path.read_text()
    assert 'ASYNC_REG = "TRUE"' in src or 'ASYNC_REG="TRUE"' in src, \
        "ASYNC_REG attribute missing from cdc_sync2.sv"
    assert "ff1" in src and "ff2" in src, "ff1/ff2 synchronizer flip-flops missing"


@cocotb.test()
async def test_cdc_soc_wiring(dut):
    """soc_top.sv instantiates cdc_sync2 for uart_rx and gpio_in."""
    soc_src = Path(__file__).resolve().parents[2] / "phase5_soc" / "rtl" / "soc_top.sv"
    src = soc_src.read_text()
    assert "cdc_sync2" in src, "cdc_sync2 not instantiated in soc_top"
    assert "uart_rx_sync" in src or "uart_rx_i" in src and "cdc_sync2" in src, \
        "UART RX CDC missing in soc_top"
    assert "gpio_in_sync" in src or "gpio_in_i" in src and "cdc_sync2" in src, \
        "GPIO input CDC missing in soc_top"
    # Check max-delay constraints
    xdc = Path(__file__).resolve().parents[1] / "constraints" / "constraints.xdc"
    xdc_txt = xdc.read_text()
    assert "set_max_delay" in xdc_txt, "CDC max-delay constraints missing"
    assert "clk_cpu" in xdc_txt and "clk_peri" in xdc_txt, \
        "clk_cpu/clk_peri not referenced in max-delay constraints"
