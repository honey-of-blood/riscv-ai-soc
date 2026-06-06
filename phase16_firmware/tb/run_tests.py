"""
Phase 16 test runner.

Usage:
    python run_tests.py              # run ALL tests (Python + cocotb)
    python run_tests.py python       # Python XMODEM tests only (fast)
    python run_tests.py instr_bram   # cocotb RTL tests only
    python run_tests.py stress       # stress suite only
"""

import sys
import os
import unittest
import subprocess
from pathlib import Path

TB_DIR  = Path(__file__).parent
RTL_DIR = TB_DIR.parent / "rtl"


def run_python_tests(pattern="test_*.py") -> unittest.TestResult:
    loader = unittest.TestLoader()
    suite  = loader.discover(str(TB_DIR), pattern=pattern)
    runner = unittest.TextTestRunner(verbosity=2, stream=sys.stdout)
    return runner.run(suite)


def run_cocotb(module_name: str) -> None:
    from cocotb_tools.runner import get_runner

    build_dir = TB_DIR / "sim_build" / module_name
    runner    = get_runner("icarus")
    runner.build(
        sources      = [RTL_DIR / f"{module_name}.sv"],
        hdl_toplevel = module_name,
        build_dir    = build_dir,
        always       = True,
    )
    runner.test(
        hdl_toplevel = module_name,
        test_module  = f"test_{module_name}",
        build_dir    = build_dir,
        test_dir     = TB_DIR,
        results_xml  = str(build_dir / "results.xml"),
    )


def main():
    arg = sys.argv[1] if len(sys.argv) > 1 else "all"

    if arg == "instr_bram":
        run_cocotb("instr_bram")
        return

    if arg == "stress":
        result = run_python_tests(pattern="test_xmodem_stress.py")
        total  = result.testsRun
        failed = len(result.failures) + len(result.errors)
        print(f"\n** TESTS={total} PASS={total - failed} FAIL={failed} SKIP={len(result.skipped)} **")
        sys.exit(0 if failed == 0 else 1)

    if arg in ("python", "xmodem"):
        result = run_python_tests(pattern="test_xmodem*.py")
        total  = result.testsRun
        failed = len(result.failures) + len(result.errors)
        print(f"\n** TESTS={total} PASS={total - failed} FAIL={failed} SKIP={len(result.skipped)} **")
        sys.exit(0 if failed == 0 else 1)

    # Default: run everything
    print("=" * 60)
    print("Phase 16 — Python XMODEM tests")
    print("=" * 60)
    py_result = run_python_tests(pattern="test_xmodem*.py")

    print("\n" + "=" * 60)
    print("Phase 16 — cocotb instr_bram tests")
    print("=" * 60)
    try:
        run_cocotb("instr_bram")
        cocotb_ok = True
    except SystemExit as e:
        cocotb_ok = (e.code == 0)

    py_total  = py_result.testsRun
    py_failed = len(py_result.failures) + len(py_result.errors)
    py_passed = py_total - py_failed

    print(f"\n{'='*60}")
    print(f"Phase 16 summary:")
    print(f"  Python  TESTS={py_total} PASS={py_passed} FAIL={py_failed}")
    print(f"  cocotb  instr_bram: {'PASS' if cocotb_ok else 'FAIL'}")
    print(f"{'='*60}")

    sys.exit(0 if (py_failed == 0 and cocotb_ok) else 1)


if __name__ == "__main__":
    main()
