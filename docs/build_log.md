# RISC-V AI SoC — Phase-by-Phase Build Log

**Project:** Portfolio-grade RISC-V AI SoC built from scratch using 100% open-source tools  
**Goal:** RV32I 5-stage pipeline → L1 cache → AXI4 crossbar → Systolic array AI accelerator → Full integration → Sky130 synthesis  
**Tool stack:** Icarus Verilog 12.0, Verilator 5.020, cocotb 2.0.1, Yosys, yosys-smtbmc, Z3, GTKWave  
**Verification approach:** cocotb (Phases 1–2 unit tests), UVM-mini + Verilator (Phase 3 integration), formal SMT (Phase 3)

---

## Phase 0 — Environment & Toolchain Setup

**Commit:** `56e1b76`

### What was built
- Full directory skeleton created:
  ```
  phase1_riscv_core/  rtl/  tb/
  phase2_cache/       rtl/  tb/
  phase3_axi/         rtl/  tb/  formal/
  phase4_systolic/    rtl/  tb/
  phase5_integration/ rtl/
  docs/
  ```
- Python virtual environment at `.venv/` with cocotb 2.0.1 installed
- Confirmed correct import path: `cocotb_tools.runner` (not `cocotb.runner` — the API changed in 2.x)
- Baseline simulation: D flip-flop RTL written, simulated with Icarus, waveforms viewed in GTKWave

### Key decisions made
- Use `cocotb_tools.runner` with Icarus as the simulator for all unit tests
- Use `Timer(N, unit="ns")` (singular `unit=`) throughout — cocotb 2.x dropped `units=`
- All RTL to include `` `timescale 1ns/1ps `` to prevent precision warnings

---

## Phase 1 — RV32I 5-Stage Pipeline

### Step 1 — ALU + Register File
**Commit:** `aaabd2f`

**What was built:**
- `alu.sv`: 10-operation ALU
  - Operations: ADD, SUB, AND, OR, XOR, SLL, SRL, SRA, SLT, SLTU
  - Encoding: ADD=0000, SUB=0001, AND=0010, OR=0011, XOR=0100, SLL=0101, SRL=0110, SRA=0111, SLT=1000, SLTU=1001
- `reg_file.sv`: 32×32-bit register file
  - Dual async read ports, single sync write port
  - Synchronous reset, x0 hardwired to 0

**Icarus compatibility rules discovered here:**
- Rule 1: No bit-selects inside `always_comb`. `shamt = b[4:0]` must be extracted as `assign shamt = b[4:0]` outside the block, then `shamt` used inside.
- Rule 2: Signed casts must also be `assign` outside `always_comb`. Used for SLT/SLTU comparisons.

**Tests:** cocotb — all ALU ops, all register addresses, x0 hardwire, simultaneous read/write

---

### Step 2 — Immediate Generator
**Commit:** `3582b9d`

**What was built:**
- `imm_gen.sv`: decodes all 5 RISC-V immediate types from a 32-bit instruction
  - I-type, S-type, B-type, U-type, J-type
  - All five extensions precomputed as `assign` statements; `case` on `imm_sel` picks the right one
  - Sign-extension handled at assign time

**Tests:** cocotb — one instruction per immediate type, verified sign extension on negative values

---

### Step 3 — Fetch Stage + IF/ID Pipeline Register
**Commit:** `3cf4882`

**What was built:**
- `fetch_stage.sv`:
  - PC register with synchronous reset
  - Branch mux: static not-taken prediction (PC+4 normally; branch target when `branch_taken` asserted)
  - Async instruction memory interface (`imem_addr_o`, `imem_rdata_i`)
- `pipeline_reg_IF_ID.sv`:
  - Flush input: loads NOP (`32'h0000_0013` = ADDI x0, x0, 0) to squash in-flight instruction
  - Stall input: holds current value (freezes pipeline)
- `fetch_if_id_wrap.sv`: simulation wrapper combining both modules for cocotb testing

**Design decisions:**
- NOP chosen as `32'h0000_0013` (ADDI x0, x0, 0) — has no side effects, no memory access, no register write
- Branch penalty: 2 cycles (flush IF/ID and ID/EX when branch resolves in EX stage)

