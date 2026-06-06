# vivado_build.tcl — one-command Vivado build for the RV32 SoC.
#
# Usage (from repo root):
#   vivado -mode batch -source phase16_firmware/scripts/vivado_build.tcl
#
# Targets Arty A7-100T (xc7a100tcsg324-1).
# Output: vivado_proj/my_soc.runs/impl_1/soc_top.bit
#
# NOTE: Vivado synthesis takes 15-30 minutes and requires a Vivado license.
#       CI uses simulation-only checks; gate synthesis behind a manual trigger.

# ── Project setup ────────────────────────────────────────────────────────────
set PART      "xc7a100tcsg324-1"
set PROJ_DIR  "./vivado_proj"
set TOP       "soc_top"

create_project my_soc $PROJ_DIR -part $PART -force
set_property target_language SystemVerilog [current_project]

# ── RTL sources ───────────────────────────────────────────────────────────────
# Core pipeline
add_files -fileset sources_1 [glob phase1_riscv_core/rtl/*.sv]

# Cache
add_files -fileset sources_1 [glob phase2_cache/rtl/*.sv]

# AXI crossbar + SRAM + APB bridge
add_files -fileset sources_1 [glob phase3_axi/rtl/*.sv]

# AI accelerator
add_files -fileset sources_1 [glob phase4_accelerator/rtl/*.sv]

# SoC top + glue
add_files -fileset sources_1 [glob phase5_soc/rtl/*.sv]

# Peripherals
add_files -fileset sources_1 [glob phase8_peripherals/rtl/*.sv]

# Memory backend (BRAM)
add_files -fileset sources_1 [glob phase10_memory/rtl/*.sv]

# Debug / JTAG
add_files -fileset sources_1 [glob phase14_debug/rtl/*.sv]

# Performance (I-cache, BP, fast_mul)
add_files -fileset sources_1 [glob phase15_perf/rtl/*.sv]

# Bootloader instruction BRAM
add_files -fileset sources_1 [glob phase16_firmware/rtl/*.sv]

# FPGA board wrapper (Arty A7-100T)
add_files -fileset sources_1 phase10_memory/fpga/boards/arty_a7_100t/fpga_top_arty_a7.sv

# Constraints
add_files -fileset constrs_1 phase10_memory/fpga/boards/arty_a7_100t/arty_a7.xdc

# Bootloader hex initialisation
set_property generic "INIT_FILE=phase16_firmware/sw/bootloader/bootloader.hex" \
    [get_filesets sources_1]

# ── Synthesis options ─────────────────────────────────────────────────────────
set_property top $TOP [current_fileset]
set_property \
    -name {STEPS.SYNTH_DESIGN.ARGS.MORE OPTIONS} \
    -value {-flatten_hierarchy rebuilt} \
    [get_runs synth_1]

# ── Run synthesis → implementation → bitstream ────────────────────────────────
launch_runs synth_1 -jobs 8
wait_on_run synth_1
if {[get_property PROGRESS [get_runs synth_1]] ne "100%"} {
    error "Synthesis failed"
}

launch_runs impl_1 -to_step write_bitstream -jobs 8
wait_on_run impl_1
if {[get_property PROGRESS [get_runs impl_1]] ne "100%"} {
    error "Implementation failed"
}

set bit [get_files -of_objects [get_runs impl_1] *.bit]
puts "============================================"
puts "Bitstream: $bit"
puts "Flash with:  program_hw_devices -bitfile $bit"
puts "============================================"
