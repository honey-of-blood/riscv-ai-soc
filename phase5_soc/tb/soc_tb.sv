`timescale 1ns/1ps
// Phase 5 full-integration testbench.
//
// Verifies all four phases are exercised end-to-end:
//   Phase 1 — RV32I pipeline: register values after cache-hit LW instructions
//   Phase 2 — L1 cache: cold miss, write hit, dirty eviction, post-eviction miss
//   Phase 3 — AXI4 crossbar: routes SRAM (m0→s0) and MMIO (m1→s2) correctly
//   Phase 4 — systolic array: all 16 Y outputs checked via MMIO read bus
//
// Detection method:
//   done_flag fires when PC = 0x12C (infinite-loop JAL, last instruction).
//   After done_flag, register file and Y captures are sampled.
//   Eviction writes are monitored throughout on the s0 AXI bus.

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

// ── DUT ────────────────────────────────────────────────────────────────────────
soc_top dut (.clk(clk), .rst_n(rst_n));

// ── Done flag: firmware infinite-loop JAL at PC = 0x12C ───────────────────────
logic done_flag;
initial done_flag = 0;
always @(posedge clk)
    if (rst_n && dut.imem_addr == 32'h12C)
        done_flag <= 1;

// ══════════════════════════════════════════════════════════════════════════════
// Phase 4 — capture all 16 Y values from MMIO read bus (adapter → m1 → accel)
// Addresses: 0x5000_0024 (Y[0][0]) .. 0x5000_0060 (Y[3][3])
// ══════════════════════════════════════════════════════════════════════════════
logic [31:0] y_cap [0:15];   // y_cap[m*4+n] = Y[m][n]
bit          y_valid [0:15];
initial foreach (y_valid[i]) y_valid[i] = 0;

// Offset within the Y block: (addr - 0x5000_0024) / 4  gives index 0..15
always @(posedge clk) begin
    if (rst_n && dut.u_adapter.m_rvalid && dut.u_adapter.m_rready) begin
        automatic logic [31:0] a = dut.u_adapter.addr_r;
        if (a >= 32'h5000_0024 && a <= 32'h5000_0060) begin
            automatic int idx = (a - 32'h5000_0024) >> 2;
            y_cap[idx]   <= dut.u_adapter.m_rdata;
            y_valid[idx] <= 1;
        end
    end
end

// ══════════════════════════════════════════════════════════════════════════════
// Phase 2 — monitor s0 write bus for dirty-eviction writes
// Cache evicts 0x0000_0000 line (words 0xAB/0xCD/0xEF/0x12) to SRAM via
// the burst-to-lite bridge.  Capture the four beats.
// ══════════════════════════════════════════════════════════════════════════════
logic [31:0] evict_data [0:3];
bit          evict_valid [0:3];
initial foreach (evict_valid[i]) evict_valid[i] = 0;

always @(posedge clk) begin
    if (rst_n && dut.s0_awvalid && dut.s0_wvalid) begin
        automatic logic [31:0] wa = dut.s0_awaddr;
        automatic logic [31:0] wd = dut.s0_wdata;
        // Eviction of cache line at 0x0000_0000: 4 words at byte offsets 0..12
        if (wa <= 32'hC) begin
            automatic int beat = int'(wa[3:2]);  // 0..3
            evict_data[beat]  <= wd;
            evict_valid[beat] <= 1;
        end
    end
end

// ══════════════════════════════════════════════════════════════════════════════
// Main test
// ══════════════════════════════════════════════════════════════════════════════
task automatic check(
    input string label,
    input logic [31:0] got,
    input logic [31:0] exp
);
    if (got === exp)
        $display("[PASS] %-40s got=%0d (0x%08x)", label, got, got);
    else begin
        $display("[FAIL] %-40s got=%0d (0x%08x)  expected=%0d (0x%08x)",
                 label, got, got, exp, exp);
        error_count++;
    end
endtask

initial begin
    $display("=== Phase 5 Full-Integration SoC Test ===");
    $display("  Ph1: RV32I pipeline | Ph2: L1 cache | Ph3: AXI crossbar | Ph4: systolic array");

    // Wait for done flag (timeout: 200 000 cycles)
    repeat (200_000) begin
        @(posedge clk);
        if (done_flag) break;
    end

    if (!done_flag) begin
        $display("[FAIL] Timeout: firmware did not reach done label (PC=0x12C)");
        error_count++;
        $finish;
    end

    $display("\n[OK] Firmware reached done label at %0t ns", $time / 1000);

    // Give in-flight pipeline stages one extra drain.
    repeat (20) @(posedge clk);

    // ── Phase 1 + Phase 2 verification ────────────────────────────────────────
    // The LW instructions for cache-hit reads wrote results into a0..a3.
    // Access via register file hierarchy.
    $display("\n--- Phase 1+2: RV32I pipeline + L1 cache hits ---");
    check("a0 = LW SRAM[0x00] cache hit",  dut.u_cpu.u_regfile.regs[10], 32'h000000AB);
    check("a1 = LW SRAM[0x04] cache hit",  dut.u_cpu.u_regfile.regs[11], 32'h000000CD);
    check("a2 = LW SRAM[0x08] cache hit",  dut.u_cpu.u_regfile.regs[12], 32'h000000EF);
    check("a3 = LW SRAM[0x0C] cache hit",  dut.u_cpu.u_regfile.regs[13], 32'h00000012);

    // ── Phase 2: dirty eviction verification ──────────────────────────────────
    $display("\n--- Phase 2: dirty eviction (WRITE_BACK) to SRAM ---");
    // Wait a bit more for eviction if not yet captured.
    if (!evict_valid[0] || !evict_valid[1] || !evict_valid[2] || !evict_valid[3])
        repeat (200) @(posedge clk);
    check("evict SRAM[0x00] = 0xAB", evict_data[0], 32'h000000AB);
    check("evict SRAM[0x04] = 0xCD", evict_data[1], 32'h000000CD);
    check("evict SRAM[0x08] = 0xEF", evict_data[2], 32'h000000EF);
    check("evict SRAM[0x0C] = 0x12", evict_data[3], 32'h00000012);

    // ── Phase 3: crossbar routing via SRAM mem array (committed by eviction) ──
    $display("\n--- Phase 3: AXI crossbar SRAM commitment ---");
    check("SRAM mem[0] = 0xAB (eviction committed)", dut.u_sram0.mem[0], 32'h000000AB);
    check("SRAM mem[1] = 0xCD (eviction committed)", dut.u_sram0.mem[1], 32'h000000CD);
    check("SRAM mem[2] = 0xEF (eviction committed)", dut.u_sram0.mem[2], 32'h000000EF);
    check("SRAM mem[3] = 0x12 (eviction committed)", dut.u_sram0.mem[3], 32'h00000012);

    // ── Phase 4: all 16 Y outputs (identity matmul → Y = A) ───────────────────
    $display("\n--- Phase 4: systolic array — all 16 Y outputs ---");
    // Wait for all Y captures if not yet collected.
    begin
        int wait_cnt = 0;
        automatic bit all_y;
        all_y = 1;
        foreach (y_valid[i]) if (!y_valid[i]) all_y = 0;
        while (!all_y && wait_cnt < 500) begin
            @(posedge clk); wait_cnt++;
            all_y = 1;
            foreach (y_valid[ii]) if (!y_valid[ii]) all_y = 0;
        end
    end

    begin
        automatic int expected = 1;
        for (int m = 0; m < 4; m++) begin
            for (int n = 0; n < 4; n++) begin
                automatic int idx = m*4 + n;
                automatic string lbl;
                lbl = $sformatf("Y[%0d][%0d]", m, n);
                check(lbl, y_cap[idx], 32'(expected));
                expected++;
            end
        end
    end

    // ── Summary ────────────────────────────────────────────────────────────────
    $display("");
    if (error_count == 0)
        $display("╔═══════════════════════════════════════════╗");
    else
        $display("╔═══════════════════════════════════════════╗");
    if (error_count == 0) begin
        $display("║  ALL TESTS PASSED — full SoC integration  ║");
        $display("║  Ph1✓ Ph2✓ Ph3✓ Ph4✓  (0 errors)         ║");
    end else begin
        $display("║  %0d ERRORS — see [FAIL] lines above", error_count);
    end
    $display("╚═══════════════════════════════════════════╝");

    repeat (5) @(posedge clk);
    $finish;
end

initial begin
    #20_000_000;
    $display("[TIMEOUT] SoC test exceeded 20ms");
    $finish;
end

endmodule
