"""
cocotb unit tests for apb_demux.sv.

The demux fans one APB master to 8 peripheral slaves using paddr[15:12] as
the select:
  sel=0  0x1000_0xxx  apb_regs
  sel=1  0x1000_1xxx  UART
  sel=2  0x1000_2xxx  GPIO
  sel=3  0x1000_3xxx  Timer
  sel=4  0x1000_4xxx  SPI
  sel=5  0x1000_5xxx  CLINT
  sel=6  0x1000_6xxx  PLIC
  sel=7  0x1000_7xxx  DMA

Tests:
  1–8:  Each slave gets psel=1 for its address; others see psel=0.
  9:    paddr[11:0] is forwarded correctly as local_addr to every slave.
  10:   prdata mux returns the responding slave's data.
  11:   pready mux — forwarded from the selected slave.
  12:   pslverr forwarded from apb_regs (sel=0); 0 for other slaves.
  13:   penable / pwrite / pwdata broadcast to all slaves.
  14:   No transaction (psel=0) → all slave psel = 0.
"""
import cocotb
from cocotb.triggers import Timer

SLAVE_NAMES = ["regs", "uart", "gpio", "timer", "spi", "clint", "plic", "dma"]

async def wait_ns(n=1):
    await Timer(n, unit="ns")

def set_apb(dut, paddr, psel, penable, pwrite, pwdata, pstrb=0xF):
    dut.paddr.value   = paddr
    dut.psel.value    = psel
    dut.penable.value = penable
    dut.pwrite.value  = pwrite
    dut.pwdata.value  = pwdata
    dut.pstrb.value   = pstrb

def set_slave_defaults(dut):
    """Drive default slave responses: prdata=0, pready=1, pslverr=0."""
    for name in SLAVE_NAMES:
        try: getattr(dut, f"{name}_prdata").value  = 0
        except AttributeError: pass
        try: getattr(dut, f"{name}_pready").value  = 1
        except AttributeError: pass
    # regs has pslverr
    try: dut.regs_pslverr.value = 0
    except AttributeError: pass

def base_addr(sel):
    return 0x10000000 | (sel << 12)


# ── 1–8: Slave psel decode ───────────────────────────────────────────────────

@cocotb.test()
async def test_psel_regs(dut):
    """sel=0 (0x1000_0xxx) → regs_psel=1; all others=0."""
    set_slave_defaults(dut)
    set_apb(dut, paddr=0x10000004, psel=1, penable=1, pwrite=1, pwdata=0xAA)
    await wait_ns(1)
    assert int(dut.regs_psel.value)  == 1, "regs_psel should be 1"
    for name in SLAVE_NAMES[1:]:
        v = int(getattr(dut, f"{name}_psel").value)
        assert v == 0, f"{name}_psel should be 0, got {v}"


@cocotb.test()
async def test_psel_uart(dut):
    """sel=1 (0x1000_1xxx) → uart_psel=1."""
    set_slave_defaults(dut)
    set_apb(dut, paddr=0x10001000, psel=1, penable=0, pwrite=0, pwdata=0)
    await wait_ns(1)
    assert int(dut.uart_psel.value) == 1
    for name in [n for n in SLAVE_NAMES if n != "uart"]:
        assert int(getattr(dut, f"{name}_psel").value) == 0, f"{name}_psel should be 0"


@cocotb.test()
async def test_psel_gpio(dut):
    """sel=2 (0x1000_2xxx) → gpio_psel=1."""
    set_slave_defaults(dut)
    set_apb(dut, paddr=0x10002008, psel=1, penable=1, pwrite=0, pwdata=0)
    await wait_ns(1)
    assert int(dut.gpio_psel.value) == 1
    for name in [n for n in SLAVE_NAMES if n != "gpio"]:
        assert int(getattr(dut, f"{name}_psel").value) == 0


@cocotb.test()
async def test_psel_timer(dut):
    """sel=3 (0x1000_3xxx) → timer_psel=1."""
    set_slave_defaults(dut)
    set_apb(dut, paddr=0x10003000, psel=1, penable=1, pwrite=1, pwdata=100)
    await wait_ns(1)
    assert int(dut.timer_psel.value) == 1
    for name in [n for n in SLAVE_NAMES if n != "timer"]:
        assert int(getattr(dut, f"{name}_psel").value) == 0


@cocotb.test()
async def test_psel_spi(dut):
    """sel=4 (0x1000_4xxx) → spi_psel=1."""
    set_slave_defaults(dut)
    set_apb(dut, paddr=0x10004004, psel=1, penable=0, pwrite=1, pwdata=0xFF)
    await wait_ns(1)
    assert int(dut.spi_psel.value) == 1
    for name in [n for n in SLAVE_NAMES if n != "spi"]:
        assert int(getattr(dut, f"{name}_psel").value) == 0


@cocotb.test()
async def test_psel_clint(dut):
    """sel=5 (0x1000_5xxx) → clint_psel=1."""
    set_slave_defaults(dut)
    set_apb(dut, paddr=0x10005008, psel=1, penable=1, pwrite=0, pwdata=0)
    await wait_ns(1)
    assert int(dut.clint_psel.value) == 1
    for name in [n for n in SLAVE_NAMES if n != "clint"]:
        assert int(getattr(dut, f"{name}_psel").value) == 0


