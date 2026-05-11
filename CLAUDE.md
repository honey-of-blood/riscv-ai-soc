# RISC-V AI SoC — Project Context

## Goal
Portfolio project: RV32I 5-stage pipeline → L1 cache → AXI4 crossbar → systolic array AI accelerator.
Document: `docs/SoC_Blueprint_FromScratch.docx`

## Environment
- Python venv: `/home/bhaavesh/projects/vlsi_projects/soc/.venv` (activate before running tests)
- Simulator: Icarus Verilog 12.0
- Verification: cocotb 2.0.1 — import from `cocotb_tools.runner` (NOT `cocotb.runner`)
- Test runner: `phase1_riscv_core/tb/run_tests.py`
- Git identity: `git -c user.email="pltech@powerlinksworld.com" -c user.name="Bhaavesh"`

## Icarus Verilog Compatibility Rules
1. No bit-selects inside `always_comb` — extract to `assign` outside the block:
   ```sv
   logic [4:0] shamt;
   assign shamt = b[4:0];   // then use shamt inside always_comb
   ```
2. Signed casts must also be `assign` outside `always_comb`:
   ```sv
   logic signed [31:0] a_sgn;
   assign a_sgn = a;        // then use a_sgn in comparisons
   ```

## cocotb Rules
- Timer: `await Timer(N, unit="ns")` — singular `unit=`, NOT `units=`
- Combinational probing: use `Timer(1, unit="ns")` after driving inputs (not ReadOnly phase)
- All RTL must have `` `timescale 1ns/1ps `` (prevents precision warning)

## Phase 1 — RV32I Pipeline (current)

### Completed RTL (`phase1_riscv_core/rtl/`)
| File | Description |
|------|-------------|
| `alu.sv` | 10-op ALU; shamt extracted via assign |
| `reg_file.sv` | 32×32-bit, dual async read, sync write, sync reset, x0 hardwired |
| `imm_gen.sv` | All 5 immediate types; precomputed as assigns, case selects |
| `fetch_stage.sv` | PC register, branch mux, async imem interface |
| `pipeline_reg_IF_ID.sv` | NOP=32'h0000_0013 on rst/flush; hold on stall |
| `fetch_if_id_wrap.sv` | Sim wrapper: fetch_stage + pipeline_reg_IF_ID |
| `decode_stage.sv` | Purely combinational; instantiates imm_gen; external reg_file |
| `pipeline_reg_ID_EX.sv` | flush→NOP (zero all); stall→hold |
| `decode_id_ex_wrap.sv` | Sim wrapper: decode_stage + pipeline_reg_ID_EX |
| `execute_stage.sv` | Forwarding muxes, ALU, branch/jump evaluation — combinational |
| `pipeline_reg_EX_MEM.sv` | No flush/stall; carries alu_result, rs2_fwd, pc_plus4, imm |

### Still To Write
- `memory_stage.sv` + `pipeline_reg_MEM_WB.sv`
- `writeback_stage.sv`
- `hazard_unit.sv` (load-use stall + branch flush)
- `forwarding_unit.sv`
- `riscv_core.sv` (top-level integration)
- Wrappers + cocotb tests for execute, memory, writeback
- `test_hazards.py`, `test_load_use.py`, `test_bubblesort.py`

### Key Encodings

**ALU control (must match alu.sv):**
```
ADD=0000  SUB=0001  AND=0010  OR=0011   XOR=0100
SLL=0101  SRL=0110  SRA=0111  SLT=1000  SLTU=1001
```

**wb_sel:**
```
WB_ALU=00  WB_MEM=01  WB_PC4=10  WB_IMM=11
```

**Forwarding select (fwd_a/fwd_b):**
```
00=ID/EX data  01=EX/MEM alu_result  10=MEM/WB writeback
```

**Control signal intent:**
- `alu_src_a`: 0=rs1, 1=PC (AUIPC and JAL use PC as ALU A)
- `alu_src_b`: 0=rs2, 1=imm
- JAL: alu_src_a=1 → target=PC+imm (ALU computes it)
- JALR: alu_src_a=0 → target=(rs1+imm)&~1 (bit 0 cleared in execute_stage)
- Branch condition: evaluated directly on forwarded rs1/rs2, not through ALU

### Pipeline Register Flush/Stall Policy
- IF/ID: flush→NOP instruction (32'h0000_0013); stall→hold
- ID/EX: flush→zero all control signals; stall→hold
- EX/MEM: no flush/stall (branch resolved before this stage commits)
- MEM/WB: no flush/stall

### Branch Handling (static not-taken)
- 2-cycle penalty when branch taken
- Hazard unit flushes IF/ID and ID/EX when branch_taken arrives from execute stage
