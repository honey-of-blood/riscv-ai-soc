#!/usr/bin/env python3
"""
test_phase12.py — aggressive Phase 12 test suite.

Coverage:
  A) weights.h content validation   — 18 checks
  B) gen_weights_numpy.py behaviour  — 8 checks
  C) Firmware compilation            — 4 checks  (gcc -fsyntax-only)
  D) train_mnist.py structure        — 5 checks

Run from project root:
    python3 phase12_validation/tools/test_phase12.py
Or from phase12_validation/:
    python3 tools/test_phase12.py
"""

import sys, os, re, subprocess, tempfile, ast
import numpy as np

SCRIPT_DIR   = os.path.dirname(os.path.abspath(__file__))
PH12_ROOT    = os.path.dirname(SCRIPT_DIR)         # phase12_validation/
PROJECT_ROOT = os.path.dirname(PH12_ROOT)          # soc/
SW_DIR       = os.path.join(PH12_ROOT, "sw")
WEIGHTS_H    = os.path.join(SW_DIR, "weights.h")
PH11_NN_DIR  = os.path.join(PROJECT_ROOT, "phase11_sw", "sw", "nn")
PH8_HAL_DIR  = os.path.join(PROJECT_ROOT, "phase8_peripherals", "sw", "hal")

PASS = 0; FAIL = 0

def check(cond, label, detail=""):
    global PASS, FAIL
    if cond:
        PASS += 1; print(f"  PASS  {label}")
    else:
        FAIL += 1; print(f"  FAIL  {label}" + (f": {detail}" if detail else ""))

def section(name): print(f"\n── {name} ──")

# ══════════════════════════════════════════════════════════════════════════════
# A) weights.h content validation
# ══════════════════════════════════════════════════════════════════════════════
section("A) weights.h content validation")

with open(WEIGHTS_H) as f:
    WH = f.read()

# A1–A2: header boilerplate
check("#ifndef" in WH and "#define" in WH, "A1 header guard present")
check('#include "nn.h"' in WH,              "A2 includes nn.h")

# A3: N_LAYERS macro
m = re.search(r'#define MNIST_NET_N_LAYERS\s+(\d+)', WH)
check(m and int(m.group(1)) == 2, "A3 MNIST_NET_N_LAYERS == 2",
      f"got {m.group(1) if m else 'missing'}")

# A4–A7: array element counts (count commas inside each array body)
def count_elements(header, array_name):
    pat = rf'int[_a-z0-9 ]+{re.escape(array_name)}\[\] = \{{(.*?)\}};'
    m = re.search(pat, header, re.DOTALL)
    if not m: return -1
    return m.group(1).count(',')

w0_n = count_elements(WH, "w0")
w1_n = count_elements(WH, "w1")
b0_n = count_elements(WH, "b0")
b1_n = count_elements(WH, "b1")
check(w0_n == 784 * 128, f"A4 w0 has 784×128={784*128} elements", f"got {w0_n}")
check(w1_n == 128 * 10,  f"A5 w1 has 128×10={128*10} elements",   f"got {w1_n}")
check(b0_n == 128,        "A6 b0 has 128 elements",                f"got {b0_n}")
check(b1_n == 10,         "A7 b1 has 10 elements",                 f"got {b1_n}")

# A8–A9: all INT8 values in [-128, 127]
def parse_int8_array(header, name):
    pat = rf'int8_t {re.escape(name)}\[\] = \{{(.*?)\}};'
    m = re.search(pat, header, re.DOTALL)
    if not m: return None
    return [int(x.strip()) for x in m.group(1).split(',') if x.strip()]

w0_vals = parse_int8_array(WH, "w0")
w1_vals = parse_int8_array(WH, "w1")
check(w0_vals is not None and all(-128 <= v <= 127 for v in w0_vals[:1000]),
      "A8 w0 sample: all values in [-128, 127]",
      f"first 1000 checked")
