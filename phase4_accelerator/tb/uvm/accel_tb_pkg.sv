// UVM testbench package for the 4×4 systolic-array accelerator.
// Flat coroutine structure (Verilator 5.020 --timing compatible).

`include "uvm_mini_pkg.sv"

package accel_tb_pkg;
  import uvm_mini_pkg::*;

  // MMIO base address (matches crossbar slave-2 decode)
  localparam logic [31:0] BASE = 32'h5000_0000;

  // Register byte offsets
  localparam int CTRL   = 'h00;
  localparam int W_ROW0 = 'h04;  // W_row1..3 at +4,+8,+12
  localparam int A_ROW0 = 'h14;  // A_row1..3 at +4,+8,+12
  localparam int Y_BASE = 'h24;  // Y[m][n] at Y_BASE + (m*4+n)*4

  // ── seq_item ────────────────────────────────────────────────────────────────
  typedef enum logic { DIR_WRITE=0, DIR_READ=1 } dir_t;

  class accel_seq_item extends uvm_sequence_item;
    dir_t        dir;
    logic [31:0] addr;
    logic [31:0] data;
    logic  [3:0] wstrb;
    logic  [1:0] resp;
    function new(string name="item"); super.new(name); endfunction
  endclass

  // ── driver ──────────────────────────────────────────────────────────────────
  class accel_driver extends uvm_component;
    virtual accel_if vif;
    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction

    task init_signals();
      vif.awvalid=0; vif.wvalid=0; vif.bready=0;
      vif.arvalid=0; vif.rready=0;
      vif.awaddr=0; vif.wdata=0; vif.wstrb=0; vif.araddr=0;
    endtask

    task axi_write(output logic [1:0] resp,
                   input  logic [31:0] addr,
                   input  logic [31:0] data,
                   input  logic  [3:0] strb = 4'hF);
      @(posedge vif.clk);
      vif.awaddr  <= addr; vif.awvalid <= 1;
      vif.wdata   <= data; vif.wstrb   <= strb; vif.wvalid <= 1;
      vif.bready  <= 1;
      @(posedge vif.clk);
      while (!vif.awready) @(posedge vif.clk);
      vif.awvalid <= 0;
      while (!vif.wready)  @(posedge vif.clk);
      vif.wvalid  <= 0;
      while (!vif.bvalid)  @(posedge vif.clk);
      resp = vif.bresp;
      @(posedge vif.clk);
      vif.bready <= 0;
    endtask

    task axi_read(output logic [31:0] data,
                  output logic  [1:0] resp,
                  input  logic [31:0] addr);
      @(posedge vif.clk);
      vif.araddr  <= addr; vif.arvalid <= 1; vif.rready <= 1;
      @(posedge vif.clk);
      while (!vif.arready) @(posedge vif.clk);
      vif.arvalid <= 0;
      while (!vif.rvalid) @(posedge vif.clk);
      data = vif.rdata; resp = vif.rresp;
      @(posedge vif.clk);
      vif.rready <= 0;
    endtask

    // Poll CTRL until done=1; returns after done is set.
    task wait_done();
      logic [31:0] ctrl; logic [1:0] r;
      do begin
        axi_read(ctrl, r, BASE + CTRL);
      end while (!ctrl[1]);
    endtask

    // Load 4×4 weight matrix (w[k][n], packed as {w[k][3],..,w[k][0]} per row).
    task load_weights(input logic [31:0] rows[4]);
      logic [1:0] r;
      axi_write(r, BASE+W_ROW0,    rows[0]); @(posedge vif.clk);
      axi_write(r, BASE+W_ROW0+'h4, rows[1]); @(posedge vif.clk);
      axi_write(r, BASE+W_ROW0+'h8, rows[2]); @(posedge vif.clk);
      axi_write(r, BASE+W_ROW0+'hC, rows[3]); @(posedge vif.clk);
    endtask

    // Load 4×4 activation matrix.
    task load_activations(input logic [31:0] rows[4]);
      logic [1:0] r;
      axi_write(r, BASE+A_ROW0,    rows[0]); @(posedge vif.clk);
      axi_write(r, BASE+A_ROW0+'h4, rows[1]); @(posedge vif.clk);
      axi_write(r, BASE+A_ROW0+'h8, rows[2]); @(posedge vif.clk);
      axi_write(r, BASE+A_ROW0+'hC, rows[3]); @(posedge vif.clk);
    endtask

    // Trigger computation and wait for done.
    task start_and_wait();
      logic [1:0] r;
      axi_write(r, BASE+CTRL, 32'h1);
      wait_done();
    endtask

    // Read all 16 output registers into y[m][n].
    task read_outputs(output logic [31:0] y[4][4]);
      logic [1:0] r;
      for (int m = 0; m < 4; m++)
        for (int n = 0; n < 4; n++)
          axi_read(y[m][n], r, BASE + Y_BASE + (m*4+n)*4);
    endtask
  endclass

  // ── monitor ─────────────────────────────────────────────────────────────────
  class accel_monitor extends uvm_monitor;
    virtual accel_if vif;
    uvm_tlm_analysis_fifo #(accel_seq_item) ap;

    function new(string name, uvm_component parent);
      super.new(name, parent);
      ap = new(0);
    endfunction

    task run_monitor();
      fork
        forever begin // write channel
          accel_seq_item item;
          while (!(vif.awvalid && vif.awready)) @(posedge vif.clk);
          item = new("mon_wr"); item.dir = DIR_WRITE; item.addr = vif.awaddr;
          while (!(vif.wvalid && vif.wready)) @(posedge vif.clk);
          item.data = vif.wdata; item.wstrb = vif.wstrb;
          while (!(vif.bvalid && vif.bready)) @(posedge vif.clk);
          item.resp = vif.bresp; ap.write(item); @(posedge vif.clk);
        end
        forever begin // read channel
          accel_seq_item item;
          while (!(vif.arvalid && vif.arready)) @(posedge vif.clk);
          item = new("mon_rd"); item.dir = DIR_READ; item.addr = vif.araddr;
          while (!(vif.rvalid && vif.rready)) @(posedge vif.clk);
          item.data = vif.rdata; item.resp = vif.rresp; ap.write(item); @(posedge vif.clk);
        end
      join_none
    endtask
  endclass

  // ── scoreboard ──────────────────────────────────────────────────────────────
  // Tracks written W and A; on start, computes expected Y; verifies Y reads.
  class accel_scoreboard extends uvm_scoreboard;
    logic [7:0]  sw_w[4][4]; // shadow W[k][n]
    logic [7:0]  sw_a[4][4]; // shadow A[m][k]
    logic [31:0] exp_y[4][4]; // expected output
    bit          y_valid;     // whether exp_y is current

    int unsigned pass_count = 0;
    int unsigned fail_count = 0;

    function new(string name, uvm_component parent);
      super.new(name, parent);
      y_valid = 0;
    endfunction

    // Software reference model: Y = A × W (signed INT8 → INT32)
    function automatic void compute_expected();
      for (int m = 0; m < 4; m++)
        for (int n = 0; n < 4; n++) begin
          logic signed [31:0] acc;
          acc = 0;
          for (int k = 0; k < 4; k++)
            acc += signed'(sw_a[m][k]) * signed'(sw_w[k][n]);
          exp_y[m][n] = acc;
        end
      y_valid = 1;
    endfunction

    function void process_item(accel_seq_item item);
      // Declare all locals at function scope (Verilator: no decls inside case/if)
      logic [5:0] idx;
      int         row_k, row_m, flat, yrow, ycol;
      idx = item.addr[7:2];

      if (item.dir == DIR_WRITE) begin
        case (idx)
          6'd0: begin // CTRL write with start=1
            if (item.data[0]) begin
              compute_expected();
              `uvm_info("SB", "start detected — expected Y computed", `UVM_LOW)
            end
          end
          6'd1, 6'd2, 6'd3, 6'd4: begin // W_row0..3
            row_k = int'(idx) - 1;
            if (item.wstrb[0]) sw_w[row_k][0] = item.data[ 7: 0];
            if (item.wstrb[1]) sw_w[row_k][1] = item.data[15: 8];
            if (item.wstrb[2]) sw_w[row_k][2] = item.data[23:16];
            if (item.wstrb[3]) sw_w[row_k][3] = item.data[31:24];
            y_valid = 0;
          end
          6'd5, 6'd6, 6'd7, 6'd8: begin // A_row0..3
            row_m = int'(idx) - 5;
            if (item.wstrb[0]) sw_a[row_m][0] = item.data[ 7: 0];
            if (item.wstrb[1]) sw_a[row_m][1] = item.data[15: 8];
            if (item.wstrb[2]) sw_a[row_m][2] = item.data[23:16];
            if (item.wstrb[3]) sw_a[row_m][3] = item.data[31:24];
            y_valid = 0;
          end
          default: ;
        endcase
      end else begin // DIR_READ
        if (idx >= 6'd9 && idx <= 6'd24) begin
          flat = int'(idx) - 9;
          yrow = flat / 4;
          ycol = flat % 4;
          if (y_valid) begin
            if (item.data === exp_y[yrow][ycol]) begin
              pass_count++;
              `uvm_info("SB", $sformatf("Y[%0d][%0d] PASS exp=%0d got=%0d",
                         yrow, ycol, $signed(exp_y[yrow][ycol]), $signed(item.data)), `UVM_LOW)
            end else begin
              fail_count++;
              `uvm_error("SB", $sformatf("Y[%0d][%0d] FAIL exp=%0d got=%0d",
                          yrow, ycol, $signed(exp_y[yrow][ycol]), $signed(item.data)))
            end
          end
        end
      end
    endfunction

    virtual function void report_phase(uvm_phase phase);
      $display("[SB] PASS=%0d FAIL=%0d", pass_count, fail_count);
    endfunction
  endclass

  // ── coverage ────────────────────────────────────────────────────────────────
  class accel_coverage extends uvm_component;
    bit cov_identity_weights;
    bit cov_full_matmul;
    bit cov_signed_weights;
    bit cov_zero_activations;
    bit cov_back_to_back;
    bit cov_max_positive;
    bit cov_max_negative;
    bit cov_mixed_sign;
    bit cov_ctrl_lifecycle;

    int unsigned total_computes = 0;

    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction

    function void mark(string tag);
      case (tag)
        "identity_weights":  cov_identity_weights  = 1;
        "full_matmul":       cov_full_matmul        = 1;
        "signed_weights":    cov_signed_weights     = 1;
        "zero_activations":  cov_zero_activations   = 1;
        "back_to_back":      cov_back_to_back       = 1;
        "max_positive":      cov_max_positive       = 1;
        "max_negative":      cov_max_negative       = 1;
        "mixed_sign":        cov_mixed_sign         = 1;
        "ctrl_lifecycle":    cov_ctrl_lifecycle     = 1;
      endcase
      total_computes++;
    endfunction

    virtual function void report_phase(uvm_phase phase);
      int hits;
      hits = int'(cov_identity_weights) + int'(cov_full_matmul) + int'(cov_signed_weights)
           + int'(cov_zero_activations) + int'(cov_back_to_back)
           + int'(cov_max_positive)     + int'(cov_max_negative)
           + int'(cov_mixed_sign)       + int'(cov_ctrl_lifecycle);
      $display("[COV] %0d/9 scenario bins covered  (computes=%0d)", hits, total_computes);
      $display("[COV] identity=%0b full=%0b signed=%0b zero=%0b b2b=%0b max+=%0b max-=%0b mixed=%0b ctrl=%0b",
               cov_identity_weights, cov_full_matmul, cov_signed_weights,
               cov_zero_activations, cov_back_to_back,
               cov_max_positive, cov_max_negative, cov_mixed_sign, cov_ctrl_lifecycle);
    endfunction
  endclass

  // ── env ─────────────────────────────────────────────────────────────────────
  class accel_env extends uvm_env;
    accel_driver      drv;
    accel_monitor     mon;
    accel_scoreboard  sb;
    accel_coverage    cov;
    virtual accel_if  m_vif;

    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction

    virtual function void build_phase(uvm_phase phase);
      drv = new("drv", this); drv.vif = m_vif;
      mon = new("mon", this); mon.vif = m_vif;
      sb  = new("sb",  this);
      cov = new("cov", this);
    endfunction

    function void drain();
      accel_seq_item item;
      while (mon.ap.used() > 0) begin
        mon.ap.get(item);
        sb.process_item(item);
      end
    endfunction

    virtual function void report_phase(uvm_phase phase);
      drain();
      sb.report_phase(phase);
      cov.report_phase(phase);
    endfunction
  endclass

endpackage
