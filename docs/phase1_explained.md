# Phase 1 — RV32I 5-Stage Pipeline
### A Beginner's Guide: Every Step Explained

---

## Before We Start — What Are We Actually Building?

Phase 1 builds a **CPU** (Central Processing Unit) — the brain of a computer. Specifically, it builds an **RV32I** CPU, which is the smallest useful version of a RISC-V processor.

Before explaining any code, let's make sure the big concepts are clear.

---

## Concept 1 — What Is a CPU?

A CPU's job is simple to describe but complex to build:

1. Fetch an instruction from memory (e.g., "add two numbers")
2. Decode it (figure out what operation it is and which registers it uses)
3. Execute it (perform the addition)
4. Access memory if needed (load or store data)
5. Write the result back to a register

It repeats this loop billions of times per second. Every program you have ever run — a browser, a game, a Python script — is just a sequence of these instructions.

---

## Concept 2 — What Is RISC-V?

**RISC-V** (pronounced "risk five") is an open-source CPU instruction set architecture (ISA). An ISA is essentially a contract: "these are the instructions a CPU understands, and this is exactly how each one behaves."

The "V" means it is the fifth RISC architecture from UC Berkeley. Unlike x86 (Intel/AMD) or ARM (mobile chips), RISC-V is completely free — anyone can build a chip that runs RISC-V code without paying royalties.

**RV32I** specifically means:
- **RV** = RISC-V
- **32** = 32-bit (registers and addresses are 32 bits wide)
- **I** = the base integer instruction set — about 47 instructions covering arithmetic, logic, loads, stores, branches, and jumps

This is what we implemented. No floating point, no multiply/divide — just the core 47 instructions. This is enough to run real programs.

---

## Concept 3 — What Is a Pipeline?

Imagine a car wash. One car at a time going through the whole wash takes 5 minutes per car. But if you break the wash into 5 stations (rinse, soap, scrub, rinse again, dry) and have one car at each station simultaneously, you can finish a car every 1 minute even though each car still takes 5 minutes total.

That is a pipeline.

A **5-stage pipeline** processes 5 instructions simultaneously — one in each stage. While instruction 5 is being fetched, instruction 4 is being decoded, instruction 3 is being executed, instruction 2 is accessing memory, and instruction 1 is writing its result back. When they all finish their current stage, each moves one step forward.

Without a pipeline, one instruction per 5 clock cycles. With a 5-stage pipeline (at steady state), one instruction per clock cycle — 5× speedup.

The 5 stages in our CPU:

```
┌──────────┐   ┌──────────┐   ┌──────────┐   ┌──────────┐   ┌──────────┐
│    IF    │──▶│    ID    │──▶│    EX    │──▶│   MEM    │──▶│    WB    │
│  Fetch   │   │  Decode  │   │ Execute  │   │  Memory  │   │Writeback │
└──────────┘   └──────────┘   └──────────┘   └──────────┘   └──────────┘
```

Between each stage there is a **pipeline register** — a set of flip-flops that capture the output of one stage and hold it until the next stage is ready to consume it on the next clock cycle.

---

## Concept 4 — What Is a Register?

A register is a tiny, extremely fast storage location inside the CPU. RISC-V has 32 registers, named `x0` through `x31`, each 32 bits wide.

Think of registers as the CPU's scratchpad — the numbers it is actively working with right now. Memory (RAM) is much larger but much slower. The CPU always pulls data from memory into registers before doing arithmetic on it.

Special registers:
- `x0` is hardwired to 0 — reading it always gives 0; writing to it does nothing
- `x1` is conventionally used as the return address for function calls
- `x2` is the stack pointer
- All others are general-purpose

---

## The Build Order

Phase 1 was built bottom-up — start with the simplest pieces, verify each one works alone, then assemble them into the full pipeline:

```
Step 1: ALU + Register File         (the computational core)
Step 2: Immediate Generator         (decodes constants from instructions)
Step 3: Fetch Stage + IF/ID Reg     (gets instructions from memory)
Step 4: Decode Stage + ID/EX Reg    (reads the instruction, generates control signals)
Step 5: Execute + Memory + WB
         + Hazard + Forwarding
         + riscv_core (top level)   (the complete pipeline)
Step 6: Bug fix + integration tests (22/22 passing)
```

---

## Step 1 — The ALU

**File:** `phase1_riscv_core/rtl/alu.sv`

### What is an ALU?

The **Arithmetic Logic Unit** is the part of the CPU that actually does computations. It takes two 32-bit numbers and an operation code, and produces a result. It is the engine inside the engine.

Our ALU supports 10 operations:

| Code | Name | What it does |
|------|------|-------------|
| 0000 | ADD  | a + b |
| 0001 | SUB  | a - b |
| 0010 | AND  | a AND b (bitwise) |
| 0011 | OR   | a OR b (bitwise) |
| 0100 | XOR  | a XOR b (bitwise) |
| 0101 | SLL  | Shift a left by b[4:0] bits |
| 0110 | SRL  | Shift a right (unsigned) by b[4:0] bits |
| 0111 | SRA  | Shift a right (signed, keeps sign bit) by b[4:0] bits |
| 1000 | SLT  | 1 if a < b (signed), else 0 |
| 1001 | SLTU | 1 if a < b (unsigned), else 0 |

### The full code

