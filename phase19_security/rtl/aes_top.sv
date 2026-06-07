`timescale 1ns/1ps
// AES-128 hardware accelerator — APB slave, ECB/CBC/CTR modes.
//
// APB register map (byte offset):
//   0x00  CTRL    [0]=start [1]=decrypt [3:2]=mode(00=ECB,01=CBC,10=CTR)
//   0x04–0x10  KEY0–KEY3   128-bit key (4×32-bit)
//   0x14–0x20  IV0–IV3     128-bit IV  (updated in-place after CBC/CTR block)
//   0x24–0x30  DIN0–DIN3   128-bit input
//   0x34–0x40  DOUT0–DOUT3 128-bit output
//   0x44        STATUS  [0]=done [1]=busy
//
// State is stored column-major: st[col][row], col=0..3, row=0..3.
// Words are big-endian: word[31:24] = byte[row=0].

module aes_top (
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

// ── S-box forward ─────────────────────────────────────────────────────────
function automatic logic [7:0] sbox_fwd(input logic [7:0] x);
    logic [7:0] t [0:255];
    t[  0]=8'h63;t[  1]=8'h7c;t[  2]=8'h77;t[  3]=8'h7b;t[  4]=8'hf2;t[  5]=8'h6b;t[  6]=8'h6f;t[  7]=8'hc5;
    t[  8]=8'h30;t[  9]=8'h01;t[ 10]=8'h67;t[ 11]=8'h2b;t[ 12]=8'hfe;t[ 13]=8'hd7;t[ 14]=8'hab;t[ 15]=8'h76;
    t[ 16]=8'hca;t[ 17]=8'h82;t[ 18]=8'hc9;t[ 19]=8'h7d;t[ 20]=8'hfa;t[ 21]=8'h59;t[ 22]=8'h47;t[ 23]=8'hf0;
    t[ 24]=8'had;t[ 25]=8'hd4;t[ 26]=8'ha2;t[ 27]=8'haf;t[ 28]=8'h9c;t[ 29]=8'ha4;t[ 30]=8'h72;t[ 31]=8'hc0;
    t[ 32]=8'hb7;t[ 33]=8'hfd;t[ 34]=8'h93;t[ 35]=8'h26;t[ 36]=8'h36;t[ 37]=8'h3f;t[ 38]=8'hf7;t[ 39]=8'hcc;
    t[ 40]=8'h34;t[ 41]=8'ha5;t[ 42]=8'he5;t[ 43]=8'hf1;t[ 44]=8'h71;t[ 45]=8'hd8;t[ 46]=8'h31;t[ 47]=8'h15;
    t[ 48]=8'h04;t[ 49]=8'hc7;t[ 50]=8'h23;t[ 51]=8'hc3;t[ 52]=8'h18;t[ 53]=8'h96;t[ 54]=8'h05;t[ 55]=8'h9a;
    t[ 56]=8'h07;t[ 57]=8'h12;t[ 58]=8'h80;t[ 59]=8'he2;t[ 60]=8'heb;t[ 61]=8'h27;t[ 62]=8'hb2;t[ 63]=8'h75;
    t[ 64]=8'h09;t[ 65]=8'h83;t[ 66]=8'h2c;t[ 67]=8'h1a;t[ 68]=8'h1b;t[ 69]=8'h6e;t[ 70]=8'h5a;t[ 71]=8'ha0;
    t[ 72]=8'h52;t[ 73]=8'h3b;t[ 74]=8'hd6;t[ 75]=8'hb3;t[ 76]=8'h29;t[ 77]=8'he3;t[ 78]=8'h2f;t[ 79]=8'h84;
    t[ 80]=8'h53;t[ 81]=8'hd1;t[ 82]=8'h00;t[ 83]=8'hed;t[ 84]=8'h20;t[ 85]=8'hfc;t[ 86]=8'hb1;t[ 87]=8'h5b;
    t[ 88]=8'h6a;t[ 89]=8'hcb;t[ 90]=8'hbe;t[ 91]=8'h39;t[ 92]=8'h4a;t[ 93]=8'h4c;t[ 94]=8'h58;t[ 95]=8'hcf;
    t[ 96]=8'hd0;t[ 97]=8'hef;t[ 98]=8'haa;t[ 99]=8'hfb;t[100]=8'h43;t[101]=8'h4d;t[102]=8'h33;t[103]=8'h85;
    t[104]=8'h45;t[105]=8'hf9;t[106]=8'h02;t[107]=8'h7f;t[108]=8'h50;t[109]=8'h3c;t[110]=8'h9f;t[111]=8'ha8;
    t[112]=8'h51;t[113]=8'ha3;t[114]=8'h40;t[115]=8'h8f;t[116]=8'h92;t[117]=8'h9d;t[118]=8'h38;t[119]=8'hf5;
    t[120]=8'hbc;t[121]=8'hb6;t[122]=8'hda;t[123]=8'h21;t[124]=8'h10;t[125]=8'hff;t[126]=8'hf3;t[127]=8'hd2;
    t[128]=8'hcd;t[129]=8'h0c;t[130]=8'h13;t[131]=8'hec;t[132]=8'h5f;t[133]=8'h97;t[134]=8'h44;t[135]=8'h17;
    t[136]=8'hc4;t[137]=8'ha7;t[138]=8'h7e;t[139]=8'h3d;t[140]=8'h64;t[141]=8'h5d;t[142]=8'h19;t[143]=8'h73;
    t[144]=8'h60;t[145]=8'h81;t[146]=8'h4f;t[147]=8'hdc;t[148]=8'h22;t[149]=8'h2a;t[150]=8'h90;t[151]=8'h88;
    t[152]=8'h46;t[153]=8'hee;t[154]=8'hb8;t[155]=8'h14;t[156]=8'hde;t[157]=8'h5e;t[158]=8'h0b;t[159]=8'hdb;
    t[160]=8'he0;t[161]=8'h32;t[162]=8'h3a;t[163]=8'h0a;t[164]=8'h49;t[165]=8'h06;t[166]=8'h24;t[167]=8'h5c;
    t[168]=8'hc2;t[169]=8'hd3;t[170]=8'hac;t[171]=8'h62;t[172]=8'h91;t[173]=8'h95;t[174]=8'he4;t[175]=8'h79;
    t[176]=8'he7;t[177]=8'hc8;t[178]=8'h37;t[179]=8'h6d;t[180]=8'h8d;t[181]=8'hd5;t[182]=8'h4e;t[183]=8'ha9;
    t[184]=8'h6c;t[185]=8'h56;t[186]=8'hf4;t[187]=8'hea;t[188]=8'h65;t[189]=8'h7a;t[190]=8'hae;t[191]=8'h08;
    t[192]=8'hba;t[193]=8'h78;t[194]=8'h25;t[195]=8'h2e;t[196]=8'h1c;t[197]=8'ha6;t[198]=8'hb4;t[199]=8'hc6;
    t[200]=8'he8;t[201]=8'hdd;t[202]=8'h74;t[203]=8'h1f;t[204]=8'h4b;t[205]=8'hbd;t[206]=8'h8b;t[207]=8'h8a;
    t[208]=8'h70;t[209]=8'h3e;t[210]=8'hb5;t[211]=8'h66;t[212]=8'h48;t[213]=8'h03;t[214]=8'hf6;t[215]=8'h0e;
    t[216]=8'h61;t[217]=8'h35;t[218]=8'h57;t[219]=8'hb9;t[220]=8'h86;t[221]=8'hc1;t[222]=8'h1d;t[223]=8'h9e;
    t[224]=8'he1;t[225]=8'hf8;t[226]=8'h98;t[227]=8'h11;t[228]=8'h69;t[229]=8'hd9;t[230]=8'h8e;t[231]=8'h94;
    t[232]=8'h9b;t[233]=8'h1e;t[234]=8'h87;t[235]=8'he9;t[236]=8'hce;t[237]=8'h55;t[238]=8'h28;t[239]=8'hdf;
    t[240]=8'h8c;t[241]=8'ha1;t[242]=8'h89;t[243]=8'h0d;t[244]=8'hbf;t[245]=8'he6;t[246]=8'h42;t[247]=8'h68;
    t[248]=8'h41;t[249]=8'h99;t[250]=8'h2d;t[251]=8'h0f;t[252]=8'hb0;t[253]=8'h54;t[254]=8'hbb;t[255]=8'h16;
    return t[x];
endfunction

// ── S-box inverse ─────────────────────────────────────────────────────────
function automatic logic [7:0] sbox_inv(input logic [7:0] x);
    logic [7:0] t [0:255];
    t[  0]=8'h52;t[  1]=8'h09;t[  2]=8'h6a;t[  3]=8'hd5;t[  4]=8'h30;t[  5]=8'h36;t[  6]=8'ha5;t[  7]=8'h38;
    t[  8]=8'hbf;t[  9]=8'h40;t[ 10]=8'ha3;t[ 11]=8'h9e;t[ 12]=8'h81;t[ 13]=8'hf3;t[ 14]=8'hd7;t[ 15]=8'hfb;
    t[ 16]=8'h7c;t[ 17]=8'he3;t[ 18]=8'h39;t[ 19]=8'h82;t[ 20]=8'h9b;t[ 21]=8'h2f;t[ 22]=8'hff;t[ 23]=8'h87;
    t[ 24]=8'h34;t[ 25]=8'h8e;t[ 26]=8'h43;t[ 27]=8'h44;t[ 28]=8'hc4;t[ 29]=8'hde;t[ 30]=8'he9;t[ 31]=8'hcb;
    t[ 32]=8'h54;t[ 33]=8'h7b;t[ 34]=8'h94;t[ 35]=8'h32;t[ 36]=8'ha6;t[ 37]=8'hc2;t[ 38]=8'h23;t[ 39]=8'h3d;
    t[ 40]=8'hee;t[ 41]=8'h4c;t[ 42]=8'h95;t[ 43]=8'h0b;t[ 44]=8'h42;t[ 45]=8'hfa;t[ 46]=8'hc3;t[ 47]=8'h4e;
    t[ 48]=8'h08;t[ 49]=8'h2e;t[ 50]=8'ha1;t[ 51]=8'h66;t[ 52]=8'h28;t[ 53]=8'hd9;t[ 54]=8'h24;t[ 55]=8'hb2;
    t[ 56]=8'h76;t[ 57]=8'h5b;t[ 58]=8'ha2;t[ 59]=8'h49;t[ 60]=8'h6d;t[ 61]=8'h8b;t[ 62]=8'hd1;t[ 63]=8'h25;
    t[ 64]=8'h72;t[ 65]=8'hf8;t[ 66]=8'hf6;t[ 67]=8'h64;t[ 68]=8'h86;t[ 69]=8'h68;t[ 70]=8'h98;t[ 71]=8'h16;
    t[ 72]=8'hd4;t[ 73]=8'ha4;t[ 74]=8'h5c;t[ 75]=8'hcc;t[ 76]=8'h5d;t[ 77]=8'h65;t[ 78]=8'hb6;t[ 79]=8'h92;
    t[ 80]=8'h6c;t[ 81]=8'h70;t[ 82]=8'h48;t[ 83]=8'h50;t[ 84]=8'hfd;t[ 85]=8'hed;t[ 86]=8'hb9;t[ 87]=8'hda;
    t[ 88]=8'h5e;t[ 89]=8'h15;t[ 90]=8'h46;t[ 91]=8'h57;t[ 92]=8'ha7;t[ 93]=8'h8d;t[ 94]=8'h9d;t[ 95]=8'h84;
    t[ 96]=8'h90;t[ 97]=8'hd8;t[ 98]=8'hab;t[ 99]=8'h00;t[100]=8'h8c;t[101]=8'hbc;t[102]=8'hd3;t[103]=8'h0a;
    t[104]=8'hf7;t[105]=8'he4;t[106]=8'h58;t[107]=8'h05;t[108]=8'hb8;t[109]=8'hb3;t[110]=8'h45;t[111]=8'h06;
    t[112]=8'hd0;t[113]=8'h2c;t[114]=8'h1e;t[115]=8'h8f;t[116]=8'hca;t[117]=8'h3f;t[118]=8'h0f;t[119]=8'h02;
    t[120]=8'hc1;t[121]=8'haf;t[122]=8'hbd;t[123]=8'h03;t[124]=8'h01;t[125]=8'h13;t[126]=8'h8a;t[127]=8'h6b;
    t[128]=8'h3a;t[129]=8'h91;t[130]=8'h11;t[131]=8'h41;t[132]=8'h4f;t[133]=8'h67;t[134]=8'hdc;t[135]=8'hea;
    t[136]=8'h97;t[137]=8'hf2;t[138]=8'hcf;t[139]=8'hce;t[140]=8'hf0;t[141]=8'hb4;t[142]=8'he6;t[143]=8'h73;
    t[144]=8'h96;t[145]=8'hac;t[146]=8'h74;t[147]=8'h22;t[148]=8'he7;t[149]=8'had;t[150]=8'h35;t[151]=8'h85;
    t[152]=8'he2;t[153]=8'hf9;t[154]=8'h37;t[155]=8'he8;t[156]=8'h1c;t[157]=8'h75;t[158]=8'hdf;t[159]=8'h6e;
    t[160]=8'h47;t[161]=8'hf1;t[162]=8'h1a;t[163]=8'h71;t[164]=8'h1d;t[165]=8'h29;t[166]=8'hc5;t[167]=8'h89;
    t[168]=8'h6f;t[169]=8'hb7;t[170]=8'h62;t[171]=8'h0e;t[172]=8'haa;t[173]=8'h18;t[174]=8'hbe;t[175]=8'h1b;
    t[176]=8'hfc;t[177]=8'h56;t[178]=8'h3e;t[179]=8'h4b;t[180]=8'hc6;t[181]=8'hd2;t[182]=8'h79;t[183]=8'h20;
    t[184]=8'h9a;t[185]=8'hdb;t[186]=8'hc0;t[187]=8'hfe;t[188]=8'h78;t[189]=8'hcd;t[190]=8'h5a;t[191]=8'hf4;
    t[192]=8'h1f;t[193]=8'hdd;t[194]=8'ha8;t[195]=8'h33;t[196]=8'h88;t[197]=8'h07;t[198]=8'hc7;t[199]=8'h31;
    t[200]=8'hb1;t[201]=8'h12;t[202]=8'h10;t[203]=8'h59;t[204]=8'h27;t[205]=8'h80;t[206]=8'hec;t[207]=8'h5f;
    t[208]=8'h60;t[209]=8'h51;t[210]=8'h7f;t[211]=8'ha9;t[212]=8'h19;t[213]=8'hb5;t[214]=8'h4a;t[215]=8'h0d;
    t[216]=8'h2d;t[217]=8'he5;t[218]=8'h7a;t[219]=8'h9f;t[220]=8'h93;t[221]=8'hc9;t[222]=8'h9c;t[223]=8'hef;
    t[224]=8'ha0;t[225]=8'he0;t[226]=8'h3b;t[227]=8'h4d;t[228]=8'hae;t[229]=8'h2a;t[230]=8'hf5;t[231]=8'hb0;
    t[232]=8'hc8;t[233]=8'heb;t[234]=8'hbb;t[235]=8'h3c;t[236]=8'h83;t[237]=8'h53;t[238]=8'h99;t[239]=8'h61;
    t[240]=8'h17;t[241]=8'h2b;t[242]=8'h04;t[243]=8'h7e;t[244]=8'hba;t[245]=8'h77;t[246]=8'hd6;t[247]=8'h26;
    t[248]=8'he1;t[249]=8'h69;t[250]=8'h14;t[251]=8'h63;t[252]=8'h55;t[253]=8'h21;t[254]=8'h0c;t[255]=8'h7d;
    return t[x];
endfunction

// ── GF(2^8) multiply helpers ──────────────────────────────────────────────
function automatic logic [7:0] xtime(input logic [7:0] b);
    return {b[6:0],1'b0} ^ (b[7] ? 8'h1b : 8'h00);
endfunction
function automatic logic [7:0] gm2(input logic [7:0] b);
    return xtime(b);
endfunction
function automatic logic [7:0] gm4(input logic [7:0] b);
    return xtime(xtime(b));
endfunction
function automatic logic [7:0] gm8(input logic [7:0] b);
    return xtime(xtime(xtime(b)));
endfunction
function automatic logic [7:0] gm9 (input logic [7:0] b); return gm8(b)^b;              endfunction
function automatic logic [7:0] gm11(input logic [7:0] b); return gm8(b)^gm2(b)^b;       endfunction
function automatic logic [7:0] gm13(input logic [7:0] b); return gm8(b)^gm4(b)^b;       endfunction
function automatic logic [7:0] gm14(input logic [7:0] b); return gm8(b)^gm4(b)^gm2(b); endfunction

// ── Rcon bytes for AES-128 ────────────────────────────────────────────────
function automatic logic [7:0] rcon_byte(input logic [3:0] i);
    case (i)
        4'd0: return 8'h01; 4'd1: return 8'h02; 4'd2: return 8'h04; 4'd3: return 8'h08;
        4'd4: return 8'h10; 4'd5: return 8'h20; 4'd6: return 8'h40; 4'd7: return 8'h80;
        4'd8: return 8'h1b; 4'd9: return 8'h36;
        default: return 8'h00;
    endcase
endfunction

// ── APB registers ─────────────────────────────────────────────────────────
logic [31:0] key_r [0:3];
logic [31:0] iv_r  [0:3];
logic [31:0] din_r [0:3];
logic [31:0] dout_r[0:3];
logic        ctrl_start_r, ctrl_decrypt_r;
logic [1:0]  ctrl_mode_r;
logic        status_done_r, status_busy_r;

// ── Round key storage (AES-128: 44 words) ─────────────────────────────────
logic [31:0] rk [0:43];

// ── AES state: st[col][row], col-major, big-endian bytes ──────────────────
logic [7:0] st [0:3][0:3];

// ── FSM ───────────────────────────────────────────────────────────────────
typedef enum logic [2:0] {
    S_IDLE, S_KEYSCHED, S_ADDRK0, S_SUBBYTES, S_SHIFTROWS, S_MIXCOLS, S_ADDRK, S_OUTPUT
} aes_fsm_t;
aes_fsm_t aes_fsm;

logic [5:0] ks_i;
logic [3:0] rnd;

// ── Key-schedule combinational (all assign, no variable declarations) ──────
logic [31:0] ks_prev_word, ks_base_word, ks_sub_word, ks_new_word;
logic [7:0]  ks_rcon_byte;
logic [3:0]  ks_rnd_idx;

assign ks_prev_word = rk[ks_i - 1];
assign ks_base_word = rk[ks_i - 4];
assign ks_rnd_idx   = ks_i[5:2] - 4'd1;
assign ks_rcon_byte = rcon_byte(ks_rnd_idx);
// SubWord(RotWord(prev)): rotate bytes left by 1, apply S-box, XOR Rcon into MSB
assign ks_sub_word  = { sbox_fwd(ks_prev_word[23:16]) ^ ks_rcon_byte,
                         sbox_fwd(ks_prev_word[15: 8]),
                         sbox_fwd(ks_prev_word[ 7: 0]),
                         sbox_fwd(ks_prev_word[31:24]) };
assign ks_new_word  = (ks_i[1:0] == 2'b00) ? (ks_sub_word ^ ks_base_word)
                                             : (ks_prev_word ^ ks_base_word);

// ── AddRoundKey combinational ─────────────────────────────────────────────
logic [5:0]  rk_base;
logic [31:0] rk_w0, rk_w1, rk_w2, rk_w3;
assign rk_base = {rnd, 2'b00};
assign rk_w0   = rk[rk_base + 0];
assign rk_w1   = rk[rk_base + 1];
assign rk_w2   = rk[rk_base + 2];
assign rk_w3   = rk[rk_base + 3];

// Initial-round key (enc: rk[0..3], dec: rk[40..43])
logic [31:0] rk0_w0, rk0_w1, rk0_w2, rk0_w3;
assign rk0_w0 = ctrl_decrypt_r ? rk[40] : rk[0];
assign rk0_w1 = ctrl_decrypt_r ? rk[41] : rk[1];
assign rk0_w2 = ctrl_decrypt_r ? rk[42] : rk[2];
assign rk0_w3 = ctrl_decrypt_r ? rk[43] : rk[3];

// ── Pre-processed state input (handles CBC/CTR XOR before key schedule) ───
logic [31:0] din_blk [0:3];
assign din_blk[0] = (ctrl_mode_r==2'b01 && !ctrl_decrypt_r) ? (din_r[0]^iv_r[0]) :
                    (ctrl_mode_r==2'b10)                     ?  iv_r[0]            : din_r[0];
assign din_blk[1] = (ctrl_mode_r==2'b01 && !ctrl_decrypt_r) ? (din_r[1]^iv_r[1]) :
                    (ctrl_mode_r==2'b10)                     ?  iv_r[1]            : din_r[1];
assign din_blk[2] = (ctrl_mode_r==2'b01 && !ctrl_decrypt_r) ? (din_r[2]^iv_r[2]) :
                    (ctrl_mode_r==2'b10)                     ?  iv_r[2]            : din_r[2];
assign din_blk[3] = (ctrl_mode_r==2'b01 && !ctrl_decrypt_r) ? (din_r[3]^iv_r[3]) :
                    (ctrl_mode_r==2'b10)                     ?  iv_r[3]            : din_r[3];

// ── Output word reassembly ────────────────────────────────────────────────
logic [31:0] out_word [0:3];
assign out_word[0] = {st[0][0],st[0][1],st[0][2],st[0][3]};
assign out_word[1] = {st[1][0],st[1][1],st[1][2],st[1][3]};
assign out_word[2] = {st[2][0],st[2][1],st[2][2],st[2][3]};
assign out_word[3] = {st[3][0],st[3][1],st[3][2],st[3][3]};

// ── MixCols / InvMixCols — plain assign, no always block (Icarus-safe) ────
// Functions with bit-selects (gm2/xtime) must be in assign, not always_*.
logic [7:0] mc_s [0:3][0:3];

// col 0
assign mc_s[0][0] = ctrl_decrypt_r ? (gm14(st[0][0])^gm11(st[0][1])^gm13(st[0][2])^gm9 (st[0][3])) : (gm2(st[0][0])^(gm2(st[0][1])^st[0][1])^st[0][2]^st[0][3]);
assign mc_s[0][1] = ctrl_decrypt_r ? (gm9 (st[0][0])^gm14(st[0][1])^gm11(st[0][2])^gm13(st[0][3])) : (st[0][0]^gm2(st[0][1])^(gm2(st[0][2])^st[0][2])^st[0][3]);
assign mc_s[0][2] = ctrl_decrypt_r ? (gm13(st[0][0])^gm9 (st[0][1])^gm14(st[0][2])^gm11(st[0][3])) : (st[0][0]^st[0][1]^gm2(st[0][2])^(gm2(st[0][3])^st[0][3]));
assign mc_s[0][3] = ctrl_decrypt_r ? (gm11(st[0][0])^gm13(st[0][1])^gm9 (st[0][2])^gm14(st[0][3])) : ((gm2(st[0][0])^st[0][0])^st[0][1]^st[0][2]^gm2(st[0][3]));
// col 1
assign mc_s[1][0] = ctrl_decrypt_r ? (gm14(st[1][0])^gm11(st[1][1])^gm13(st[1][2])^gm9 (st[1][3])) : (gm2(st[1][0])^(gm2(st[1][1])^st[1][1])^st[1][2]^st[1][3]);
assign mc_s[1][1] = ctrl_decrypt_r ? (gm9 (st[1][0])^gm14(st[1][1])^gm11(st[1][2])^gm13(st[1][3])) : (st[1][0]^gm2(st[1][1])^(gm2(st[1][2])^st[1][2])^st[1][3]);
assign mc_s[1][2] = ctrl_decrypt_r ? (gm13(st[1][0])^gm9 (st[1][1])^gm14(st[1][2])^gm11(st[1][3])) : (st[1][0]^st[1][1]^gm2(st[1][2])^(gm2(st[1][3])^st[1][3]));
assign mc_s[1][3] = ctrl_decrypt_r ? (gm11(st[1][0])^gm13(st[1][1])^gm9 (st[1][2])^gm14(st[1][3])) : ((gm2(st[1][0])^st[1][0])^st[1][1]^st[1][2]^gm2(st[1][3]));
// col 2
assign mc_s[2][0] = ctrl_decrypt_r ? (gm14(st[2][0])^gm11(st[2][1])^gm13(st[2][2])^gm9 (st[2][3])) : (gm2(st[2][0])^(gm2(st[2][1])^st[2][1])^st[2][2]^st[2][3]);
assign mc_s[2][1] = ctrl_decrypt_r ? (gm9 (st[2][0])^gm14(st[2][1])^gm11(st[2][2])^gm13(st[2][3])) : (st[2][0]^gm2(st[2][1])^(gm2(st[2][2])^st[2][2])^st[2][3]);
assign mc_s[2][2] = ctrl_decrypt_r ? (gm13(st[2][0])^gm9 (st[2][1])^gm14(st[2][2])^gm11(st[2][3])) : (st[2][0]^st[2][1]^gm2(st[2][2])^(gm2(st[2][3])^st[2][3]));
assign mc_s[2][3] = ctrl_decrypt_r ? (gm11(st[2][0])^gm13(st[2][1])^gm9 (st[2][2])^gm14(st[2][3])) : ((gm2(st[2][0])^st[2][0])^st[2][1]^st[2][2]^gm2(st[2][3]));
// col 3
assign mc_s[3][0] = ctrl_decrypt_r ? (gm14(st[3][0])^gm11(st[3][1])^gm13(st[3][2])^gm9 (st[3][3])) : (gm2(st[3][0])^(gm2(st[3][1])^st[3][1])^st[3][2]^st[3][3]);
assign mc_s[3][1] = ctrl_decrypt_r ? (gm9 (st[3][0])^gm14(st[3][1])^gm11(st[3][2])^gm13(st[3][3])) : (st[3][0]^gm2(st[3][1])^(gm2(st[3][2])^st[3][2])^st[3][3]);
assign mc_s[3][2] = ctrl_decrypt_r ? (gm13(st[3][0])^gm9 (st[3][1])^gm14(st[3][2])^gm11(st[3][3])) : (st[3][0]^st[3][1]^gm2(st[3][2])^(gm2(st[3][3])^st[3][3]));
assign mc_s[3][3] = ctrl_decrypt_r ? (gm11(st[3][0])^gm13(st[3][1])^gm9 (st[3][2])^gm14(st[3][3])) : ((gm2(st[3][0])^st[3][0])^st[3][1]^st[3][2]^gm2(st[3][3]));

// ── APB write ─────────────────────────────────────────────────────────────
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        ctrl_start_r<=0; ctrl_decrypt_r<=0; ctrl_mode_r<=0;
        for (int i=0;i<4;i++) begin key_r[i]<=0; iv_r[i]<=0; din_r[i]<=0; end
    end else begin
        ctrl_start_r <= 1'b0;
        if (apb_wr) begin
            case (paddr)
                8'h00: begin ctrl_start_r<=pwdata[0]; ctrl_decrypt_r<=pwdata[1]; ctrl_mode_r<=pwdata[3:2]; end
                8'h04: key_r[0]<=pwdata; 8'h08: key_r[1]<=pwdata;
                8'h0C: key_r[2]<=pwdata; 8'h10: key_r[3]<=pwdata;
                8'h14: iv_r[0] <=pwdata; 8'h18: iv_r[1] <=pwdata;
                8'h1C: iv_r[2] <=pwdata; 8'h20: iv_r[3] <=pwdata;
                8'h24: din_r[0]<=pwdata; 8'h28: din_r[1]<=pwdata;
                8'h2C: din_r[2]<=pwdata; 8'h30: din_r[3]<=pwdata;
                default: ;
            endcase
        end
    end
end

// ── APB read ──────────────────────────────────────────────────────────────
always_comb begin
    prdata = '0;
    case (paddr)
        8'h00: prdata = {29'b0,ctrl_mode_r,ctrl_decrypt_r,ctrl_start_r};
        8'h04: prdata = key_r[0]; 8'h08: prdata = key_r[1];
        8'h0C: prdata = key_r[2]; 8'h10: prdata = key_r[3];
        8'h14: prdata = iv_r[0];  8'h18: prdata = iv_r[1];
        8'h1C: prdata = iv_r[2];  8'h20: prdata = iv_r[3];
        8'h24: prdata = din_r[0]; 8'h28: prdata = din_r[1];
        8'h2C: prdata = din_r[2]; 8'h30: prdata = din_r[3];
        8'h34: prdata = dout_r[0];8'h38: prdata = dout_r[1];
        8'h3C: prdata = dout_r[2];8'h40: prdata = dout_r[3];
        8'h44: prdata = {30'b0,status_busy_r,status_done_r};
        default: prdata = '0;
    endcase
end

// ── Main AES FSM — no local variable declarations anywhere ────────────────
always_ff @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        aes_fsm<=S_IDLE; status_done_r<=0; status_busy_r<=0;
        ks_i<=0; rnd<=0;
        for (int c=0;c<4;c++) for (int r=0;r<4;r++) st[c][r]<=0;
        for (int i=0;i<44;i++) rk[i]<=0;
        for (int i=0;i<4;i++) dout_r[i]<=0;
    end else begin
        case (aes_fsm)

        S_IDLE: begin
            if (ctrl_start_r && !status_busy_r) begin
                status_done_r<=0;
                status_busy_r<=1;
                rk[0]<=key_r[0]; rk[1]<=key_r[1]; rk[2]<=key_r[2]; rk[3]<=key_r[3];
                ks_i   <=6'd4;
                aes_fsm<=S_KEYSCHED;
            end
        end

        // One new key word per cycle; ks_new_word computed combinationally above.
        S_KEYSCHED: begin
            rk[ks_i] <= ks_new_word;
            ks_i     <= ks_i + 6'd1;
            if (ks_i == 6'd43) begin
                st[0][0]<=din_blk[0][31:24]; st[0][1]<=din_blk[0][23:16];
                st[0][2]<=din_blk[0][15: 8]; st[0][3]<=din_blk[0][ 7: 0];
                st[1][0]<=din_blk[1][31:24]; st[1][1]<=din_blk[1][23:16];
                st[1][2]<=din_blk[1][15: 8]; st[1][3]<=din_blk[1][ 7: 0];
                st[2][0]<=din_blk[2][31:24]; st[2][1]<=din_blk[2][23:16];
                st[2][2]<=din_blk[2][15: 8]; st[2][3]<=din_blk[2][ 7: 0];
                st[3][0]<=din_blk[3][31:24]; st[3][1]<=din_blk[3][23:16];
                st[3][2]<=din_blk[3][15: 8]; st[3][3]<=din_blk[3][ 7: 0];
                rnd     <= ctrl_decrypt_r ? 4'd10 : 4'd0;
                aes_fsm <= S_ADDRK0;
            end
        end

        // AddRoundKey: initial key (enc rk[0..3], dec rk[40..43]).
        S_ADDRK0: begin
            st[0][0]<=st[0][0]^rk0_w0[31:24]; st[0][1]<=st[0][1]^rk0_w0[23:16];
            st[0][2]<=st[0][2]^rk0_w0[15: 8]; st[0][3]<=st[0][3]^rk0_w0[ 7: 0];
            st[1][0]<=st[1][0]^rk0_w1[31:24]; st[1][1]<=st[1][1]^rk0_w1[23:16];
            st[1][2]<=st[1][2]^rk0_w1[15: 8]; st[1][3]<=st[1][3]^rk0_w1[ 7: 0];
            st[2][0]<=st[2][0]^rk0_w2[31:24]; st[2][1]<=st[2][1]^rk0_w2[23:16];
            st[2][2]<=st[2][2]^rk0_w2[15: 8]; st[2][3]<=st[2][3]^rk0_w2[ 7: 0];
            st[3][0]<=st[3][0]^rk0_w3[31:24]; st[3][1]<=st[3][1]^rk0_w3[23:16];
            st[3][2]<=st[3][2]^rk0_w3[15: 8]; st[3][3]<=st[3][3]^rk0_w3[ 7: 0];
            rnd     <= ctrl_decrypt_r ? 4'd9 : 4'd1;
            aes_fsm <= S_SUBBYTES;
        end

        S_SUBBYTES: begin
            if (!ctrl_decrypt_r)
                for (int c=0;c<4;c++) for (int r=0;r<4;r++) st[c][r]<=sbox_fwd(st[c][r]);
            else
                for (int c=0;c<4;c++) for (int r=0;r<4;r++) st[c][r]<=sbox_inv(st[c][r]);
            aes_fsm <= S_SHIFTROWS;
        end

        // NBA semantics: all RHS values sampled at clock edge before any write.
        S_SHIFTROWS: begin
            if (!ctrl_decrypt_r) begin
                st[0][1]<=st[1][1]; st[1][1]<=st[2][1]; st[2][1]<=st[3][1]; st[3][1]<=st[0][1];
                st[0][2]<=st[2][2]; st[1][2]<=st[3][2]; st[2][2]<=st[0][2]; st[3][2]<=st[1][2];
                st[0][3]<=st[3][3]; st[1][3]<=st[0][3]; st[2][3]<=st[1][3]; st[3][3]<=st[2][3];
                aes_fsm <= (rnd==4'd10) ? S_ADDRK : S_MIXCOLS;
            end else begin
                st[0][1]<=st[3][1]; st[1][1]<=st[0][1]; st[2][1]<=st[1][1]; st[3][1]<=st[2][1];
                st[0][2]<=st[2][2]; st[1][2]<=st[3][2]; st[2][2]<=st[0][2]; st[3][2]<=st[1][2];
                st[0][3]<=st[1][3]; st[1][3]<=st[2][3]; st[2][3]<=st[3][3]; st[3][3]<=st[0][3];
                aes_fsm <= S_ADDRK;   // decrypt: AddRoundKey before InvMixCols
            end
        end

        // mc_s computed combinationally from current st[][].
        S_MIXCOLS: begin
            for (int c=0;c<4;c++) for (int r=0;r<4;r++) st[c][r] <= mc_s[c][r];
            if (ctrl_decrypt_r) begin
                rnd     <= rnd - 4'd1;      // decrement AFTER AddRoundKey+InvMixCols
                aes_fsm <= S_SUBBYTES;
            end else
                aes_fsm <= S_ADDRK;
        end

        // rk_w0..rk_w3 computed combinationally from rnd.
        S_ADDRK: begin
            st[0][0]<=st[0][0]^rk_w0[31:24]; st[0][1]<=st[0][1]^rk_w0[23:16];
            st[0][2]<=st[0][2]^rk_w0[15: 8]; st[0][3]<=st[0][3]^rk_w0[ 7: 0];
            st[1][0]<=st[1][0]^rk_w1[31:24]; st[1][1]<=st[1][1]^rk_w1[23:16];
            st[1][2]<=st[1][2]^rk_w1[15: 8]; st[1][3]<=st[1][3]^rk_w1[ 7: 0];
            st[2][0]<=st[2][0]^rk_w2[31:24]; st[2][1]<=st[2][1]^rk_w2[23:16];
            st[2][2]<=st[2][2]^rk_w2[15: 8]; st[2][3]<=st[2][3]^rk_w2[ 7: 0];
            st[3][0]<=st[3][0]^rk_w3[31:24]; st[3][1]<=st[3][1]^rk_w3[23:16];
            st[3][2]<=st[3][2]^rk_w3[15: 8]; st[3][3]<=st[3][3]^rk_w3[ 7: 0];
            if (!ctrl_decrypt_r) begin
                if (rnd==4'd10) aes_fsm<=S_OUTPUT;
                else begin rnd<=rnd+4'd1; aes_fsm<=S_SUBBYTES; end
            end else begin
                // decrypt: AddRoundKey done; go to InvMixCols (rnd>0) or OUTPUT (rnd==0)
                if (rnd==4'd0) aes_fsm<=S_OUTPUT;
                else           aes_fsm<=S_MIXCOLS;
            end
        end

        // out_word[0..3] reassembled combinationally; no local logic needed.
        S_OUTPUT: begin
            dout_r[0] <= (ctrl_mode_r==2'b10)                   ? (out_word[0]^din_r[0]) :
                         (ctrl_mode_r==2'b01 && ctrl_decrypt_r) ? (out_word[0]^iv_r[0])  : out_word[0];
            dout_r[1] <= (ctrl_mode_r==2'b10)                   ? (out_word[1]^din_r[1]) :
                         (ctrl_mode_r==2'b01 && ctrl_decrypt_r) ? (out_word[1]^iv_r[1])  : out_word[1];
            dout_r[2] <= (ctrl_mode_r==2'b10)                   ? (out_word[2]^din_r[2]) :
                         (ctrl_mode_r==2'b01 && ctrl_decrypt_r) ? (out_word[2]^iv_r[2])  : out_word[2];
            dout_r[3] <= (ctrl_mode_r==2'b10)                   ? (out_word[3]^din_r[3]) :
                         (ctrl_mode_r==2'b01 && ctrl_decrypt_r) ? (out_word[3]^iv_r[3])  : out_word[3];
            if (ctrl_mode_r==2'b10) begin
                iv_r[3] <= iv_r[3] + 32'd1;
            end else if (ctrl_mode_r==2'b01 && !ctrl_decrypt_r) begin
                iv_r[0]<=out_word[0]; iv_r[1]<=out_word[1];
                iv_r[2]<=out_word[2]; iv_r[3]<=out_word[3];
            end else if (ctrl_mode_r==2'b01 && ctrl_decrypt_r) begin
                iv_r[0]<=din_r[0]; iv_r[1]<=din_r[1];
                iv_r[2]<=din_r[2]; iv_r[3]<=din_r[3];
            end
            status_done_r<=1; status_busy_r<=0;
            aes_fsm<=S_IDLE;
        end

        default: aes_fsm<=S_IDLE;
        endcase
    end
end

endmodule
