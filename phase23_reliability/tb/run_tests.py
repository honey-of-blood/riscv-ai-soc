#!/usr/bin/env python3
"""Phase 23 — RTL Reliability Hardening test runner.

Core suites (25 tests):
  23.1  icache wired into soc_top          → test_icache_soc     (5 tests)
  23.2  AXI4 burst SRAM / no burst_to_lite → test_burst_refill   (5 tests)
  23.3  2-way SA cache + SECDED ECC        → test_cache_2way     (5 tests)
  23.4  TRNG synthesis ring oscillators    → test_trng_synth     (5 tests)
  23.5  CDC hardening (cdc_sync2)          → test_cdc            (5 tests)

Stress suites (15 tests):
  cache_stress  — word-offsets, byte-enables, all-64-sets, dirty-WB, LRU, ECC corners
  burst_stress  — all strobes, back-to-back bursts, hazard, data patterns, overwrite

Usage:
  cd phase23_reliability/tb
  python run_tests.py              # run all 40 tests (core + stress)
  python run_tests.py core         # core 25 only
  python run_tests.py stress       # stress 15 only
  python run_tests.py cache_stress # single suite
  python run_tests.py cache --waves
"""
import sys
from pathlib import Path
from cocotb_tools.runner import get_runner

ROOT    = Path(__file__).resolve().parents[2]
PH1_RTL = ROOT / "phase1_riscv_core" / "rtl"
PH2_RTL = ROOT / "phase2_cache"      / "rtl"
PH3_RTL = ROOT / "phase3_axi"        / "rtl"
PH15_RTL= ROOT / "phase15_perf"      / "rtl"
PH17_RTL= ROOT / "phase17_peripherals" / "rtl"
PH23_RTL= ROOT / "phase23_reliability" / "rtl"
BUILD   = Path(__file__).parent / "build_ph23"

# ── RTL file lists ────────────────────────────────────────────────────────────

CACHE_2WAY_SOURCES = [
    PH2_RTL / "cache_tag_array_2way.sv",
    PH2_RTL / "cache_data_array_2way.sv",
    PH2_RTL / "cache_controller_2way.sv",
    PH2_RTL / "cache_top.sv",
]

BURST_SRAM_SOURCES = [
    PH3_RTL / "axi_sram.sv",
]

ICACHE_SOURCES = [
    PH15_RTL / "icache.sv",
]

TRNG_SOURCES = [
    PH17_RTL / "trng.sv",
]

CDC_SOURCES = [
    PH23_RTL / "cdc_sync2.sv",
]

MODULES = {
    "icache": {
        "sources":  ICACHE_SOURCES,
        "toplevel": "icache",
        "module":   "test_icache_soc",
        "defines":  [],
        "n_tests":  5,
    },
    "burst": {
        "sources":  BURST_SRAM_SOURCES,
        "toplevel": "axi_sram",
        "module":   "test_burst_refill",
        "defines":  [],
        "n_tests":  5,
    },
    "cache": {
        "sources":  CACHE_2WAY_SOURCES,
        "toplevel": "cache_top",
        "module":   "test_cache_2way",
        "defines":  [],
        "n_tests":  5,
    },
    "trng": {
        "sources":  TRNG_SOURCES,
        "toplevel": "trng",
        "module":   "test_trng_synth",
        "defines":  ["SIMULATION"],
        "n_tests":  5,
    },
    "cdc": {
        "sources":  CDC_SOURCES,
        "toplevel": "cdc_sync2",
        "module":   "test_cdc",
        "defines":  [],
        "params":   {"W": 8},
        "n_tests":  5,
    },
    # ── Stress suites ─────────────────────────────────────────────────────────
    "cache_stress": {
        "sources":  CACHE_2WAY_SOURCES,
        "toplevel": "cache_top",
        "module":   "test_cache_stress",
        "defines":  [],
        "n_tests":  10,
    },
    "burst_stress": {
        "sources":  BURST_SRAM_SOURCES,
        "toplevel": "axi_sram",
        "module":   "test_burst_stress",
        "defines":  [],
        "n_tests":  5,
    },
}


def run_suite(name: str, waves: bool = False):
    cfg     = MODULES[name]
    runner  = get_runner("icarus")
    extra   = [f"-D{d}" for d in cfg.get("defines", [])]
    params  = cfg.get("params", {})

    runner.build(
        sources        = cfg["sources"],
        hdl_toplevel   = cfg["toplevel"],
        build_dir      = BUILD / name,
        always         = True,
        waves          = waves,
        build_args     = extra,
        parameters     = params,
    )
    runner.test(
        hdl_toplevel   = cfg["toplevel"],
        test_module    = cfg["module"],
        build_dir      = BUILD / name,
        test_dir       = Path(__file__).parent,
        results_xml    = str(BUILD / name / "results.xml"),
        waves          = waves,
    )


CORE_SUITES   = ["icache", "burst", "cache", "trng", "cdc"]
STRESS_SUITES = ["cache_stress", "burst_stress"]


def main():
    args  = sys.argv[1:]
    waves = "--waves" in args
    args  = [a for a in args if a != "--waves"]
    suite = args[0] if args else "all"

    if suite == "all":
        targets = CORE_SUITES + STRESS_SUITES
    elif suite == "core":
        targets = CORE_SUITES
    elif suite == "stress":
        targets = STRESS_SUITES
    elif suite in MODULES:
        targets = [suite]
    else:
        print(f"Unknown suite: {suite}. "
              f"Choices: all, core, stress, {', '.join(MODULES)}")
        sys.exit(1)

    passed = failed = 0
    pass_tests = fail_tests = 0
    for name in targets:
        print(f"\n{'─'*60}\n[Phase 23] {name}\n{'─'*60}")
        n = MODULES[name].get("n_tests", 5)
        try:
            run_suite(name, waves)
            print(f"  ✓ {name} PASS ({n} tests)")
            passed += 1
            pass_tests += n
        except SystemExit as e:
            print(f"  ✗ {name} FAIL (exit {e.code})")
            failed += 1
            fail_tests += n
        except Exception as e:
            print(f"  ✗ {name} ERROR: {e}")
            failed += 1
            fail_tests += n

    total = pass_tests + fail_tests
    print(f"\n{'='*60}")
    print(f"Phase 23 Results: {passed} suites passed, {failed} failed "
          f"({pass_tests}/{total} tests)")
    sys.exit(0 if failed == 0 else 1)


if __name__ == "__main__":
    main()