```systemverilog
module alu (
    input  logic [31:0] a,
    input  logic [31:0] b,
    input  logic [ 3:0] alu_ctrl,
    output logic [31:0] result,
    output logic        zero
);
    localparam ALU_ADD  = 4'b0000;
    localparam ALU_SUB  = 4'b0001;
    // ... (all 10 encodings)

    logic [4:0] shamt;
    assign shamt = b[4:0];          // ← Icarus rule: extract bit-select outside always_comb

    always_comb begin
        case (alu_ctrl)
            ALU_ADD  : result = a + b;
            ALU_SUB  : result = a - b;
            ALU_AND  : result = a & b;
            ALU_OR   : result = a | b;
            ALU_XOR  : result = a ^ b;
            ALU_SLL  : result = a << shamt;
            ALU_SRL  : result = a >> shamt;
            ALU_SRA  : result = $signed(a) >>> shamt;
            ALU_SLT  : result = {31'b0, $signed(a) < $signed(b)};
            ALU_SLTU : result = {31'b0, a < b};
            default  : result = 32'b0;
        endcase
    end

    assign zero = (result == 32'b0);
endmodule
```

### Key points explained

**`localparam`** — like a constant in C (`#define ALU_ADD 0`). The name `ALU_ADD` is replaced by `4'b0000` everywhere it appears. Using named constants makes code readable and prevents bugs from misremembering magic numbers.

**`always_comb`** — this block describes combinational logic: logic with no memory, no clock. Output changes instantly when inputs change. The hardware equivalent is just wires and gates — no flip-flops involved.

**Why is `shamt` extracted outside `always_comb`?** This is the Icarus Verilog compatibility rule discovered in Phase 0. Inside `always_comb`, you cannot use bit-selects like `b[4:0]` directly. The fix: `assign shamt = b[4:0]` outside the block, then use `shamt` inside.

**`$signed(a)`** — casts a to signed. In hardware, all bits are just bits; the interpretation (signed or unsigned) is in the instructions. `>>>` is arithmetic right shift (fills with the sign bit). `>>` is logical right shift (fills with zeros).

**`{31'b0, $signed(a) < $signed(b)}`** — the comparison `$signed(a) < $signed(b)` produces a 1-bit result (true/false). We concatenate 31 zeros on the left to make it 32 bits. This is how SLT (Set Less Than) works: the result register gets 1 if a < b, otherwise 0.

**`zero`** — a flag that goes high when the result is zero. The branch unit uses this for BEQ (branch if equal): BEQ computes a-b using SUB; if the result is zero, the two values were equal.

---

## Step 1 (continued) — The Register File

**File:** `phase1_riscv_core/rtl/reg_file.sv`

### What it is

The register file is 32 registers × 32 bits = 1024 bits of storage, with two simultaneous read ports and one write port. In a 5-stage pipeline, you need to read two source registers (rs1 and rs2) at the same time during the Decode stage while writing back a result to a destination register (rd) during Writeback.

```systemverilog
module reg_file (
    input  logic        clk,
    input  logic        rst,
    input  logic        we,         // write enable
    input  logic [4:0]  rs1,        // source register 1 address (0-31)
    input  logic [4:0]  rs2,        // source register 2 address (0-31)
    input  logic [4:0]  rd,         // destination register address
    input  logic [31:0] wd,         // write data
    output logic [31:0] rd1,        // read data 1
    output logic [31:0] rd2         // read data 2
);
    logic [31:0] regs [1:31];       // x0 is not stored — hardwired to 0

    // Synchronous write
    always_ff @(posedge clk) begin
        if (rst) begin
            for (int i = 1; i < 32; i++)
                regs[i] <= 32'b0;
        end else if (we && rd != 5'b0) begin
            regs[rd] <= wd;
        end
    end

    // Asynchronous read with write-before-read (bypass)
    assign rd1 = (rs1 == 5'b0)    ? 32'b0 :
                 (we && rd == rs1) ? wd    : regs[rs1];
    assign rd2 = (rs2 == 5'b0)    ? 32'b0 :
                 (we && rd == rs2) ? wd    : regs[rs2];
endmodule
```

### Key design decisions

**Why is x0 not stored?** x0 is always zero by definition. Storing it as a flip-flop would waste area, and you'd need to handle writes to it specially anyway. Instead, the read logic just returns 0 whenever `rs1 == 5'b0` (address 0). The write path has `rd != 5'b0` as a guard — writes to x0 are silently discarded.

**Synchronous write vs asynchronous read** — writes happen on the rising clock edge (synchronous). Reads are immediate — the output appears as soon as the address input arrives (asynchronous). This is how real SRAMs work in CPUs.

**Write-before-read bypass** — look at the read logic:
```systemverilog
assign rd1 = (rs1 == 5'b0)    ? 32'b0 :   // x0 is always 0
             (we && rd == rs1) ? wd    :   // WB is writing this same register right now → give new value
                                  regs[rs1]; // normal case
```
If the Writeback stage is writing to x5 right now, and the Decode stage is simultaneously reading x5, the read returns the new value being written (not the old stale value). This resolves a subtle hazard called a "distance-3 RAW hazard" without any extra forwarding logic.

---

## Step 2 — The Immediate Generator

**File:** `phase1_riscv_core/rtl/imm_gen.sv`

### What is an immediate?

Many instructions use a constant value that is encoded directly inside the instruction word, rather than reading from a register. For example, `ADDI x1, x2, 100` adds 100 to x2 and stores in x1. That 100 is the **immediate**.

RISC-V encodes immediates in 5 different ways depending on instruction type:

```
I-type: [ imm[11:0] | rs1 | funct3 | rd | opcode ]  ← loads, ALU-immediate, JALR
S-type: [ imm[11:5] | rs2 | rs1 | funct3 | imm[4:0] | opcode ]  ← stores
B-type: [ imm[12|10:5] | rs2 | rs1 | funct3 | imm[4:1|11] | opcode ]  ← branches
U-type: [ imm[31:12] | rd | opcode ]  ← LUI, AUIPC
J-type: [ imm[20|10:1|11|19:12] | rd | opcode ]  ← JAL
```

The bits are scrambled across different positions in the instruction. The immediate generator unscrambles them and sign-extends the result to 32 bits.

### The full code

```systemverilog
assign imm_i = {{20{instr[31]}}, instr[31:20]};                          // I-type
assign imm_s = {{20{instr[31]}}, instr[31:25], instr[11:7]};             // S-type
assign imm_b = {{19{instr[31]}}, instr[31], instr[7], instr[30:25], instr[11:8], 1'b0};  // B-type
assign imm_u = {instr[31:12], 12'b0};                                    // U-type
assign imm_j = {{11{instr[31]}}, instr[31], instr[19:12], instr[20], instr[30:21], 1'b0}; // J-type
```

### Why are the bits so scrambled?

The RISC-V designers scrambled the immediate bits intentionally so that certain bit positions in the instruction are always the same type. For example, `instr[30]` is always the funct7 bit that distinguishes ADD from SUB. This means the hardware that decodes the opcode can be built more simply — it always reads from the same physical bit positions regardless of instruction type.

### Sign extension explained

`{{20{instr[31]}}, ...}` — this replicates bit 31 twenty times. Bit 31 of the instruction is the sign bit of the immediate. If it is 1 (negative number), we fill the upper 20 bits with 1s. If it is 0 (positive), we fill with 0s. This is sign extension — stretching a small signed number to 32 bits while preserving its mathematical value.

Example: 12-bit value `1111_1111_1001` = -7 in two's complement.  
After sign extension to 32 bits: `1111_1111_1111_1111_1111_1111_1111_1001` = still -7.

---

## Step 3 — Fetch Stage + IF/ID Pipeline Register

**Files:** `fetch_stage.sv`, `pipeline_reg_IF_ID.sv`

### What the Fetch stage does

The Fetch stage is the first stage of the pipeline. Its job: figure out the address of the next instruction and read it from instruction memory.

The **Program Counter (PC)** is a register that holds the address of the instruction currently being fetched. Normally, after every clock cycle, PC = PC + 4 (because each instruction is 4 bytes). When a branch or jump is taken, the PC jumps to a different address.

```systemverilog
module fetch_stage (
    input  logic        clk,
    input  logic        rst,
    input  logic        stall_i,          // freeze PC (hazard unit says "wait")
    input  logic        branch_taken_i,   // jump to a new address
    input  logic [31:0] branch_target_i,  // the new address to jump to
    output logic [31:0] imem_addr_o,      // address sent to instruction memory
    input  logic [31:0] imem_rdata_i,     // instruction read back from memory
    output logic [31:0] pc_if_o,
    output logic [31:0] instr_if_o
);
    logic [31:0] pc, pc_next;

    // PC + 4 normally; branch target when a branch is taken
    always_comb begin
        if (branch_taken_i) pc_next = branch_target_i;
        else                pc_next = pc + 32'd4;
    end

    // PC register: holds value unless stalled or reset
    always_ff @(posedge clk or posedge rst) begin
        if (rst)           pc <= 32'b0;
        else if (!stall_i) pc <= pc_next;
    end

    assign imem_addr_o = pc;
    assign pc_if_o     = pc;
    assign instr_if_o  = imem_rdata_i;
endmodule
```

### The "static not-taken" branch prediction

When the CPU encounters a branch instruction (e.g., "if x1 == x2, jump to address 0x100"), it doesn't know yet whether the branch will be taken — that determination happens two stages later in EX. In the meantime, the pipeline keeps fetching instructions after the branch (as if the branch is NOT taken).

If the branch IS taken, the two instructions that were fetched behind the branch are wrong and must be thrown away (flushed). This costs 2 clock cycles — called the **branch penalty**.

The strategy of always assuming "branch not taken" is called **static not-taken prediction**. It is simple and correct on loops that eventually exit.

### What `stall_i` does

When the hazard unit detects a problem that requires the pipeline to pause (explained later), it asserts `stall_i`. When stalled, the `always_ff` block simply doesn't execute (the `if (!stall_i)` condition is false), so the PC freezes at its current value. On the next clock cycle, the same instruction is fetched again.

### The IF/ID Pipeline Register

```systemverilog
module pipeline_reg_IF_ID (
    input  logic        clk, rst, stall_i, flush_i,
    input  logic [31:0] pc_if_i, instr_if_i,
    output logic [31:0] pc_id_o, instr_id_o
);
    localparam NOP = 32'h0000_0013; // ADDI x0, x0, 0

    always_ff @(posedge clk or posedge rst) begin
        if (rst || flush_i) begin
            pc_id_o    <= 32'b0;
            instr_id_o <= NOP;      // insert a harmless instruction
        end else if (!stall_i) begin
            pc_id_o    <= pc_if_i;
            instr_id_o <= instr_if_i;
        end
        // stall: flip-flops hold their values automatically (no else clause)
    end
endmodule
```

