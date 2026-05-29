# Phase 0 — Environment Setup & First Simulation
### A Beginner's Guide: Every Step Explained

---

## What Is Phase 0 and Why Does It Exist?

Before writing a single line of chip design, you need to answer one question: **do my tools actually work on my machine?**

Imagine a carpenter who buys a new saw and immediately tries to build a house. If the saw is broken or set up wrong, every piece of wood they cut will be wrong — and they won't know why until the house collapses. Phase 0 is the equivalent of testing every tool on a simple piece of wood before touching the real project.

In this project, Phase 0 had three goals:

1. Install and verify every tool in the chain
2. Create the folder structure for the entire 7-phase project
3. Write and simulate the simplest possible piece of hardware (a D flip-flop) to prove the simulation flow works end-to-end

If the D flip-flop simulation produces the right output, it means: Icarus Verilog can compile SystemVerilog, the testbench runs correctly, and the waveform file is generated. Every more complex thing we build later uses this exact same flow.

---

## The Tool Stack — What Each Tool Is and Why We Use It

This project uses six main tools. Here is what each one does and why it was chosen.

---

### 1. Icarus Verilog (`iverilog`) — The Simulator
**Version used: 12.0**

#### What is simulation?
When you write a chip design (called RTL — Register Transfer Level), you are describing how digital logic should behave. But you cannot run RTL code on a regular computer the way you run a Python script. A **simulator** reads your RTL and pretends to be that hardware — it steps through time, propagates signals, and tells you what the output would be at every moment.

Think of it like a flight simulator. A pilot can practise flying without being in a real plane. A chip designer can test a design without manufacturing actual silicon.

#### Why Icarus Verilog?
- It is 100% free and open source
- It compiles and simulates Verilog and SystemVerilog files
- It is fast enough for small-to-medium designs
- It integrates directly with cocotb (our Python testing library)
- It has been the standard open-source simulator for over 20 years — well documented, huge community

#### How you use it:
```bash
# Compile your RTL + testbench into a simulation binary
iverilog -g2012 -o sim_output dff.sv tb_dff.sv

# Run the simulation
./sim_output
```

The `-g2012` flag tells Icarus to use the SystemVerilog 2012 standard.

---

### 2. GTKWave — The Waveform Viewer
**Version used: 3.3.116**

#### What is a waveform?
When a simulation runs, every signal in the design changes value over time. A **waveform** is a graph that shows the value of each signal on the vertical axis and time on the horizontal axis. It looks like this:

```
clk:  ‾|_|‾|_|‾|_|‾|_|‾|_|
d:    _____‾‾‾‾‾‾‾‾‾_______
q:    _________‾‾‾‾‾_______
```

By looking at a waveform you can see:
- Did the output change at the right time?
- Did a signal go high when it should have stayed low?
- How many clock cycles did an operation take?

Without a waveform viewer, debugging is like trying to understand music from a list of numbers. With it, you see everything visually.

#### Why GTKWave?
- Free, open source, runs on Linux/Mac/Windows
- Reads VCD files (Value Change Dump) — the standard waveform format that Icarus Verilog produces
- The standard waveform viewer in open-source chip design

#### How waveforms are generated:
Your testbench (the file that drives your design during simulation) contains these two lines:
```sv
$dumpfile("dff.vcd");   // create a file called dff.vcd
$dumpvars(0, tb_dff);   // record ALL signals in tb_dff and below
```

After simulation, `dff.vcd` is a text file full of timestamps and signal values. GTKWave reads this file and displays it graphically.

---

### 3. Verilator — The Linter (and Later, Fast Simulator)
**Version used: 5.020**

#### What is linting?
Linting is checking code for mistakes *before* running it — like spell-check, but for hardware. A linter reads your RTL and warns you about:
- Signals that are declared but never used
- Implicit type conversions (which can cause subtle bugs)
- Constructs that might behave differently in simulation vs. real hardware
- Coding style violations

#### Why Verilator?
Verilator is the most strict open-source SystemVerilog linter available. It catches many classes of bugs that Icarus Verilog silently ignores.

