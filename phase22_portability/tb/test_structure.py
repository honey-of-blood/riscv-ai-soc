"""test_structure.py — Phase 22: file structure completeness checks."""
from pathlib import Path

ROOT  = Path(__file__).resolve().parents[2]
PH22  = ROOT / "phase22_portability"
SDK   = PH22 / "sdk"
ZEP   = PH22 / "zephyr"


def test_rtl_files_exist():
    """tech_cells_intel.sv and fpga_top_de1_soc.sv exist."""
    rtl = PH22 / "rtl"
    for f in ["tech_cells_intel.sv", "fpga_top_de1_soc.sv"]:
        p = rtl / f
        assert p.exists(), f"Missing RTL file: {p}"
        assert p.stat().st_size > 500, f"RTL file too small (stub?): {p}"


def test_constraint_files_exist():
    """de1_soc.sdc and ulx3s.lpf exist with clock constraints."""
    cdir = PH22 / "constraints"
    sdc = (cdir / "de1_soc.sdc").read_text()
    lpf = (cdir / "ulx3s.lpf").read_text()
    assert "create_clock" in sdc,    "de1_soc.sdc missing create_clock"
    assert "LOCATE COMP" in lpf,     "ulx3s.lpf missing LOCATE COMP"
    assert "CLOCK_50" in sdc or "clk50" in sdc, "de1_soc.sdc missing CLOCK_50 constraint"
    assert "clk_25mhz" in lpf,       "ulx3s.lpf missing clk_25mhz"


def test_scripts_exist():
    """All three scripts exist with required content."""
    scripts = PH22 / "scripts"
    tcl = (scripts / "quartus_build.tcl").read_text()
    mk  = (scripts / "Makefile.ecp5").read_text()
    sh  = (scripts / "ci_yosys_check.sh").read_text()

    assert "execute_flow" in tcl,   "quartus_build.tcl missing execute_flow"
    assert "DEVICE" in tcl,         "quartus_build.tcl missing DEVICE"
    assert "synth_ecp5" in mk,      "Makefile.ecp5 missing synth_ecp5"
    assert "nextpnr" in mk,         "Makefile.ecp5 missing nextpnr"
    assert "yosys" in sh,           "ci_yosys_check.sh missing yosys call"
    assert "PASS" in sh,            "ci_yosys_check.sh missing PASS message"


def test_sdk_bsp_headers_exist():
    """All 6 BSP headers exist with required API declarations."""
    inc = SDK / "bsp" / "include"
    checks = {
        "soc.h":    ["REG32", "UART_BASE", "GPIO_BASE", "ACCEL_BASE"],
        "uart.h":   ["uart_init", "uart_putchar", "uart_puts", "uart_getchar"],
        "gpio.h":   ["gpio_set_dir", "gpio_write", "gpio_read"],
        "i2c.h":    ["i2c_init", "i2c_write", "i2c_read"],
        "accel.h":  ["accel_init", "accel_matmul_int4", "ACCEL_CTRL"],
        "crypto.h": ["aes128_ecb_encrypt", "sha256_hash", "sha256_verify"],
    }
    for fname, symbols in checks.items():
        text = (inc / fname).read_text()
        for sym in symbols:
            assert sym in text, f"{fname} missing symbol: {sym}"


def test_sdk_bsp_sources_exist():
    """All BSP C source files exist."""
    src = SDK / "bsp" / "src"
    for f in ["uart.c", "gpio.c", "i2c.c", "accel.c", "syscalls.c"]:
        p = src / f
        assert p.exists(), f"Missing BSP source: {p}"
        assert p.stat().st_size > 100, f"BSP source too small: {p}"


def test_sdk_examples_exist():
    """All 5 example directories have main.c and Makefile."""
    examples = ["hello_world", "freertos_blinky", "mnist_inference",
                "keyword_spotting", "secure_ota"]
    for ex in examples:
        d = SDK / "examples" / ex
        assert (d / "main.c").exists(),   f"Missing: {d}/main.c"
        assert (d / "Makefile").exists(), f"Missing: {d}/Makefile"
        assert (d / "main.c").stat().st_size > 200, f"main.c too small: {d}"