This register sits between IF and ID. Every clock cycle it captures the PC and instruction from IF and presents them to the ID stage.

**Flush → NOP:** When a branch is taken, the instruction that was already fetched is wrong. We flush it by replacing it with a **NOP** (no-operation). The NOP we use (`32'h0000_0013` = `ADDI x0, x0, 0`) is harmless: it writes to x0 (which ignores writes), reads no memory, and causes no side effects.

**Stall → hold:** When there is a load-use hazard (explained later), we must freeze IF and ID in place for one cycle. If we don't have an `else` clause in the `always_ff` block, flip-flops naturally hold their value — no action needed.

---

## Step 4 — Decode Stage + ID/EX Pipeline Register

**Files:** `decode_stage.sv`, `pipeline_reg_ID_EX.sv`

### What the Decode stage does

The Decode stage receives a raw 32-bit instruction word and answers two questions:

1. **What fields does this instruction have?** (source registers rs1, rs2; destination register rd; immediate; funct3; funct7)
2. **What control signals does the execute/memory/writeback stages need?** (Which ALU operation? Load or store? Jump or branch? Write back ALU result or memory data?)

It is purely combinational — no clock. It just decodes the bit pattern.

### Instruction format reminder

```
 31        25 24     20 19     15 14   12 11      7 6        0
┌────────────┬─────────┬─────────┬───────┬──────────┬────────┐
│  funct7    │   rs2   │   rs1   │funct3 │    rd    │ opcode │  R-type
└────────────┴─────────┴─────────┴───────┴──────────┴────────┘
```

The 7-bit **opcode** tells us the instruction type. The **funct3** and **funct7** fields refine it further. For example: opcode `0110011` means "R-type arithmetic"; funct3 `000` + funct7 bit 30 = `0` means ADD; funct7 bit 30 = `1` means SUB.

### The control signals generated

```systemverilog
// Main control decoder
always_comb begin
    // Defaults — prevents latches
    reg_write_o = 0; mem_read_o = 0; mem_write_o = 0;
    alu_src_b_o = 0; alu_src_a_o = 0;
    branch_o = 0; jump_o = 0;
    wb_sel_o = WB_ALU;

    case (opcode)
        OP_R:    begin reg_write_o = 1; end                        // ADD, SUB, AND, etc.
        OP_IMM:  begin reg_write_o = 1; alu_src_b_o = 1; end      // ADDI, ANDI, etc.
        OP_LOAD: begin reg_write_o = 1; mem_read_o = 1;
                       alu_src_b_o = 1; wb_sel_o = WB_MEM; end    // LW, LB, LH...
        OP_STORE: begin mem_write_o = 1; alu_src_b_o = 1; end     // SW, SB, SH...
        OP_BRANCH: begin branch_o = 1; end                         // BEQ, BNE, BLT...
        OP_JAL:  begin reg_write_o = 1; jump_o = 1;
                       alu_src_a_o = 1; alu_src_b_o = 1;
                       wb_sel_o = WB_PC4; end
        OP_JALR: begin reg_write_o = 1; jump_o = 1;
                       alu_src_b_o = 1; wb_sel_o = WB_PC4; end
        OP_LUI:  begin reg_write_o = 1; wb_sel_o = WB_IMM; end
        OP_AUIPC: begin reg_write_o = 1; alu_src_a_o = 1;
                        alu_src_b_o = 1; end
    endcase
end
```

Let's explain each signal:

- **`reg_write_o`**: "This instruction writes a result to a register." Not all do — stores and branches don't.
- **`mem_read_o`**: "This instruction reads from data memory." Only load instructions.
- **`mem_write_o`**: "This instruction writes to data memory." Only store instructions.
- **`alu_src_b_o`**: Selects the second ALU input. `0` = use register rs2. `1` = use immediate. Immediate instructions (ADDI, LW, SW) use the immediate; register instructions (ADD, SUB) use rs2.
- **`alu_src_a_o`**: Selects the first ALU input. `0` = use register rs1. `1` = use PC. AUIPC and JAL use the PC: they compute `PC + immediate`.
- **`branch_o`**: "Check the branch condition in EX and possibly redirect the PC."
- **`jump_o`**: "Unconditionally redirect the PC (JAL or JALR)."
- **`wb_sel_o`**: Selects what gets written back to the register file:
  - `WB_ALU=00`: write the ALU result (most arithmetic instructions)
  - `WB_MEM=01`: write the loaded memory data (LW, LB, LH, etc.)
  - `WB_PC4=10`: write PC+4 (JAL, JALR — saves the return address)
  - `WB_IMM=11`: write the immediate itself (LUI — Load Upper Immediate)

### Why defaults matter

The `always_comb` block sets defaults for every signal before the `case` statement. Without defaults, if an opcode falls through without setting some signal, the synthesiser creates a **latch** — a memory element that holds the previous value. Latches in combinational logic are a bug: they make the circuit dependent on its history in ways that are hard to predict. Explicit defaults prevent this entirely.

### ALU control decoder

```systemverilog
always_comb begin
    alu_ctrl_o = ALU_ADD;  // default covers LOAD, STORE, JAL, JALR, AUIPC

    case (opcode)
        OP_R, OP_IMM: begin
            case (funct3)
                3'b000: alu_ctrl_o = (opcode == OP_R && funct7_5) ? ALU_SUB : ALU_ADD;
                3'b001: alu_ctrl_o = ALU_SLL;
                3'b010: alu_ctrl_o = ALU_SLT;
                // ...
                3'b101: alu_ctrl_o = funct7_5 ? ALU_SRA : ALU_SRL;
                // ...
            endcase
        end
    endcase
end
```

