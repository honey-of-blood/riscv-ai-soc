#!/usr/bin/env python3
"""Phase 20 — Architecture hardening test runner.

RTL suites (cocotb + Icarus):
    crossbar  — Parameterized AXI4-Lite NM×NS crossbar (NM=3, NS=4)
    cru       — Clock and Reset Management Unit
    dft       — DFT scan chain

Run all:
    python run_tests.py

Run one suite:
    python run_tests.py crossbar
    python run_tests.py cru
    python run_tests.py dft
"""
import sys, os, subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
RTL  = ROOT / "phase20_hardening" / "rtl"
TB   = ROOT / "phase20_hardening" / "tb"
VENV = str(ROOT / ".venv" / "bin" / "python")

RTL_SUITES = [
    ("crossbar", ["axi4_crossbar_param.sv", "crossbar_3m4s_wrap.sv"],
                  "crossbar_3m4s_wrap",  "test_crossbar_param"),
    ("cru",      ["cru.sv"],             "cru",                 "test_cru"),
    ("dft",      ["dft_top.sv"],         "dft_top",             "test_dft"),
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
    env["PYTHONPATH"] = str(TB) + ":" + env.get("PYTHONPATH", "")
    r = subprocess.run([VENV, str(script)], cwd=str(TB), env=env)
    script.unlink(missing_ok=True)
    return r.returncode == 0


def main():
    arg = sys.argv[1] if len(sys.argv) > 1 else "all"
    passed = failed = 0
    for name, sources, top, module in RTL_SUITES:
        if arg not in ("all", name):
            continue
        ok = run_rtl(name, sources, top, module)
        passed += ok; failed += not ok
    if passed + failed == 0:
        print(f"Unknown suite: {arg}")
        sys.exit(1)
    print(f"\n{'='*60}\nResults: {passed} passed, {failed} failed out of {passed+failed} suites")
    sys.exit(0 if failed == 0 else 1)


if __name__ == "__main__":
    main()
