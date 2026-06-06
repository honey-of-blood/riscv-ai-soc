"""
Phase 14 Debug Module test runner.
Usage:
    python run_tests.py               # run all tests
    python run_tests.py dm_ctrl       # run specific test suite
    python run_tests.py --waves       # generate VCD
"""
import sys
from pathlib import Path
from cocotb_tools.runner import get_runner

ROOT     = Path(__file__).parent.parent.parent
PH1_RTL  = ROOT / "phase1_riscv_core" / "rtl"
PH14_RTL = Path(__file__).parent.parent / "rtl"
TB_DIR   = Path(__file__).parent
BUILD_DIR = Path(__file__).parent.parent / "sim_build"

# Common Phase 1 RTL sources (ordered for dependency)
PH1_SOURCES = [
    PH1_RTL / "rvc_expander.sv",
    PH1_RTL / "csr_file.sv",
    PH1_RTL / "pmp_checker.sv",
    PH1_RTL / "atomic_unit.sv",
    PH1_RTL / "alu.sv",
    PH1_RTL / "reg_file.sv",
    PH1_RTL / "imm_gen.sv",
    PH1_RTL / "fetch_stage.sv",
    PH1_RTL / "pipeline_reg_IF_ID.sv",
    PH1_RTL / "decode_stage.sv",
    PH1_RTL / "pipeline_reg_ID_EX.sv",
    PH1_RTL / "execute_stage.sv",
    PH1_RTL / "pipeline_reg_EX_MEM.sv",
    PH1_RTL / "memory_stage.sv",
    PH1_RTL / "pipeline_reg_MEM_WB.sv",
    PH1_RTL / "writeback_stage.sv",
    PH1_RTL / "hazard_unit.sv",
    PH1_RTL / "forwarding_unit.sv",
    PH1_RTL / "mext_unit.sv",
    PH1_RTL / "riscv_core.sv",
]

PH14_SOURCES = [
    PH14_RTL / "trigger_module.sv",
    PH14_RTL / "dm_top.sv",
    PH14_RTL / "jtag_dtm.sv",
]

SUITES = {
    "dm_ctrl": {
        "sources":   PH1_SOURCES + PH14_SOURCES + [TB_DIR / "debug_wrap.sv"],
        "toplevel":  "debug_wrap",
        "test_mod":  "test_dm_ctrl",
    },
    "dm_progbuf": {
        "sources":   PH1_SOURCES + PH14_SOURCES + [TB_DIR / "debug_wrap.sv"],
        "toplevel":  "debug_wrap",
        "test_mod":  "test_dm_progbuf",
    },
    "trigger": {
        "sources":   PH1_SOURCES + PH14_SOURCES + [TB_DIR / "debug_wrap.sv"],
        "toplevel":  "debug_wrap",
        "test_mod":  "test_trigger",
    },
    "jtag_dtm": {
        "sources":   PH14_SOURCES + [TB_DIR / "jtag_wrap.sv"],
        "toplevel":  "jtag_wrap",
        "test_mod":  "test_jtag_dtm",
    },
}


def run(suite="all", waves=False):
    suites_to_run = list(SUITES.keys()) if suite == "all" else [suite]

    for name in suites_to_run:
        cfg = SUITES[name]
        bd  = BUILD_DIR / name

        runner = get_runner("icarus")
        runner.build(
            sources=cfg["sources"],
            hdl_toplevel=cfg["toplevel"],
            build_dir=bd,
            always=True,
            waves=waves,
        )
        runner.test(
            hdl_toplevel=cfg["toplevel"],
            test_module=cfg["test_mod"],
            build_dir=bd,
            test_dir=TB_DIR,
            results_xml=str(bd / "results.xml"),
            waves=waves,
        )


if __name__ == "__main__":
    suite = "all"
    waves = "--waves" in sys.argv
    for arg in sys.argv[1:]:
        if not arg.startswith("--"):
            suite = arg
    run(suite=suite, waves=waves)
