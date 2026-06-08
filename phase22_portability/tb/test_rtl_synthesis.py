"""test_rtl_synthesis.py — Phase 22: Yosys RTL synthesis / parse checks."""
import subprocess, os, re
from pathlib import Path

ROOT   = Path(__file__).resolve().parents[2]
PH22   = ROOT / "phase22_portability"
PH1    = ROOT / "phase1_riscv_core" / "rtl"
CI_SH  = PH22 / "scripts" / "ci_yosys_check.sh"


def _yosys_parse(*sv_files):
    """Return (ok, log) after asking Yosys to parse the given SV files."""
    cmds = " ".join(f"read_verilog -sv -defer {f};" for f in sv_files)
    cmds += " proc"
    r = subprocess.run(
        ["yosys", "-Q", "-p", cmds],
        capture_output=True, text=True, timeout=60
    )
    combined = r.stdout + r.stderr
    ok = r.returncode == 0 and not re.search(
        r"^ERROR:.*syntax|Parse error|unexpected", combined, re.IGNORECASE | re.MULTILINE
    )
    return ok, combined


def test_ci_script_runs():
    """ci_yosys_check.sh is executable and exits 0."""
    assert CI_SH.exists(),        f"Missing: {CI_SH}"
    assert os.access(CI_SH, os.X_OK), "ci_yosys_check.sh is not executable"
    r = subprocess.run(["bash", str(CI_SH)], capture_output=True, text=True, timeout=120)
    assert r.returncode == 0, f"ci_yosys_check.sh failed:\n{r.stdout}\n{r.stderr}"


def test_alu_sv_parses():
    """alu.sv parses cleanly with Yosys (no syntax errors)."""
    ok, log = _yosys_parse(PH1 / "alu.sv")
    assert ok, f"Yosys parse errors in alu.sv:\n{log}"


def test_tech_cells_intel_parses():
    """tech_cells_intel.sv parses without error when INTEL_FPGA is undefined."""
    f = PH22 / "rtl" / "tech_cells_intel.sv"
    ok, log = _yosys_parse(f)
    assert ok, f"tech_cells_intel.sv parse errors:\n{log}"


def test_fpga_top_de1_soc_parses():
    """fpga_top_de1_soc.sv parses cleanly (defer mode — soc_top not needed)."""
    f = PH22 / "rtl" / "fpga_top_de1_soc.sv"
    ok, log = _yosys_parse(f)
    assert ok, f"fpga_top_de1_soc.sv parse errors:\n{log}"


def test_ecp5_makefile_targets():
    """Makefile.ecp5 contains all required make targets."""
    mk = (PH22 / "scripts" / "Makefile.ecp5").read_text()
    for target in ["synth", "pnr", "pack", "all", "clean"]:
        assert f"{target}:" in mk, f"Makefile.ecp5 missing target: {target}"
    assert "yosys" in mk.lower(), "Makefile.ecp5 missing Yosys invocation"
    assert "nextpnr" in mk.lower(), "Makefile.ecp5 missing nextpnr invocation"