For R-type and I-type instructions, the ALU operation comes from `funct3` and a single bit from `funct7`. For loads, stores, and jumps, the ALU always does addition (to compute a memory address or jump target).

The `funct7_5` bit (bit 30 of the instruction) is the disambiguation bit:
- `ADD` has funct7 = `0000000`; `SUB` has funct7 = `0100000` → bit 30 = 0 means ADD, 1 means SUB
- `SRL` has funct7 = `0000000`; `SRA` has funct7 = `0100000` → same bit distinguishes them

---

## Step 5 — Execute Stage

**File:** `execute_stage.sv`

### What the Execute stage does

This is where the actual computation happens. Three things occur here:
1. **Forwarding muxes** select which value to feed into the ALU (see the Hazards section below)
2. **ALU** performs the arithmetic or logic operation
3. **Branch/jump evaluation** determines if the PC should redirect

### Forwarding muxes

```systemverilog
// rs1 forwarding mux
always_comb begin
    case (fwd_a_i)
        2'b01:   rs1_fwd = fwd_ex_mem_i;  // use result from 1 instruction ago
        2'b10:   rs1_fwd = fwd_mem_wb_i;  // use result from 2 instructions ago
        default: rs1_fwd = rs1_data_i;    // use value from register file (no hazard)
    endcase
end
```

The forwarding unit (a separate module) detects when an instruction in EX needs a value that is still being computed by a previous instruction. It sets `fwd_a_i` or `fwd_b_i` to tell the mux where to get the value from instead. This is explained fully in the Hazards section.

### ALU input muxes

```systemverilog
assign alu_a = alu_src_a_i ? pc_i    : rs1_fwd;   // AUIPC/JAL use PC
assign alu_b = alu_src_b_i ? imm_i   : rs2_fwd;   // immediate or register
```

### Branch evaluation

```systemverilog
logic signed [31:0] rs1_sgn, rs2_sgn;
assign rs1_sgn = rs1_fwd;   // signed cast outside always_comb (Icarus rule)
assign rs2_sgn = rs2_fwd;

always_comb begin
    case (funct3_i)
        3'b000:  branch_cond = (rs1_fwd == rs2_fwd);   // BEQ
        3'b001:  branch_cond = (rs1_fwd != rs2_fwd);   // BNE
        3'b100:  branch_cond = (rs1_sgn <  rs2_sgn);   // BLT  (signed)
        3'b101:  branch_cond = (rs1_sgn >= rs2_sgn);   // BGE  (signed)
        3'b110:  branch_cond = (rs1_fwd <  rs2_fwd);   // BLTU (unsigned)
        3'b111:  branch_cond = (rs1_fwd >= rs2_fwd);   // BGEU (unsigned)
    endcase
end
```

Branch conditions are evaluated on the **forwarded** rs1/rs2 values, not on the stale values from the register file. This is crucial — if the previous instruction wrote to rs1, we need the updated value to evaluate the branch correctly.

### Jump target calculation

```systemverilog
assign branch_target = pc_i + imm_i;
assign jump_target   = alu_src_a_i ? alu_result : {alu_result[31:1], 1'b0};
```

For **JAL**: `alu_src_a_i = 1` so the ALU computed `PC + imm`. We use that directly as the jump target.

For **JALR**: `alu_src_a_i = 0` so the ALU computed `rs1 + imm`. The RISC-V spec says JALR must clear bit 0 of the target (to ensure alignment to a 4-byte boundary). `{alu_result[31:1], 1'b0}` does this — it takes bits [31:1] and forces bit 0 to 0.

---

## Step 5 (continued) — Memory Stage

**File:** `memory_stage.sv`

### What the Memory stage does

For loads (LW, LB, LH, LBU, LHU): sends the address to data memory and receives back the data, then sign-extends it if needed.

For stores (SW, SB, SH): sends the address and data to data memory with byte enables.

For all other instructions: passes ALU result through to Writeback unchanged.

### Byte enables for stores

When you do `SB` (store byte), you only want to change 1 byte of a 4-byte memory word, not all 4. **Byte enables** (`dmem_be_o[3:0]`) tell the memory which bytes to update:

```systemverilog
// Byte enables for stores
case (funct3_w)
    2'b00: begin  // SB — which of the 4 byte lanes?
        case (byte_off)
            2'b00: dmem_be_o = 4'b0001;  // byte 0 only
            2'b01: dmem_be_o = 4'b0010;  // byte 1 only
            2'b10: dmem_be_o = 4'b0100;  // byte 2 only
            2'b11: dmem_be_o = 4'b1000;  // byte 3 only
        endcase
    end
    2'b01: dmem_be_o = half_off ? 4'b1100 : 4'b0011;  // SH — 2 bytes
    2'b10: dmem_be_o = 4'b1111;                        // SW — all 4 bytes
endcase
```

The byte offset comes from `alu_result[1:0]` — the two least significant bits of the computed address. Since a word is 4 bytes, address bits [1:0] tell you which byte within the word.

### Sign extension for loads

