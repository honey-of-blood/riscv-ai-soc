"""
Test runner for phase1 modules using cocotb_tools.runner (cocotb 2.x).
Usage:
    python run_tests.py alu
    python run_tests.py riscv_core
    python run_tests.py riscv_core --waves      # dump FST for GTKWave

Waveform output: sim_build/<module>/<toplevel>.fst
Open with:       gtkwave sim_build/riscv_core/riscv_core.fst
"""
import sys
from pathlib import Path
from cocotb_tools.runner import get_runner

RTL_DIR   = Path(__file__).parent.parent / "rtl"
BUILD_DIR = Path(__file__).parent / "sim_build"

MULTI_SRC = {
    "fetch_stage": {
        "sources": [
            RTL_DIR / "fetch_stage.sv",
            RTL_DIR / "pipeline_reg_IF_ID.sv",
            RTL_DIR / "fetch_if_id_wrap.sv",
        ],
        "toplevel": "fetch_if_id_wrap",
    },
    "decode_stage": {
        "sources": [
            RTL_DIR / "imm_gen.sv",
            RTL_DIR / "decode_stage.sv",
            RTL_DIR / "pipeline_reg_ID_EX.sv",
            RTL_DIR / "decode_id_ex_wrap.sv",
        ],
        "toplevel": "decode_id_ex_wrap",
    },
    "riscv_core": {
        "sources": [
            RTL_DIR / "alu.sv",
            RTL_DIR / "reg_file.sv",
            RTL_DIR / "imm_gen.sv",
            RTL_DIR / "fetch_stage.sv",
            RTL_DIR / "pipeline_reg_IF_ID.sv",
            RTL_DIR / "decode_stage.sv",
            RTL_DIR / "pipeline_reg_ID_EX.sv",
            RTL_DIR / "execute_stage.sv",
            RTL_DIR / "pipeline_reg_EX_MEM.sv",
            RTL_DIR / "memory_stage.sv",
            RTL_DIR / "pipeline_reg_MEM_WB.sv",
            RTL_DIR / "writeback_stage.sv",
            RTL_DIR / "forwarding_unit.sv",
            RTL_DIR / "hazard_unit.sv",
            RTL_DIR / "riscv_core.sv",
        ],
        "toplevel": "riscv_core",
    },
}

def run(module_name: str, waves: bool = False):
    cfg      = MULTI_SRC.get(module_name, {})
    sources  = cfg.get("sources",  [RTL_DIR / f"{module_name}.sv"])
    toplevel = cfg.get("toplevel", module_name)

    runner = get_runner("icarus")
    runner.build(
        sources=sources,
        hdl_toplevel=toplevel,
        build_dir=BUILD_DIR / module_name,
        always=True,
        waves=waves,
    )
    runner.test(
        hdl_toplevel=toplevel,
        test_module=f"test_{module_name}",
        build_dir=BUILD_DIR / module_name,
        test_dir=Path(__file__).parent,
        results_xml=str(BUILD_DIR / module_name / "results.xml"),
        waves=waves,
    )

    if waves:
        fst = BUILD_DIR / module_name / f"{toplevel}.fst"
        print(f"\n  Waveform written to: {fst}")
        print(f"  Open with:           gtkwave {fst}\n")

if __name__ == "__main__":
    if len(sys.argv) not in (2, 3):
        print("Usage: python run_tests.py <module_name> [--waves]")
        sys.exit(1)
    waves = "--waves" in sys.argv
    run(sys.argv[1], waves=waves)