In Phase 0, we ran:
```bash
verilator --lint-only -Wall dff.sv
```

`--lint-only` means "check for errors but don't actually simulate."  
`-Wall` means "show all warnings, even minor ones."

If Verilator outputs nothing, the code is clean.

In Phase 3, we used Verilator for something much more powerful: compiling SystemVerilog into C++ and running it at near-native speed (much faster than Icarus), which is how the UVM integration testbench was run.

---

### 4. Yosys — The Synthesiser
**Version used: 0.33**

#### What is synthesis?
Your RTL (the design you write) describes *what* the hardware should do. Synthesis is the process of translating that description into actual gates — AND gates, OR gates, flip-flops, multiplexers — that can be manufactured on silicon.

Synthesis is like translating an architectural blueprint into a list of actual materials: "use 47 bricks here, 12 steel beams there." After synthesis, you have a **netlist** — a list of primitive logic cells and the connections between them.

#### Why Yosys?
- The only mature open-source RTL synthesiser
- Can target many different gate libraries, including Sky130 (the open-source 130nm chip process we use in Phase 6)
- Used in Phase 3 for formal verification (translates RTL into a mathematical format that a theorem prover can check)
- Used in Phase 6 to synthesise the full SoC onto Sky130

---

### 5. cocotb — Python-Based Verification
**Version used: 2.0.1**

#### What is verification, and why not just use a Verilog testbench?
A **testbench** is code that drives inputs into your design and checks the outputs. You can write testbenches in Verilog/SystemVerilog, but that has limitations:
- Verilog's test-writing language is awkward and limited
- Reading files, doing arithmetic, calling external APIs — all painful in Verilog
- No proper test framework (no assertions, no test isolation, no reporting)

**cocotb** lets you write testbenches in Python instead. Your Python test code runs alongside the simulation — it can drive signals, read signals, wait for events, and check results using all of Python's expressiveness.

#### Why cocotb?
- Python is far easier to write correct test logic in
- You can use Python libraries (random, math, struct, etc.) freely
- Tests look like normal software unit tests
- Industry used it for real chip verification — not a toy

#### Important API detail discovered in Phase 0:
cocotb 2.0 changed how simulations are launched. The import must be:
```python
from cocotb_tools.runner import get_runner   # CORRECT for v2.0
# NOT:
from cocotb.runner import get_runner         # This was the v1.x way — broken in v2.0
```

This kind of discovery is exactly why Phase 0 exists — finding this on the first real test would waste hours of debugging.

---

### 6. Python Virtual Environment (`.venv`)

#### What is a virtual environment?
When you install Python packages with `pip install something`, they go into your system's global Python installation. This causes problems when:
- Project A needs `numpy==1.20` but Project B needs `numpy==2.0`
- A system update accidentally upgrades a package and breaks your project
- You want to share the exact package versions with someone else

A **virtual environment** is an isolated Python installation just for this project. Packages installed inside it don't affect anything outside it.

#### Why we created it:
```bash
python3 -m venv .venv          # Create the virtual environment
source .venv/bin/activate       # Activate it (all pip installs go here now)
pip install cocotb              # Install cocotb inside the venv
```

The `.venv/` folder is listed in `.gitignore` so it is never committed to git (it is machine-specific and regeneratable).

---

## Step 1 — Creating the Folder Structure

The very first thing committed was the project skeleton:

```
phase1_riscv_core/
    rtl/         ← SystemVerilog source files
    tb/          ← testbenches
    formal/      ← formal verification scripts
    synth/       ← synthesis scripts
phase2_cache/
    rtl/
    tb/
phase3_axi/
    rtl/
    tb/
    formal/
phase4_systolic/
    rtl/
    tb/
phase5_integration/
    rtl/
docs/            ← diagrams, documents
openlane/        ← OpenLane synthesis configuration (Phase 6)
```

**Why this structure?**

Each phase is self-contained. This matters because:
- You can run Phase 1 tests without Phase 2 even existing yet
- A bug in Phase 3 RTL doesn't contaminate Phase 1 files
- When reviewing the project, someone can open `phase1_riscv_core/` and find everything related to the pipeline in one place
- The separation mirrors how real chip projects are structured: each IP block lives in its own directory

