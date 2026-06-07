`timescale 1ns/1ps
// Clock and Reset Management Unit (CRU)
// Generates three clock domains from a single reference clock:
//   clk_cpu   – 100 MHz  (ref ÷ 1  when ref = 100 MHz)
//   clk_peri  –  25 MHz  (ref ÷ 4)
//   clk_ddr   – 200 MHz  (ref × 2)
// Each domain has an independent two-flop reset synchronizer.
//
// `ifdef SIMULATION: pure behavioral model (no FPGA primitives).
// `ifndef SIMULATION: instantiates Xilinx MMCME2_BASE + BUFGMUX for real FPGA.

module cru #(
    parameter int REF_MHZ = 100    // reference clock frequency in MHz
)(
    input  logic clk_ref,          // reference clock (100 MHz assumed)
    input  logic rst_async_n,      // async active-low POR reset
    // ── Generated clocks ────────────────────────────────────────────────────
    output logic clk_cpu,
    output logic clk_peri,
    output logic clk_ddr,
    // ── Synchronised resets (active-low, deasserted synchronously) ──────────
    output logic rst_cpu_n,
    output logic rst_peri_n,
    output logic rst_ddr_n,
    // ── MMCM lock indicator ─────────────────────────────────────────────────
    output logic locked
);

`ifdef SIMULATION
// ─── Behavioral MMCM model ────────────────────────────────────────────────────
// Generate the three clocks as divided/multiplied reference
localparam int CPU_DIV  = 1;
localparam int PERI_DIV = 4;
localparam int DDR_DIV  = 1;  // DDR generated at 2× by toggling at half ref period

// Derive periods from REF_MHZ
localparam real REF_PERIOD_NS  = 1000.0 / REF_MHZ;
localparam real CPU_PERIOD_NS  = REF_PERIOD_NS * CPU_DIV;
localparam real PERI_PERIOD_NS = REF_PERIOD_NS * PERI_DIV;
localparam real DDR_PERIOD_NS  = REF_PERIOD_NS / 2.0;

// Clock generation (free-running behavioral oscillators)
initial clk_cpu  = 1'b0;
initial clk_peri = 1'b0;
initial clk_ddr  = 1'b0;

always #(CPU_PERIOD_NS  / 2.0) clk_cpu  = ~clk_cpu;
always #(PERI_PERIOD_NS / 2.0) clk_peri = ~clk_peri;
always #(DDR_PERIOD_NS  / 2.0) clk_ddr  = ~clk_ddr;

// MMCM lock: assert after a fixed startup latency (200 ref cycles)
logic [7:0] lock_cnt;
always_ff @(posedge clk_ref or negedge rst_async_n) begin
    if (!rst_async_n) begin
        lock_cnt <= 8'd0;
        locked   <= 1'b0;
    end else begin
        if (!locked) begin
            if (lock_cnt == 8'd199)
                locked <= 1'b1;
            else
                lock_cnt <= lock_cnt + 8'd1;
        end
    end
end

`else
// ─── FPGA implementation (Xilinx 7-series MMCME2_BASE) ───────────────────────
// Multiply ×10 then divide: CPU÷10=1×, PERI÷40=0.25×, DDR÷5=2×
// CLKFBOUT_MULT_F=10, DIVCLK_DIVIDE=1, ref=100MHz → VCO=1000MHz
logic clkfb, clk_cpu_raw, clk_peri_raw, clk_ddr_raw;

MMCME2_BASE #(
    .CLKIN1_PERIOD    (10.0),       // 100 MHz ref
    .CLKFBOUT_MULT_F  (10.0),       // VCO = 1000 MHz
    .DIVCLK_DIVIDE    (1),
    .CLKOUT0_DIVIDE_F (10.0),       // 100 MHz → clk_cpu
    .CLKOUT1_DIVIDE   (40),         //  25 MHz → clk_peri
    .CLKOUT2_DIVIDE   (5)           // 200 MHz → clk_ddr
) u_mmcm (
    .CLKIN1    (clk_ref),
    .CLKFBIN   (clkfb),
    .CLKFBOUT  (clkfb),
    .CLKOUT0   (clk_cpu_raw),
    .CLKOUT1   (clk_peri_raw),
    .CLKOUT2   (clk_ddr_raw),
    .LOCKED    (locked),
    .PWRDWN    (1'b0),
    .RST       (!rst_async_n)
);

BUFG u_buf_cpu  (.I(clk_cpu_raw),  .O(clk_cpu));
BUFG u_buf_peri (.I(clk_peri_raw), .O(clk_peri));
BUFG u_buf_ddr  (.I(clk_ddr_raw),  .O(clk_ddr));

`endif // SIMULATION

// ─── Two-flop reset synchronizers (one per domain) ───────────────────────────
// Reset is deasserted only after MMCM is locked.
// Asserted async (any edge of rst_async_n or locked going low).

logic sync_rst_in;
assign sync_rst_in = rst_async_n & locked;  // both conditions required

// CPU domain synchronizer
logic rst_cpu_ff1, rst_cpu_ff2;
always_ff @(posedge clk_cpu or negedge sync_rst_in) begin
    if (!sync_rst_in) begin
        rst_cpu_ff1 <= 1'b0;
        rst_cpu_ff2 <= 1'b0;
    end else begin
        rst_cpu_ff1 <= 1'b1;
        rst_cpu_ff2 <= rst_cpu_ff1;
    end
end
assign rst_cpu_n = rst_cpu_ff2;

// Peripheral domain synchronizer
logic rst_peri_ff1, rst_peri_ff2;
always_ff @(posedge clk_peri or negedge sync_rst_in) begin
    if (!sync_rst_in) begin
        rst_peri_ff1 <= 1'b0;
        rst_peri_ff2 <= 1'b0;
    end else begin
        rst_peri_ff1 <= 1'b1;
        rst_peri_ff2 <= rst_peri_ff1;
    end
end
assign rst_peri_n = rst_peri_ff2;

// DDR domain synchronizer
logic rst_ddr_ff1, rst_ddr_ff2;
always_ff @(posedge clk_ddr or negedge sync_rst_in) begin
    if (!sync_rst_in) begin
        rst_ddr_ff1 <= 1'b0;
        rst_ddr_ff2 <= 1'b0;
    end else begin
        rst_ddr_ff1 <= 1'b1;
        rst_ddr_ff2 <= rst_ddr_ff1;
    end
end
assign rst_ddr_n = rst_ddr_ff2;

endmodule
