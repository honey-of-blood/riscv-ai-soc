// Minimal UVM base class library compatible with Verilator 5.020 + --timing
// Implements: object, component, sequence_item, sequencer, driver, monitor,
//             agent, scoreboard, env, test, and a simple analysis TLM FIFO.

`ifndef UVM_MINI_PKG_SV
`define UVM_MINI_PKG_SV

`ifndef UVM_VERBOSITY_NONE
  `define UVM_NONE   0
  `define UVM_LOW    100
  `define UVM_MEDIUM 200
  `define UVM_HIGH   300
  `define UVM_FULL   400
`endif

`define uvm_info(ID, MSG, VERB) \
    begin \
      $display("[%0t ps][INFO ][%s] %s", $time, ID, MSG); \
    end

`define uvm_error(ID, MSG) \
    begin \
      $display("[%0t ps][ERROR][%s] %s", $time, ID, MSG); \
      uvm_mini_pkg::g_error_count++; \
    end

`define uvm_fatal(ID, MSG) \
    begin \
      $display("[%0t ps][FATAL][%s] %s", $time, ID, MSG); \
      $finish; \
    end

package uvm_mini_pkg;

  int unsigned g_error_count = 0;

  // ─── uvm_phase (placeholder — phases run via task calls) ───────────────────
  class uvm_phase;
    string name;
    function new(string name = ""); this.name = name; endfunction
  endclass

  // ─── uvm_object ────────────────────────────────────────────────────────────
  virtual class uvm_object;
    protected string m_name;
    function new(string name = "");
      m_name = name;
    endfunction
    virtual function string get_name(); return m_name; endfunction
    virtual function string get_type_name(); return "uvm_object"; endfunction
    virtual function string convert2string(); return $sformatf("uvm_object(%s)", m_name); endfunction
  endclass

  // ─── uvm_component ─────────────────────────────────────────────────────────
  virtual class uvm_component extends uvm_object;
    uvm_component m_parent;
    function new(string name, uvm_component parent);
      super.new(name);
      m_parent = parent;
    endfunction
    virtual function void build_phase(uvm_phase phase);   endfunction
    virtual function void connect_phase(uvm_phase phase); endfunction
    virtual task         run_phase(uvm_phase phase);      endtask
    virtual function void report_phase(uvm_phase phase);  endfunction
    virtual function string get_full_name();
      if (m_parent != null)
        return {m_parent.get_full_name(), ".", get_name()};
      return get_name();
    endfunction
  endclass

  // ─── uvm_sequence_item ─────────────────────────────────────────────────────
  class uvm_sequence_item extends uvm_object;
    function new(string name = "seq_item"); super.new(name); endfunction
  endclass

  // ─── uvm_sequencer (mailbox-based) ─────────────────────────────────────────
  class uvm_sequencer #(type REQ = uvm_sequence_item) extends uvm_component;
    mailbox #(REQ) m_fifo;
    function new(string name, uvm_component parent);
      super.new(name, parent);
      m_fifo = new(16);
    endfunction
    task put(REQ item); m_fifo.put(item); endtask
    task get(output REQ item); m_fifo.get(item); endtask
    function int num(); return m_fifo.num(); endfunction
  endclass

  // ─── uvm_driver ────────────────────────────────────────────────────────────
  virtual class uvm_driver #(type REQ = uvm_sequence_item) extends uvm_component;
    uvm_sequencer #(REQ) seq_item_port;
    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction
    task get_next_item(output REQ item);
      seq_item_port.get(item);
    endtask
    function void item_done(); endfunction
  endclass

  // ─── uvm_monitor ───────────────────────────────────────────────────────────
  virtual class uvm_monitor extends uvm_component;
    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction
  endclass

  // ─── uvm_scoreboard ────────────────────────────────────────────────────────
  virtual class uvm_scoreboard extends uvm_component;
    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction
  endclass

  // ─── uvm_agent ─────────────────────────────────────────────────────────────
  virtual class uvm_agent extends uvm_component;
    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction
  endclass

  // ─── uvm_env ───────────────────────────────────────────────────────────────
  virtual class uvm_env extends uvm_component;
    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction
  endclass

  // ─── uvm_test ──────────────────────────────────────────────────────────────
  virtual class uvm_test extends uvm_component;
    function new(string name, uvm_component parent);
      super.new(name, parent);
    endfunction
  endclass

  // ─── uvm_tlm_analysis_fifo (simplified write/get) ──────────────────────────
  class uvm_tlm_analysis_fifo #(type T = uvm_sequence_item);
    mailbox #(T) m_mbx;
    function new(int unsigned depth = 0);
      m_mbx = new(depth);
    endfunction
    function void write(T item); void'(m_mbx.try_put(item)); endfunction
    task get(output T item); m_mbx.get(item); endtask
    function int unsigned used(); return m_mbx.num(); endfunction
  endclass

endpackage

`endif // UVM_MINI_PKG_SV
