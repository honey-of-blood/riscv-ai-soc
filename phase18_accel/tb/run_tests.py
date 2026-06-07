#!/usr/bin/env python3
"""Phase 18 — AI accelerator v3 test runner.

RTL suites (cocotb + Icarus):
    pe_int4           — INT4/INT8 processing element
    pe_int4_stress    — full 256-pair sweep, accumulation, reset, pipeline
    systolic_v3       — N×N systolic array with APB interface
    systolic_v3_stress — nontrivial matrices, negative weights, random sweep
    sg_dma            — scatter-gather DMA engine
    sg_dma_stress     — 4-chain, byte_count=0, large xfer, fixed addr, abort

Python suites (unittest, no cocotb):
    ops_py        — operator library reference algorithms
    onnx_py       — onnx_to_c.py pack/quantise helpers

Run all:
    python run_tests.py

Run one suite:
    python run_tests.py pe_int4_stress
    python run_tests.py ops_py
"""
import sys
import os
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
RTL  = ROOT / "phase18_accel" / "rtl"
TB   = ROOT / "phase18_accel" / "tb"

VENV_PYTHON = str(ROOT / ".venv" / "bin" / "python")

# (suite_name, rtl_sources, dut_toplevel, test_module)
RTL_SUITES = [
    ("pe_int4",
     ["pe_int4.sv"],
     "pe_int4",
     "test_pe_int4"),
    ("pe_int4_stress",
     ["pe_int4.sv"],
     "pe_int4",
     "test_pe_int4_stress"),
    ("systolic_v3",
     ["pe_int4.sv", "systolic_array_v3.sv"],
     "systolic_array_v3",
     "test_systolic_v3"),
    ("systolic_v3_stress",
     ["pe_int4.sv", "systolic_array_v3.sv"],
     "systolic_array_v3",
     "test_systolic_v3_stress"),
    ("sg_dma",
     ["sg_dma.sv"],
     "sg_dma",
     "test_sg_dma"),
    ("sg_dma_stress",
     ["sg_dma.sv"],
     "sg_dma",
     "test_sg_dma_stress"),
]

# Pure Python suites (module name relative to TB)
PY_SUITES = [
    ("ops_py",  "test_ops_py"),
    ("onnx_py", "test_onnx_py"),
]


def run_rtl_suite(suite_name, rtl_sources, toplevel, test_module):
    build_dir = TB / f"build_{suite_name}"
    build_dir.mkdir(exist_ok=True)

    rtl_paths = [str(RTL / s) for s in rtl_sources]

    # Write runner script
    sources_str = ", ".join(f'"{p}"' for p in rtl_paths)
    runner_script = TB / f"_run_{suite_name}.py"
    runner_script.write_text(f"""\
import sys
sys.path.insert(0, "{TB}")
from cocotb_tools.runner import get_runner

runner = get_runner("icarus")
runner.build(
    verilog_sources=[{sources_str}],
    hdl_toplevel="{toplevel}",
    build_dir="{build_dir}",
    defines={{"SIMULATION": 1}},
    always=True,
)
runner.test(
    hdl_toplevel="{toplevel}",
    test_module="{test_module}",
    build_dir="{build_dir}",
    test_dir="{TB}",
)
""")

    print(f"\n{'='*60}")
    print(f"[RTL] {suite_name} ({toplevel})")
    env = os.environ.copy()
    env["COCOTB_RESOLVE_X"] = "ZEROS"
    env["PYTHONPATH"] = str(TB) + ":" + env.get("PYTHONPATH", "")

    r = subprocess.run(
        [VENV_PYTHON, str(runner_script)],
        capture_output=False,
        cwd=str(TB),
        env=env,
    )
    runner_script.unlink(missing_ok=True)
    return r.returncode == 0


def run_py_suite(suite_name, module_name):
    print(f"\n{'='*60}")
    print(f"[PY]  {suite_name}")
    r = subprocess.run(
        [VENV_PYTHON, str(TB / f"{module_name}.py"), "-v"],
        capture_output=False,
        cwd=str(TB),
    )
    return r.returncode == 0


def main():
    arg = sys.argv[1] if len(sys.argv) > 1 else "all"

    all_suites = [(n, "rtl") for n, *_ in RTL_SUITES] + \
                 [(n, "py")  for n, _ in PY_SUITES]

    passed = 0
    failed = 0

    for suite_name, rtl_sources, toplevel, test_module in RTL_SUITES:
        if arg not in ("all", suite_name):
            continue
        ok = run_rtl_suite(suite_name, rtl_sources, toplevel, test_module)
        passed += ok
        failed += not ok

    for suite_name, module_name in PY_SUITES:
        if arg not in ("all", suite_name):
            continue
        ok = run_py_suite(suite_name, module_name)
        passed += ok
        failed += not ok

    if passed + failed == 0:
        print(f"Unknown suite filter: {arg}")
        print(f"Available: {[n for n,_ in all_suites]}")
        sys.exit(1)

    print(f"\n{'='*60}")
    print(f"Results: {passed} passed, {failed} failed out of {passed+failed} suites")
    sys.exit(0 if failed == 0 else 1)


if __name__ == "__main__":
    main()
