`timescale 1ns/1ps
// AXI4-Lite slave wrapper for the 4×4 systolic-array accelerator.
// Base address: 0x5000_0000  (crossbar slave 2)
//
// MMIO register map (byte offset, word-aligned):
//   0x00  CTRL     {31:2=0, 1:done(RO), 0:start(W1)}
//   0x04  W_row0   {W[0][3],W[0][2],W[0][1],W[0][0]} — signed INT8 packed
//   0x08  W_row1
//   0x0C  W_row2
//   0x10  W_row3
//   0x14  A_row0   {A[0][3],A[0][2],A[0][1],A[0][0]} — signed INT8 packed
//   0x18  A_row1
//   0x1C  A_row2
//   0x20  A_row3
//   0x24  Y[0][0]  (32-bit signed result, read-only)
//   0x28  Y[0][1] ... 0x60  Y[3][3]   (16 registers total)
//
// Computation flow:
//   1. Write W_row0..3 (weights)
//   2. Write A_row0..3 (activations)
//   3. Write CTRL.start = 1
//   4. Poll CTRL.done until 1 (~10 cycles)
//   5. Read Y[r][c] registers

module accel_top (
    input  logic        clk,
    input  logic        rst_n,

    input  logic [31:0] s_awaddr,
    input  logic        s_awvalid,
    output logic        s_awready,
    input  logic [31:0] s_wdata,
    input  logic  [3:0] s_wstrb,
    input  logic        s_wvalid,
    output logic        s_wready,
    output logic  [1:0] s_bresp,
    output logic        s_bvalid,
    input  logic        s_bready,
    input  logic [31:0] s_araddr,
    input  logic        s_arvalid,
    output logic        s_arready,
    output logic [31:0] s_rdata,
    output logic  [1:0] s_rresp,
    output logic        s_rvalid,
    input  logic        s_rready
);

    // ── Register bank ─────────────────────────────────────────────────────────
    logic [7:0] w_reg [4][4];  // w_reg[k][n] = W[k][n]
    logic [7:0] a_reg [4][4];  // a_reg[m][k] = A[m][k]
    logic [31:0] y_reg [4][4]; // y_reg[m][n] = Y[m][n], captured from array

    logic done_r, start_r;

    // ── FSM ───────────────────────────────────────────────────────────────────
    typedef enum logic [1:0] {IDLE, COMPUTE, DONE_ST} state_t;
    state_t state;
    logic [2:0] cyc; // compute cycle counter 0..7

    // ── Staggered activation feeds (combinational) ─────────────────────────────
    // a_feed[k] = A[cyc-k][k]  if 0 ≤ cyc-k ≤ 3, else 0
    logic [7:0] af0, af1, af2, af3;

    // Row 0: valid at cyc=0..3
    assign af0 = (cyc == 3'd0) ? a_reg[0][0] :
                 (cyc == 3'd1) ? a_reg[1][0] :
                 (cyc == 3'd2) ? a_reg[2][0] :
                 (cyc == 3'd3) ? a_reg[3][0] : 8'h0;

    // Row 1: valid at cyc=1..4
    assign af1 = (cyc == 3'd1) ? a_reg[0][1] :
                 (cyc == 3'd2) ? a_reg[1][1] :
                 (cyc == 3'd3) ? a_reg[2][1] :
                 (cyc == 3'd4) ? a_reg[3][1] : 8'h0;

    // Row 2: valid at cyc=2..5
    assign af2 = (cyc == 3'd2) ? a_reg[0][2] :
                 (cyc == 3'd3) ? a_reg[1][2] :
                 (cyc == 3'd4) ? a_reg[2][2] :
                 (cyc == 3'd5) ? a_reg[3][2] : 8'h0;

    // Row 3: valid at cyc=3..6
    assign af3 = (cyc == 3'd3) ? a_reg[0][3] :
                 (cyc == 3'd4) ? a_reg[1][3] :
                 (cyc == 3'd5) ? a_reg[2][3] :
                 (cyc == 3'd6) ? a_reg[3][3] : 8'h0;

    // Feed zeros when not computing (so array doesn't accumulate garbage)
    logic [7:0] feed0, feed1, feed2, feed3;
    assign feed0 = (state == COMPUTE) ? af0 : 8'h0;
    assign feed1 = (state == COMPUTE) ? af1 : 8'h0;
    assign feed2 = (state == COMPUTE) ? af2 : 8'h0;
    assign feed3 = (state == COMPUTE) ? af3 : 8'h0;

    // ── Systolic array instance ───────────────────────────────────────────────
    logic [31:0] y_out0, y_out1, y_out2, y_out3;

    systolic_array u_array (
        .clk    (clk),
        .rst_n  (rst_n),
        .w_row0 ({w_reg[0][3], w_reg[0][2], w_reg[0][1], w_reg[0][0]}),
        .w_row1 ({w_reg[1][3], w_reg[1][2], w_reg[1][1], w_reg[1][0]}),
        .w_row2 ({w_reg[2][3], w_reg[2][2], w_reg[2][1], w_reg[2][0]}),
        .w_row3 ({w_reg[3][3], w_reg[3][2], w_reg[3][1], w_reg[3][0]}),
        .a_feed0(feed0), .a_feed1(feed1),
        .a_feed2(feed2), .a_feed3(feed3),
        .y_out0 (y_out0), .y_out1(y_out1),
        .y_out2 (y_out2), .y_out3(y_out3)
    );

    // ── FSM + output capture ──────────────────────────────────────────────────
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            state   <= IDLE;
            cyc     <= 3'd0;
            done_r  <= 1'b0;
            start_r <= 1'b0;
        end else begin
            case (state)
                IDLE: begin
                    if (start_r) begin
                        state  <= COMPUTE;
                        cyc    <= 3'd0;
                        done_r <= 1'b0;
                    end
                end
                COMPUTE: begin
                    cyc <= cyc + 3'd1;
                    // y_out[n] holds Y[m][n] one cycle after edge m+3,
                    // i.e. at cyc=4,5,6,7 → capture rows 0,1,2,3.
                    case (cyc)
                        3'd4: begin
                            y_reg[0][0] <= y_out0; y_reg[0][1] <= y_out1;
                            y_reg[0][2] <= y_out2; y_reg[0][3] <= y_out3;
                        end
                        3'd5: begin
                            y_reg[1][0] <= y_out0; y_reg[1][1] <= y_out1;
                            y_reg[1][2] <= y_out2; y_reg[1][3] <= y_out3;
                        end
                        3'd6: begin
                            y_reg[2][0] <= y_out0; y_reg[2][1] <= y_out1;
                            y_reg[2][2] <= y_out2; y_reg[2][3] <= y_out3;
                        end
                        3'd7: begin
                            y_reg[3][0] <= y_out0; y_reg[3][1] <= y_out1;
                            y_reg[3][2] <= y_out2; y_reg[3][3] <= y_out3;
                            state  <= DONE_ST;
                            done_r <= 1'b1;
                        end
                        default: ;
                    endcase
                end
                DONE_ST: begin
                    // Stay here; a new start write clears done and restarts.
                    if (start_r && !done_r) begin
                        state <= COMPUTE;
                        cyc   <= 3'd0;
                    end
                end
            endcase
        end
    end

    // ── AXI4-Lite write path ──────────────────────────────────────────────────
    // AWREADY = WREADY = 1 (always accept)
    assign s_awready = 1'b1;
    assign s_wready  = 1'b1;
    assign s_bresp   = 2'b00;

    // Word address extracted outside always (Icarus bit-select rule)
    logic [5:0] aw_idx;
    assign aw_idx = s_awaddr[7:2];

    logic        wr_pending;
    logic [5:0]  wr_idx_r;
    logic [31:0] wr_data_r;
    logic  [3:0] wr_strb_r;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            wr_pending <= 1'b0;
            s_bvalid   <= 1'b0;
            for (int i = 0; i < 4; i++) begin
                for (int j = 0; j < 4; j++) begin
                    w_reg[i][j] <= 8'h0;
                    a_reg[i][j] <= 8'h0;
                    y_reg[i][j] <= 32'h0;
                end
            end
        end else begin
            // Latch AW+W
            if (s_awvalid && s_wvalid) begin
                wr_idx_r   <= aw_idx;
                wr_data_r  <= s_wdata;
                wr_strb_r  <= s_wstrb;
                wr_pending <= 1'b1;
            end

            // Perform register write
            if (wr_pending) begin
                wr_pending <= 1'b0;
                s_bvalid   <= 1'b1;
                case (wr_idx_r)
                    6'd0: begin // CTRL
                        if (wr_strb_r[0]) begin
                            start_r <= wr_data_r[0];
                            // New start clears done
                            if (wr_data_r[0]) done_r <= 1'b0;
                        end
                    end
                    6'd1: begin // W_row0
                        if (wr_strb_r[0]) w_reg[0][0] <= wr_data_r[ 7: 0];
                        if (wr_strb_r[1]) w_reg[0][1] <= wr_data_r[15: 8];
                        if (wr_strb_r[2]) w_reg[0][2] <= wr_data_r[23:16];
                        if (wr_strb_r[3]) w_reg[0][3] <= wr_data_r[31:24];
                    end
                    6'd2: begin // W_row1
                        if (wr_strb_r[0]) w_reg[1][0] <= wr_data_r[ 7: 0];
                        if (wr_strb_r[1]) w_reg[1][1] <= wr_data_r[15: 8];
                        if (wr_strb_r[2]) w_reg[1][2] <= wr_data_r[23:16];
                        if (wr_strb_r[3]) w_reg[1][3] <= wr_data_r[31:24];
                    end
                    6'd3: begin // W_row2
                        if (wr_strb_r[0]) w_reg[2][0] <= wr_data_r[ 7: 0];
                        if (wr_strb_r[1]) w_reg[2][1] <= wr_data_r[15: 8];
                        if (wr_strb_r[2]) w_reg[2][2] <= wr_data_r[23:16];
                        if (wr_strb_r[3]) w_reg[2][3] <= wr_data_r[31:24];
                    end
                    6'd4: begin // W_row3
                        if (wr_strb_r[0]) w_reg[3][0] <= wr_data_r[ 7: 0];
                        if (wr_strb_r[1]) w_reg[3][1] <= wr_data_r[15: 8];
                        if (wr_strb_r[2]) w_reg[3][2] <= wr_data_r[23:16];
                        if (wr_strb_r[3]) w_reg[3][3] <= wr_data_r[31:24];
                    end
                    6'd5: begin // A_row0
                        if (wr_strb_r[0]) a_reg[0][0] <= wr_data_r[ 7: 0];
                        if (wr_strb_r[1]) a_reg[0][1] <= wr_data_r[15: 8];
                        if (wr_strb_r[2]) a_reg[0][2] <= wr_data_r[23:16];
                        if (wr_strb_r[3]) a_reg[0][3] <= wr_data_r[31:24];
                    end
                    6'd6: begin // A_row1
                        if (wr_strb_r[0]) a_reg[1][0] <= wr_data_r[ 7: 0];
                        if (wr_strb_r[1]) a_reg[1][1] <= wr_data_r[15: 8];
                        if (wr_strb_r[2]) a_reg[1][2] <= wr_data_r[23:16];
                        if (wr_strb_r[3]) a_reg[1][3] <= wr_data_r[31:24];
                    end
                    6'd7: begin // A_row2
                        if (wr_strb_r[0]) a_reg[2][0] <= wr_data_r[ 7: 0];
                        if (wr_strb_r[1]) a_reg[2][1] <= wr_data_r[15: 8];
                        if (wr_strb_r[2]) a_reg[2][2] <= wr_data_r[23:16];
                        if (wr_strb_r[3]) a_reg[2][3] <= wr_data_r[31:24];
                    end
                    6'd8: begin // A_row3
                        if (wr_strb_r[0]) a_reg[3][0] <= wr_data_r[ 7: 0];
                        if (wr_strb_r[1]) a_reg[3][1] <= wr_data_r[15: 8];
                        if (wr_strb_r[2]) a_reg[3][2] <= wr_data_r[23:16];
                        if (wr_strb_r[3]) a_reg[3][3] <= wr_data_r[31:24];
                    end
                    default: ; // Y registers are read-only
                endcase
            end

            if (s_bvalid && s_bready) s_bvalid <= 1'b0;
        end
    end

    // ── AXI4-Lite read path ───────────────────────────────────────────────────
    assign s_arready = 1'b1;
    assign s_rresp   = 2'b00;

    logic [5:0] ar_idx;
    assign ar_idx = s_araddr[7:2];

    // Combinational read-data mux
    logic [31:0] rdata_comb;
    always_comb begin
        rdata_comb = 32'h0;
        case (ar_idx)
            6'd0:  rdata_comb = {30'h0, done_r, start_r};
            6'd1:  rdata_comb = {w_reg[0][3],w_reg[0][2],w_reg[0][1],w_reg[0][0]};
            6'd2:  rdata_comb = {w_reg[1][3],w_reg[1][2],w_reg[1][1],w_reg[1][0]};
            6'd3:  rdata_comb = {w_reg[2][3],w_reg[2][2],w_reg[2][1],w_reg[2][0]};
            6'd4:  rdata_comb = {w_reg[3][3],w_reg[3][2],w_reg[3][1],w_reg[3][0]};
            6'd5:  rdata_comb = {a_reg[0][3],a_reg[0][2],a_reg[0][1],a_reg[0][0]};
            6'd6:  rdata_comb = {a_reg[1][3],a_reg[1][2],a_reg[1][1],a_reg[1][0]};
            6'd7:  rdata_comb = {a_reg[2][3],a_reg[2][2],a_reg[2][1],a_reg[2][0]};
            6'd8:  rdata_comb = {a_reg[3][3],a_reg[3][2],a_reg[3][1],a_reg[3][0]};
            // Y[m][n] at index 9 + m*4 + n
            6'd9:  rdata_comb = y_reg[0][0]; 6'd10: rdata_comb = y_reg[0][1];
            6'd11: rdata_comb = y_reg[0][2]; 6'd12: rdata_comb = y_reg[0][3];
            6'd13: rdata_comb = y_reg[1][0]; 6'd14: rdata_comb = y_reg[1][1];
            6'd15: rdata_comb = y_reg[1][2]; 6'd16: rdata_comb = y_reg[1][3];
            6'd17: rdata_comb = y_reg[2][0]; 6'd18: rdata_comb = y_reg[2][1];
            6'd19: rdata_comb = y_reg[2][2]; 6'd20: rdata_comb = y_reg[2][3];
            6'd21: rdata_comb = y_reg[3][0]; 6'd22: rdata_comb = y_reg[3][1];
            6'd23: rdata_comb = y_reg[3][2]; 6'd24: rdata_comb = y_reg[3][3];
            default: rdata_comb = 32'h0;
        endcase
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s_rvalid <= 1'b0;
            s_rdata  <= 32'h0;
        end else begin
            if (s_arvalid) begin
                s_rdata  <= rdata_comb;
                s_rvalid <= 1'b1;
            end else if (s_rvalid && s_rready) begin
                s_rvalid <= 1'b0;
            end
        end
    end

endmodule
