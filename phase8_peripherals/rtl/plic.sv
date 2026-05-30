`timescale 1ns/1ps
// PLIC — Platform Level Interrupt Controller
// 8 interrupt sources → 1 CPU external interrupt (m_ext_irq)
// Reg map (base 0x0C00_0000):
//   0x000..0x01C  Priority[0..7]: 3-bit priority per source (32-bit registers)
//   0x020         Pending:   bitmask of pending sources (RO, set by hw)
//   0x024         Enable:    bitmask of enabled sources (R/W)
//   0x028         Threshold: minimum priority to forward (R/W)
//   0x02C         Claim/Complete: read=ID of highest-priority pending+enabled source
//                               write=complete (clear pending for that source ID)
// Interrupt sources: 0=uart_rx_valid 1=uart_tx_empty 2=gpio_edge 3=timer_cmp
//                    4=spi_done 5-7=reserved
module plic (
    input  logic        clk, rst_n,
    input  logic [11:0] paddr,
    input  logic        psel, penable, pwrite,
    input  logic [31:0] pwdata,
    output logic [31:0] prdata,
    output logic        pready,
    // Interrupt source inputs
    input  logic [7:0]  irq_src,
    // CPU external interrupt output
    output logic        m_ext_irq
);
    logic [7:0] apb_addr;
    assign apb_addr = paddr[7:0];

    // Registers
    logic [2:0]  priority_r [0:7];  // 3-bit priority per source
    logic [7:0]  enable_r;
    logic [2:0]  threshold_r;
    logic [7:0]  pending_r;

    // Claim logic: find highest-priority pending+enabled source
    // Returns 0 if none (ID 0 = no interrupt, IDs 1-8 map to sources 0-7)
    logic [3:0]  claim_id;
    logic [2:0]  claim_pri;

    integer i;
    always_comb begin
        claim_id  = 4'd0;
        claim_pri = 3'd0;
        for (i = 0; i < 8; i = i + 1) begin
            if (pending_r[i] && enable_r[i] && (priority_r[i] > threshold_r)) begin
                if (priority_r[i] > claim_pri) begin
                    claim_pri = priority_r[i];
                    claim_id  = i[3:0] + 4'd1;  // 1-based ID
                end
            end
        end
    end

    // Pending register: set by hardware, cleared by claim/complete write
    // Use separate bit indexing (Icarus compat: avoid bit-select in always_comb)
    logic apb_wr;
    assign apb_wr = psel & penable & pwrite;

    logic [7:0] irq_src_sync;   // registered inputs to avoid glitches
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < 8; i = i + 1) priority_r[i] <= 3'd0;
            enable_r    <= 8'h00;
            threshold_r <= 3'd0;
            pending_r   <= 8'h00;
            irq_src_sync <= 8'h00;
        end else begin
            irq_src_sync <= irq_src;
            // Set pending on rising edge of irq_src (any assertion)
            pending_r <= pending_r | irq_src_sync;

            if (apb_wr) begin
                casez (apb_addr)
                    8'h0?,    // 0x00-0x0F: prio[0..3]
                    8'h1?:    // 0x10-0x1F: prio[4..7]
                    begin
                        // Priority register: addr[4:2] selects source
                        case (apb_addr[4:2])
                            3'd0: priority_r[0] <= pwdata[2:0];
                            3'd1: priority_r[1] <= pwdata[2:0];
                            3'd2: priority_r[2] <= pwdata[2:0];
                            3'd3: priority_r[3] <= pwdata[2:0];
                            3'd4: priority_r[4] <= pwdata[2:0];
                            3'd5: priority_r[5] <= pwdata[2:0];
                            3'd6: priority_r[6] <= pwdata[2:0];
                            3'd7: priority_r[7] <= pwdata[2:0];
                        endcase
                    end
                    8'h24: enable_r    <= pwdata[7:0];
                    8'h28: threshold_r <= pwdata[2:0];
                    8'h2C: begin
                        // Complete: clear pending for claimed source
                        if (pwdata[3:0] >= 4'd1 && pwdata[3:0] <= 4'd8) begin
                            case (pwdata[3:0])
                                4'd1: pending_r[0] <= 1'b0;
                                4'd2: pending_r[1] <= 1'b0;
                                4'd3: pending_r[2] <= 1'b0;
                                4'd4: pending_r[3] <= 1'b0;
                                4'd5: pending_r[4] <= 1'b0;
                                4'd6: pending_r[5] <= 1'b0;
                                4'd7: pending_r[6] <= 1'b0;
                                4'd8: pending_r[7] <= 1'b0;
                            endcase
                        end
                    end
                    default: ;
                endcase
            end
        end
    end

    // APB read
    always_comb begin
        casez (apb_addr)
            8'h0?,
            8'h1?: begin
                case (apb_addr[4:2])
                    3'd0: prdata = {29'b0, priority_r[0]};
                    3'd1: prdata = {29'b0, priority_r[1]};
                    3'd2: prdata = {29'b0, priority_r[2]};
                    3'd3: prdata = {29'b0, priority_r[3]};
                    3'd4: prdata = {29'b0, priority_r[4]};
                    3'd5: prdata = {29'b0, priority_r[5]};
                    3'd6: prdata = {29'b0, priority_r[6]};
                    3'd7: prdata = {29'b0, priority_r[7]};
                endcase
            end
            8'h20:   prdata = {24'b0, pending_r};
            8'h24:   prdata = {24'b0, enable_r};
            8'h28:   prdata = {29'b0, threshold_r};
            8'h2C:   prdata = {28'b0, claim_id};
            default: prdata = 32'b0;
        endcase
    end

    assign pready    = 1'b1;
    assign m_ext_irq = (claim_id != 4'd0);
endmodule