@cocotb.test()
async def test_psel_plic(dut):
    """sel=6 (0x1000_6xxx) → plic_psel=1."""
    set_slave_defaults(dut)
    set_apb(dut, paddr=0x10006000, psel=1, penable=1, pwrite=0, pwdata=0)
    await wait_ns(1)
    assert int(dut.plic_psel.value) == 1
    for name in [n for n in SLAVE_NAMES if n != "plic"]:
        assert int(getattr(dut, f"{name}_psel").value) == 0


@cocotb.test()
async def test_psel_dma(dut):
    """sel=7 (0x1000_7xxx) → dma_psel=1."""
    set_slave_defaults(dut)
    set_apb(dut, paddr=0x10007004, psel=1, penable=0, pwrite=0, pwdata=0)
    await wait_ns(1)
    assert int(dut.dma_psel.value) == 1
    for name in [n for n in SLAVE_NAMES if n != "dma"]:
        assert int(getattr(dut, f"{name}_psel").value) == 0


# ── 9: Local address forwarding ──────────────────────────────────────────────

@cocotb.test()
async def test_local_addr_forward(dut):
    """paddr[11:0] forwarded correctly to selected slave."""
    set_slave_defaults(dut)
    for sel, name in enumerate(SLAVE_NAMES):
        addr = base_addr(sel) | 0xABC
        set_apb(dut, paddr=addr, psel=1, penable=1, pwrite=0, pwdata=0)
        await wait_ns(1)
        local = int(getattr(dut, f"{name}_paddr").value)
        assert local == 0xABC, \
            f"sel={sel} ({name}): paddr={hex(local)}, expected 0xABC"


# ── 10: prdata mux ────────────────────────────────────────────────────────────

@cocotb.test()
async def test_prdata_mux(dut):
    """prdata output equals responding slave's prdata."""
    patterns = [0x11111111, 0x22222222, 0x33333333, 0x44444444,
                0x55555555, 0x66666666, 0x77777777, 0x88888888]
    set_slave_defaults(dut)

    for sel, name in enumerate(SLAVE_NAMES):
        # Set all slave rdata to unique values; the mux should pick the selected one
        for i, n in enumerate(SLAVE_NAMES):
            try: getattr(dut, f"{n}_prdata").value = patterns[i]
            except AttributeError: pass
        set_apb(dut, paddr=base_addr(sel), psel=1, penable=1, pwrite=0, pwdata=0)
        await wait_ns(1)
        got = int(dut.prdata.value)
        assert got == patterns[sel], \
            f"sel={sel}: prdata={hex(got)}, expected {hex(patterns[sel])}"


# ── 11: pready mux ───────────────────────────────────────────────────────────

@cocotb.test()
async def test_pready_mux(dut):
    """pready follows the selected slave's pready."""
    set_slave_defaults(dut)

    for sel, name in enumerate(SLAVE_NAMES):
        # Drive the selected slave's pready = 0; others = 1
        for n in SLAVE_NAMES:
            try: getattr(dut, f"{n}_pready").value = (0 if n == name else 1)
            except AttributeError: pass
        set_apb(dut, paddr=base_addr(sel), psel=1, penable=1, pwrite=0, pwdata=0)
        await wait_ns(1)
        assert int(dut.pready.value) == 0, \
            f"sel={sel}: pready should be 0 (slave not ready)"


# ── 12: pslverr forwarded from apb_regs (sel=0 only) ─────────────────────────

@cocotb.test()
async def test_pslverr_regs(dut):
    """pslverr is forwarded from regs_pslverr when sel=0."""
    set_slave_defaults(dut)
    dut.regs_pslverr.value = 1
    set_apb(dut, paddr=0x10000000, psel=1, penable=1, pwrite=1, pwdata=0)
    await wait_ns(1)
    assert int(dut.pslverr.value) == 1, "pslverr should be 1 when regs_pslverr=1 and sel=0"

    # Other slaves: pslverr is 0 (not wired)
    dut.regs_pslverr.value = 0
    set_apb(dut, paddr=0x10001000, psel=1, penable=1, pwrite=0, pwdata=0)
    await wait_ns(1)
    assert int(dut.pslverr.value) == 0, "pslverr should be 0 for uart (sel=1)"


# ── 13: Broadcast of penable / pwrite / pwdata ───────────────────────────────

@cocotb.test()
async def test_broadcast(dut):
    """penable, pwrite, pwdata are broadcast to all slaves."""
    set_slave_defaults(dut)
    set_apb(dut, paddr=0x10002000, psel=1, penable=1, pwrite=1, pwdata=0xBEEF0000)
    await wait_ns(1)
    for name in SLAVE_NAMES:
        assert int(getattr(dut, f"{name}_penable").value) == 1, \
            f"{name}_penable should be 1"
        assert int(getattr(dut, f"{name}_pwrite").value)  == 1, \
            f"{name}_pwrite should be 1"
        assert int(getattr(dut, f"{name}_pwdata").value)  == 0xBEEF0000, \
            f"{name}_pwdata mismatch"


# ── 14: psel=0 → all slave psel = 0 ─────────────────────────────────────────

@cocotb.test()
async def test_no_select(dut):
    """When psel=0, all slave psel outputs are 0."""
    set_slave_defaults(dut)
    set_apb(dut, paddr=0x10001000, psel=0, penable=0, pwrite=0, pwdata=0)
    await wait_ns(1)
    for name in SLAVE_NAMES:
        v = int(getattr(dut, f"{name}_psel").value)
        assert v == 0, f"{name}_psel={v} should be 0 when master psel=0"
