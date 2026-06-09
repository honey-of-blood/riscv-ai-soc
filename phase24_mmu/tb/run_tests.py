#!/usr/bin/env python3
"""Phase 24 — SV32 Virtual Memory test runner.

Suites (25 tests):
  24.1  TLB unit tests          → test_tlb     (5 tests)
  24.2  Page table walker tests → test_ptw     (5 tests)
  24.3  MMU integration tests   → test_mmu     (5 tests)
  24.4  Privilege & CSR tests   → test_priv    (5 tests)
  24.5  SFENCE.VMA tests        → test_sfence  (5 tests)

Usage:
  cd phase24_mmu/tb
  python run_tests.py           # all 25 tests
  python run_tests.py tlb       # single suite
  python run_tests.py --waves   # all with waveform dump
"""
import sys
import xml.etree.ElementTree as ET
from pathlib import Path
from cocotb_tools.runner import get_runner


def _count_xml_results(xml_path: str):
    """Return (passed, failed) from a JUnit XML written by cocotb."""
    p = Path(xml_path)
    if not p.exists():
        return 0, 1   # missing XML = treat as failure
    root = ET.parse(str(p)).getroot()
    suites = [root] if root.tag == "testsuite" else root.findall("testsuite")
    passed = failed = 0
    for suite in suites:
        for tc in suite.findall("testcase"):
            if tc.find("failure") is not None or tc.find("error") is not None:
                failed += 1
            else:
                passed += 1
    return passed, failed

ROOT    = Path(__file__).resolve().parents[2]
PH1_RTL = ROOT / "phase1_riscv_core" / "rtl"
PH24_RTL= ROOT / "phase24_mmu"       / "rtl"
BUILD   = Path(__file__).parent / "build_ph24"

TLB_SOURCES = [PH24_RTL / "tlb.sv"]
PTW_SOURCES = [PH24_RTL / "ptw.sv"]
MMU_SOURCES = [PH24_RTL / "tlb.sv",
               PH24_RTL / "ptw.sv",
               PH24_RTL / "mmu.sv"]
CSR_SOURCES = [PH1_RTL / "csr_file.sv"]

MODULES = {
    "tlb": {
        "sources":  TLB_SOURCES,
        "toplevel": "tlb",
        "module":   "test_tlb",
        "n_tests":  5,
    },
    "ptw": {
        "sources":  PTW_SOURCES,
        "toplevel": "ptw",
        "module":   "test_ptw",
        "n_tests":  5,
    },
    "mmu": {
        "sources":  MMU_SOURCES,
        "toplevel": "mmu",
        "module":   "test_mmu",
        "n_tests":  5,
    },
    "priv": {
        "sources":  CSR_SOURCES,
        "toplevel": "csr_file",
        "module":   "test_priv",
        "n_tests":  5,
    },
    "sfence": {
        "sources":  MMU_SOURCES,
        "toplevel": "mmu",
        "module":   "test_sfence",
        "n_tests":  5,
    },
}

ALL_SUITES = ["tlb", "ptw", "mmu", "priv", "sfence"]


def run_suite(name: str, waves: bool = False):
    cfg      = MODULES[name]
    runner   = get_runner("icarus")
    xml_path = str(BUILD / name / "results.xml")
    runner.build(
        sources      = cfg["sources"],
        hdl_toplevel = cfg["toplevel"],
        build_dir    = BUILD / name,
        always       = True,
        waves        = waves,
    )
    try:
        runner.test(
            hdl_toplevel = cfg["toplevel"],
            test_module  = cfg["module"],
            build_dir    = BUILD / name,
            test_dir     = Path(__file__).parent,
            results_xml  = xml_path,
            waves        = waves,
        )
    except SystemExit as e:
        if e.code not in (None, 0):
            raise
    # Detect failures via XML even when runner exits with 0
    p, f = _count_xml_results(xml_path)
    if f > 0:
        raise RuntimeError(f"{f}/{p + f} test(s) FAILED in suite '{name}'")


def main():
    args  = sys.argv[1:]
    waves = "--waves" in args
    args  = [a for a in args if a != "--waves"]
    suite = args[0] if args else "all"

    if suite == "all":
        targets = ALL_SUITES
    elif suite in MODULES:
        targets = [suite]
    else:
        print(f"Unknown suite '{suite}'. Choices: all, {', '.join(MODULES)}")
        sys.exit(1)

    passed = failed = 0
    pass_tests = fail_tests = 0
    for name in targets:
        n = MODULES[name]["n_tests"]
        print(f"\n{'─'*60}\n[Phase 24] {name}\n{'─'*60}")
        try:
            run_suite(name, waves)
            print(f"  ✓ {name} PASS ({n} tests)")
            passed     += 1
            pass_tests += n
        except SystemExit as e:
            print(f"  ✗ {name} FAIL (exit {e.code})")
            failed     += 1
            fail_tests += n
        except Exception as e:
            print(f"  ✗ {name} ERROR: {e}")
            failed     += 1
            fail_tests += n

    total = pass_tests + fail_tests
    print(f"\n{'='*60}")
    print(f"Phase 24 Results: {passed} suites passed, {failed} failed "
          f"({pass_tests}/{total} tests)")
    sys.exit(0 if failed == 0 else 1)


if __name__ == "__main__":
    main()
