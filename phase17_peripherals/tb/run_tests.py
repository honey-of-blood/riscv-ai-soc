#!/usr/bin/env python3
"""Phase 17 — peripheral completeness test runner."""
import sys
import os
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
RTL  = ROOT / "phase17_peripherals" / "rtl"
TB   = ROOT / "phase17_peripherals" / "tb"

# (module_name, rtl_file, test_module)
SUITES = [
    ("i2c_master",  "i2c_master.sv",  "test_i2c"),
    ("wdt",         "wdt.sv",         "test_wdt"),
    ("trng",        "trng.sv",        "test_trng"),
    ("uart_dma",    "uart_dma.sv",    "test_uart_dma"),
]

VENV_PYTHON = str(ROOT / ".venv" / "bin" / "python")


def run_suite(module, rtl_file, test_module):
    build_dir = TB / f"build_{module}"
    build_dir.mkdir(exist_ok=True)

    # Compile RTL
    rtl_path = RTL / rtl_file
    vvp_path = build_dir / f"{module}.vvp"

    defines = ["-DSIMULATION"]
    compile_cmd = [
        "iverilog", "-g2012", "-Wall",
        *defines,
        "-o", str(vvp_path),
        str(rtl_path),
    ]
    print(f"\n{'='*60}")
    print(f"Compiling {rtl_file} ...")
    r = subprocess.run(compile_cmd, capture_output=True, text=True)
    if r.returncode != 0:
        print(f"COMPILE FAIL:\n{r.stdout}\n{r.stderr}")
        return False

    # Run cocotb via pytest
    env = os.environ.copy()
    env["COCOTB_RESOLVE_X"] = "ZEROS"
    env["MODULE"]    = test_module
    env["TOPLEVEL"]  = module
    env["TOPLEVEL_LANG"] = "verilog"
    env["SIM"]       = "icarus"
    env["COCOTB_SIM_BUILD_DIR"] = str(build_dir)
    env["PYTHONPATH"] = str(TB) + ":" + env.get("PYTHONPATH", "")

    # Use cocotb-run-tests if available, else pytest
    test_cmd = [
        VENV_PYTHON, "-m", "pytest",
        str(TB / f"{test_module}.py"),
        "-v", "--tb=short",
        f"--cocotb-sim-build={build_dir}",
    ]

    # Actually invoke cocotb runner directly
    runner_script = TB / f"_run_{module}.py"
    runner_script.write_text(f"""\
import sys
sys.path.insert(0, "{TB}")
from cocotb_tools.runner import get_runner

runner = get_runner("icarus")
runner.build(
    verilog_sources=["{rtl_path}"],
    hdl_toplevel="{module}",
    build_dir="{build_dir}",
    defines={{"SIMULATION": 1}},
    always=True,
)
runner.test(
    hdl_toplevel="{module}",
    test_module="{test_module}",
    build_dir="{build_dir}",
    test_dir="{TB}",
)
""")

    print(f"Running {test_module} ...")
    r2 = subprocess.run(
        [VENV_PYTHON, str(runner_script)],
        capture_output=False,
        cwd=str(TB),
        env=env,
    )
    runner_script.unlink(missing_ok=True)
    return r2.returncode == 0


def main():
    arg = sys.argv[1] if len(sys.argv) > 1 else "all"

    suites_to_run = SUITES
    if arg != "all":
        suites_to_run = [s for s in SUITES if arg in s[0] or arg in s[2]]
        if not suites_to_run:
            print(f"Unknown suite filter: {arg}")
            sys.exit(1)

    passed = 0
    failed = 0
    for module, rtl_file, test_module in suites_to_run:
        ok = run_suite(module, rtl_file, test_module)
        if ok:
            passed += 1
        else:
            failed += 1

    print(f"\n{'='*60}")
    print(f"Results: {passed} passed, {failed} failed out of {passed+failed} suites")
    sys.exit(0 if failed == 0 else 1)


if __name__ == "__main__":
    main()
