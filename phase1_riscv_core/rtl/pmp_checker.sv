`timescale 1ns/1ps

// PMP (Physical Memory Protection) checker — 8 regions, NAPOT + TOR + NA4.
// pmpcfg[n] bits: [7]=L(lock), [4:3]=A(00=OFF,01=TOR,10=NA4,11=NAPOT),
//                 [2]=X, [1]=W, [0]=R
// M-mode bypasses PMP unless the region has L-bit set.
// Default when no region matches: deny for U-mode, allow for M-mode.
//
// Address spaces:
//   addr_word = addr_i[31:2]  — word address (matches pmpaddr register format)
//   TOR bounds use pmpaddr<<2 (byte address) compared to addr_i (byte address)
//   NA4/NAPOT use word-address comparison: addr_word vs pmpaddr
//
// Icarus compat: NO bit-selects or unpacked-array accesses inside always blocks.
// All such extractions are done with assign statements outside always.
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
    // Packed arrays — variable indexing in always_comb is supported by Icarus
    logic [N-1:0] match;
    logic [N-1:0] allow;
    logic [N-1:0] locked;

    // Word address: pmpaddr register stores addr[31:2], so NA4/NAPOT compare in word space
    logic [31:0] addr_word;
    assign addr_word = {2'b00, addr_i[31:2]};   // zero-extend word address to 32 bits

    genvar n;
    generate
        for (n = 0; n < N; n++) begin : gen_region
            // ── Field extraction via assign (Icarus: OK outside always) ──────
            logic [1:0]  a_mode;
            logic        r_bit, w_bit, x_bit;

            assign a_mode    = pmpcfg[n][4:3];
            assign locked[n] = pmpcfg[n][7];
            assign r_bit     = pmpcfg[n][0];
            assign w_bit     = pmpcfg[n][1];
            assign x_bit     = pmpcfg[n][2];

            // ── Pre-extracted pmpaddr values ──────────────────────────────────
            logic [31:0] pmpaddr_n;      // pmpaddr[n] — word address value
            logic [31:0] pmpaddr_n_tor;  // pmpaddr[n]<<2 — byte address upper TOR bound
            logic [31:0] napot_mask;     // ~(pmpaddr[n] | (pmpaddr[n]+1)) — word-space mask
            logic [31:0] tor_lo;         // lower TOR bound (byte address)

            assign pmpaddr_n     = pmpaddr[n];
            assign pmpaddr_n_tor = {pmpaddr[n][29:0], 2'b00};  // pmpaddr<<2 (byte addr)
            assign napot_mask    = ~(pmpaddr[n] | (pmpaddr[n] + 32'd1));

            if (n == 0)
                assign tor_lo = 32'd0;
            else
                assign tor_lo = {pmpaddr[n-1][29:0], 2'b00};   // pmpaddr[n-1]<<2

            // ── Match: all comparisons consistent in their address space ──────
            // TOR:   byte-space  (addr_i vs pmpaddr<<2)
            // NA4:   word-space  (addr_i[31:2] vs pmpaddr)
            // NAPOT: word-space  (addr_i[31:2] & mask vs pmpaddr & mask)
            assign match[n] =
                (a_mode == 2'b01) ? ((addr_i   >= tor_lo)   && (addr_i  < pmpaddr_n_tor)) // TOR
              : (a_mode == 2'b10) ? (addr_word == pmpaddr_n)                               // NA4
              : (a_mode == 2'b11) ? ((addr_word & napot_mask) == (pmpaddr_n & napot_mask)) // NAPOT
              : 1'b0;                                                                       // OFF

            // ── Permission check ─────────────────────────────────────────────
            assign allow[n] = (!read_i  || r_bit) &&
                               (!write_i || w_bit) &&
                               (!exec_i  || x_bit);
        end
    endgenerate

    // ── Priority encode: first matching region wins ───────────────────────────
    // locked[i], match[i], allow[i] are packed-array accesses with variable index
    // — Icarus supports this (generates a MUX/priority tree at runtime).
    always_comb begin
        fault_o = 1'b0;
        if (m_mode_i) begin
            // M-mode: only locked regions constrain
            for (int i = 0; i < N; i++) begin
                if (match[i] && locked[i] && !allow[i])
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