The `rtl/` vs `tb/` split inside each phase is also intentional. RTL is the actual design — what goes into silicon. Testbenches are only for simulation — they never go near silicon. Keeping them separate avoids accidental cross-contamination.

---

## Step 2 — The `.gitignore` File

Git tracks every file in the repository. But some files should never be committed:

```gitignore
# Python / cocotb
.venv/          ← virtual environment (machine-specific, 100MB+)
__pycache__/    ← Python bytecode cache (regenerated automatically)
*.pyc           ← compiled Python files
sim_build/      ← cocotb simulation build artifacts
results.xml     ← test results (generated each run)
*.fst           ← waveform files (large, regeneratable)
*.vcd           ← waveform files

# Yosys
*.blif          ← synthesis intermediate formats
*.aig
*_netlist.v

# OpenLane
openlane/*/runs/  ← synthesis run outputs (can be gigabytes)

# GTKWave
*.gtkw          ← GTKWave save files (user-specific preferences)

# Editor
.vscode/        ← VS Code workspace settings (per-developer)
*.swp           ← Vim swap files
```

**Why does this matter?**

If you accidentally commit `sim_build/` or `.venv/`, the repository becomes hundreds of megabytes larger and full of files that are different on every machine. The `.gitignore` file is what keeps the repository clean, small, and portable — so anyone can clone it, run `source .venv/bin/activate`, and have everything work.

---

## Step 3 — The D Flip-Flop RTL

The first actual design file written was `phase1_riscv_core/rtl/dff.sv`:

```systemverilog
module dff (
    input  logic clk,
    input  logic rst,
    input  logic d,
    output logic q
);
    always_ff @(posedge clk or posedge rst) begin
        if (rst) q <= 1'b0;
        else     q <= d;
    end
endmodule
```

### What is a D flip-flop?

A flip-flop is the most fundamental memory element in digital hardware. Every register, every counter, every state machine is built from flip-flops.

The **D flip-flop** (Data flip-flop) has a simple rule:
- On every rising edge of the clock, the output `q` takes the value of the input `d`
- If `rst` (reset) is high, `q` is forced to 0 regardless of `d`

Think of it like taking a photograph. The "photo" (`q`) only updates at the moment the shutter clicks (rising clock edge). Whatever the scene (`d`) looks like at that instant is captured. Between clicks, the photo doesn't change even if the scene does.

### Why a D flip-flop for Phase 0?

The D flip-flop is the smallest piece of sequential (stateful) logic. It is:
- Simple enough that we can predict its output exactly — if it gives the wrong answer, we know the tool is broken, not our logic
- The building block everything else is made from — if the flip-flop simulation works, all future designs will also simulate correctly
- A complete end-to-end test of the flow: write SystemVerilog → compile with Icarus → simulate → produce waveform

### Explaining the code line by line

```systemverilog
module dff (
```
`module` is the fundamental unit in SystemVerilog, like a class in Python or a function in C. The module is named `dff`.

```systemverilog
    input  logic clk,
    input  logic rst,
    input  logic d,
    output logic q
```
These are the ports — the "pins" on the module. `logic` is the SystemVerilog data type (replaces the older `wire`/`reg` types). `clk` is the clock, `rst` is reset, `d` is the data input, `q` is the output.

```systemverilog
    always_ff @(posedge clk or posedge rst) begin
```
`always_ff` means "this block describes flip-flop behaviour." The `@(posedge clk or posedge rst)` is the **sensitivity list** — this block runs whenever the clock rises (`posedge clk`) or when reset rises (`posedge rst`). In real hardware, this corresponds to an asynchronous reset flip-flop: reset can happen at any time, not just on a clock edge.

```systemverilog
        if (rst) q <= 1'b0;
        else     q <= d;
```
`1'b0` means "1 bit, binary, value 0" — it is how you write the number zero as a single bit in SystemVerilog.