---

### Step 4 — Decode Stage + ID/EX Pipeline Register
**Commit:** `ee1bc39`  
**Tests at this point:** 14/14

**What was built:**
- `decode_stage.sv`: purely combinational
  - Instantiates `imm_gen`; external `reg_file` passed in from top level
  - Generates all control signals from opcode/funct3/funct7:
    - `alu_ctrl[3:0]`: selects ALU operation
    - `alu_src_a`: 0=rs1, 1=PC (AUIPC and JAL add PC+imm)
    - `alu_src_b`: 0=rs2, 1=imm
    - `mem_we`, `mem_re`: data memory write/read enables
    - `wb_sel[1:0]`: WB_ALU=00, WB_MEM=01, WB_PC4=10, WB_IMM=11
    - `branch`, `jal`, `jalr`: branch/jump type flags
- `pipeline_reg_ID_EX.sv`:
  - Flush: zeros all control signals (inserts a bubble — no write, no memory, no branch)
  - Stall: holds current values

**Key encoding decisions locked in here:**
- `alu_src_a=1` for AUIPC (PC+imm) and JAL (PC+imm for target)
- `alu_src_a=0` for JALR (rs1+imm, bit 0 cleared in execute stage)
- Branch condition evaluated directly on forwarded rs1/rs2 values, not through ALU

---

### Step 5 — Execute, Memory, Writeback, Hazard, Forwarding + Full Core
**Commit:** `ce0521f`  
**Tests at this point:** 43/43

**What was built:**
- `execute_stage.sv`:
  - Forwarding muxes on both rs1 and rs2 before ALU (3-way: 00=ID/EX, 01=EX/MEM, 10=MEM/WB)
  - ALU computation
  - Branch condition evaluation (separate from ALU, on forwarded values)
  - JALR: bit 0 cleared on jump target (`{alu_result[31:1], 1'b0}`)
- `memory_stage.sv`: data memory interface, byte/halfword/word load sign extension
- `pipeline_reg_MEM_WB.sv`: no flush/stall (branch resolves before this stage commits)
- `writeback_stage.sv`: 4-way mux on `wb_sel` — ALU result / memory read / PC+4 / immediate
- `hazard_unit.sv`:
  - Load-use stall: detects when EX stage is a load and its destination matches ID stage source → stalls IF/ID + ID/EX, flushes EX/MEM (inserts bubble)
  - Branch flush: flushes IF/ID + ID/EX when `branch_taken` asserted from execute stage
- `forwarding_unit.sv`:
  - EX/MEM forwarding: if EX/MEM writes and matches rs1/rs2 → forward
  - MEM/WB forwarding: if MEM/WB writes and matches and EX/MEM doesn't → forward
- `riscv_core.sv`: complete top-level instantiation + wiring of all 5 stages

**Tests written:** All RV32I opcodes end-to-end — LUI, AUIPC, JAL, JALR, all 6 branch types, all R-type, all I-type, all load variants (LB/LH/LW/LBU/LHU), all store variants (SB/SH/SW), hazard scenarios

---

### Step 6 — Bug Fix + Integration Tests
**Commit:** `b5e7c6b`  
**Tests:** 22/22

**Bug found and fixed:**
- **EX/MEM forwarding for LUI was broken.** LUI uses `wb_sel=WB_IMM`, so the correct forward value is the immediate, not `alu_result` (which is 0 for LUI since `alu_src_a=0, alu_src_b=imm, alu_op=ADD` with rs1=x0).
- **Fix:** Added `fwd_ex_mem_val` mux in `riscv_core.sv` that selects between `alu_result_m` and `imm_m` based on `wb_sel_m == WB_IMM`. Forwarding unit forwards this muxed value instead of raw `alu_result`.

**New integration tests:**
- EX/MEM forwarding: chain of dependent R-type instructions
- MEM/WB forwarding: result used two cycles later
- Load-use stall: LW followed immediately by dependent instruction
- Branch with forwarded condition values
- Bubblesort stress test: sorts `[3, 1, 4, 1, 5]` in under 300 simulation cycles

---

## Phase 2 — L1 Data Cache

### Step 7 — Cache Implementation (13 tests)
**Commit:** `03e52a0`

