#!/usr/bin/env python3
"""
test_quantize.py — numpy-only unit tests for quantize.py helpers.

No PyTorch required. Tests the mathematical correctness of quantize_tensor,
quantize_bias, the generated C header syntax, and edge cases.

Usage:
    python3 tools/test_quantize.py
"""

import sys, os, subprocess, tempfile
import numpy as np

sys.path.insert(0, os.path.dirname(__file__))

# Import helpers directly (they don't need torch)
import importlib.util, types

# Inject a minimal torch stub so quantize.py can be imported without torch.
class _Tensor:
    def __init__(self, data):
        self._d = np.asarray(data, dtype=np.float32)
    def abs(self):        return _Tensor(np.abs(self._d))
    def max(self):        return _Tensor(self._d.max())
    def item(self):       return float(self._d)
    def detach(self):     return self
    def cpu(self):        return self
    def numpy(self):      return self._d
    def __truediv__(self, s): return _Tensor(self._d / s)
    @property
    def shape(self): return self._d.shape

def _clamp(t, lo, hi):  return _Tensor(np.clip(t._d, lo, hi))
def _round(t):          return _Tensor(np.round(t._d))

torch_stub = types.ModuleType("torch")
torch_stub.Tensor = _Tensor
torch_stub.clamp  = _clamp
torch_stub.round  = _round
torch_stub.int8   = np.int8
torch_stub.zeros  = lambda n: _Tensor(np.zeros(n))

nn_stub = types.ModuleType("torch.nn")
class _Linear:
    def __init__(self, w, b):
        self.weight      = _Tensor(w)
        self.bias        = _Tensor(b)
        self.in_features = w.shape[1]
        self.out_features= w.shape[0]

nn_stub.Linear   = _Linear
torch_stub.nn    = nn_stub
sys.modules["torch"]    = torch_stub
sys.modules["torch.nn"] = nn_stub

spec = importlib.util.spec_from_file_location(
    "quantize",
    os.path.join(os.path.dirname(__file__), "quantize.py")
)
qmod = importlib.util.module_from_spec(spec)
qmod.TORCH_AVAILABLE = True
spec.loader.exec_module(qmod)

quantize_tensor = qmod.quantize_tensor
quantize_bias   = qmod.quantize_bias
export_model    = qmod.export_model

# ── Test infrastructure ───────────────────────────────────────────────────────
PASS = 0; FAIL = 0

def check(cond, label, detail=""):
    global PASS, FAIL
    if cond:
        PASS += 1
        print(f"  PASS  {label}")
    else:
        FAIL += 1
        print(f"  FAIL  {label}" + (f": {detail}" if detail else ""))

def section(name):
    print(f"\n── {name} ──")

# ── A) quantize_tensor ────────────────────────────────────────────────────────

section("A) quantize_tensor")

# A1: symmetric range — max maps to +127
t = _Tensor(np.array([ 1.0, -1.0,  0.0,  0.5, -0.5]))
q, scale = quantize_tensor(t)
check(int(q[0]) == 127,  "A1 max=+1.0 → q=127",       f"got {q[0]}")
check(int(q[1]) == -127, "A2 min=-1.0 → q=-127",      f"got {q[1]}")
check(int(q[2]) == 0,    "A3 zero → q=0",              f"got {q[2]}")
check(abs(scale - 1.0/127) < 1e-5, "A4 scale=max/127", f"got {scale}")

# A5: all-zero tensor — scale must not be zero (no division by zero)
t_zero = _Tensor(np.zeros(4))
q_zero, scale_zero = quantize_tensor(t_zero)
check(scale_zero == 1.0,         "A5 all-zero scale=1.0",         f"got {scale_zero}")
check(np.all(q_zero == 0),       "A6 all-zero quant=0",           f"got {q_zero}")

# A7: all-positive tensor
t_pos = _Tensor(np.array([64.0, 32.0, 0.0]))
q_pos, s_pos = quantize_tensor(t_pos)
check(int(q_pos[0]) == 127, "A7 max positive maps to 127",  f"got {q_pos[0]}")
check(int(q_pos[2]) == 0,   "A8 zero stays 0",              f"got {q_pos[2]}")

# A9: all-negative tensor (symmetric: max(|vals|) = |-64|)
t_neg = _Tensor(np.array([-64.0, -32.0, 0.0]))
q_neg, s_neg = quantize_tensor(t_neg)
check(int(q_neg[0]) == -127, "A9 max-neg maps to -127",  f"got {q_neg[0]}")

# A10: values must be clipped to [-128, 127] range
t_clamp = _Tensor(np.array([1.0, 1.0, 1.0, -1.0]))
q_cl, s_cl = quantize_tensor(t_clamp)
check(int(q_cl.max()) <= 127,  "A10 no value exceeds  127", f"max={q_cl.max()}")
check(int(q_cl.min()) >= -128, "A11 no value below   -128", f"min={q_cl.min()}")

# A12: result dtype is int8
check(q_pos.dtype == np.int8, "A12 output dtype is int8", f"got {q_pos.dtype}")

# ── B) quantize_bias ──────────────────────────────────────────────────────────

section("B) quantize_bias")

bias_fp = _Tensor(np.array([1.0, -1.0, 0.5, 0.0]))
scale   = 1.0 / 127

b_q = quantize_bias(bias_fp, scale)
expected_0 = int(round(1.0 / scale))     # = 127
expected_1 = int(round(-1.0 / scale))    # = -127
expected_3 = 0

