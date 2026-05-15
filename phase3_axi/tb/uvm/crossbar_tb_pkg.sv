// UVM testbench package for axi4_crossbar
// Execution model: drivers called directly from top-level initial block;
// monitors forked from top-level initial block.
// This flat coroutine structure works reliably with Verilator 5.020 --timing.

`include "uvm_mini_pkg.sv"

package crossbar_tb_pkg;
  import uvm_mini_pkg::*;

  typedef enum logic { AXI_WRITE=0, AXI_READ=1 } axi_dir_t;

  // ─── axi4_seq_item ─────────────────────────────────────────────────────────
  class axi4_seq_item extends uvm_sequence_item;
    axi_dir_t    dir;
    logic [31:0] addr;
    logic [31:0] data;
    logic  [3:0] wstrb;
    logic  [1:0] resp;
    int unsigned master_id;

    function new(string name = "axi4_seq_item"); super.new(name); endfunction

    function string convert2string();
      return $sformatf("[M%0d] %s addr=0x%08X data=0x%08X resp=%02b",
                       master_id, dir.name(), addr, data, resp);
    endfunction
  endclass

  // ─── axi4_master_driver ───────────────────────────────────────────────────
  // Stateless helper: all transactions driven directly by calling these tasks.
  class axi4_master_driver extends uvm_component;
    virtual axi4_if vif;
    int unsigned master_id;

    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction

    task init_signals();
      vif.awvalid = 0; vif.wvalid  = 0;
      vif.bready  = 0; vif.arvalid = 0; vif.rready  = 0;
      vif.awaddr  = 0; vif.wdata   = 0; vif.wstrb   = 0; vif.araddr = 0;
    endtask

    task axi_write(output logic [1:0] resp,
                   input  logic [31:0] addr,
                   input  logic [31:0] data,
                   input  logic  [3:0] strb = 4'hF);
      @(posedge vif.clk);
      vif.awaddr  <= addr; vif.awvalid <= 1;
      vif.wdata   <= data; vif.wstrb   <= strb; vif.wvalid <= 1;
      vif.bready  <= 1;
      // Crossbar arbiter is registered: AWREADY/WREADY come 1+ cycles after AWVALID.
      // Must hold AWVALID/WVALID until READY is returned, else SRAM never latches.
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
      // Hold ARVALID until ARREADY (crossbar grants on next clock).
      @(posedge vif.clk);
      while (!vif.arready) @(posedge vif.clk);
      vif.arvalid <= 0;
      while (!vif.rvalid) @(posedge vif.clk);
      data = vif.rdata; resp = vif.rresp;
      @(posedge vif.clk);
      vif.rready <= 0;
    endtask
  endclass

  // ─── axi4_master_monitor ─────────────────────────────────────────────────
  // Monitors one master port; spawned from top-level initial via run_monitor().
  class axi4_master_monitor extends uvm_monitor;
    virtual axi4_if vif;
    int unsigned master_id;
    uvm_tlm_analysis_fifo #(axi4_seq_item) ap;

    function new(string name, uvm_component parent);
      super.new(name, parent);
      ap = new(0);
    endfunction

    // Call from a forked initial block at the top level.
    task run_monitor();
      fork
        forever begin // write path
          axi4_seq_item item;
          while (!(vif.awvalid && vif.awready)) @(posedge vif.clk);
          item = new("mon_wr");
          item.dir = AXI_WRITE; item.addr = vif.awaddr; item.master_id = master_id;
          while (!(vif.wvalid && vif.wready)) @(posedge vif.clk);
          item.data = vif.wdata; item.wstrb = vif.wstrb;
          while (!(vif.bvalid && vif.bready)) @(posedge vif.clk);
          item.resp = vif.bresp;
          ap.write(item);
          @(posedge vif.clk);
        end
        forever begin // read path
          axi4_seq_item item;
          while (!(vif.arvalid && vif.arready)) @(posedge vif.clk);
          item = new("mon_rd");
          item.dir = AXI_READ; item.addr = vif.araddr; item.master_id = master_id;
          while (!(vif.rvalid && vif.rready)) @(posedge vif.clk);
          item.data = vif.rdata; item.resp = vif.rresp;
          ap.write(item);
          @(posedge vif.clk);
        end
      join_none
    endtask
  endclass

  // ─── axi4_master_agent ───────────────────────────────────────────────────
  class axi4_master_agent extends uvm_agent;
    axi4_master_driver  drv;
    axi4_master_monitor mon;
    int unsigned master_id;
    virtual axi4_if vif;

    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction

    virtual function void build_phase(uvm_phase phase);
      drv = new("drv", this); drv.vif = vif; drv.master_id = master_id;
      mon = new("mon", this); mon.vif = vif; mon.master_id = master_id;
    endfunction

    virtual function void connect_phase(uvm_phase phase); endfunction
  endclass

  // ─── crossbar_scoreboard ─────────────────────────────────────────────────
  class crossbar_scoreboard extends uvm_scoreboard;
    logic [31:0] shadow_mem [logic [31:0]];
    int unsigned pass_count = 0;
    int unsigned fail_count = 0;

    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction

    function void write(axi4_seq_item item);
      logic [31:0] waddr = {item.addr[31:2], 2'b00};
      if (item.dir == AXI_WRITE) begin
        if (shadow_mem.exists(waddr) == 0) shadow_mem[waddr] = 32'h0;
        if (item.wstrb[0]) shadow_mem[waddr][ 7: 0] = item.data[ 7: 0];
        if (item.wstrb[1]) shadow_mem[waddr][15: 8] = item.data[15: 8];
        if (item.wstrb[2]) shadow_mem[waddr][23:16] = item.data[23:16];
        if (item.wstrb[3]) shadow_mem[waddr][31:24] = item.data[31:24];
        `uvm_info("SB", $sformatf("WRITE 0x%08X=0x%08X M%0d", waddr, shadow_mem[waddr], item.master_id), `UVM_LOW)
      end else begin
        if (shadow_mem.exists(waddr) != 0) begin
          if (item.data === shadow_mem[waddr]) begin
            pass_count++;
            `uvm_info("SB", $sformatf("READ PASS 0x%08X exp=0x%08X got=0x%08X", waddr, shadow_mem[waddr], item.data), `UVM_LOW)
          end else begin
            fail_count++;
            `uvm_error("SB", $sformatf("READ FAIL 0x%08X exp=0x%08X got=0x%08X", waddr, shadow_mem[waddr], item.data))
          end
        end
      end
    endfunction

    virtual function void report_phase(uvm_phase phase);
      $display("[SB] PASS=%0d FAIL=%0d", pass_count, fail_count);
    endfunction
  endclass

  // ─── crossbar_coverage ───────────────────────────────────────────────────
  class crossbar_coverage extends uvm_component;
    bit covered[3][3];
    int unsigned write_count[3];
    int unsigned read_count[3];

    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction

    function void sample(axi4_seq_item item);
      int m = item.master_id;
      int s = (item.addr[31:16] == 16'h0000) ? 0 :
              (item.addr[31:16] == 16'h1000) ? 1 : 2;
      covered[m][s] = 1;
      if (item.dir == AXI_WRITE) write_count[m]++;
      else                        read_count[m]++;
    endfunction

    virtual function void report_phase(uvm_phase phase);
      int hits = 0;
      for (int m = 0; m < 3; m++)
        for (int s = 0; s < 3; s++)
          if (covered[m][s]) hits++;
      $display("[COV] Master-Slave pairs: %0d/9 covered", hits);
      for (int m = 0; m < 3; m++)
        $display("[COV] M%0d: writes=%0d reads=%0d", m, write_count[m], read_count[m]);
    endfunction
  endclass

  // ─── crossbar_env ────────────────────────────────────────────────────────
  class crossbar_env extends uvm_env;
    axi4_master_agent   agent[3];
    crossbar_scoreboard sb;
    crossbar_coverage   cov;
    virtual axi4_if     m_vif0, m_vif1, m_vif2;

    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction

    virtual function void build_phase(uvm_phase phase);
      sb  = new("sb",  this);
      cov = new("cov", this);
      agent[0] = new("a0", this); agent[0].master_id = 0; agent[0].vif = m_vif0; agent[0].build_phase(phase);
      agent[1] = new("a1", this); agent[1].master_id = 1; agent[1].vif = m_vif1; agent[1].build_phase(phase);
      agent[2] = new("a2", this); agent[2].master_id = 2; agent[2].vif = m_vif2; agent[2].build_phase(phase);
    endfunction

    // Drain analysis FIFOs into scoreboard+coverage (call periodically)
    function void drain();
      axi4_seq_item item;
      repeat (3) begin
        while (agent[0].mon.ap.used() > 0) begin agent[0].mon.ap.get(item); sb.write(item); cov.sample(item); end
        while (agent[1].mon.ap.used() > 0) begin agent[1].mon.ap.get(item); sb.write(item); cov.sample(item); end
        while (agent[2].mon.ap.used() > 0) begin agent[2].mon.ap.get(item); sb.write(item); cov.sample(item); end
      end
    endfunction

    virtual function void report_phase(uvm_phase phase);
      drain();
      sb.report_phase(phase);
      cov.report_phase(phase);
    endfunction
  endclass

endpackage