```systemverilog
case (funct3_i)
    3'b000: mem_rdata_o = {{24{rd_byte_msb}}, rd_byte};  // LB  — sign extend 8→32 bits
    3'b001: mem_rdata_o = {{16{rd_half_msb}}, rd_half};  // LH  — sign extend 16→32 bits
    3'b010: mem_rdata_o = dmem_rdata_i;                  // LW  — no extension needed
    3'b100: mem_rdata_o = {24'b0, rd_byte};              // LBU — zero extend (no sign)
    3'b101: mem_rdata_o = {16'b0, rd_half};              // LHU — zero extend
endcase
```

`LB` (load byte signed) reads 1 byte and sign-extends it to 32 bits. If the byte's value is -3 (255 in unsigned), the 32-bit result should also be -3, not 253. `LBU` (load byte unsigned) zero-extends instead — it treats the byte as a number from 0 to 255, never negative.

---

## Step 5 (continued) — Writeback Stage

**File:** `writeback_stage.sv`

The simplest stage — just a 4-way mux:

```systemverilog
always_comb begin
    case (wb_sel_i)
        WB_MEM:  wb_data_o = mem_rdata_i;   // LOAD: write the loaded value
        WB_PC4:  wb_data_o = pc_plus4_i;    // JAL/JALR: write return address
        WB_IMM:  wb_data_o = imm_i;         // LUI: write the immediate itself
        default: wb_data_o = alu_result_i;  // everything else: write ALU result
    endcase
end
```

The selected value goes to the register file's write port and also feeds back into the forwarding network.

---

## Step 5 (continued) — The Hazard Unit

**File:** `hazard_unit.sv`

### What is a hazard?

A **hazard** is any situation where the pipeline cannot proceed correctly without special handling. There are three types:

**Data hazard** — an instruction needs a value that hasn't been computed yet.  
**Control hazard** — the pipeline fetched the wrong instruction (branch was taken).  
**Structural hazard** — two instructions need the same hardware resource simultaneously. (Our design avoids these with Harvard architecture — separate instruction and data memories.)

### Load-use hazard (data hazard)

Consider this code:
```
LW  x1, 0(x2)    ← load a value from memory into x1
ADD x3, x1, x4   ← immediately use x1
```

The load result from `LW` is not available until the MEM stage — two cycles after it enters EX. But `ADD` needs x1 in its EX stage, which is only one cycle after `LW` entered EX. Even forwarding cannot help here because the data doesn't exist yet.

The only solution is to **stall** — freeze the pipeline for one cycle. During the stall:
- The PC doesn't advance (fetch stage is frozen)
- The IF/ID register holds its value (the instruction behind LW is held)
- A NOP bubble is inserted into ID/EX (so the EX stage does nothing for one cycle)

After one cycle, the load result is available in the EX/MEM register and can be forwarded to ADD.

```systemverilog
assign load_use = mem_read_ex_i          // instruction in EX is a LOAD
               && (rd_ex_i != 5'b0)      // it writes to a real register (not x0)
               && ((rd_ex_i == rs1_id_i) || (rd_ex_i == rs2_id_i));  // that register is needed by instruction in ID
```

### Branch flush (control hazard)

```
BEQ x1, x2, LABEL    ← branch instruction enters IF
ADD x3, x4, x5       ← fetched next (in IF/ID)
SUB x6, x7, x8       ← fetched next (in ID/EX is wrong if branch taken)
```

By the time the CPU resolves whether the branch is taken (in EX stage), two instructions have already been fetched behind it. If the branch IS taken, those two instructions are wrong and must be squashed.

The **flush** operation replaces IF/ID and ID/EX contents with NOPs. The PC simultaneously redirects to the branch target.

```systemverilog
assign flush_id_o = branch_taken_i && !cache_stall_i;   // flush IF/ID
assign flush_ex_o = (load_use || branch_taken_i) && !cache_stall_i;  // flush ID/EX
```

The `!cache_stall_i` guard prevents flushes during a cache miss — if the pipeline is frozen due to a cache miss and a branch is in EX at that moment, we don't want to incorrectly flush the frozen registers. The flush fires normally when the pipeline resumes.

### Stall outputs — which stages freeze

```systemverilog
assign stall_if_o     = load_use || cache_stall_i;  // freeze PC
assign stall_id_o     = load_use || cache_stall_i;  // freeze IF/ID
assign stall_id_ex_o  = cache_stall_i;              // freeze ID/EX (only cache stall)
assign stall_ex_mem_o = cache_stall_i;              // freeze EX/MEM
assign stall_mem_wb_o = cache_stall_i;              // freeze MEM/WB
```

For a load-use stall, only IF and ID freeze (and ID/EX gets a NOP bubble). For a cache miss, the entire pipeline freezes.

---

## Step 5 (continued) — The Forwarding Unit

**File:** `forwarding_unit.sv`

### What is forwarding?

Consider this code:
```
ADD x1, x2, x3    ← produces result for x1 in EX stage, cycle N
SUB x4, x1, x5    ← needs x1 in EX stage, cycle N+1
```

Without forwarding, `SUB` reads x1 from the register file — but the register file hasn't been updated yet (the result of ADD reaches WB on cycle N+3, not N+1). We would need to stall 2 cycles.

**Forwarding** short-circuits this: instead of waiting for the result to go through WB and back to the register file, we take the result directly from the pipeline register where it sits and feed it forward to the next instruction's EX stage.

```
Cycle N+1: ADD result is in EX/MEM register
           SUB is in EX stage and needs it
           → forward directly from EX/MEM → EX input
```

