#!/usr/bin/env python3
"""Phase 22 — Portability & Ecosystem test runner.

Tests:
  test_rtl_synthesis  — Yosys parse/synthesis checks (5 tests)
  test_structure      — File completeness (6 tests)
  test_trm            — TRM content checks (5 tests)
  test_sdk            — SDK example/BSP checks (5 tests)
  test_zephyr         — Zephyr board definition checks (6 tests)

Usage:
  python run_tests.py          # run all
  python run_tests.py trm      # run one module
"""
import sys, importlib, traceback, time
from pathlib import Path

TB = Path(__file__).resolve().parent
sys.path.insert(0, str(TB))

MODULES = [
    "test_rtl_synthesis",
    "test_structure",
    "test_trm",
    "test_sdk",
    "test_zephyr",
]


def _run_module(mod_name):
    mod = importlib.import_module(mod_name)
    tests = [(n, fn) for n, fn in vars(mod).items()
             if n.startswith("test_") and callable(fn)]
    tests.sort(key=lambda x: x[0])

    passed = failed = 0
    for name, fn in tests:
        t0 = time.time()
        try:
            fn()
            dt = time.time() - t0
            print(f"  PASS  {mod_name}.{name}  ({dt*1000:.0f} ms)")
            passed += 1
        except Exception as e:
            dt = time.time() - t0
            print(f"  FAIL  {mod_name}.{name}  ({dt*1000:.0f} ms)")
            for line in traceback.format_exc().splitlines()[-6:]:
                print(f"        {line}")
            failed += 1
    return passed, failed


def main():
    arg = sys.argv[1] if len(sys.argv) > 1 else "all"
    total_pass = total_fail = 0

    for mod in MODULES:
        if arg not in ("all", mod.replace("test_", "")):
            continue
        print(f"\n{'─'*60}")
        print(f"[Phase 22] {mod}")
        p, f = _run_module(mod)
        total_pass += p
        total_fail += f
        print(f"  → {p} passed, {f} failed")

    if total_pass + total_fail == 0:
        print(f"Unknown suite: {arg}  (choices: all, {', '.join(m.replace('test_','') for m in MODULES)})")
        sys.exit(1)

    print(f"\n{'='*60}")
    print(f"Phase 22 Results: {total_pass} passed, {total_fail} failed "
          f"out of {total_pass+total_fail} tests")
    sys.exit(0 if total_fail == 0 else 1)


if __name__ == "__main__":
    main()
