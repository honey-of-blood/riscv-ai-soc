`timescale 1ns/1ps
// SHA-256 hardware accelerator — APB slave.
//
// APB register map (byte offset):
//   0x00        CTRL     [0]=start  [1]=reset_hash
//   0x04–0x40   MSG0–MSG15   512-bit message block (16 × 32-bit big-endian words)
//   0x44–0x60   HASH0–HASH7  256-bit running digest (read after STATUS.done=1)
//   0x64        STATUS   [0]=done  [1]=busy
//
// Multi-block usage:
//   1. Write CTRL[1]=1 (reset_hash) to init IV.
//   2. For each 512-bit block: write MSG0–MSG15, write CTRL[0]=1, poll STATUS[0].
//   3. Read HASH0–HASH7 after last block.
//
// Latency: 64 cycles per block.

module sha256_top (
    input  logic        clk,
    input  logic        rst_n,

    input  logic [7:0]  paddr,
    input  logic        psel,
    input  logic        penable,
    input  logic        pwrite,
    input  logic [31:0] pwdata,
    output logic [31:0] prdata,
    output logic        pready
);

assign pready = 1'b1;

logic apb_wr;
assign apb_wr = psel & penable & pwrite;

// ── SHA-256 round constants ───────────────────────────────────────────────
logic [31:0] K [0:63];
assign K[ 0]=32'h428a2f98; assign K[ 1]=32'h71374491; assign K[ 2]=32'hb5c0fbcf; assign K[ 3]=32'he9b5dba5;
assign K[ 4]=32'h3956c25b; assign K[ 5]=32'h59f111f1; assign K[ 6]=32'h923f82a4; assign K[ 7]=32'hab1c5ed5;
assign K[ 8]=32'hd807aa98; assign K[ 9]=32'h12835b01; assign K[10]=32'h243185be; assign K[11]=32'h550c7dc3;
assign K[12]=32'h72be5d74; assign K[13]=32'h80deb1fe; assign K[14]=32'h9bdc06a7; assign K[15]=32'hc19bf174;
assign K[16]=32'he49b69c1; assign K[17]=32'hefbe4786; assign K[18]=32'h0fc19dc6; assign K[19]=32'h240ca1cc;
assign K[20]=32'h2de92c6f; assign K[21]=32'h4a7484aa; assign K[22]=32'h5cb0a9dc; assign K[23]=32'h76f988da;
assign K[24]=32'h983e5152; assign K[25]=32'ha831c66d; assign K[26]=32'hb00327c8; assign K[27]=32'hbf597fc7;
assign K[28]=32'hc6e00bf3; assign K[29]=32'hd5a79147; assign K[30]=32'h06ca6351; assign K[31]=32'h14292967;
assign K[32]=32'h27b70a85; assign K[33]=32'h2e1b2138; assign K[34]=32'h4d2c6dfc; assign K[35]=32'h53380d13;
assign K[36]=32'h650a7354; assign K[37]=32'h766a0abb; assign K[38]=32'h81c2c92e; assign K[39]=32'h92722c85;
assign K[40]=32'ha2bfe8a1; assign K[41]=32'ha81a664b; assign K[42]=32'hc24b8b70; assign K[43]=32'hc76c51a3;
assign K[44]=32'hd192e819; assign K[45]=32'hd6990624; assign K[46]=32'hf40e3585; assign K[47]=32'h106aa070;
assign K[48]=32'h19a4c116; assign K[49]=32'h1e376c08; assign K[50]=32'h2748774c; assign K[51]=32'h34b0bcb5;
assign K[52]=32'h391c0cb3; assign K[53]=32'h4ed8aa4a; assign K[54]=32'h5b9cca4f; assign K[55]=32'h682e6ff3;
assign K[56]=32'h748f82ee; assign K[57]=32'h78a5636f; assign K[58]=32'h84c87814; assign K[59]=32'h8cc70208;
assign K[60]=32'h90befffa; assign K[61]=32'ha4506ceb; assign K[62]=32'hbef9a3f7; assign K[63]=32'hc67178f2;

// ── SHA-256 IV (individual localparams — Icarus doesn't support array init) ──
localparam logic [31:0] IV0=32'h6a09e667, IV1=32'hbb67ae85,
                         IV2=32'h3c6ef372, IV3=32'ha54ff53a,
                         IV4=32'h510e527f, IV5=32'h9b05688c,
                         IV6=32'h1f83d9ab, IV7=32'h5be0cd19;

// ── Registers ─────────────────────────────────────────────────────────────
logic [31:0] msg_r [0:15];
logic [31:0] H     [0:7];    // running hash state; init to IV; updated each block
logic        ctrl_start_r, ctrl_reset_r;
logic        status_done_r, status_busy_r;

// ── Working variables and message schedule ────────────────────────────────
logic [31:0] a_r, b_r, c_r, d_r, e_r, f_r, g_r, h_r;
logic [31:0] W [0:15];
logic [5:0]  round_r;

// ── Combinational round logic (Icarus: no bit-selects in always_comb) ─────
logic [31:0] S0_a, S1_e, ch_v, maj_v, T1, T2, s0_w1, s1_w14, new_W;

assign S0_a   = {a_r[1:0],   a_r[31:2]}   ^ {a_r[12:0], a_r[31:13]}  ^ {a_r[21:0],  a_r[31:22]};
assign S1_e   = {e_r[5:0],   e_r[31:6]}   ^ {e_r[10:0], e_r[31:11]}  ^ {e_r[24:0],  e_r[31:25]};
assign ch_v   = (e_r & f_r) ^ (~e_r & g_r);
assign maj_v  = (a_r & b_r) ^ (a_r & c_r) ^ (b_r & c_r);
assign s0_w1  = {W[1][6:0],   W[1][31:7]}  ^ {W[1][17:0], W[1][31:18]}  ^ (W[1]  >> 3);
assign s1_w14 = {W[14][16:0], W[14][31:17]}^ {W[14][18:0],W[14][31:19]} ^ (W[14] >> 10);
assign new_W  = W[0] + s0_w1 + W[9] + s1_w14;
assign T1     = h_r + S1_e + ch_v + K[round_r] + W[0];
assign T2     = S0_a + maj_v;

// ── APB write ─────────────────────────────────────────────────────────────
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        ctrl_start_r <= 1'b0; ctrl_reset_r <= 1'b0;
        for (int i=0;i<16;i++) msg_r[i] <= '0;
    end else begin
        ctrl_start_r <= 1'b0; ctrl_reset_r <= 1'b0;   // auto-clear
        if (apb_wr) begin
            case (paddr)
                8'h00: begin ctrl_start_r <= pwdata[0]; ctrl_reset_r <= pwdata[1]; end
                8'h04: msg_r[ 0] <= pwdata; 8'h08: msg_r[ 1] <= pwdata;
                8'h0C: msg_r[ 2] <= pwdata; 8'h10: msg_r[ 3] <= pwdata;
                8'h14: msg_r[ 4] <= pwdata; 8'h18: msg_r[ 5] <= pwdata;
                8'h1C: msg_r[ 6] <= pwdata; 8'h20: msg_r[ 7] <= pwdata;
                8'h24: msg_r[ 8] <= pwdata; 8'h28: msg_r[ 9] <= pwdata;
                8'h2C: msg_r[10] <= pwdata; 8'h30: msg_r[11] <= pwdata;
                8'h34: msg_r[12] <= pwdata; 8'h38: msg_r[13] <= pwdata;
                8'h3C: msg_r[14] <= pwdata; 8'h40: msg_r[15] <= pwdata;
                default: ;
            endcase
        end
    end
end

// ── APB read ──────────────────────────────────────────────────────────────
always_comb begin
    prdata = '0;
    case (paddr)
        8'h00: prdata = {30'b0, ctrl_reset_r, ctrl_start_r};
        8'h04: prdata = msg_r[ 0]; 8'h08: prdata = msg_r[ 1];
        8'h0C: prdata = msg_r[ 2]; 8'h10: prdata = msg_r[ 3];
        8'h14: prdata = msg_r[ 4]; 8'h18: prdata = msg_r[ 5];
        8'h1C: prdata = msg_r[ 6]; 8'h20: prdata = msg_r[ 7];
        8'h24: prdata = msg_r[ 8]; 8'h28: prdata = msg_r[ 9];
        8'h2C: prdata = msg_r[10]; 8'h30: prdata = msg_r[11];
        8'h34: prdata = msg_r[12]; 8'h38: prdata = msg_r[13];
        8'h3C: prdata = msg_r[14]; 8'h40: prdata = msg_r[15];
        8'h44: prdata = H[0]; 8'h48: prdata = H[1];
        8'h4C: prdata = H[2]; 8'h50: prdata = H[3];
        8'h54: prdata = H[4]; 8'h58: prdata = H[5];
        8'h5C: prdata = H[6]; 8'h60: prdata = H[7];
        8'h64: prdata = {30'b0, status_busy_r, status_done_r};
        default: prdata = '0;
    endcase
end

// ── Compression FSM ───────────────────────────────────────────────────────
typedef enum logic [1:0] { S_IDLE, S_ROUND, S_FINAL } sha_state_t;
sha_state_t state;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        state <= S_IDLE;
        status_done_r <= 1'b0; status_busy_r <= 1'b0;
        round_r <= '0;
        a_r<='0; b_r<='0; c_r<='0; d_r<='0; e_r<='0; f_r<='0; g_r<='0; h_r<='0;
        H[0]<=IV0;H[1]<=IV1;H[2]<=IV2;H[3]<=IV3;
        H[4]<=IV4;H[5]<=IV5;H[6]<=IV6;H[7]<=IV7;
        for (int i=0;i<16;i++) W[i] <= '0;
    end else begin
        case (state)

        S_IDLE: begin
            if (ctrl_reset_r) begin
                H[0]<=IV0;H[1]<=IV1;H[2]<=IV2;H[3]<=IV3;
                H[4]<=IV4;H[5]<=IV5;H[6]<=IV6;H[7]<=IV7;
            end
            if (ctrl_start_r && !status_busy_r) begin
                status_busy_r <= 1'b1;
                status_done_r <= 1'b0;
                a_r<=H[0]; b_r<=H[1]; c_r<=H[2]; d_r<=H[3];
                e_r<=H[4]; f_r<=H[5]; g_r<=H[6]; h_r<=H[7];
                for (int i=0;i<16;i++) W[i] <= msg_r[i];
                round_r <= 6'd0;
                state   <= S_ROUND;
            end
        end

        S_ROUND: begin
            h_r <= g_r; g_r <= f_r; f_r <= e_r;
            e_r <= d_r + T1;
            d_r <= c_r; c_r <= b_r; b_r <= a_r;
            a_r <= T1 + T2;
            for (int i=0;i<15;i++) W[i] <= W[i+1];
            W[15]   <= new_W;
            round_r <= round_r + 6'd1;
            if (round_r == 6'd63) state <= S_FINAL;
        end

        S_FINAL: begin
            H[0] <= H[0] + a_r; H[1] <= H[1] + b_r;
            H[2] <= H[2] + c_r; H[3] <= H[3] + d_r;
            H[4] <= H[4] + e_r; H[5] <= H[5] + f_r;
            H[6] <= H[6] + g_r; H[7] <= H[7] + h_r;
            status_done_r <= 1'b1;
            status_busy_r <= 1'b0;
            state <= S_IDLE;
        end

        default: state <= S_IDLE;
        endcase
    end
end

endmodule