check(w1_vals is not None and all(-128 <= v <= 127 for v in w1_vals),
      "A9 w1: all values in [-128, 127]",
      f"all {len(w1_vals) if w1_vals else '?'} checked")

# A10–A11: bias arrays are all-zero (Xavier init with zero bias)
def parse_int32_array(header, name):
    pat = rf'int32_t {re.escape(name)}\[\] = \{{(.*?)\}};'
    m = re.search(pat, header, re.DOTALL)
    if not m: return None
    return [int(x.strip()) for x in m.group(1).split(',') if x.strip()]

b0_vals = parse_int32_array(WH, "b0")
b1_vals = parse_int32_array(WH, "b1")
check(b0_vals and all(v == 0 for v in b0_vals), "A10 b0 all-zero (Xavier zero bias)", f"{b0_vals[:4]}...")
check(b1_vals and all(v == 0 for v in b1_vals), "A11 b1 all-zero (Xavier zero bias)", f"{b1_vals}")

# A12–A13: scale macros are positive
q16_0 = re.search(r'W0_SCALE_Q16\s+(\d+)u', WH)
q16_1 = re.search(r'W1_SCALE_Q16\s+(\d+)u', WH)
check(q16_0 and int(q16_0.group(1)) > 0, "A12 W0_SCALE_Q16 > 0",
      f"got {q16_0.group(1) if q16_0 else 'missing'}")
check(q16_1 and int(q16_1.group(1)) > 0, "A13 W1_SCALE_Q16 > 0",
      f"got {q16_1.group(1) if q16_1 else 'missing'}")

# A14: symmetric quantization maps max |W_float| to exactly 127; verify INT8 range is fully used
if w0_vals:
    max_abs_int8 = max(abs(v) for v in w0_vals)
    check(max_abs_int8 == 127,
          "A14 max |w0| == 127 (INT8 range fully utilised by symmetric quant)",
          f"got {max_abs_int8}")

# A15–A16: relu flags
check("relu     = 1u" in WH, "A15 layer0 relu=1u in nn_layer_t initialiser")
check("relu     = 0u" in WH, "A16 layer1 relu=0u in nn_layer_t initialiser")

# A17: expected_labels = {0,1,...,9}
labels_m = re.search(r'expected_labels\[10\] = \{([^}]+)\}', WH)
if labels_m:
    labels = [int(x.strip()) for x in labels_m.group(1).split(',')]
    check(labels == list(range(10)), "A17 expected_labels = {0,1,...,9}", f"got {labels}")
else:
    check(False, "A17 expected_labels array found", "array missing")

# A18: test_images array dimensions declared correctly
check("test_images[10][784]" in WH, "A18 test_images[10][784] declared")

# ══════════════════════════════════════════════════════════════════════════════
# B) gen_weights_numpy.py behaviour
# ══════════════════════════════════════════════════════════════════════════════
section("B) gen_weights_numpy.py behaviour")

gen_py = os.path.join(SCRIPT_DIR, "gen_weights_numpy.py")

def run_gen(seed, out_path):
    r = subprocess.run(
        [sys.executable, gen_py, "--seed", str(seed), "--output", out_path],
        capture_output=True, text=True
    )
    return r.returncode == 0

