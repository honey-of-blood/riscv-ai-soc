"""
Test runner for phase1 modules using cocotb_tools.runner (cocotb 2.x).
Usage:
    python run_tests.py alu
    python run_tests.py reg_file
"""
import sys
from pathlib import Path
from cocotb_tools.runner import get_runner

RTL_DIR = Path(__file__).parent.parent / "rtl"
BUILD_DIR = Path(__file__).parent / "sim_build"

def run(module_name: str):
    runner = get_runner("icarus")
    runner.build(
        sources=[RTL_DIR / f"{module_name}.sv"],
        hdl_toplevel=module_name,
        build_dir=BUILD_DIR / module_name,
        always=True,
    )
    runner.test(
        hdl_toplevel=module_name,
        test_module=f"test_{module_name}",
        build_dir=BUILD_DIR / module_name,
        test_dir=Path(__file__).parent,
        results_xml=str(BUILD_DIR / module_name / "results.xml"),
    )

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python run_tests.py <module_name>")
        sys.exit(1)
    run(sys.argv[1])
