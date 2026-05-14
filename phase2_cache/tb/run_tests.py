"""
Test runner for phase2 cache modules.
Usage:
    python run_tests.py cache_top
    python run_tests.py cache_tag_array
    python run_tests.py cache_data_array
"""
import sys
from pathlib import Path
from cocotb_tools.runner import get_runner

RTL_DIR   = Path(__file__).parent.parent / "rtl"
BUILD_DIR = Path(__file__).parent / "sim_build"

CONFIGS = {
    "cache_top": {
        "sources": [
            RTL_DIR / "cache_tag_array.sv",
            RTL_DIR / "cache_data_array.sv",
            RTL_DIR / "cache_controller.sv",
            RTL_DIR / "cache_top.sv",
        ],
        "toplevel": "cache_top",
    },
    "cache_tag_array": {
        "sources": [RTL_DIR / "cache_tag_array.sv"],
        "toplevel": "cache_tag_array",
    },
    "cache_data_array": {
        "sources": [RTL_DIR / "cache_data_array.sv"],
        "toplevel": "cache_data_array",
    },
}

def run(module_name: str):
    cfg      = CONFIGS.get(module_name, {})
    sources  = cfg.get("sources",  [RTL_DIR / f"{module_name}.sv"])
    toplevel = cfg.get("toplevel", module_name)

    runner = get_runner("icarus")
    runner.build(
        sources=sources,
        hdl_toplevel=toplevel,
        build_dir=BUILD_DIR / module_name,
        always=True,
    )
    runner.test(
        hdl_toplevel=toplevel,
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