with tempfile.TemporaryDirectory() as td:
    # Use the same filename for both seed-42 runs so the header guard matches
    p42a = os.path.join(td, "weights_seed42.h")
    p42b = os.path.join(td, "weights_seed42.h")   # same path → overwrite
    p99  = os.path.join(td, "weights_seed99.h")

    ok_42a = run_gen(42, p42a)
    with open(p42a) as f: c42a = f.read()

    ok_42b = run_gen(42, p42b)   # regenerate same file
    with open(p42b) as f: c42b = f.read()

    ok_99  = run_gen(99, p99)
    with open(p99) as f: c99 = f.read()

    check(ok_42a and ok_42b and ok_99, "B1 gen_weights_numpy.py runs for seeds 42 and 99")
    check(c42a == c42b, "B2 same seed → identical output (reproducible)")

    if ok_42a and ok_99:
        with open(p99) as f: c99 = f.read()
        check(c42a != c99, "B3 different seeds → different weight arrays")

    # B4: Xavier init should give max |weight| < 1.0 (limit ≈ 0.0811 for 784+128)
    if ok_42a:
        w0 = parse_int8_array(c42a, "w0")
        if w0:
            # INT8 is quantized — max value ≤ 127. Scale back to float to check Xavier range.
            q16 = int(re.search(r'W0_SCALE_Q16\s+(\d+)u', c42a).group(1))
            scale = q16 / 65536.0
            max_fp = max(abs(v) * scale for v in w0)
            xavier_limit = (6 / (784 + 128)) ** 0.5
            check(max_fp <= xavier_limit + 1e-3,
                  f"B4 max reconstructed |w0| ≤ Xavier limit ({xavier_limit:.5f})",
                  f"got {max_fp:.5f}")

    # B5: scale Q16 > 0 for all seeds
    if ok_99:
        q16s = re.findall(r'W\d+_SCALE_Q16\s+(\d+)u', c99)
        check(all(int(q) > 0 for q in q16s), "B5 all W*_SCALE_Q16 > 0 for seed 99",
              f"got {q16s}")

# B6: layer in/out sizes match MNIST network definition
in0  = re.search(r'\.in_size\s+=\s+(\d+)u', WH)
out0 = re.search(r'\.out_size\s+=\s+(\d+)u', WH)
check(in0 and int(in0.group(1)) == 784, "B6 layer0 in_size == 784",
      f"got {in0.group(1) if in0 else 'missing'}")
check(out0 and int(out0.group(1)) == 128, "B7 layer0 out_size == 128",
      f"got {out0.group(1) if out0 else 'missing'}")

# B8: weights.h compiles with gcc -fsyntax-only (with a minimal nn.h stub)
nn_h_stub = (
    "#ifndef NN_H\n#define NN_H\n#include <stdint.h>\n"
    "typedef struct { uint32_t in_size; uint32_t out_size; "
    "int8_t *weights; int32_t *bias; uint8_t relu; } nn_layer_t;\n"
    "void nn_fc_forward(const nn_layer_t*,const int8_t*,int32_t*);\n"
    "void nn_requantize(const int32_t*,int8_t*,int32_t,int32_t,uint32_t);\n"
    "void nn_forward(const nn_layer_t*,int,const int8_t*,int32_t*);\n"
    "#endif\n"
)
with tempfile.TemporaryDirectory() as td:
    nn_path = os.path.join(td, "nn.h")
    with open(nn_path, "w") as f: f.write(nn_h_stub)
    # Patch weights.h to use absolute nn.h path
    patched = WH.replace('#include "nn.h"', f'#include "{nn_path}"')
    wh_tmp = os.path.join(td, "weights.h")
    with open(wh_tmp, "w") as f: f.write(patched)
    test_c = os.path.join(td, "t.c")
    with open(test_c, "w") as f:
        f.write(f'#include "{wh_tmp}"\nint main(void){{return 0;}}\n')
    r = subprocess.run(["gcc", "-O0", "-fsyntax-only", test_c],
                       capture_output=True, text=True)
    ok = (r.returncode == 0)
    if not ok: print(f"    gcc: {r.stderr[:300]}")
    check(ok, "B8 weights.h compiles cleanly with gcc -fsyntax-only")

# ══════════════════════════════════════════════════════════════════════════════
# C) Firmware compilation (gcc -fsyntax-only)
# ══════════════════════════════════════════════════════════════════════════════
section("C) Firmware compilation (gcc -fsyntax-only)")

