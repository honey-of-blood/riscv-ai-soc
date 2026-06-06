"""
Phase 3 cocotb unit test runner.
Usage:
    python run_tests.py axi_sram
    python run_tests.py axi_apb_bridge
    python run_tests.py axi_sram --waves      # dump FST for GTKWave

Waveform output: sim_build/<module>/<toplevel>.fst
"""
import sys
from pathlib import Path
from cocotb_tools.runner import get_runner

RTL_DIR   = Path(__file__).parent.parent / "rtl"
BUILD_DIR = Path(__file__).parent / "sim_build"

CONFIGS = {
    "axi_sram": {
        "sources":  [RTL_DIR / "axi_sram.sv"],
        "toplevel": "axi_sram",
    },
    "axi_apb_bridge": {
        "sources":  [RTL_DIR / "axi_apb_bridge.sv"],
        "toplevel": "axi_apb_bridge",
    },
    "axi4_crossbar": {
        "sources":  [
            RTL_DIR / "axi4_crossbar.sv",
            RTL_DIR / "axi_sram.sv",
        ],
        "toplevel": "axi4_crossbar",
    },
    "axi4_crossbar_stress": {
        "sources":  [
            RTL_DIR / "axi4_crossbar.sv",
            RTL_DIR / "axi_sram.sv",
        ],
        "toplevel": "axi4_crossbar",
    },
}

def run(module_name: str, waves: bool = False):
    cfg      = CONFIGS[module_name]
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
    if len(sys.argv) < 2:
        print("Usage: python run_tests.py <module> [--waves]")
        sys.exit(1)
    run(sys.argv[1], waves="--waves" in sys.argv)
