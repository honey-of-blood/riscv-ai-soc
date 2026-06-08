#!/usr/bin/env python3
"""Phase 21 — Production verification test runner.

Suites:
    iss_compare     — 17 ISS-vs-DUT random program comparisons
    coverage        — 6 structured coverage tests (R/I-type, loads, branches, forwarding, M-ext)
    formal_checks   — 5 simulation-based formal property checks

Run all:
    python run_tests.py

Run one suite:
    python run_tests.py iss_compare
    python run_tests.py coverage
    python run_tests.py formal_checks
"""
import sys, os, subprocess
from pathlib import Path

ROOT  = Path(__file__).resolve().parents[2]
PH1   = ROOT / "phase1_riscv_core" / "rtl"
PH15  = ROOT / "phase15_perf" / "rtl"
TB    = ROOT / "phase21_production" / "tb"
VENV  = str(ROOT / ".venv" / "bin" / "python")

# All RTL sources needed to elaborate riscv_core (includes phase15 branch predictor)
PH1_SOURCES = [
    "alu.sv",
    "reg_file.sv",
    "imm_gen.sv",
    "dff.sv",
    "fetch_stage.sv",
    "pipeline_reg_IF_ID.sv",
    "decode_stage.sv",
    "pipeline_reg_ID_EX.sv",
    "execute_stage.sv",
    "pipeline_reg_EX_MEM.sv",
    "memory_stage.sv",
    "pipeline_reg_MEM_WB.sv",
    "writeback_stage.sv",
    "hazard_unit.sv",
    "forwarding_unit.sv",
    "mext_unit.sv",
    "atomic_unit.sv",
    "csr_file.sv",
    "pmp_checker.sv",
    "rvc_expander.sv",
    "riscv_core.sv",
]

# Extra sources from other phases required by riscv_core
EXTRA_SOURCES = [
    str(ROOT / "phase15_perf" / "rtl" / "branch_predictor.sv"),
]

SUITES = [
    ("iss_compare",   "test_iss_compare"),
    ("coverage",      "test_coverage"),
    ("formal_checks", "test_formal_checks"),
]


def run_suite(name, module):
    build = TB / f"build_{name}"
    build.mkdir(exist_ok=True)
    all_srcs = [str(PH1 / s) for s in PH1_SOURCES] + EXTRA_SOURCES
    src_str  = ", ".join(f'"{s}"' for s in all_srcs)
    script  = TB / f"_run_{name}.py"
    script.write_text(f"""\
import sys
sys.path.insert(0, "{TB}")
sys.path.insert(0, "{TB.parent}")   # for iss package
from cocotb_tools.runner import get_runner
r = get_runner("icarus")
r.build(verilog_sources=[{src_str}],
        hdl_toplevel="riscv_core",
        build_dir="{build}",
        defines={{"SIMULATION": 1}},
        always=True)
r.test(hdl_toplevel="riscv_core",
       test_module="{module}",
       build_dir="{build}",
       test_dir="{TB}")
""")
    print(f"\n{'='*60}\n[Phase 21] {name}")
    env = os.environ.copy()
    env["COCOTB_RESOLVE_X"] = "ZEROS"
    env["PYTHONPATH"] = str(TB) + ":" + str(TB.parent) + ":" + env.get("PYTHONPATH", "")
    r = subprocess.run([VENV, str(script)], cwd=str(TB), env=env)
    script.unlink(missing_ok=True)
    return r.returncode == 0


def main():
    arg = sys.argv[1] if len(sys.argv) > 1 else "all"
    passed = failed = 0
    for name, module in SUITES:
        if arg not in ("all", name):
            continue
        ok = run_suite(name, module)
        passed += ok
        failed += not ok
    if passed + failed == 0:
        print(f"Unknown suite: {arg}  (choices: {[n for n,_ in SUITES]})")
        sys.exit(1)
    print(f"\n{'='*60}")
    print(f"Results: {passed} passed, {failed} failed out of {passed+failed} suites")
    sys.exit(0 if failed == 0 else 1)


if __name__ == "__main__":
    main()
