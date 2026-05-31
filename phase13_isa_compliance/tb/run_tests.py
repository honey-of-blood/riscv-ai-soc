"""
Phase 13 ISA compliance test runner.
Usage:
    python run_tests.py          # run all tests
    python run_tests.py --waves  # also generate VCD
"""
import sys
from pathlib import Path
from cocotb_tools.runner import get_runner

RTL_DIR  = Path(__file__).parent.parent.parent / "phase1_riscv_core" / "rtl"
BUILD_DIR = Path(__file__).parent.parent / "sim_build"

RTL_SOURCES = [
    RTL_DIR / "rvc_expander.sv",
    RTL_DIR / "csr_file.sv",
    RTL_DIR / "pmp_checker.sv",
    RTL_DIR / "atomic_unit.sv",
    RTL_DIR / "alu.sv",
    RTL_DIR / "reg_file.sv",
    RTL_DIR / "imm_gen.sv",
    RTL_DIR / "fetch_stage.sv",
    RTL_DIR / "pipeline_reg_IF_ID.sv",
    RTL_DIR / "decode_stage.sv",
    RTL_DIR / "pipeline_reg_ID_EX.sv",
    RTL_DIR / "execute_stage.sv",
    RTL_DIR / "pipeline_reg_EX_MEM.sv",
    RTL_DIR / "memory_stage.sv",
    RTL_DIR / "pipeline_reg_MEM_WB.sv",
    RTL_DIR / "writeback_stage.sv",
    RTL_DIR / "hazard_unit.sv",
    RTL_DIR / "forwarding_unit.sv",
    RTL_DIR / "mext_unit.sv",
    RTL_DIR / "riscv_core.sv",
]

def run(module="all", waves=False):
    runner = get_runner("icarus")
    runner.build(
        sources=RTL_SOURCES,
        hdl_toplevel="riscv_core",
        build_dir=BUILD_DIR,
        always=True,
        waves=waves,
    )
    if module == "all":
        test_modules = "test_phase13,test_phase13_deep"
    else:
        test_modules = module
    runner.test(
        hdl_toplevel="riscv_core",
        test_module=test_modules,
        build_dir=BUILD_DIR,
        test_dir=Path(__file__).parent,
        results_xml=str(BUILD_DIR / "results.xml"),
        waves=waves,
    )

if __name__ == "__main__":
    module = "all"
    for arg in sys.argv[1:]:
        if not arg.startswith("--"):
            module = arg
    run(module=module, waves="--waves" in sys.argv)
