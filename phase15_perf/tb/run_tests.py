"""
Phase 15 test runner — I-cache, branch predictor, fast_mul, integration.
Usage:
    python run_tests.py              # run all suites
    python run_tests.py icache       # run a single suite
    python run_tests.py bpred
    python run_tests.py fast_mul
    python run_tests.py perf
    python run_tests.py --waves      # all suites with waveform dump
"""
import sys
from pathlib import Path
from cocotb_tools.runner import get_runner

ROOT   = Path(__file__).resolve().parents[2]
PH1    = ROOT / "phase1_riscv_core" / "rtl"
PH15   = ROOT / "phase15_perf" / "rtl"
TB_DIR = Path(__file__).resolve().parent
BUILD  = ROOT / "phase15_perf" / "sim_build"

# All Phase-1 RTL sources (riscv_core and its dependencies)
PH1_SOURCES = [
    PH1 / "rvc_expander.sv",
    PH1 / "csr_file.sv",
    PH1 / "pmp_checker.sv",
    PH1 / "atomic_unit.sv",
    PH1 / "alu.sv",
    PH1 / "reg_file.sv",
    PH1 / "imm_gen.sv",
    PH1 / "fetch_stage.sv",
    PH1 / "pipeline_reg_IF_ID.sv",
    PH1 / "decode_stage.sv",
    PH1 / "pipeline_reg_ID_EX.sv",
    PH1 / "execute_stage.sv",
    PH1 / "pipeline_reg_EX_MEM.sv",
    PH1 / "memory_stage.sv",
    PH1 / "pipeline_reg_MEM_WB.sv",
    PH1 / "writeback_stage.sv",
    PH1 / "hazard_unit.sv",
    PH1 / "forwarding_unit.sv",
    PH1 / "mext_unit.sv",
    PH1 / "riscv_core.sv",
]

SUITES = {
    "icache": {
        "sources": [
            PH15 / "icache.sv",
            TB_DIR / "icache_wrap.sv",
        ],
        "toplevel": "icache_wrap",
        "module":   "test_icache",
    },
    "bpred": {
        "sources": [
            PH15 / "branch_predictor.sv",
            TB_DIR / "bpred_wrap.sv",
        ],
        "toplevel": "bpred_wrap",
        "module":   "test_bpred",
    },
    "fast_mul": {
        "sources": [
            PH15 / "fast_mul.sv",
            TB_DIR / "mul_wrap.sv",
        ],
        "toplevel": "mul_wrap",
        "module":   "test_fast_mul",
    },
    "perf": {
        "sources": PH1_SOURCES + [
            PH15 / "icache.sv",
            PH15 / "branch_predictor.sv",
            PH15 / "fast_mul.sv",
            TB_DIR / "perf_wrap.sv",
        ],
        "toplevel": "perf_wrap",
        "module":   "test_perf",
    },
}


def run_suite(name, waves=False):
    cfg = SUITES[name]
    build_dir = BUILD / name
    runner = get_runner("icarus")
    runner.build(
        sources=cfg["sources"],
        hdl_toplevel=cfg["toplevel"],
        build_dir=build_dir,
        always=True,
        waves=waves,
    )
    runner.test(
        hdl_toplevel=cfg["toplevel"],
        test_module=cfg["module"],
        build_dir=build_dir,
        test_dir=TB_DIR,
        results_xml=str(build_dir / "results.xml"),
        waves=waves,
    )


if __name__ == "__main__":
    args = [a for a in sys.argv[1:] if not a.startswith("-")]
    waves = "--waves" in sys.argv

    if args:
        suite = args[0]
        if suite not in SUITES:
            print(f"Unknown suite '{suite}'. Choose from: {list(SUITES)}")
            sys.exit(1)
        run_suite(suite, waves=waves)
    else:
        failed = []
        for name in SUITES:
            try:
                run_suite(name, waves=waves)
                print(f"[PASS] {name}")
            except SystemExit as e:
                if e.code != 0:
                    failed.append(name)
                    print(f"[FAIL] {name}")
            except Exception as e:
                failed.append(name)
                print(f"[ERROR] {name}: {e}")

        if failed:
            print(f"\nFailed suites: {failed}")
            sys.exit(1)
        else:
            print("\nAll Phase 15 suites passed.")
