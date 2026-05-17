`timescale 1ns/1ps
// Phase 5 SoC testbench.
// Boots the RISC-V core, waits for it to complete the identity-matmul
// firmware (detected by reaching the infinite-loop JAL at PC=0x70),
// then reads a0 and a1 from the register file via DPI or by monitoring
// the dmem bus.
//
// Detection strategy: watch for PC=0x70 (done label) via the imem_addr
// signal, then sample the AXI read of Y[0][0] (a0) and Y[3][3] (a1)
// from the scoreboard monitor.

module soc_tb;

  logic clk, rst_n;
  int   error_count = 0;

  initial clk = 0;
  always #5 clk = ~clk;

  initial begin
    rst_n = 0;
    repeat (5) @(posedge clk);
    rst_n = 1;
  end

  // ── DUT ────────────────────────────────────────────────────────────────────
  soc_top dut (.clk(clk), .rst_n(rst_n));

  // ── Convenience aliases into DUT hierarchy ─────────────────────────────────
  // CPU register file result registers (written by WB stage)
  // We observe the AXI read data bus for Y[0][0] and Y[3][3] instead —
  // avoids needing DPI or hierarchy hacks.

  // Capture AXI reads to known Y addresses.
  // Firmware reads Y[0][0] @ 0x5000_0024 and Y[3][3] @ 0x5000_0060.
  logic [31:0] y00_captured, y33_captured;
  bit          y00_valid = 0, y33_valid = 0;

  // m_rready is driven by the adapter when state==RD_DATA; m_rvalid from slave.
  always @(posedge clk) begin
    if (rst_n && dut.u_adapter.m_rvalid && dut.u_adapter.m_rready) begin
      if (dut.u_adapter.addr_r == 32'h5000_0024) begin
        y00_captured <= dut.u_adapter.m_rdata;
        y00_valid <= 1;
      end
      if (dut.u_adapter.addr_r == 32'h5000_0060) begin
        y33_captured <= dut.u_adapter.m_rdata;
        y33_valid <= 1;
      end
    end
  end

  // ── Detect firmware completion (infinite-loop JAL at PC = 0x70) ────────────
  logic done_flag;
  initial done_flag = 0;

  always @(posedge clk) begin
    if (rst_n && dut.imem_addr == 32'h70)
      done_flag <= 1;
  end

  // ── Main test ───────────────────────────────────────────────────────────────
  initial begin
    $display("=== Phase 5 SoC boot test ===");
    $display("Waiting for firmware to complete (PC=0x70)...");

    // Wait for done flag (timeout after 50 000 cycles)
    repeat (50_000) begin
      @(posedge clk);
      if (done_flag) break;
    end

    if (!done_flag) begin
      $display("[FAIL] Timeout: firmware did not reach done label");
      error_count++;
    end else begin
      $display("[OK] Firmware reached done label at time %0t", $time);
      // Wait for in-flight LW pipeline stages to complete their AXI reads.
      // The LW a0/a1 instructions may still be in MEM stage when PC=0x70 is fetched.
      repeat (200) begin
        @(posedge clk);
        if (y00_valid && y33_valid) break;
      end
      if (!y00_valid || !y33_valid)
        $display("[WARN] Timed out waiting for Y captures after done");


      // The firmware's final two AXI reads are Y[0][0] and Y[3][3].
      // rd_count should be >= 2 at this point.
      if (!y00_valid || !y33_valid) begin
        $display("[FAIL] Y captures incomplete: Y[0][0]_valid=%0b Y[3][3]_valid=%0b",
                 y00_valid, y33_valid);
        error_count++;
      end else begin
        if (y00_captured === 32'd1)
          $display("[PASS] Y[0][0] = %0d (expected 1)", y00_captured);
        else begin
          $display("[FAIL] Y[0][0] = %0d (expected 1)", y00_captured);
          error_count++;
        end

        if (y33_captured === 32'd16)
          $display("[PASS] Y[3][3] = %0d (expected 16)", y33_captured);
        else begin
          $display("[FAIL] Y[3][3] = %0d (expected 16)", y33_captured);
          error_count++;
        end
      end
    end

    repeat (5) @(posedge clk);
    if (error_count == 0)
      $display("\n*** ALL TESTS PASSED (0 errors) ***");
    else
      $display("\n*** %0d ERRORS ***", error_count);
    $finish;
  end

  initial begin
    #10_000_000;
    $display("[TIMEOUT] SoC test exceeded 10ms");
    $finish;
  end

endmodule