def syntax_check(src_file, extra_includes=None):
    """Return (ok, stderr) from gcc -fsyntax-only."""
    inc = [f"-I{d}" for d in (extra_includes or [])]
    r = subprocess.run(
        ["gcc", "-O0", "-fsyntax-only", "-DTEST_HOST"] + inc + [src_file],
        capture_output=True, text=True
    )
    return r.returncode == 0, r.stderr

bench_c  = os.path.join(SW_DIR, "benchmark.c")
mnist_c  = os.path.join(SW_DIR, "mnist", "main.c")
tw_c     = os.path.join(SW_DIR, "test_weights.c")
nn_inc   = PH11_NN_DIR
hal_inc  = PH8_HAL_DIR
sw_inc   = SW_DIR

# C1: benchmark.c
ok, err = syntax_check(bench_c, [sw_inc, nn_inc, hal_inc])
if not ok: print(f"    {err[:400]}")
check(ok, "C1 benchmark.c: gcc -fsyntax-only PASS")

# C2: mnist/main.c
ok, err = syntax_check(mnist_c, [sw_inc, nn_inc, hal_inc])
if not ok: print(f"    {err[:400]}")
check(ok, "C2 mnist/main.c: gcc -fsyntax-only PASS")

# C3: test_weights.c
ok, err = syntax_check(tw_c, [sw_inc, nn_inc, hal_inc])
if not ok: print(f"    {err[:400]}")
check(ok, "C3 test_weights.c: gcc -fsyntax-only PASS")

# C4: No unresolved uart_uint/uart_int symbol in benchmark.c
# The post-decrement bug was: while (n--) uart_putc(buf[n + 1])
# Fixed: for (int i = n - 1; i >= 0; i--) uart_putc(buf[i])
with open(bench_c) as f: bench_src = f.read()
check("while (n--)" not in bench_src,
      "C4 benchmark.c: post-decrement loop bug absent")

with open(mnist_c) as f: mnist_src = f.read()
check("while (n--)" not in mnist_src,
      "C5 mnist/main.c: post-decrement loop bug absent")

# ══════════════════════════════════════════════════════════════════════════════
# D) train_mnist.py structure validation
# ══════════════════════════════════════════════════════════════════════════════
section("D) train_mnist.py structure validation")

train_py = os.path.join(SCRIPT_DIR, "train_mnist.py")
with open(train_py) as f:
    train_src = f.read()

# D1: valid Python syntax
try:
    tree = ast.parse(train_src)
    check(True, "D1 train_mnist.py is syntactically valid Python")
except SyntaxError as e:
    check(False, "D1 train_mnist.py is syntactically valid Python", str(e))
    tree = None

# D2: MnistMLP class defined with correct layer sizes
check("class MnistMLP" in train_src,           "D2 MnistMLP class defined")
check("nn.Linear(784, 128" in train_src,       "D3 fc1: Linear(784, 128)")
check("nn.Linear(128,  10" in train_src or
      "nn.Linear(128, 10" in train_src,        "D4 fc2: Linear(128, 10)")

# D5: ReLU applied after fc1 but NOT after fc2 (correct for classification)
check("torch.relu(self.fc1(x))" in train_src, "D5 ReLU on fc1 output only")
check("torch.relu(self.fc2" not in train_src, "D6 no ReLU on fc2 (logits)")

# D7: --quantize flag invokes quantize.py
check("quantize" in train_src and "quantize.py" in train_src,
      "D7 --quantize flag calls quantize.py")

# D8: argparse flags present
for flag in ("--epochs", "--batch", "--lr", "--quantize", "--model-out"):
    check(flag in train_src, f"D8 argparse has {flag} flag")

# ── Summary ───────────────────────────────────────────────────────────────────
print(f"\n{'='*40}")
print(f"TOTAL: {PASS} / {PASS+FAIL} passed", end="")
if FAIL == 0: print("  ✓ ALL PASS")
else:         print(f"  ✗ {FAIL} FAILED")

sys.exit(0 if FAIL == 0 else 1)
