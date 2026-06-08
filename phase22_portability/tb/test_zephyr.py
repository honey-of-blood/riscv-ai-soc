"""test_zephyr.py — Phase 22: Zephyr board definition completeness checks."""
from pathlib import Path

ROOT  = Path(__file__).resolve().parents[2]
ZEP   = ROOT / "phase22_portability" / "zephyr"
BOARD = ZEP / "boards" / "riscv" / "rv32_soc"
SOC   = ZEP / "soc" / "riscv" / "rv32_soc"


def test_dts_has_cpu_node():
    """rv32_soc.dts has a CPU node with rv32imac ISA and 100 MHz clock."""
    dts = (BOARD / "rv32_soc.dts").read_text()
    assert "cpus" in dts,                       "DTS missing cpus node"
    assert "riscv" in dts,                      "DTS CPU missing compatible = riscv"
    assert "rv32imac" in dts,                   "DTS missing riscv,isa = rv32imac"
    assert "100000000" in dts,                  "DTS missing 100 MHz clock-frequency"
    assert "interrupt-controller" in dts,       "DTS missing interrupt-controller"


def test_dts_has_uart_node():
    """rv32_soc.dts has uart0 with ns16550 compatible and correct address."""
    dts = (BOARD / "rv32_soc.dts").read_text()
    assert "uart0" in dts,            "DTS missing uart0 node"
    assert "ns16550" in dts,          "DTS uart0 missing compatible = ns16550"
    assert "10001000" in dts,         "DTS uart0 missing base address 0x10001000"
    assert "115200" in dts,           "DTS uart0 missing current-speed = 115200"
    assert "25000000" in dts,         "DTS uart0 missing clock-frequency"


def test_dts_has_memory_node():
    """rv32_soc.dts has sram0 memory node."""
    dts = (BOARD / "rv32_soc.dts").read_text()
    assert "sram0" in dts,            "DTS missing sram0 memory node"
    assert "mmio-sram" in dts or "memory" in dts, "DTS sram0 missing compatible"
    assert "20000000" in dts,         "DTS sram0 missing base address 0x20000000"
    assert "chosen" in dts,           "DTS missing chosen node"
    assert "zephyr,console" in dts,   "DTS chosen missing zephyr,console"


def test_kconfig_board():
    """Kconfig.board defines BOARD_RV32_SOC and variant options."""
    text = (BOARD / "Kconfig.board").read_text()
    assert "BOARD_RV32_SOC" in text,       "Kconfig.board missing BOARD_RV32_SOC"
    assert "depends on SOC_SERIES" in text, "Kconfig.board missing SOC_SERIES dependency"
    assert "bool" in text,                  "Kconfig.board missing bool keyword"


def test_zephyr_soc_h():
    """Zephyr soc.h defines UART base address and interrupt numbers."""
    text = (SOC / "soc.h").read_text()
    assert "UART0_BASE_ADDR" in text, "Zephyr soc.h missing UART0_BASE_ADDR"
    assert "0x10001000" in text,      "Zephyr soc.h wrong UART base address"
    assert "IRQ_UART0" in text,       "Zephyr soc.h missing IRQ_UART0"
    assert "IRQ_GPIO0" in text,       "Zephyr soc.h missing IRQ_GPIO0"


def test_zephyr_defconfig():
    """rv32_soc_defconfig enables UART, GPIO, and RV32IMAC."""
    text = (BOARD / "rv32_soc_defconfig").read_text()
    assert "CONFIG_UART_NS16550=y" in text, "defconfig missing UART_NS16550"
    assert "CONFIG_GPIO=y" in text,          "defconfig missing GPIO"
    assert "CONFIG_RISCV_ISA_EXT_C=y" in text, "defconfig missing RVC extension"
    assert "CONFIG_SYS_CLOCK_HW_CYCLES_PER_SEC=100000000" in text, \
        "defconfig missing 100 MHz clock frequency"
