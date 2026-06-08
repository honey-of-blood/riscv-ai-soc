# quartus_build.tcl — Full Quartus Prime compilation flow for DE1-SoC
#
# Usage:
#   quartus_sh -t scripts/quartus_build.tcl
#
# Requires: Quartus Prime 18.1+ (Lite or Standard) with device family Cyclone V.

package require ::quartus::project
package require ::quartus::flow

# ── Project setup ─────────────────────────────────────────────────────────────
set PROJECT_NAME "rv32_soc_de1"
set TOP_ENTITY   "fpga_top_de1_soc"
set DEVICE       "5CSEMA5F31C6N"   ;# Cyclone V on DE1-SoC board

if {[project_exists $PROJECT_NAME]} {
    project_open $PROJECT_NAME
} else {
    project_new $PROJECT_NAME -revision $PROJECT_NAME -overwrite
}

# ── Device ───────────────────────────────────────────────────────────────────
set_global_assignment -name FAMILY          "Cyclone V"
set_global_assignment -name DEVICE          $DEVICE
set_global_assignment -name TOP_LEVEL_ENTITY $TOP_ENTITY

# ── RTL sources (this phase + all referenced phases) ─────────────────────────
# Phase 22 wrappers
set_global_assignment -name SYSTEMVERILOG_FILE ../phase22_portability/rtl/tech_cells_intel.sv
set_global_assignment -name SYSTEMVERILOG_FILE ../phase22_portability/rtl/fpga_top_de1_soc.sv

# Phase 5 SoC top
set_global_assignment -name SYSTEMVERILOG_FILE ../phase5_soc/rtl/soc_top.sv

# Phase 1 pipeline core
foreach f {
    alu.sv reg_file.sv imm_gen.sv dff.sv
    fetch_stage.sv pipeline_reg_IF_ID.sv
    decode_stage.sv pipeline_reg_ID_EX.sv
    execute_stage.sv pipeline_reg_EX_MEM.sv
    memory_stage.sv pipeline_reg_MEM_WB.sv
    writeback_stage.sv hazard_unit.sv forwarding_unit.sv
    mext_unit.sv atomic_unit.sv csr_file.sv
    pmp_checker.sv rvc_expander.sv riscv_core.sv
} {
    set_global_assignment -name SYSTEMVERILOG_FILE ../phase1_riscv_core/rtl/$f
}

# Phase 2 cache
set_global_assignment -name SYSTEMVERILOG_FILE ../phase2_cache/rtl/cache_top.sv

# Phase 3 AXI crossbar
foreach f [glob -nocomplain ../phase3_axi/rtl/*.sv] {
    set_global_assignment -name SYSTEMVERILOG_FILE $f
}

# Phase 15 performance (branch predictor, I-cache, fast_mul)
foreach f [glob -nocomplain ../phase15_perf/rtl/*.sv] {
    set_global_assignment -name SYSTEMVERILOG_FILE $f
}

# Phase 16 firmware BRAM
set_global_assignment -name SYSTEMVERILOG_FILE ../phase16_firmware/rtl/instr_bram.sv

# ── Defines ───────────────────────────────────────────────────────────────────
set_global_assignment -name VERILOG_MACRO "INTEL_FPGA=1"
set_global_assignment -name VERILOG_MACRO "SYNTHESIS=1"

# ── Timing constraints ────────────────────────────────────────────────────────
set_global_assignment -name SDC_FILE ../phase22_portability/constraints/de1_soc.sdc

# ── Compilation settings ──────────────────────────────────────────────────────
set_global_assignment -name SEED                    1
set_global_assignment -name OPTIMIZE_HOLD_TIMING    "ALL PATHS"
set_global_assignment -name FITTER_EFFORT           "STANDARD FIT"
set_global_assignment -name PHYSICAL_SYNTHESIS_EFFORT "NORMAL"
set_global_assignment -name MIN_CORE_JUNCTION_TEMP  0
set_global_assignment -name MAX_CORE_JUNCTION_TEMP  85

# ── Run full compilation ──────────────────────────────────────────────────────
execute_flow -compile

# ── Report timing summary ─────────────────────────────────────────────────────
set_global_assignment -name FLOW_ENABLE_RTL_VIEWER  OFF
load_report $PROJECT_NAME

set fmax [get_clock_fmax_info -nworst 1 -clock clk_cpu]
post_message "CPU clock Fmax: $fmax"

project_close
