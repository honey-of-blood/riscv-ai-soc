"""
Phase 5 adapter unit test runner.
Usage:
    python run_unit_tests.py dmem_axi_adapter
    python run_unit_tests.py dmem_axi_adapter --waves
"""
import sys
from pathlib import Path
from cocotb_tools.runner import get_runner

RTL_DIR   = Path(__file__).parent.parent / "rtl"
BUILD_DIR = Path(__file__).parent / "sim_build"

MODULES = {
    "dmem_axi_adapter": {
        "sources":  [RTL_DIR / "dmem_axi_adapter.sv"],
        "toplevel": "dmem_axi_adapter",
    },
}

def run(module_name: str, waves: bool = False):
    cfg    = MODULES[module_name]
    runner = get_runner("icarus")
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
        print("Usage: python run_unit_tests.py <module> [--waves]")
        sys.exit(1)
    run(sys.argv[1], waves="--waves" in sys.argv)