The `<=` operator is called a **non-blocking assignment**. It means "schedule this assignment to happen after the current time step resolves." This is what makes flip-flop descriptions correct in simulation — if you used `=` (blocking assignment) instead, you would get glitchy, unrealistic simulation results where signals change in the middle of a clock edge. All flip-flop behaviour must use `<=`.

---

## Step 4 — The Testbench

The testbench was written in `phase1_riscv_core/tb/tb_dff.sv`:

```systemverilog
`timescale 1ns/1ps

module tb_dff;
    logic clk, rst, d, q;

    dff uut (.clk(clk), .rst(rst), .d(d), .q(q));

    initial clk = 0;
    always #5 clk = ~clk;  // 100 MHz

    initial begin
        $dumpfile("dff.vcd");
        $dumpvars(0, tb_dff);

        rst = 1; d = 0; #12;
        rst = 0;

        d = 1; #10; $display("t=%0t d=%b q=%b (expect q=1)", $time, d, q);
        d = 0; #10; $display("t=%0t d=%b q=%b (expect q=0)", $time, d, q);
        d = 1; #10; $display("t=%0t d=%b q=%b (expect q=1)", $time, d, q);

        rst = 1; #10; $display("t=%0t rst=1 q=%b (expect q=0)", $time, q);
        rst = 0;

        $display("PASS: D flip-flop simulation complete");
        $finish;
    end
endmodule
```

### Explaining the testbench line by line

```systemverilog
`timescale 1ns/1ps
```
This tells the simulator what "time" means. `1ns` is the time unit (every `#1` in the code means 1 nanosecond). `1ps` is the precision (the smallest time step the simulator tracks). Without this line, Icarus produces a warning and may behave unexpectedly.

```systemverilog
module tb_dff;
```
The testbench itself is a module — but it has no ports because nothing drives it from outside. It is the outermost wrapper for the entire simulation.

```systemverilog
    logic clk, rst, d, q;
    dff uut (.clk(clk), .rst(rst), .d(d), .q(q));
```
We declare wires and **instantiate** the DFF. `uut` stands for "Unit Under Test" — a convention meaning "the thing we are testing." The `.clk(clk)` syntax connects the module port named `clk` to our local wire also named `clk`.

```systemverilog
    initial clk = 0;
    always #5 clk = ~clk;
```
This generates the clock. `#5` means "wait 5 nanoseconds." The clock starts at 0, then every 5 ns it flips (`~` is NOT). So it is: 0 for 5ns, 1 for 5ns, 0 for 5ns, 1 for 5ns... — a 10ns period = 100 MHz.

```systemverilog
        $dumpfile("dff.vcd");
        $dumpvars(0, tb_dff);
```
These two lines tell the simulator to record all signal changes into a file called `dff.vcd`. After simulation, this file can be opened in GTKWave to see the waveforms. `0` means "dump all hierarchy levels" (not just the top).

```systemverilog
        rst = 1; d = 0; #12;
        rst = 0;
```
Hold reset high for 12 ns to put the flip-flop into a known state (q=0). Then release reset. Why 12 ns? The first clock edge is at 5 ns, the second at 15 ns. By holding reset for 12 ns, we guarantee the flip-flop sees reset asserted for at least one full clock edge.

```systemverilog
        d = 1; #10; $display("...");
        d = 0; #10; $display("...");
```
Apply test patterns and wait 10 ns between each. `$display` prints to the terminal — it is like `printf` in C or `print()` in Python. This gives us a text record of what happened.

```systemverilog
        rst = 1; #10; $display("...");
        rst = 0;
```
Test asynchronous reset: even mid-operation, asserting `rst` should immediately force `q=0`. This verifies the `posedge rst` part of the sensitivity list.

```systemverilog
        $finish;
```
Tells the simulator to stop. Without `$finish`, the simulation runs forever (the clock keeps toggling).

---

## Step 5 — Running the Simulation

```bash
# Compile
iverilog -g2012 -o sim_dff phase1_riscv_core/rtl/dff.sv phase1_riscv_core/tb/tb_dff.sv

# Simulate
./sim_dff
```

