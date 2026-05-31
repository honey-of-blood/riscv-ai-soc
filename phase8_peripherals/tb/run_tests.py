"""
Test runner for Phase 8 peripheral unit tests.
Usage:
    python run_tests.py uart
    python run_tests.py gpio
    python run_tests.py timer
    python run_tests.py uart --waves
"""
import sys
from pathlib import Path
from cocotb_tools.runner import get_runner

RTL_DIR   = Path(__file__).parent.parent / "rtl"
BUILD_DIR = Path(__file__).parent / "sim_build"

MODULES = {
    "uart":      {"sources": [RTL_DIR / "uart.sv"],      "toplevel": "uart"},
    "gpio":      {"sources": [RTL_DIR / "gpio.sv"],      "toplevel": "gpio"},
    "timer":     {"sources": [RTL_DIR / "timer.sv"],     "toplevel": "timer"},
    "spi":       {"sources": [RTL_DIR / "spi.sv"],       "toplevel": "spi"},
    "clint":     {"sources": [RTL_DIR / "clint.sv"],     "toplevel": "clint"},
    "plic":      {"sources": [RTL_DIR / "plic.sv"],      "toplevel": "plic"},
    "apb_demux": {"sources": [RTL_DIR / "apb_demux.sv"], "toplevel": "apb_demux"},
}

def run(module_name: str, waves: bool = False):
    cfg      = MODULES[module_name]
    runner   = get_runner("icarus")
    runner.build(
        sources=cfg["sources"],
        hdl_toplevel=cfg["toplevel"],
        build_dir=BUILD_DIR / module_name,
        always=True,
        waves=waves,
    )
    runner.test(
        hdl_toplevel=cfg["toplevel"],
        test_module=f"test_{module_name}",
        build_dir=BUILD_DIR / module_name,
        test_dir=Path(__file__).parent,
        results_xml=str(BUILD_DIR / module_name / "results.xml"),
        waves=waves,
    )

if __name__ == "__main__":
    if len(sys.argv) not in (2, 3):
        print("Usage: python run_tests.py <uart|gpio|timer|spi> [--waves]")
        sys.exit(1)
    run(sys.argv[1], waves="--waves" in sys.argv)
