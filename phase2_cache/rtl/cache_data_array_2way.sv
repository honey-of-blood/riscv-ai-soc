`timescale 1ns/1ps
// 2-way set-associative data array with SECDED ECC.
//
// Each word is stored as 39 bits: {p[6], d[31:0] with p[5:0] interleaved}.
// Encoding: standard [39,32] SECDED Hamming.
//   Data bits are placed at codeword positions (1-indexed):
//   3,5,6,7,9,10,11,12,13,14,15,17,18,19,20,21,22,23,24,25,26,27,28,29,30,
//   31,33,34,35,36,37,38
//   Parity bits at positions: 1(p0),2(p1),4(p2),8(p3),16(p4),32(p5)
//   Overall parity p6 covers all 38 bits.
//
// On read: syndrome computed; single-bit errors corrected silently;
// double-bit errors flagged via ecc_error_o (sticky in controller).
//
// Simulation: ecc_inject_pos_i / ecc_inject_en_i can corrupt a stored bit
// for testing SECDED decode paths.

module cache_data_array_2way #(
    parameter N_SETS    = 64,
    parameter LINE_WORDS = 4
)(
    input  logic        clk,
    input  logic        rst,

    // Write port (one word per cycle)
    input  logic        we_i,
    input  logic        way_i,         // 0=way0, 1=way1
    input  logic [5:0]  idx_i,
    input  logic [1:0]  word_i,
    input  logic [3:0]  be_i,
    input  logic [31:0] wdata_i,

    // Read outputs — all four words from each way (async)
    output logic [31:0] way0_w0_o, way0_w1_o, way0_w2_o, way0_w3_o,
    output logic [31:0] way1_w0_o, way1_w1_o, way1_w2_o, way1_w3_o,

    // ECC status
    output logic        ecc_error_o,   // double-bit detect; cleared on rst

    // Test injection (simulation only — use to corrupt stored bits for ECC tests)
    input  logic        ecc_inject_en_i,
    input  logic        way_inject_i,
    input  logic [5:0]  idx_inject_i,
    input  logic [1:0]  word_inject_i,
    input  logic [5:0]  bit_inject_i    // which bit [5:0] in 38-bit data+parity word to flip
);

// ── SECDED encode ───────────────────────────────────────────────────────────
// Returns 7 parity bits for 32-bit data d.
function automatic [6:0] secded_encode;
    input [31:0] d;
    logic [5:0] p;
    begin
        // p[0]: positions with bit0 set: 3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,37,39
        //       data: d0,d1,d3,d4,d6,d8,d10,d11,d13,d15,d17,d19,d21,d23,d25,d26,d28,d30
        p[0] = d[0]^d[1]^d[3]^d[4]^d[6]^d[8]^d[10]^d[11]^d[13]^d[15]
              ^d[17]^d[19]^d[21]^d[23]^d[25]^d[26]^d[28]^d[30];
        // p[1]: positions with bit1 set: 3,6,7,10,11,14,15,18,19,22,23,26,27,30,31,34,35,38,39
        //       data: d0,d2,d3,d5,d6,d9,d10,d12,d13,d16,d17,d20,d21,d24,d25,d27,d28,d31
        p[1] = d[0]^d[2]^d[3]^d[5]^d[6]^d[9]^d[10]^d[12]^d[13]^d[16]
              ^d[17]^d[20]^d[21]^d[24]^d[25]^d[27]^d[28]^d[31];
        // p[2]: positions with bit2 set: 5,6,7,12,13,14,15,20,21,22,23,28,29,30,31,36,37,38,39
        //       data: d1,d2,d3,d7,d8,d9,d10,d14,d15,d16,d17,d22,d23,d24,d25,d29,d30,d31
        p[2] = d[1]^d[2]^d[3]^d[7]^d[8]^d[9]^d[10]^d[14]^d[15]^d[16]
              ^d[17]^d[22]^d[23]^d[24]^d[25]^d[29]^d[30]^d[31];
        // p[3]: positions with bit3 set: 9-15,24-31
        //       data: d4,d5,d6,d7,d8,d9,d10,d18,d19,d20,d21,d22,d23,d24,d25
        p[3] = d[4]^d[5]^d[6]^d[7]^d[8]^d[9]^d[10]
              ^d[18]^d[19]^d[20]^d[21]^d[22]^d[23]^d[24]^d[25];
        // p[4]: positions with bit4 set: 17-31
        //       data: d11,d12,d13,d14,d15,d16,d17,d18,d19,d20,d21,d22,d23,d24,d25
        p[4] = d[11]^d[12]^d[13]^d[14]^d[15]^d[16]^d[17]
              ^d[18]^d[19]^d[20]^d[21]^d[22]^d[23]^d[24]^d[25];
        // p[5]: positions with bit5 set: 33-39
        //       data: d26,d27,d28,d29,d30,d31
        p[5] = d[26]^d[27]^d[28]^d[29]^d[30]^d[31];
        // p[6]: overall even parity over all 38 bits
        secded_encode = {(^p ^ ^d), p};
    end
endfunction

// ── SECDED decode: returns corrected data and error flags ───────────────────
// corrected  = d with single-bit fix applied
// dbl_err    = double-bit error detected (uncorrectable)
// Return: [32]=dbl_err, [31:0]=corrected (33-bit total)
function automatic [32:0] secded_decode;
    input [38:0] stored;   // {p6, p5, p4, p3, p2, p1, p0, d[31:0]} but we store flat
    // For simplicity, stored[6:0] = parity, stored[38:7] = data[31:0] - NO
    // Stored format: {p[6], d[31:0], p[5:0]} where overall parity is MSB
    // Actually stored as: stored[38:32]=p[6:0], stored[31:0]=d[31:0]
    logic [6:0] p_stored;
    logic [31:0] d_stored;
    logic [6:0] p_calc;
    logic [5:0] syn;
    logic        overall_syn;
    logic [31:0] corrected;
    logic        dbl_err;
    begin
        p_stored  = stored[38:32];
        d_stored  = stored[31:0];
        p_calc    = secded_encode(d_stored);
        syn       = p_stored[5:0] ^ p_calc[5:0];
        // overall_syn = XOR of all 39 received bits.
        // Correct: p_stored[6] ^ (^p_stored[5:0] ^ ^d_stored).
        // Using p_calc[6] instead would re-derive from corrupted data and
        // give wrong results for 2-bit data errors (odd Hamming parity changes).
        overall_syn = p_stored[6] ^ (^p_stored[5:0] ^ ^d_stored);

        corrected = d_stored;
        dbl_err   = 1'b0;

        if (syn == 6'd0) begin
            // no error or overall parity flipped alone — no data fix
        end else if (overall_syn) begin
            // Single-bit error: syndrome gives codeword position (1-indexed)
            // Map syndrome value → data bit index
            case (syn)
                // parity bit positions: 1,2,4,8,16,32 → no data correction
                6'd1, 6'd2, 6'd4, 6'd8, 6'd16, 6'd32: corrected = d_stored;
                // data bit positions
                6'd3:  corrected[0]  = ~d_stored[0];
                6'd5:  corrected[1]  = ~d_stored[1];
                6'd6:  corrected[2]  = ~d_stored[2];
                6'd7:  corrected[3]  = ~d_stored[3];
                6'd9:  corrected[4]  = ~d_stored[4];
                6'd10: corrected[5]  = ~d_stored[5];
                6'd11: corrected[6]  = ~d_stored[6];
                6'd12: corrected[7]  = ~d_stored[7];
                6'd13: corrected[8]  = ~d_stored[8];
                6'd14: corrected[9]  = ~d_stored[9];
                6'd15: corrected[10] = ~d_stored[10];
                6'd17: corrected[11] = ~d_stored[11];
                6'd18: corrected[12] = ~d_stored[12];
                6'd19: corrected[13] = ~d_stored[13];
                6'd20: corrected[14] = ~d_stored[14];
                6'd21: corrected[15] = ~d_stored[15];
                6'd22: corrected[16] = ~d_stored[16];
                6'd23: corrected[17] = ~d_stored[17];
                6'd24: corrected[18] = ~d_stored[18];
                6'd25: corrected[19] = ~d_stored[19];
                6'd26: corrected[20] = ~d_stored[20];
                6'd27: corrected[21] = ~d_stored[21];
                6'd28: corrected[22] = ~d_stored[22];
                6'd29: corrected[23] = ~d_stored[23];
                6'd30: corrected[24] = ~d_stored[24];
                6'd31: corrected[25] = ~d_stored[25];
                6'd33: corrected[26] = ~d_stored[26];
                6'd34: corrected[27] = ~d_stored[27];
                6'd35: corrected[28] = ~d_stored[28];
                6'd36: corrected[29] = ~d_stored[29];
                6'd37: corrected[30] = ~d_stored[30];
                6'd38: corrected[31] = ~d_stored[31];
                default: corrected = d_stored;
            endcase
        end else begin
            // syn != 0 and overall_syn = 0 → double-bit error
            dbl_err = 1'b1;
        end

        secded_decode = {dbl_err, corrected};
    end
endfunction

// ── Storage arrays — {p[6:0], d[31:0]} = 39 bits per word ──────────────────
logic [38:0] way0 [0:N_SETS-1][0:LINE_WORDS-1];
logic [38:0] way1 [0:N_SETS-1][0:LINE_WORDS-1];

// Initialize to all-zero valid SECDED codewords so unwritten way entries don't
// trigger spurious double-bit errors in the registered ECC check.
integer _si, _wi;
initial begin
    for (_si = 0; _si < N_SETS; _si = _si + 1) begin
        for (_wi = 0; _wi < LINE_WORDS; _wi = _wi + 1) begin
            way0[_si][_wi] = 39'b0;
            way1[_si][_wi] = 39'b0;
        end
    end
end

// ── Write (with byte enables, ECC re-encoded on write) ──────────────────────
logic [31:0] cur_d0, cur_d1;
logic [31:0] new_d;
logic [6:0]  new_p;

integer si, wi;
always_ff @(posedge clk) begin
    if (we_i) begin
        if (!way_i) begin
            cur_d0 = way0[idx_i][word_i][31:0];
            new_d  = cur_d0;
            if (be_i[0]) new_d[ 7: 0] = wdata_i[ 7: 0];
            if (be_i[1]) new_d[15: 8] = wdata_i[15: 8];
            if (be_i[2]) new_d[23:16] = wdata_i[23:16];
            if (be_i[3]) new_d[31:24] = wdata_i[31:24];
            new_p = secded_encode(new_d);
            way0[idx_i][word_i] <= {new_p, new_d};
        end else begin
            cur_d1 = way1[idx_i][word_i][31:0];
            new_d  = cur_d1;
            if (be_i[0]) new_d[ 7: 0] = wdata_i[ 7: 0];
            if (be_i[1]) new_d[15: 8] = wdata_i[15: 8];
            if (be_i[2]) new_d[23:16] = wdata_i[23:16];
            if (be_i[3]) new_d[31:24] = wdata_i[31:24];
            new_p = secded_encode(new_d);
            way1[idx_i][word_i] <= {new_p, new_d};
        end
    end

    // ECC test injection: flip one bit of stored word.
    // Variable bit-select on LHS not supported by Icarus 12; mask-XOR is used instead.
    if (ecc_inject_en_i) begin
        if (!way_inject_i)
            way0[idx_inject_i][word_inject_i] <=
                way0[idx_inject_i][word_inject_i] ^ (39'b1 << bit_inject_i);
        else
            way1[idx_inject_i][word_inject_i] <=
                way1[idx_inject_i][word_inject_i] ^ (39'b1 << bit_inject_i);
    end
end

// ── Read with SECDED correction (async) ─────────────────────────────────────
// Data outputs: combinational; re-triggered when idx_i changes (every new cache
// access), which covers all normal hit/fill paths.
logic [32:0] dec_w0_0, dec_w1_0, dec_w2_0, dec_w3_0;
logic [32:0] dec_w0_1, dec_w1_1, dec_w2_1, dec_w3_1;

assign dec_w0_0 = secded_decode(way0[idx_i][0]);
assign dec_w1_0 = secded_decode(way0[idx_i][1]);
assign dec_w2_0 = secded_decode(way0[idx_i][2]);
assign dec_w3_0 = secded_decode(way0[idx_i][3]);
assign dec_w0_1 = secded_decode(way1[idx_i][0]);
assign dec_w1_1 = secded_decode(way1[idx_i][1]);
assign dec_w2_1 = secded_decode(way1[idx_i][2]);
assign dec_w3_1 = secded_decode(way1[idx_i][3]);

assign way0_w0_o = dec_w0_0[31:0];
assign way0_w1_o = dec_w1_0[31:0];
assign way0_w2_o = dec_w2_0[31:0];
assign way0_w3_o = dec_w3_0[31:0];

assign way1_w0_o = dec_w0_1[31:0];
assign way1_w1_o = dec_w1_1[31:0];
assign way1_w2_o = dec_w2_1[31:0];
assign way1_w3_o = dec_w3_1[31:0];

// ── ECC error: registered, 1-cycle delayed ───────────────────────────────────
// always_ff reads array elements directly at each clock edge — no sensitivity
// tracking needed. After an injection NBA on edge N, ecc_error_o asserts on
// edge N+1 when the FF reads the updated (post-injection) values.
// Blocking temps r0..r7 hold the intermediate decode results within the same
// clock edge evaluation before the NBA for ecc_error_o is scheduled.
logic [32:0] r0, r1, r2, r3, r4, r5, r6, r7;

always_ff @(posedge clk or posedge rst) begin
    if (rst) begin
        ecc_error_o <= 1'b0;
    end else begin
        r0 = secded_decode(way0[idx_i][0]);
        r1 = secded_decode(way0[idx_i][1]);
        r2 = secded_decode(way0[idx_i][2]);
        r3 = secded_decode(way0[idx_i][3]);
        r4 = secded_decode(way1[idx_i][0]);
        r5 = secded_decode(way1[idx_i][1]);
        r6 = secded_decode(way1[idx_i][2]);
        r7 = secded_decode(way1[idx_i][3]);
        ecc_error_o <= r0[32] | r1[32] | r2[32] | r3[32]
                     | r4[32] | r5[32] | r6[32] | r7[32];
    end
end

endmodule