Expected terminal output:
```
t=22000 d=1 q=1 (expect q=1)
t=32000 d=0 q=0 (expect q=0)
t=42000 d=1 q=1 (expect q=1)
t=52000 rst=1 q=0 (expect q=0)
PASS: D flip-flop simulation complete
```

Time is in picoseconds here because we set `timescale 1ns/1ps` — so 22000 ps = 22 ns.

This output tells us everything is working: the flip-flop captures `d` correctly on each clock edge, and reset forces `q=0` instantly.

---

## Step 6 — Linting with Verilator

```bash
verilator --lint-only -Wall phase1_riscv_core/rtl/dff.sv
```

If there is no output, the code is lint-clean.

**Why lint before moving on?** Linting catches things like:
- Using `=` instead of `<=` in a flip-flop (would simulate incorrectly)
- Declared but undriven signals (potential X-propagation bugs in real hardware)
- Width mismatches in assignments (a 4-bit signal assigned to an 8-bit bus — are you sure?)

A clean lint pass on the D flip-flop confirmed the RTL was written correctly before building anything more complex on top of it.

**Important rule discovered here:** Verilator is stricter than Icarus. Some code that Icarus accepts silently will cause Verilator errors. The two main rules that came out of Phase 0 and affected all later phases:

1. **No bit-selects inside `always_comb`.**  
   ```systemverilog
   // WRONG — Icarus accepts, Verilator rejects
   always_comb begin
       result = a[4:0];
   end

   // CORRECT
   logic [4:0] a_low;
   assign a_low = a[4:0];   // extract outside
   always_comb begin
       result = a_low;
   end
   ```

2. **No signed casts inside `always_comb`.**  
   Same solution: extract the signed assignment to an `assign` outside the block.

These rules shaped how every subsequent module was written.

---

## Step 7 — Viewing Waveforms in GTKWave

After simulation, a `dff.vcd` file was produced. To view it:

```bash
gtkwave dff.vcd
```

In GTKWave:
1. In the left panel, expand `tb_dff`
2. Select signals: `clk`, `rst`, `d`, `q`
3. Drag them to the signal view
4. Press `Ctrl+Shift+F` to zoom to fit

You can then visually verify:
- `q` changes exactly one clock cycle after `d` changes
- `q` immediately drops to 0 when `rst` goes high
- The clock is a perfect square wave at 100 MHz

This visual verification is why waveforms matter — edge cases that are hard to spot in text output become obvious when you see the timing relationships drawn out.

---

## What Phase 0 Proved

By the end of Phase 0, we had confirmed:

| Tool | Verified |
|------|---------|
| Icarus Verilog 12.0 | Compiles and simulates SystemVerilog correctly |
| GTKWave 3.3.116 | Reads VCD files, waveforms display correctly |
| Verilator 5.020 | Lint passes, critical coding rules identified |
| Yosys 0.33 | Installed and available for Phase 3 synthesis |
| cocotb 2.0.1 | Installed in venv, correct import path confirmed |
| Python venv | Isolated environment working, .gitignore in place |

And the design itself proved:
- `always_ff` with non-blocking `<=` correctly models a flip-flop in simulation
- Asynchronous reset (`posedge rst` in sensitivity list) works as expected
- The `$dumpfile`/`$dumpvars` → GTKWave pipeline produces usable waveforms
- The `$display` system task gives readable simulation output

---

## Why This All Matters for the Rest of the Project

Every single phase that followed used this exact same foundation:

- The **same Icarus simulation flow** — just with larger RTL files
- The **same waveform format** — FST (a compressed VCD) instead of VCD for large designs
- The **same Verilator rules** — every module written in every later phase followed the bit-select and signed-cast rules discovered here
- The **same Python venv** — cocotb test files in every phase activated this same environment
- The **same folder structure** — all RTL in `rtl/`, all tests in `tb/`

Phase 0 is small, but it is the foundation everything else stands on. A 5-minute verification that the D flip-flop simulates correctly saved potentially dozens of hours of confused debugging in Phases 1 through 3.

---

*Document created: 2026-05-15*  
*Part of the RISC-V AI SoC build log series*