check(b_q[0] == expected_0, "B1 bias=+1.0/scale → 127",  f"got {b_q[0]} exp {expected_0}")
check(b_q[1] == expected_1, "B2 bias=-1.0/scale → -127", f"got {b_q[1]} exp {expected_1}")
check(b_q[3] == 0,          "B3 bias=0 → 0",             f"got {b_q[3]}")
check(b_q.dtype == np.int32,"B4 bias dtype is int32",     f"got {b_q.dtype}")

# B5: scale=1.0 — bias stays as integer
b_fp2 = _Tensor(np.array([100.0, -50.0, 0.0]))
b_q2  = quantize_bias(b_fp2, 1.0)
check(int(b_q2[0]) == 100, "B5 bias/scale=1 stays", f"got {b_q2[0]}")

# ── C) export_model — generated C header syntax ───────────────────────────────

section("C) export_model C header")

class FakeModel:
    """Mock model with 2 Linear layers: 4→8, 8→2."""
    def modules(self):
        rng = np.random.default_rng(99)
        w1 = rng.uniform(-1, 1, (8, 4)).astype(np.float32)
        b1 = rng.uniform(-1, 1, 8).astype(np.float32)
        w2 = rng.uniform(-1, 1, (2, 8)).astype(np.float32)
        b2 = rng.uniform(-1, 1, 2).astype(np.float32)
        return [
            _Linear(w1, b1),
            _Linear(w2, b2),
        ]
    def named_modules(self):
        modules = list(self.modules())
        return [("fc1", modules[0]), ("fc2", modules[1])]

with tempfile.NamedTemporaryFile(suffix=".h", delete=False, mode="w") as tmp:
    tmp_path = tmp.name

try:
    export_model(FakeModel(), tmp_path, "test_net")

    with open(tmp_path) as f:
        header = f.read()

    # C1: header guard present
    check("#ifndef" in header and "#define" in header, "C1 header guard present")
    # C2: include nn.h
    check('#include "nn.h"' in header, "C2 includes nn.h")
    # C3: weight arrays defined
    check("int8_t w0[]" in header, "C3 w0 array defined")
    check("int8_t w1[]" in header, "C4 w1 array defined")
    # C4: bias arrays defined
    check("int32_t b0[]" in header, "C5 b0 array defined")
    check("int32_t b1[]" in header, "C6 b1 array defined")
    # C5: nn_layer_t array
    check("test_net_layers[]" in header, "C7 layer array defined")
    # C6: n_layers macro
    check("TEST_NET_N_LAYERS" in header, "C8 N_LAYERS macro defined")
    # C7: first layer has relu=1, last has relu=0
    check("relu     = 1u" in header, "C9 first layer relu=1")
    check("relu     = 0u" in header, "C10 last layer relu=0")
    # C8: scale macros
    check("W0_SCALE_Q16" in header, "C11 W0_SCALE_Q16 defined")
    check("W1_SCALE_Q16" in header, "C12 W1_SCALE_Q16 defined")
    # C9: header compiles cleanly with gcc -fsyntax-only
    # (Provide a minimal nn.h stub for the syntax check)
    nn_h_stub = (
        "#ifndef NN_H\n#define NN_H\n"
        "#include <stdint.h>\n"
        "typedef struct { uint32_t in_size; uint32_t out_size; "
        "int8_t *weights; int32_t *bias; uint8_t relu; } nn_layer_t;\n"
        "#endif\n"
    )
    with tempfile.TemporaryDirectory() as td:
        nn_h_path = os.path.join(td, "nn.h")
        with open(nn_h_path, "w") as f: f.write(nn_h_stub)
        # Patch header include path
        patched = header.replace('"nn.h"', f'"{nn_h_path}"')
        test_c_path = os.path.join(td, "test.c")
        with open(test_c_path, "w") as f:
            f.write(patched)
            f.write("\nint main(void){return 0;}\n")
        r = subprocess.run(
            ["gcc", "-O0", "-fsyntax-only", test_c_path],
            capture_output=True, text=True
        )
        ok = (r.returncode == 0)
        if not ok:
            print(f"    gcc output: {r.stderr[:300]}")
        check(ok, "C13 generated header compiles cleanly")

finally:
    os.unlink(tmp_path)

# ── D) Scale correctness ──────────────────────────────────────────────────────

section("D) Scale formula correctness")

# max_val=1.0 → scale=1/127; quantize 0.5 → round(0.5*127)=63 or 64
t_half = _Tensor(np.array([1.0, 0.5, -0.5]))
q_h, s_h = quantize_tensor(t_half)
check(abs(s_h - 1.0/127) < 1e-6, "D1 scale=max/127",              f"got {s_h}")
check(int(q_h[0]) == 127,         "D2 1.0 → 127",                 f"got {q_h[0]}")
# round(0.5/scale) = round(0.5*127) = round(63.5) = 64 (numpy rounds to even → 64)
expected_half = int(np.round(0.5 * 127))
check(int(q_h[1]) == expected_half, f"D3 0.5 → {expected_half}", f"got {q_h[1]}")

# D4: reconstruction error ≤ 1/127 (quantization step)
rng = np.random.default_rng(42)
W_big = rng.uniform(-10, 10, (16, 16)).astype(np.float32)
q_big, s_big = quantize_tensor(_Tensor(W_big))
W_recon = q_big.astype(np.float32) * s_big
max_err = float(np.abs(W_big - W_recon).max())
check(max_err <= s_big + 1e-6, "D4 reconstruction error ≤ 1 step", f"max_err={max_err:.6f} step={s_big:.6f}")

# ── Summary ───────────────────────────────────────────────────────────────────

print(f"\n=================================")
print(f"TOTAL: {PASS} / {PASS+FAIL} passed", end="")
if FAIL == 0:
    print("  ✓ ALL PASS")
else:
    print(f"  ✗ {FAIL} FAILED")

sys.exit(0 if FAIL == 0 else 1)
