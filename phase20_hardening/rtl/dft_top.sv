`timescale 1ns/1ps
// DFT Scan Chain Wrapper
// Demonstrates DFT-ready infrastructure:
//   - scan_en_i  : when 1, selects scan clock and enables scan shift
//   - scan_clk_i : dedicated scan clock (muxed via BUFGMUX in FPGA, simple mux in sim)
//   - scan_in_i  : serial scan chain input
//   - scan_out_o : serial scan chain output
//
// Internal: an N-bit shift register that acts as the scan chain.
// In functional mode (scan_en_i=0): shift register loads from d_i on clk_i.
// In scan mode    (scan_en_i=1): shift register shifts through scan_in_i on scan_clk.
//
// SCAN_DEPTH: number of flip-flops in the chain (parameterized for testability).

module dft_top #(
    parameter int SCAN_DEPTH = 16   // number of scan FFs
)(
    // ── Functional interface ─────────────────────────────────────────────────
    input  logic                  clk_i,
    input  logic                  rst_n,
    input  logic [SCAN_DEPTH-1:0] d_i,     // parallel functional data in
    output logic [SCAN_DEPTH-1:0] q_o,     // parallel functional data out
    // ── DFT scan interface ───────────────────────────────────────────────────
    input  logic                  scan_en_i,
    input  logic                  scan_clk_i,
    input  logic                  scan_in_i,
    output logic                  scan_out_o
);

// ─── Clock mux: functional clock vs scan clock ────────────────────────────────
// Simulation: simple combinational mux.
// FPGA synthesis: replace with BUFGMUX for glitch-free switching.
logic clk_mux;

`ifdef SIMULATION
assign clk_mux = scan_en_i ? scan_clk_i : clk_i;
`else
// Xilinx BUFGMUX — S=0 → I0 (functional), S=1 → I1 (scan)
BUFGMUX u_clk_mux (
    .O  (clk_mux),
    .I0 (clk_i),
    .I1 (scan_clk_i),
    .S  (scan_en_i)
);
`endif

// ─── Scan chain flip-flop array ───────────────────────────────────────────────
// Each FF: in scan mode shifts; in functional mode loads d_i[i]
// (* SCAN_ENABLE = "TRUE" *) attribute marks FFs for DFT insertion tooling
logic [SCAN_DEPTH-1:0] scan_ff /* synthesis syn_sdf_annotate="DFT" */;

genvar gi;
generate
    for (gi = 0; gi < SCAN_DEPTH; gi++) begin : gen_scan_ff
        always_ff @(posedge clk_mux or negedge rst_n) begin
            if (!rst_n) begin
                scan_ff[gi] <= 1'b0;
            end else begin
                if (scan_en_i) begin
                    // Scan shift: chain from MSB to LSB
                    // FF[SCAN_DEPTH-1] gets scan_in, FF[i] gets FF[i+1]
                    if (gi == SCAN_DEPTH - 1)
                        scan_ff[gi] <= scan_in_i;
                    else
                        scan_ff[gi] <= scan_ff[gi + 1];
                end else begin
                    // Functional capture
                    scan_ff[gi] <= d_i[gi];
                end
            end
        end
    end
endgenerate

// Outputs
assign q_o       = scan_ff;
assign scan_out_o = scan_ff[0];  // LSB exits the chain last

endmodule
