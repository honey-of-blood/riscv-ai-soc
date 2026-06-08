`timescale 1ns/1ps
// tech_cells_intel.sv — Intel/Altera primitive wrappers for Cyclone V (DE1-SoC)
//
// Compile with +define+INTEL_FPGA when targeting Quartus.
// Without the define the file is empty — Xilinx or ECP5 builds use their own prims.
//
// Mapping table:
//   Xilinx          Intel (Cyclone V)
//   MMCME2_ADV   →  altpll
//   BUFG / BUFGMUX→  altclkctrl (or direct wire — FPGA fabric handles global routing)
//   DSP48E1       →  lpm_mult
//   BSCANE2       →  altera_jtag_sld_node (JTAG Atom)

`ifdef INTEL_FPGA

// ── Clock PLL: 50 MHz in → 100 MHz CPU + 25 MHz peripheral ──────────────────
module pll_50_to_100 (
    input  wire inclk0,     // 50 MHz board oscillator
    output wire c0,         // 100 MHz → CPU / AXI fabric
    output wire c1,         // 25 MHz  → UART baud reference
    output wire locked
);
    altpll #(
        .intended_device_family("Cyclone V"),
        .lpm_type              ("altpll"),
        .clk0_divide_by        (1),
        .clk0_multiply_by      (2),   // 50×2/1 = 100 MHz
        .clk1_divide_by        (2),
        .clk1_multiply_by      (1),   // 50×1/2 = 25 MHz
        .compensate_clock      ("CLK0"),
        .gate_lock_signal      ("NO"),
        .inclk0_input_frequency(20000),  // 50 MHz = 20 000 ps period
        .operation_mode        ("NORMAL")
    ) u_pll (
        .inclk ({1'b0, inclk0}),
        .clk   ({c1, c0}),
        .locked(locked),
        .activeclock(),
        .clkbad(),
        .clkena({6{1'b1}}),
        .clkloss(),
        .clkswitch(1'b0),
        .enable0(1'b1),
        .enable1(1'b1),
        .extclk(),
        .extclkena({4{1'b1}}),
        .fbin(1'b1),
        .fbmimicbidir(),
        .fbout(),
        .fref(),
        .icdrclk(),
        .pfdena(1'b1),
        .phasecounterselect({4{1'b1}}),
        .phasedone(),
        .phasestep(1'b1),
        .phaseupdown(1'b1),
        .pllena(1'b1),
        .scanaclr(1'b0),
        .scanclk(1'b0),
        .scanclkena(1'b1),
        .scandata(1'b0),
        .scandataout(),
        .scandone(),
        .scanread(1'b0),
        .scanwrite(1'b0),
        .sclkout0(),
        .sclkout1(),
        .vcooverrange(),
        .vcounderrange()
    );
endmodule


// ── 32×32 Multiplier using lpm_mult ─────────────────────────────────────────
// Replaces DSP48E1; used by mext_unit.sv fast_mul path when USE_DSP=1.
module dsp_mul32 (
    input  wire        clk,
    input  wire [31:0] a,
    input  wire [31:0] b,
    output wire [63:0] p       // full 64-bit product (registered, 1-cycle latency)
);
    lpm_mult #(
        .lpm_widtha      (32),
        .lpm_widthb      (32),
        .lpm_widthp      (64),
        .lpm_widths      (1),
        .lpm_type        ("LPM_MULT"),
        .lpm_representation("UNSIGNED"),
        .lpm_pipeline    (1)
    ) u_mul (
        .dataa  (a),
        .datab  (b),
        .result (p),
        .clock  (clk),
        .aclr   (1'b0),
        .clken  (1'b1),
        .sum    (1'b0)
    );
endmodule


// ── Global clock buffer (BUFG equivalent) ───────────────────────────────────
// Cyclone V: clocks on dedicated global routing — altclkctrl provides
// clock-enable gating.  For ungated clocks a simple wire suffices.
module clkbuf (
    input  wire i,
    output wire o
);
    altclkctrl u_clkctrl (
        .clkselect (2'b00),
        .ena       (1'b1),
        .inclk     ({3'b0, i}),
        .outclk    (o)
    );
    defparam u_clkctrl.clock_type      = "Global Clock";
    defparam u_clkctrl.intended_device_family = "Cyclone V";
    defparam u_clkctrl.lpm_type        = "altclkctrl";
    defparam u_clkctrl.width_clksel    = 2;
endmodule


// ── JTAG Debug Atom (replaces Xilinx BSCANE2) ───────────────────────────────
// Maps the SoC debug module JTAG port onto the Cyclone V JTAG chain.
module jtag_tap (
    output wire tck,
    output wire tms,
    output wire tdi,
    input  wire tdo,
    output wire capture,
    output wire shift,
    output wire update,
    output wire reset
);
    altera_jtag_sld_node #(
        .SLD_NODE_INFO       (805354496),  // DR length = 8, default info
        .SLD_MFGR_ID         (16'h6E),    // Altera manufacturer ID
        .SLD_TYPE_ID         (8'h34),
        .SLD_VERSION         (4'h0)
    ) u_jtag (
        .tck                 (tck),
        .tms                 (tms),
        .tdi                 (tdi),
        .tdo                 (tdo),
        .ir_in               (),
        .ir_out              (4'b0),
        .virtual_state_cdr   (capture),
        .virtual_state_sdr   (shift),
        .virtual_state_udr   (update),
        .virtual_state_e1dr  (),
        .virtual_state_e2dr  (),
        .virtual_state_pdr   (),
        .virtual_state_uir   (),
        .virtual_state_cir   (reset)
    );
endmodule

`endif  // INTEL_FPGA