**What was built:**
- `cache_tag_array.sv`:
  - 64 entries, each entry = `{dirty[1], valid[1], tag[21:0]}`
  - Synchronous write, asynchronous read
  - Reset clears all valid bits (dirty bits don't need reset — invalid = no eviction needed)
- `cache_data_array.sv`:
  - 64 sets × 4 words (16 bytes per cache line)
  - Byte-enable synchronous write, asynchronous read
- `cache_controller.sv`: 6-state FSM
  ```
  IDLE → TAG_CHECK
    TAG_CHECK → HIT       (valid && tag match)
    TAG_CHECK → WRITE_BACK (miss && dirty)
    TAG_CHECK → FILL       (miss && clean)
    WRITE_BACK → FILL      (after eviction complete)
    FILL → RESPOND         (after refill complete)
    HIT/RESPOND → IDLE
  ```
- `cache_top.sv`: top-level connecting all three components

**Address decode:**
- `tag   = addr[31:10]` (22 bits)
- `index = addr[9:4]`   (6 bits → 64 sets)
- `woff  = addr[3:2]`   (2 bits → word offset within 4-word line)
- `byte  = addr[1:0]`   (byte within word, used for byte enables)

**AXI4 interface (full, not Lite):**
- Cache controller uses burst signals: `awlen[7:0]`, `awsize[2:0]`, `awburst[1:0]`, `wlast`, `rlast`
- 4-word fill requires burst length = 4

**Known limitation documented:** ARVALID uses `!m_axi_rvalid_i` to de-assert — not strictly AXI4-compliant. Must fix before Phase 3 integration.

---

### Step 8 — Gap-filling Tests (18/18)
**Commit:** `adcb337`

**Additional tests added:**
- `write_miss_allocate`: write to clean missing line → FILL then write on RESPOND
- `write_miss_dirty_eviction`: write to dirty missing line → WRITE_BACK → FILL → RESPOND+write
- `byte_enable_store_end_to_end`: SB instruction → only correct byte modified
- `eviction_writes_all_four_words`: verify all 4 words of dirty line are written to memory during eviction
- `hit_latency`: cache hit takes exactly 1 stall cycle (TAG_CHECK → HIT → IDLE)
- `golden_model`: 100 random read/write operations against a software reference model

---

### Step 9 — Waveform Support
**Commit:** `5858dac`
- Added `--waves` flag to both `phase1_riscv_core/tb/run_tests.py` and `phase2_cache/tb/run_tests.py`
- Dumps FST files viewable in GTKWave for debugging

---

## Phase 1+2 Integration — Cache Stall Path

**Commit:** `ff9d967`

**What was added:**

The L1 cache can stall the CPU for multiple cycles during a miss. The pipeline must freeze in place during a stall without corrupting state or accidentally flushing.

**Changes to pipeline registers:**
- `pipeline_reg_EX_MEM.sv`: added `stall_i` — holds all values when asserted
- `pipeline_reg_MEM_WB.sv`: added `stall_i` — holds all values when asserted

**Changes to hazard unit:**
- Added `cache_stall_i` input
- Added new outputs: `stall_id_ex_o`, `stall_ex_mem_o`, `stall_mem_wb_o`
- Critical: branch flushes suppressed during cache stall. Without this, a branch in EX stage during a stall would incorrectly flush IF/ID + ID/EX even though the instruction in MEM was frozen and hadn't committed

**Changes to `riscv_core.sv`:**
- Added `dmem_stall_i` port (connected to cache `stall_o`)
- Gated `wb_reg_write` with `!dmem_stall_i` — prevents writeback stage from writing stale values during stall

---

## Phase 3 — AXI4 Crossbar, APB Bridge, Formal Verification

### Step 10 — Phase 3 RTL + Initial Verification
**Commit:** `d120d40`

#### RTL: `axi4_crossbar.sv`
- 3-master × 3-slave AXI4-Lite crossbar
- **Address decode** on `addr[31:16]`:
  - `0x0000` → Slave 0 (SRAM)
  - `0x1000` → Slave 1 (APB bridge)
  - `0x5000` → Slave 2 (AI accelerator MMIO)
- **Arbitration:** per-slave round-robin using `wr_busy[s]`, `wr_grant[s]`, `wr_last[s]` flip-flops. **Registered arbitration** — grant takes effect one clock cycle after AWVALID arrives.
- **Channel mux:** slave-side AW/W/B driven from granted master; master-side AWREADY/WREADY/BVALID routed back to granted master. Unrolled (no loop-indexed bit-selects) to satisfy Icarus compatibility.
- Same structure for read channel with `rd_busy/rd_grant/rd_last`.

#### RTL: `axi_sram.sv`
- 64KB AXI4-Lite slave (parameterized depth)
- AWREADY = WREADY = 1 combinationally (always accepting)
- BVALID asserted one cycle after AW+W latch
- ARREADY = 1 combinationally; RVALID one cycle after AR latch

#### RTL: `axi_apb_bridge.sv`
- 7-state FSM: IDLE → AXI_RD/AXI_WR → APB_SETUP → APB_ENABLE → AXI_RRESP/AXI_BRESP → IDLE
- APB PREADY wait: holds in APB_ENABLE until slave asserts PREADY
- PSLVERR propagates to BRESP/RRESP = 2 (SLVERR)

#### cocotb unit tests
- `test_axi_sram.py`: write/read, byte enables, multiple addresses, back-to-back, full strobe, overwrite isolation — **6/6**
- `test_axi_apb_bridge.py`: write, read, multi-cycle PREADY, write+read, SLVERR, back-to-back — **6/6**

#### UVM integration testbench (Verilator `--timing`)
- Custom `uvm_mini_pkg.sv` (lightweight UVM subset: component, object, env, scoreboard, monitor, coverage)
- **Critical workarounds for Verilator:**
  - No virtual interface arrays in class members → used individual `m_vif0`, `m_vif1`, `m_vif2`
  - No loop-indexed virtual interfaces in `build_phase` → unrolled explicitly
  - No `iff` qualifier in class task event expressions → replaced with `while` loops
  - `fork join_none` depth >2 causes segfault → flat coroutine structure (monitors forked from top-level `initial`, not from class tasks)
  - Include guard needed in `uvm_mini_pkg.sv` to prevent MODDUP error
- **Critical protocol fix:** Driver must hold AWVALID/WVALID/ARVALID until AWREADY/WREADY/ARREADY. Since crossbar arbitration is registered, READY arrives one cycle after VALID — dropping VALID after one clock causes the SRAM to never see a valid transaction, deadlocking.
- TEST 1: All 9 master→slave routing pairs (sequential)
- TEST 2: 3 masters simultaneously targeting Slave 0 (arbitration stress)
- **12/12 checks, 9/9 M×S coverage**

#### Formal verification (yosys-smtbmc + Z3)
**Toolchain assembled without SymbiYosys:**
```
yosys → write_smt2 → yosys-smtbmc -s z3
```

**Errors encountered and fixed during formal setup:**
1. `ERROR: Failed to resolve identifier \dut.wr_busy` — Yosys cannot follow hierarchical references from a wrapper module into the DUT. **Fix:** moved all SVA properties inside `axi4_crossbar.sv` under `` `ifdef FORMAL ``.
2. `ERROR: Unsupported cell type $adff` — async reset (`negedge rst_n`) creates `$adff` cells that `write_smt2` cannot handle. **Fix:** added `async2sync; dffunmap;` steps in the Yosys script before `write_smt2`.
3. `--smtc` flag misuse — `--smtc` is for SMT constraint files, not solver path. **Fix:** `export PATH := $(VENV_BIN):$(PATH)` in Makefile so `z3` is found by name; used `-s z3`.

**Properties proved (depth 20):**
- **P1 decode_consistent:** `addr[31:16]` unambiguously maps to slave index (combinational, `always @(*)`)
- **P2 grant_stable:** `wr_grant[s]` holds constant while `wr_busy[s]` is asserted (clocked)
- **P3 bvalid_routing:** BVALID/RVALID only reaches the master that was granted (combinational)
- **P4 awvalid_stable:** (assume) master holds AWVALID until AWREADY — models AXI protocol obligation

---

### Step 11 — Verification Expansion (Full Coverage)
**Commit:** `5c9248e`

#### cocotb `axi_sram` — expanded to 10/10
New tests added:
- `address_boundary`: word 0 (addr=0x0) and word at 0x3FC both accessible
- `all_byte_strobes`: each of strb=0x1/0x2/0x4/0x8 written to a cleared word, upper bytes verified unmodified
- `null_strobe`: write with strb=0x0 must not modify any byte of stored data
- `random_stress`: 50 random (addr, data) pairs written then read back (seed=42, reproducible)

#### cocotb `axi_apb_bridge` — expanded to 10/10
New tests added:
- `long_pready_wait`: APB slave holds PREADY low 7 extra cycles — exercises bridge FSM patience
- `multi_cycle_ready_read`: 3-cycle PREADY wait on the read path
- `read_slverr`: PSLVERR=1 on read → RRESP=2, isolated from write path
- `alternating_rw_stress`: interleaved write+read to 4 different addresses

#### UVM — expanded to 4 tests, 19 scoreboard checks
New tests added:
- **TEST 3 (no-contention):** M0→S0, M1→S1, M2→S2 all forked simultaneously — no arbitration needed, verifies full-throughput parallel path
- **TEST 4 (back-to-back single master):** M0 issues 4 consecutive writes then 4 reads to S0 — verifies arbiter re-grant on consecutive transactions

#### Formal — 6 properties, depth 40
New properties added:
- **P5 slave_idle_no_valid:** when `wr_busy[s]=0`, slave s sees no `s_awvalid` or `s_wvalid`; when `rd_busy[s]=0`, slave s sees no `s_arvalid`. Directly verifies the write/read channel mux default (else) branches.
- **P6 awready_implies_busy:** AWREADY can only reach master m when some slave s has `wr_busy[s]=1 && wr_grant[s]==m`. Verifies the master-side AW/W response mux produces no spurious handshakes.

BMC depth increased from 20 → 40 to cover multi-transaction sequences.

**All 6 properties proved.**

---

## Current Status

| Phase | Description | Tests | Status |
|---|---|---|---|
| Phase 0 | Toolchain setup | D flip-flop smoke test | COMPLETE |
| Phase 1 | RV32I 5-stage pipeline | 22/22 cocotb | COMPLETE |
| Phase 2 | L1 data cache | 18/18 cocotb | COMPLETE |
| Phase 1+2 | Cache stall integration | (covered by Phase 1+2 tests) | COMPLETE |
| Phase 3 | AXI4 crossbar + APB bridge | 10/10 + 10/10 cocotb, 19/19 UVM checks, 6/6 formal | COMPLETE |
| Phase 4 | 4×4 systolic MAC array | — | NOT STARTED |
| Phase 5 | Full SoC integration | — | NOT STARTED |
| Phase 6 | OpenLane synthesis (Sky130) | — | NOT STARTED |
| Phase 7 | README + interview prep | — | NOT STARTED |

---

## Known Gaps / Pre-Integration Work Required

Before Phase 5 integration (`soc_top.sv`) can connect all blocks:

1. **AXI4-full vs AXI4-Lite mismatch:** `cache_top.sv` uses full AXI4 burst signals (`awlen`, `awsize`, `awburst`, `wlast`, `rlast`) for 4-word cache line fills. `axi4_crossbar.sv` is AXI4-Lite only. Resolution options: (a) write a burst-splitter adapter between cache and crossbar, or (b) redesign `cache_controller.sv` to issue 4 single-beat AXI4-Lite transactions instead of one burst.

2. **No instruction memory AXI path:** `riscv_core.sv` exposes `imem_addr_o` / `imem_rdata_i` as direct wires. The CPU has no way to fetch instructions via the crossbar. A separate instruction fetch unit (IFU) with an AXI4-Lite master port is needed, or IMEM can remain a simple synchronous ROM directly wired to the core.

3. **Reset polarity mismatch:** `riscv_core.sv` and `cache_top.sv` use active-HIGH `rst`. `axi4_crossbar.sv` uses active-LOW `rst_n`. An inverter or standardized reset strategy is needed in `soc_top.sv`.

---

*Document generated: 2026-05-15*
