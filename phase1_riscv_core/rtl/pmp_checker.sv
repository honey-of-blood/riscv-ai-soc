`timescale 1ns/1ps

// PMP (Physical Memory Protection) checker — 8 regions, NAPOT + TOR + NA4.
// pmpcfg[n] bits: [7]=L(lock), [4:3]=A(00=OFF,01=TOR,10=NA4,11=NAPOT),
//                 [2]=X, [1]=W, [0]=R
// NAPOT match formula (no loops): napot_mask = ~(pmpaddr | (pmpaddr+1))
//   match iff (addr[31:2] & napot_mask) == (pmpaddr & napot_mask)
// M-mode bypasses PMP unless the region has L-bit set.
// Default when no region matches: deny for U-mode, allow for M-mode.
module pmp_checker #(
    parameter int N = 8
) (
    input  logic [31:0] addr_i,
    input  logic        read_i,
    input  logic        write_i,
    input  logic        exec_i,
    input  logic        m_mode_i,
    input  logic [7:0]  pmpcfg  [N],
    input  logic [31:0] pmpaddr [N],
    output logic        fault_o
);
    // Per-region match signals — computed as assigns (Icarus: no functions with loops)
    logic [N-1:0] match;
    logic [N-1:0] allow;

    // Icarus: extract bit fields outside always blocks
    logic [31:0] addr_w;   // word address (addr[31:2])
    assign addr_w = {addr_i[31:2], 2'b00};

    genvar n;
    generate
        for (n = 0; n < N; n++) begin : gen_region
            logic [1:0]  a_mode;
            logic        r_bit, w_bit, x_bit, l_bit;
            logic [31:0] napot_mask_n;
            logic [31:0] tor_lo;

            assign a_mode       = pmpcfg[n][4:3];
            assign l_bit        = pmpcfg[n][7];
            assign r_bit        = pmpcfg[n][0];
            assign w_bit        = pmpcfg[n][1];
            assign x_bit        = pmpcfg[n][2];

            // NAPOT mask: ~(pmpaddr | (pmpaddr+1)) — set where pmpaddr has 0s (base bits)
            assign napot_mask_n = ~(pmpaddr[n] | (pmpaddr[n] + 32'd1));

            // TOR lower bound: pmpaddr[n-1] (0 for region 0)
            if (n == 0)
                assign tor_lo = 32'd0;
            else
                assign tor_lo = {pmpaddr[n-1], 2'b00};

            always_comb begin
                match[n] = 1'b0;
                case (a_mode)
                    2'b00: match[n] = 1'b0;
                    2'b01: // TOR: tor_lo <= addr < pmpaddr[n]<<2
                        match[n] = (addr_i >= tor_lo) && (addr_i < {pmpaddr[n], 2'b00});
                    2'b10: // NA4: exact 4-byte match
                        match[n] = (addr_i[31:2] == pmpaddr[n][31:2]);
                    2'b11: // NAPOT
                        match[n] = ((addr_i[31:2] & napot_mask_n) == (pmpaddr[n] & napot_mask_n));
                    default: match[n] = 1'b0;
                endcase
            end

            // Permission check
            assign allow[n] = (!read_i  || r_bit) &&
                               (!write_i || w_bit) &&
                               (!exec_i  || x_bit);
        end
    endgenerate

    // Priority encode: first matching region wins
    always_comb begin
        fault_o = 1'b0;
        if (m_mode_i) begin
            // M-mode: only locked regions constrain
            for (int i = 0; i < N; i++) begin
                if (match[i] && pmpcfg[i][7] && !allow[i])
                    fault_o = 1'b1;
            end
        end else begin
            // U/S-mode: first matching region determines access; no match = deny
            logic found;
            found = 1'b0;
            for (int i = 0; i < N; i++) begin
                if (match[i] && !found) begin
                    found = 1'b1;
                    if (!allow[i]) fault_o = 1'b1;
                end
            end
            if (!found) fault_o = 1'b1;
        end
    end

endmodule
