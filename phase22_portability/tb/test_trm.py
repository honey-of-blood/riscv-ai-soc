"""test_trm.py — Phase 22: Technical Reference Manual completeness checks."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]
TRM  = ROOT / "phase22_portability" / "trm"

SECTIONS = [
    "index.md",
    "01_architecture_overview.md",
    "02_cpu_reference.md",
    "03_memory_map.md",
    "04_peripheral_reference.md",
    "05_accelerator_reference.md",
    "06_debug_guide.md",
    "07_getting_started.md",
    "08_benchmarks.md",
]


def test_all_trm_sections_exist():
    """All 9 TRM files (index + 8 sections) exist and are non-trivial."""
    for fname in SECTIONS:
        p = TRM / fname
        assert p.exists(), f"Missing TRM section: {p}"
        lines = p.read_text().splitlines()
        assert len(lines) >= 30, f"TRM section too short ({len(lines)} lines): {fname}"


def test_trm_register_tables():
    """04_peripheral_reference.md has register tables for every peripheral."""
    text = (TRM / "04_peripheral_reference.md").read_text()
    # Each peripheral should have a register table with Offset, Name, Access columns
    peripherals = ["UART", "GPIO", "CLINT", "SPI", "PLIC", "I2C", "WDT"]
    for p in peripherals:
        assert p in text, f"04_peripheral_reference.md missing section: {p}"
    # At least 6 register table rows (| Offset | ...)
    table_rows = re.findall(r"^\|.*0x[0-9A-Fa-f]+.*\|", text, re.MULTILINE)
    assert len(table_rows) >= 20, \
        f"Expected ≥20 register table rows, found {len(table_rows)}"


def test_trm_cpu_isa_table():
    """02_cpu_reference.md has CSR table and ISA extension table."""
    text = (TRM / "02_cpu_reference.md").read_text()
    for item in ["mstatus", "mcause", "mepc", "mtvec", "CSR"]:
        assert item in text, f"02_cpu_reference.md missing: {item}"
    # CSR table rows
    csr_rows = re.findall(r"^\|.*0x[0-9A-Fa-f]{3}.*\|", text, re.MULTILINE)
    assert len(csr_rows) >= 10, f"Expected ≥10 CSR table rows, found {len(csr_rows)}"


def test_trm_memory_map_table():
    """03_memory_map.md has address table covering all peripherals."""
    text = (TRM / "03_memory_map.md").read_text()
    for addr in ["0x1000_1000", "0x5000_0000", "0x0000_0000"]:
        assert addr in text, f"03_memory_map.md missing address: {addr}"
    # Table rows with address ranges
    rows = re.findall(r"^\|.*0x[0-9A-Fa-f_]+.*\|", text, re.MULTILINE)
    assert len(rows) >= 8, f"Expected ≥8 memory map rows, found {len(rows)}"


def test_trm_section_sizes():
    """Each TRM section (01–08) has at least 40 lines of content."""
    section_files = [s for s in SECTIONS if s != "index.md"]
    for fname in section_files:
        lines = (TRM / fname).read_text().splitlines()
        assert len(lines) >= 40, \
            f"TRM section {fname} has only {len(lines)} lines (expected ≥40)"
