`timescale 1ns/1ps
// CLINT — Core Local Interruptor
// Exposes MSIP (software interrupt) and pass-through for timer mtime/mtimecmp.
// APB register map (base 0x0200_0000):
//   0x000 MSIP       : [0]=software interrupt pending (R/W)
//   0x004 MTIME_LO   : pass-through read from timer
//   0x008 MTIME_HI   : pass-through from timer
//   0x00C MTIMECMP_LO: proxy write to timer; read from timer
//   0x010 MTIMECMP_HI: proxy write to timer; read from timer
module clint (
    input  logic        clk, rst_n,
    input  logic [11:0] paddr,
    input  logic        psel, penable, pwrite,
    input  logic [31:0] pwdata,
    output logic [31:0] prdata,
    output logic        pready,
    // Timer pass-through (connect to timer.sv's ports)
    input  logic [31:0] mtime_lo_i,
    input  logic [31:0] mtime_hi_i,
    input  logic [31:0] mtimecmp_lo_i,
    input  logic [31:0] mtimecmp_hi_i,
    output logic [31:0] mtimecmp_lo_o,
    output logic [31:0] mtimecmp_hi_o,
    output logic        mtimecmp_wr_o,   // pulse: write mtimecmp through to timer
    // Interrupt outputs
    input  logic        mtip_i,          // from timer
    output logic        mtip_o,          // forwarded to CPU
    output logic        msip_o           // software interrupt
);
    logic [7:0] apb_addr;
    assign apb_addr = paddr[7:0];

    logic        msip_r;
    logic [31:0] mtimecmp_lo_r, mtimecmp_hi_r;
    logic        mtimecmp_wr_r;

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            msip_r         <= 1'b0;
            mtimecmp_lo_r  <= 32'h0;
            mtimecmp_hi_r  <= 32'h0;
            mtimecmp_wr_r  <= 1'b0;
        end else begin
            mtimecmp_wr_r <= 1'b0;  // pulse for one cycle
            if (psel && penable && pwrite) begin
                case (apb_addr)
                    8'h00: msip_r <= pwdata[0];
                    8'h0C: begin mtimecmp_lo_r <= pwdata; mtimecmp_wr_r <= 1'b1; end
                    8'h10: begin mtimecmp_hi_r <= pwdata; mtimecmp_wr_r <= 1'b1; end
                    default: ;
                endcase
            end
        end
    end

    always_comb begin
        case (apb_addr)
            8'h00:   prdata = {31'b0, msip_r};
            8'h04:   prdata = mtime_lo_i;
            8'h08:   prdata = mtime_hi_i;
            8'h0C:   prdata = mtimecmp_lo_i;
            8'h10:   prdata = mtimecmp_hi_i;
            default: prdata = 32'b0;
        endcase
    end

    assign pready        = 1'b1;
    assign msip_o        = msip_r;
    assign mtip_o        = mtip_i;
    assign mtimecmp_lo_o = mtimecmp_lo_r;
    assign mtimecmp_hi_o = mtimecmp_hi_r;
    assign mtimecmp_wr_o = mtimecmp_wr_r;
endmodule
