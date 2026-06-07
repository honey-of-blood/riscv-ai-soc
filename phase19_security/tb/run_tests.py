#!/usr/bin/env python3
"""Phase 19 — Security subsystem test runner.

RTL suites (cocotb + Icarus):
    sha256   — SHA-256 hardware accelerator (NIST vectors)
    aes      — AES-128 ECB/CBC/CTR accelerator (NIST/SP-800-38A vectors)
    sha3     — SHA3-256 (Keccak) accelerator (FIPS 202 vectors)

Python suites (unittest, no cocotb):
    secure_boot_py  — secure boot SW logic (constant-time verify)
    pmp_py          — PMP NAPOT encoding and permission model

Run all:
    python run_tests.py

Run one suite:
    python run_tests.py sha256
    python run_tests.py secure_boot_py
"""
import sys, os, subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
RTL  = ROOT / "phase19_security" / "rtl"
TB   = ROOT / "phase19_security" / "tb"
VENV = str(ROOT / ".venv" / "bin" / "python")

RTL_SUITES = [
    ("sha256", ["sha256_top.sv"], "sha256_top", "test_sha256"),
    ("aes",    ["aes_top.sv"],    "aes_top",    "test_aes"),
    ("sha3",   ["sha3_top.sv"],   "sha3_top",   "test_sha3"),
]
PY_SUITES = [
    ("secure_boot_py", "test_secure_boot_py"),
    ("pmp_py",         "test_pmp_py"),
]


def run_rtl(name, sources, top, module):
    build = TB / f"build_{name}"
    build.mkdir(exist_ok=True)
    src_str = ", ".join(f'"{RTL/s}"' for s in sources)
    script  = TB / f"_run_{name}.py"
    script.write_text(f"""\
import sys; sys.path.insert(0, "{TB}")
from cocotb_tools.runner import get_runner
r = get_runner("icarus")
r.build(verilog_sources=[{src_str}], hdl_toplevel="{top}",
        build_dir="{build}", defines={{"SIMULATION":1}}, always=True)
r.test(hdl_toplevel="{top}", test_module="{module}",
       build_dir="{build}", test_dir="{TB}")
""")
    print(f"\n{'='*60}\n[RTL] {name} ({top})")
    env = os.environ.copy()
    env["COCOTB_RESOLVE_X"] = "ZEROS"
    env["PYTHONPATH"] = str(TB) + ":" + env.get("PYTHONPATH","")
    r = subprocess.run([VENV, str(script)], cwd=str(TB), env=env)
    script.unlink(missing_ok=True)
    return r.returncode == 0


def run_py(name, module):
    print(f"\n{'='*60}\n[PY]  {name}")
    r = subprocess.run([VENV, str(TB/f"{module}.py"), "-v"], cwd=str(TB))
    return r.returncode == 0


def main():
    arg = sys.argv[1] if len(sys.argv) > 1 else "all"
    passed = failed = 0
    for name, sources, top, module in RTL_SUITES:
        if arg not in ("all", name): continue
        ok = run_rtl(name, sources, top, module)
        passed += ok; failed += not ok
    for name, module in PY_SUITES:
        if arg not in ("all", name): continue
        ok = run_py(name, module)
        passed += ok; failed += not ok
    if passed + failed == 0:
        print(f"Unknown suite: {arg}")
        sys.exit(1)
    print(f"\n{'='*60}\nResults: {passed} passed, {failed} failed out of {passed+failed} suites")
    sys.exit(0 if failed == 0 else 1)


if __name__ == "__main__":
    main()
