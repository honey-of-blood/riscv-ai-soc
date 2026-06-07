`timescale 1ns/1ps
// SHA3-256 (Keccak-f[1600]) hardware accelerator — APB slave.
//
// SHA3-256: rate=1088 bits (17 × 64-bit lanes), capacity=512 bits, 24 rounds.
//
// APB register map (byte offset, 10-bit paddr):
//   0x000       CTRL    [0]=start  [1]=reset_state
//   0x004–0x088 BLOCK lanes 0..16: LO word at 0x004+lane*8, HI word at 0x008+lane*8
//   0x08C       STATUS  [0]=done  [1]=busy
//   0x090–0x0AC HASH lanes 0..3:  LO at 0x090+lane*8, HI at 0x094+lane*8
//
// Latency: 26 cycles per block (1 absorb + 24 rounds + 1 squeeze + overhead).
//
// Icarus compatibility: all combinational round logic expanded as assign statements.
// No variable declarations inside always_ff or always_comb.

module sha3_top (
    input  logic        clk,
    input  logic        rst_n,

    input  logic [9:0]  paddr,
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

// ── Keccak round constants (24 rounds) ────────────────────────────────────
logic [63:0] RC [0:23];
assign RC[ 0]=64'h0000000000000001; assign RC[ 1]=64'h0000000000008082;
assign RC[ 2]=64'h800000000000808A; assign RC[ 3]=64'h8000000080008000;
assign RC[ 4]=64'h000000000000808B; assign RC[ 5]=64'h0000000080000001;
assign RC[ 6]=64'h8000000080008081; assign RC[ 7]=64'h8000000000008009;
assign RC[ 8]=64'h000000000000008A; assign RC[ 9]=64'h0000000000000088;
assign RC[10]=64'h0000000080008009; assign RC[11]=64'h000000008000000A;
assign RC[12]=64'h000000008000808B; assign RC[13]=64'h800000000000008B;
assign RC[14]=64'h8000000000008089; assign RC[15]=64'h8000000000008003;
assign RC[16]=64'h8000000000008002; assign RC[17]=64'h8000000000000080;
assign RC[18]=64'h000000000000800A; assign RC[19]=64'h800000008000000A;
assign RC[20]=64'h8000000080008081; assign RC[21]=64'h8000000000008080;
assign RC[22]=64'h0000000080000001; assign RC[23]=64'h8000000080008008;

// ── Registers ─────────────────────────────────────────────────────────────
logic [63:0] state  [0:24];   // Keccak 5×5 state (flat index x+5y)
// Block input stored as split 32-bit words (avoids partial bit-select in always_ff)
logic [31:0] block_lo [0:16]; // lower 32 bits of each rate lane
logic [31:0] block_hi [0:16]; // upper 32 bits of each rate lane
logic [63:0] block_r  [0:16]; // 64-bit reassembly (assign)
logic [63:0] hash_r   [0:3];  // 256-bit output
logic        ctrl_start_r, ctrl_reset_r;
logic        status_done_r, status_busy_r;
logic [4:0]  round_r;

// Reassemble 64-bit block lanes from split halves
assign block_r[ 0]={block_hi[ 0],block_lo[ 0]}; assign block_r[ 1]={block_hi[ 1],block_lo[ 1]};
assign block_r[ 2]={block_hi[ 2],block_lo[ 2]}; assign block_r[ 3]={block_hi[ 3],block_lo[ 3]};
assign block_r[ 4]={block_hi[ 4],block_lo[ 4]}; assign block_r[ 5]={block_hi[ 5],block_lo[ 5]};
assign block_r[ 6]={block_hi[ 6],block_lo[ 6]}; assign block_r[ 7]={block_hi[ 7],block_lo[ 7]};
assign block_r[ 8]={block_hi[ 8],block_lo[ 8]}; assign block_r[ 9]={block_hi[ 9],block_lo[ 9]};
assign block_r[10]={block_hi[10],block_lo[10]}; assign block_r[11]={block_hi[11],block_lo[11]};
assign block_r[12]={block_hi[12],block_lo[12]}; assign block_r[13]={block_hi[13],block_lo[13]};
assign block_r[14]={block_hi[14],block_lo[14]}; assign block_r[15]={block_hi[15],block_lo[15]};
assign block_r[16]={block_hi[16],block_lo[16]};

// ── APB address decode for block write ────────────────────────────────────
logic [9:0]  blk_off;
logic [4:0]  blk_lane;
logic        blk_lo_sel;
assign blk_off    = paddr - 10'd4;   // offset from start of block region
assign blk_lane   = blk_off[7:3];    // (paddr-4) >> 3 = lane index 0..16
assign blk_lo_sel = paddr[2];        // 1 = LO half (paddr ≡ 4 mod 8), 0 = HI half

// ── Hash output byte-split (bit-selects in assign only) ───────────────────
logic [31:0] hash_lo [0:3];
logic [31:0] hash_hi [0:3];
assign hash_lo[0]=hash_r[0][31: 0]; assign hash_hi[0]=hash_r[0][63:32];
assign hash_lo[1]=hash_r[1][31: 0]; assign hash_hi[1]=hash_r[1][63:32];
assign hash_lo[2]=hash_r[2][31: 0]; assign hash_hi[2]=hash_r[2][63:32];
assign hash_lo[3]=hash_r[3][31: 0]; assign hash_hi[3]=hash_r[3][63:32];

// ── APB write ─────────────────────────────────────────────────────────────
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        ctrl_start_r<=0; ctrl_reset_r<=0;
        for (int i=0;i<17;i++) begin block_lo[i]<=0; block_hi[i]<=0; end
    end else begin
        ctrl_start_r<=0; ctrl_reset_r<=0;
        if (apb_wr) begin
            if (paddr == 10'h000)
                {ctrl_reset_r, ctrl_start_r} <= pwdata[1:0];
            else if (paddr >= 10'h004 && paddr <= 10'h088) begin
                if (blk_lo_sel) block_lo[blk_lane] <= pwdata;
                else            block_hi[blk_lane] <= pwdata;
            end
        end
    end
end

// ── APB read ──────────────────────────────────────────────────────────────
always_comb begin
    prdata = '0;
    case (paddr)
        10'h000: prdata = {30'b0, ctrl_reset_r, ctrl_start_r};
        10'h08C: prdata = {30'b0, status_busy_r, status_done_r};
        10'h090: prdata = hash_lo[0]; 10'h094: prdata = hash_hi[0];
        10'h098: prdata = hash_lo[1]; 10'h09C: prdata = hash_hi[1];
        10'h0A0: prdata = hash_lo[2]; 10'h0A4: prdata = hash_hi[2];
        10'h0A8: prdata = hash_lo[3]; 10'h0AC: prdata = hash_hi[3];
        default: prdata = '0;
    endcase
end

// ── Keccak-f[1600] round — full permutation as combinational assigns ───────
//
// All intermediate arrays are module-level logic wires (assign statements).
// This avoids both automatic variable declarations and bit-selects in always_*.
//
// Stage 1 θ: column parities C[0..4]
logic [63:0] kc_C [0:4];
assign kc_C[0]=state[ 0]^state[ 5]^state[10]^state[15]^state[20];
assign kc_C[1]=state[ 1]^state[ 6]^state[11]^state[16]^state[21];
assign kc_C[2]=state[ 2]^state[ 7]^state[12]^state[17]^state[22];
assign kc_C[3]=state[ 3]^state[ 8]^state[13]^state[18]^state[23];
assign kc_C[4]=state[ 4]^state[ 9]^state[14]^state[19]^state[24];

// Stage 2 θ: diffusion D[x] = C[(x+4)%5] ^ ROL64(C[(x+1)%5], 1)
// ROL64(v,1) = {v[62:0], v[63]}
logic [63:0] kc_D [0:4];
assign kc_D[0]=kc_C[4]^{kc_C[1][62:0],kc_C[1][63]};
assign kc_D[1]=kc_C[0]^{kc_C[2][62:0],kc_C[2][63]};
assign kc_D[2]=kc_C[1]^{kc_C[3][62:0],kc_C[3][63]};
assign kc_D[3]=kc_C[2]^{kc_C[4][62:0],kc_C[4][63]};
assign kc_D[4]=kc_C[3]^{kc_C[0][62:0],kc_C[0][63]};

// Stage 3 θ: A[i] = state[i] ^ D[i%5]
logic [63:0] kc_tA [0:24];
assign kc_tA[ 0]=state[ 0]^kc_D[0]; assign kc_tA[ 1]=state[ 1]^kc_D[1];
assign kc_tA[ 2]=state[ 2]^kc_D[2]; assign kc_tA[ 3]=state[ 3]^kc_D[3];
assign kc_tA[ 4]=state[ 4]^kc_D[4]; assign kc_tA[ 5]=state[ 5]^kc_D[0];
assign kc_tA[ 6]=state[ 6]^kc_D[1]; assign kc_tA[ 7]=state[ 7]^kc_D[2];
assign kc_tA[ 8]=state[ 8]^kc_D[3]; assign kc_tA[ 9]=state[ 9]^kc_D[4];
assign kc_tA[10]=state[10]^kc_D[0]; assign kc_tA[11]=state[11]^kc_D[1];
assign kc_tA[12]=state[12]^kc_D[2]; assign kc_tA[13]=state[13]^kc_D[3];
assign kc_tA[14]=state[14]^kc_D[4]; assign kc_tA[15]=state[15]^kc_D[0];
assign kc_tA[16]=state[16]^kc_D[1]; assign kc_tA[17]=state[17]^kc_D[2];
assign kc_tA[18]=state[18]^kc_D[3]; assign kc_tA[19]=state[19]^kc_D[4];
assign kc_tA[20]=state[20]^kc_D[0]; assign kc_tA[21]=state[21]^kc_D[1];
assign kc_tA[22]=state[22]^kc_D[2]; assign kc_tA[23]=state[23]^kc_D[3];
assign kc_tA[24]=state[24]^kc_D[4];

// Stage 4 ρ+π: B[pi(i)] = ROL64(A[i], rho[i])
// Mapping B[dst] = ROL(kc_tA[src], rho_off); all rotations are compile-time constants.
// ROL64(v, r) = {v[63-r:0], v[63:64-r]}
logic [63:0] kc_B [0:24];
assign kc_B[ 0]=                                     kc_tA[ 0];  // src=0,  rho=0
assign kc_B[ 1]={kc_tA[ 6][19:0],kc_tA[ 6][63:20]}; // src=6,  rho=44
assign kc_B[ 2]={kc_tA[12][20:0],kc_tA[12][63:21]}; // src=12, rho=43
assign kc_B[ 3]={kc_tA[18][42:0],kc_tA[18][63:43]}; // src=18, rho=21
assign kc_B[ 4]={kc_tA[24][49:0],kc_tA[24][63:50]}; // src=24, rho=14
assign kc_B[ 5]={kc_tA[ 3][35:0],kc_tA[ 3][63:36]}; // src=3,  rho=28
assign kc_B[ 6]={kc_tA[ 9][43:0],kc_tA[ 9][63:44]}; // src=9,  rho=20
assign kc_B[ 7]={kc_tA[10][60:0],kc_tA[10][63:61]}; // src=10, rho=3
assign kc_B[ 8]={kc_tA[16][18:0],kc_tA[16][63:19]}; // src=16, rho=45
assign kc_B[ 9]={kc_tA[22][ 2:0],kc_tA[22][63: 3]}; // src=22, rho=61
assign kc_B[10]={kc_tA[ 1][62:0],kc_tA[ 1][63]   }; // src=1,  rho=1
assign kc_B[11]={kc_tA[ 7][57:0],kc_tA[ 7][63:58]}; // src=7,  rho=6
assign kc_B[12]={kc_tA[13][38:0],kc_tA[13][63:39]}; // src=13, rho=25
assign kc_B[13]={kc_tA[19][55:0],kc_tA[19][63:56]}; // src=19, rho=8
assign kc_B[14]={kc_tA[20][45:0],kc_tA[20][63:46]}; // src=20, rho=18
assign kc_B[15]={kc_tA[ 4][36:0],kc_tA[ 4][63:37]}; // src=4,  rho=27
assign kc_B[16]={kc_tA[ 5][27:0],kc_tA[ 5][63:28]}; // src=5,  rho=36
assign kc_B[17]={kc_tA[11][53:0],kc_tA[11][63:54]}; // src=11, rho=10
assign kc_B[18]={kc_tA[17][48:0],kc_tA[17][63:49]}; // src=17, rho=15
assign kc_B[19]={kc_tA[23][ 7:0],kc_tA[23][63: 8]}; // src=23, rho=56
assign kc_B[20]={kc_tA[ 2][ 1:0],kc_tA[ 2][63: 2]}; // src=2,  rho=62
assign kc_B[21]={kc_tA[ 8][ 8:0],kc_tA[ 8][63: 9]}; // src=8,  rho=55
assign kc_B[22]={kc_tA[14][24:0],kc_tA[14][63:25]}; // src=14, rho=39
assign kc_B[23]={kc_tA[15][22:0],kc_tA[15][63:23]}; // src=15, rho=41
assign kc_B[24]={kc_tA[21][61:0],kc_tA[21][63:62]}; // src=21, rho=2

// Stage 5 χ: A[x+5y] = B[x+5y] ^ (~B[(x+1)%5+5y] & B[(x+2)%5+5y])
logic [63:0] kc_chiA [0:24];
// row y=0
assign kc_chiA[ 0]=kc_B[ 0]^(~kc_B[ 1]&kc_B[ 2]);
assign kc_chiA[ 1]=kc_B[ 1]^(~kc_B[ 2]&kc_B[ 3]);
assign kc_chiA[ 2]=kc_B[ 2]^(~kc_B[ 3]&kc_B[ 4]);
assign kc_chiA[ 3]=kc_B[ 3]^(~kc_B[ 4]&kc_B[ 0]);
assign kc_chiA[ 4]=kc_B[ 4]^(~kc_B[ 0]&kc_B[ 1]);
// row y=1
assign kc_chiA[ 5]=kc_B[ 5]^(~kc_B[ 6]&kc_B[ 7]);
assign kc_chiA[ 6]=kc_B[ 6]^(~kc_B[ 7]&kc_B[ 8]);
assign kc_chiA[ 7]=kc_B[ 7]^(~kc_B[ 8]&kc_B[ 9]);
assign kc_chiA[ 8]=kc_B[ 8]^(~kc_B[ 9]&kc_B[ 5]);
assign kc_chiA[ 9]=kc_B[ 9]^(~kc_B[ 5]&kc_B[ 6]);
// row y=2
assign kc_chiA[10]=kc_B[10]^(~kc_B[11]&kc_B[12]);
assign kc_chiA[11]=kc_B[11]^(~kc_B[12]&kc_B[13]);
assign kc_chiA[12]=kc_B[12]^(~kc_B[13]&kc_B[14]);
assign kc_chiA[13]=kc_B[13]^(~kc_B[14]&kc_B[10]);
assign kc_chiA[14]=kc_B[14]^(~kc_B[10]&kc_B[11]);
// row y=3
assign kc_chiA[15]=kc_B[15]^(~kc_B[16]&kc_B[17]);
assign kc_chiA[16]=kc_B[16]^(~kc_B[17]&kc_B[18]);
assign kc_chiA[17]=kc_B[17]^(~kc_B[18]&kc_B[19]);
assign kc_chiA[18]=kc_B[18]^(~kc_B[19]&kc_B[15]);
assign kc_chiA[19]=kc_B[19]^(~kc_B[15]&kc_B[16]);
// row y=4
assign kc_chiA[20]=kc_B[20]^(~kc_B[21]&kc_B[22]);
assign kc_chiA[21]=kc_B[21]^(~kc_B[22]&kc_B[23]);
assign kc_chiA[22]=kc_B[22]^(~kc_B[23]&kc_B[24]);
assign kc_chiA[23]=kc_B[23]^(~kc_B[24]&kc_B[20]);
assign kc_chiA[24]=kc_B[24]^(~kc_B[20]&kc_B[21]);

// Stage 6 ι: XOR round constant into lane 0
logic [63:0] kc_A [0:24];
assign kc_A[ 0]=kc_chiA[ 0]^RC[round_r];
assign kc_A[ 1]=kc_chiA[ 1]; assign kc_A[ 2]=kc_chiA[ 2]; assign kc_A[ 3]=kc_chiA[ 3];
assign kc_A[ 4]=kc_chiA[ 4]; assign kc_A[ 5]=kc_chiA[ 5]; assign kc_A[ 6]=kc_chiA[ 6];
assign kc_A[ 7]=kc_chiA[ 7]; assign kc_A[ 8]=kc_chiA[ 8]; assign kc_A[ 9]=kc_chiA[ 9];
assign kc_A[10]=kc_chiA[10]; assign kc_A[11]=kc_chiA[11]; assign kc_A[12]=kc_chiA[12];
assign kc_A[13]=kc_chiA[13]; assign kc_A[14]=kc_chiA[14]; assign kc_A[15]=kc_chiA[15];
assign kc_A[16]=kc_chiA[16]; assign kc_A[17]=kc_chiA[17]; assign kc_A[18]=kc_chiA[18];
assign kc_A[19]=kc_chiA[19]; assign kc_A[20]=kc_chiA[20]; assign kc_A[21]=kc_chiA[21];
assign kc_A[22]=kc_chiA[22]; assign kc_A[23]=kc_chiA[23]; assign kc_A[24]=kc_chiA[24];

// ── Keccak FSM ────────────────────────────────────────────────────────────
typedef enum logic [1:0] { SK_IDLE, SK_ABSORB, SK_ROUND, SK_SQUEEZE } kfsm_t;
kfsm_t kfsm;

always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        kfsm<=SK_IDLE; status_done_r<=0; status_busy_r<=0; round_r<=0;
        for (int i=0;i<25;i++) state[i]<=0;
        for (int i=0;i<4; i++) hash_r[i]<=0;
    end else begin
        case (kfsm)

        SK_IDLE: begin
            status_done_r <= 0;
            if (ctrl_reset_r) for (int i=0;i<25;i++) state[i]<=0;
            if (ctrl_start_r && !status_busy_r) begin
                status_busy_r<=1; kfsm<=SK_ABSORB;
            end
        end

        SK_ABSORB: begin
            for (int i=0;i<17;i++) state[i] <= state[i] ^ block_r[i];
            round_r <= 5'd0;
            kfsm    <= SK_ROUND;
        end

        // kc_A[0..24] computed combinationally from state and RC[round_r].
        SK_ROUND: begin
            for (int i=0;i<25;i++) state[i] <= kc_A[i];
            round_r <= round_r + 5'd1;
            if (round_r == 5'd23) kfsm <= SK_SQUEEZE;
        end

        SK_SQUEEZE: begin
            hash_r[0]<=state[0]; hash_r[1]<=state[1];
            hash_r[2]<=state[2]; hash_r[3]<=state[3];
            status_done_r<=1; status_busy_r<=0;
            kfsm<=SK_IDLE;
        end

        default: kfsm<=SK_IDLE;
        endcase
    end
end

endmodule