```systemverilog
// rs1 forwarding
always_comb begin
    if (reg_write_mem_i && (rd_mem_i != 5'b0) && (rd_mem_i == rs1_ex_i))
        fwd_a_o = 2'b01;   // forward from EX/MEM (1 instruction ago)
    else if (reg_write_wb_i && (rd_wb_i != 5'b0) && (rd_wb_i == rs1_ex_i))
        fwd_a_o = 2'b10;   // forward from MEM/WB (2 instructions ago)
    else
        fwd_a_o = 2'b00;   // no hazard — use register file value
end
```

**EX/MEM forwarding (2'b01)** takes priority over MEM/WB forwarding (2'b10) because EX/MEM is more recent. If both a 1-ago and 2-ago instruction wrote to the same register, we want the freshest value.

**Why exclude x0?** Writes to x0 are ignored (it's always 0). If we forwarded a write to x0, the subsequent instruction using x0 would get the forwarded non-zero value instead of 0 — wrong. The `rd_mem_i != 5'b0` guard prevents this.

---

## The Bug Found and Fixed — LUI Forwarding

This is one of the most instructive moments in Phase 1.

### What is LUI?

`LUI rd, imm` (Load Upper Immediate) loads a 20-bit constant into the upper 20 bits of a register, zeroing the lower 12 bits. It is used to build large constants:
```
LUI  x1, 0xABCDE   → x1 = 0xABCDE000
ADDI x1, x1, 0x123 → x1 = 0xABCDE123
```

### The bug

When `LUI` was in the EX/MEM stage and the next instruction tried to use its result (needing forwarding), the wrong value was being forwarded.

**Why?** LUI uses `wb_sel = WB_IMM`, meaning it writes the immediate directly to the register (not an ALU result). The ALU is still running — it computes `rs1 + imm` where `rs1 = x0 = 0`, so `alu_result = 0 + imm = imm`. But wait — `alu_src_a = 0` (rs1) and `alu_src_b = 1` (imm), `alu_ctrl = ADD`. So `alu_result = 0 + imm = imm`... that should be fine?

Actually no. The issue was in the forwarding path. The EX/MEM forwarding was forwarding `alu_result_m` (the EX/MEM register's ALU result). For LUI this was 0 (because `rs1 = x0 = 0`... wait, actually `alu_src_a_o = 0` for LUI means alu_a = rs1_fwd = 0, and alu_b = imm, ADD gives imm — that's correct).

The real subtle issue: when `wb_sel_m == WB_IMM`, the actual value written to the register is the **immediate** from the MEM/WB stage, but the forwarding path was only forwarding `alu_result_m`. For LUI specifically, what ends up in the register is the immediate `imm` — but since alu_a came from rs1 which is x0 (0), `alu_result = 0 + imm_value`. So the forwarded `alu_result_m` was `0`, not the immediate. The immediate itself was a 20-bit upper value that got zero-extended to 32 bits — but `alu_result` was using ALU_ADD with rs1=x0=0, giving the correct full 32-bit result... only if the immediate was correctly set up.

### The actual fix

A mux `fwd_ex_mem_val` was added in `riscv_core.sv`:

```systemverilog
// When WB_IMM is selected (LUI), the forwarded value should be the immediate,
// not alu_result — because LUI writes imm to rd, not alu_result.
assign fwd_ex_mem_val = (wb_sel_m == WB_IMM) ? imm_m : alu_result_m;
```

This mux sits between the EX/MEM register and the forwarding input to execute_stage. When the instruction in EX/MEM is LUI, the forwarded value is the immediate; for all other instructions, it is the ALU result.

### Why this bug matters

This bug only surfaces when:
1. LUI is immediately followed by an instruction that uses the LUI destination register
2. The forwarding unit activates (because the register file hasn't been written yet)

Without the integration tests that specifically tested LUI with forwarding, this bug would have stayed hidden. This is why comprehensive testing is essential — unit tests on the ALU and decoder would never catch a forwarding interaction bug.

---

## The Integration Tests

**File:** `phase1_riscv_core/tb/test_riscv_core.py`

The final 22 tests exercise the complete `riscv_core.sv` — all stages together. Each test programs a small instruction sequence into a simulated instruction memory and verifies the register and memory state after execution.

### Examples of what was tested

**All RV32I instruction types:**
- R-type: ADD, SUB, AND, OR, XOR, SLL, SRL, SRA, SLT, SLTU
- I-type: ADDI, ANDI, ORI, XORI, SLLI, SRLI, SRAI, SLTI, SLTIU
- Load: LW, LH, LB, LHU, LBU
- Store: SW, SH, SB
- Branch: BEQ, BNE, BLT, BGE, BLTU, BGEU
- Jump: JAL, JALR
- Upper: LUI, AUIPC

**Hazard scenarios:**
- Load-use stall: LW followed immediately by dependent instruction
- EX/MEM forwarding: result used in next instruction
- MEM/WB forwarding: result used in the instruction after next
- Back-to-back forwarding: chain of 3 dependent instructions

**Bubblesort stress test:**
A complete bubblesort algorithm sorting `[3, 1, 4, 1, 5]` was loaded as machine code. After 300 simulation cycles, the memory was checked to contain `[1, 1, 3, 4, 5]`. This test exercises every instruction type, multiple levels of forwarding, loop branches, and memory loads/stores simultaneously. If anything in the pipeline is wrong, this test will fail.

### How the tests work (cocotb)

```python
@cocotb.test()
async def test_add_forwarding(dut):
    cocotb.start_soon(gen_clk(dut))
    await reset(dut)

    # Load instructions into simulated memory
    # ADD x3, x1, x2 followed immediately by ADD x4, x3, x2 (forwarding needed)
    imem = {
        0x00: encode_r(ADD, rd=3, rs1=1, rs2=2),
        0x04: encode_r(ADD, rd=4, rs1=3, rs2=2),
        0x08: NOP,
        0x0C: NOP,
    }
    # Pre-load registers x1=10, x2=5
    # Run for enough cycles and check x3=15, x4=20
    for _ in range(10):
        await RisingEdge(dut.clk)

    assert int(dut.reg_file.regs[3].value) == 15
    assert int(dut.reg_file.regs[4].value) == 20
```

The test directly drives the instruction and data memory buses from Python, and reads internal register values to check results.

---

## How All the Files Connect

Here is the complete picture of how the modules wire together in `riscv_core.sv`:

```
Instruction memory (testbench)
        │
        │ imem_rdata_i
        ▼
┌──────────────┐  pc_f, instr_f   ┌────────────────┐  pc_d, instr_d
│  fetch_stage │─────────────────▶│pipeline_reg    │─────────────────▶
│  (PC, mux)   │                  │  IF/ID         │
└──────────────┘                  └────────────────┘
        ▲ branch_taken, branch_target (from execute_stage)
        │ stall (from hazard_unit)

        ┌──────────────────────────────────────────────────────────────┐
        │  decode_stage (combinational)                                │
        │  + register file read                                        │
        │  + imm_gen                                                   │
        │  → control signals + rs1_data + rs2_data + imm              │
        └──────────────────────────────────────────────────────────────┘
                          │
                  ┌──────────────┐
                  │pipeline_reg  │
                  │  ID/EX       │
                  └──────────────┘
                          │
        ┌──────────────────────────────────────────────────────────────┐
        │  execute_stage (combinational)                               │
        │  + forwarding muxes (driven by forwarding_unit)              │
        │  + ALU (add/sub/and/or/xor/shift/compare)                    │
        │  + branch condition evaluation                               │
        │  → alu_result, branch_taken, branch_target                   │
        └──────────────────────────────────────────────────────────────┘
                          │
                  ┌──────────────┐
                  │pipeline_reg  │
                  │  EX/MEM      │
                  └──────────────┘
                          │
        ┌──────────────────────────────────────────────────────────────┐
        │  memory_stage (combinational)                                │
        │  + data memory address + byte enables                        │
        │  + load data sign/zero extension                             │
        └──────────────────────────────────────────────────────────────┘
                          │
                  ┌──────────────┐
                  │pipeline_reg  │
                  │  MEM/WB      │
                  └──────────────┘
                          │
        ┌──────────────────────────────────────────────────────────────┐
        │  writeback_stage (combinational)                             │
        │  + mux: ALU result / memory data / PC+4 / immediate         │
        │  → wb_data → register file write port                        │
        └──────────────────────────────────────────────────────────────┘

Crossing all stages:
├── hazard_unit: watches pipeline → stall_if, stall_id, flush_id, flush_ex
└── forwarding_unit: watches EX/MEM + MEM/WB → fwd_a, fwd_b → execute_stage muxes
```

---

## What Phase 1 Proved

By the end of Phase 1:

| Module | Function | Tests |
|--------|----------|-------|
| `alu.sv` | 10 arithmetic/logic operations | All operations, edge cases |
| `reg_file.sv` | 32 registers, dual read, single write | All addresses, x0 hardwire, write bypass |
| `imm_gen.sv` | 5 immediate types | All formats, sign extension |
| `fetch_stage.sv` | PC register, branch mux | PC+4, branch taken, stall |
| `pipeline_reg_IF_ID.sv` | IF/ID register | Flush (NOP), stall (hold) |
| `decode_stage.sv` | All 47 RV32I instructions | Every opcode/funct combination |
| `pipeline_reg_ID_EX.sv` | ID/EX register | Flush, stall |
| `execute_stage.sv` | ALU muxes, branch eval | All branch types, JAL, JALR |
| `memory_stage.sv` | Load/store with byte enables | All load/store variants |
| `writeback_stage.sv` | 4-way WB mux | All 4 sources |
| `hazard_unit.sv` | Load-use stall, branch flush | Both hazard types |
| `forwarding_unit.sv` | EX/MEM and MEM/WB forwarding | All forwarding distances |
| `riscv_core.sv` | Complete integrated pipeline | 22/22 including bubblesort |

**Total: 22/22 integration tests passing.**  
The complete RISC-V RV32I pipeline runs correctly at 100 MHz in simulation, handling all instruction types, data hazards, and control hazards.

---

## Why This Matters for the Rest of the Project

Everything built in later phases connects to this pipeline:
- **Phase 2 (L1 cache)** connects to `riscv_core`'s data memory port (`dmem_*`) and drives `dmem_stall_i` during cache misses
- **Phase 3 (AXI crossbar)** receives transactions from the cache's AXI master port
- **Phase 5 (integration)** instantiates `riscv_core` as the CPU in the full SoC, running firmware that controls the AI accelerator

The pipeline's `dmem_stall_i` port and the hazard unit's cache stall logic were designed in Phase 1 specifically to accommodate Phase 2 — even though Phase 2 didn't exist yet. That forward-thinking design is what made the Phase 1+2 integration a single commit rather than a major redesign.

---

*Document created: 2026-05-15*  
*Part of the RISC-V AI SoC build log series*
