#!/usr/bin/env python3
"""Pure-Python reference tests for the Phase 18 operator library.

These tests verify the algorithms in ops.c using Python equivalents,
without requiring compilation of the C code.  They run with plain Python
(no cocotb / Icarus needed).
"""
import math
import unittest


# ── Python reference implementations (mirror ops.c) ──────────────────────

def softmax_f32(x):
    mx = max(x)
    ex = [math.exp(v - mx) for v in x]
    s  = sum(ex)
    return [v / s for v in ex]


def layernorm_q(x, scale_out):
    n    = len(x)
    mean = sum(x) / n
    var  = sum((v - mean) ** 2 for v in x) / n + 1e-5
    inv  = 1.0 / math.sqrt(var)
    out  = []
    for v in x:
        q = round((v - mean) * inv * scale_out)
        q = max(-128, min(127, q))
        out.append(q)
    return out


def maxpool2d(inp, H, W, kH, kW):
    outH, outW = H // kH, W // kW
    out = []
    for oh in range(outH):
        for ow in range(outW):
            mx = -128
            for kh in range(kH):
                for kw in range(kW):
                    v = inp[(oh*kH + kh)*W + (ow*kW + kw)]
                    if v > mx:
                        mx = v
            out.append(mx)
    return out


def avgpool2d(inp, H, W, kH, kW):
    outH, outW = H // kH, W // kW
    area = kH * kW
    out  = []
    for oh in range(outH):
        for ow in range(outW):
            acc = 0
            for kh in range(kH):
                for kw in range(kW):
                    acc += inp[(oh*kH + kh)*W + (ow*kW + kw)]
            q = acc // area
            q = max(-128, min(127, q))
            out.append(q)
    return out


def depthwise_conv2d(inp, weight, bias, H, W, C, kH, kW, shift):
    """inp[H,W,C], weight[kH,kW,C], bias[C] → out[H,W,C]."""
    padH, padW = kH // 2, kW // 2
    out = [0] * (H * W * C)
    for h in range(H):
        for w in range(W):
            for c in range(C):
                acc = bias[c] if bias else 0
                for kh in range(kH):
                    for kw in range(kW):
                        ih, iw = h + kh - padH, w + kw - padW
                        if 0 <= ih < H and 0 <= iw < W:
                            iv = inp[(ih*W + iw)*C + c]
                            wv = weight[(kh*kW + kw)*C + c]
                            acc += iv * wv
                acc >>= shift
                acc = max(-128, min(127, acc))
                out[(h*W + w)*C + c] = acc
    return out


def residual_add(a, b, shift):
    out = []
    for ai, bi in zip(a, b):
        s = (ai + bi) >> shift
        s = max(-128, min(127, s))
        out.append(s)
    return out


# ── Unit tests ────────────────────────────────────────────────────────────

class TestSoftmax(unittest.TestCase):
    def test_uniform(self):
        """Equal logits → all probabilities equal 1/n."""
        x = [0.0, 0.0, 0.0, 0.0]
        y = softmax_f32(x)
        for v in y:
            self.assertAlmostEqual(v, 0.25, places=5)

    def test_peaked(self):
        """Large logit dominates."""
        x = [10.0, 0.0, 0.0, 0.0]
        y = softmax_f32(x)
        self.assertGreater(y[0], 0.99)

    def test_sums_to_one(self):
        x = [1.0, 2.0, 3.0, 4.0]
        y = softmax_f32(x)
        self.assertAlmostEqual(sum(y), 1.0, places=5)


class TestLayernorm(unittest.TestCase):
    def test_zero_mean(self):
        """Output should have approximately zero mean for scale_out=1."""
        x = [1, 2, 3, 4, 5, 6, 7, 8]
        y = layernorm_q(x, scale_out=1.0)
        self.assertAlmostEqual(sum(y) / len(y), 0, delta=1)

    def test_range(self):
        """Outputs must stay in INT8 range."""
        x = list(range(-100, 100, 10))
        y = layernorm_q(x, scale_out=100.0)
        for v in y:
            self.assertGreaterEqual(v, -128)
            self.assertLessEqual(v, 127)


class TestPooling(unittest.TestCase):
    def test_maxpool2x2(self):
        inp = [1, 3, 2, 4,
               5, 7, 6, 8,
               9, 11, 10, 12,
               13, 15, 14, 16]
        out = maxpool2d(inp, H=4, W=4, kH=2, kW=2)
        self.assertEqual(out, [7, 8, 15, 16])

    def test_avgpool2x2(self):
        inp = [4, 4, 4, 4,
               4, 4, 4, 4]
        out = avgpool2d(inp, H=2, W=4, kH=2, kW=2)
        self.assertEqual(out, [4, 4])


class TestDepthwiseConv(unittest.TestCase):
    def test_identity_kernel(self):
        """1×1 kernel with weight=1 is identity."""
        inp = [1, 2, 3, 4, 5, 6, 7, 8, 9]  # 3×3, C=1
        wt  = [1]   # 1×1×1 weight
        out = depthwise_conv2d(inp, wt, None, H=3, W=3, C=1, kH=1, kW=1, shift=0)
        self.assertEqual(out, inp)


class TestResidualAdd(unittest.TestCase):
    def test_basic_add(self):
        a = [10, 20, 30, 40]
        b = [1,  2,  3,  4]
        out = residual_add(a, b, shift=0)
        self.assertEqual(out, [11, 22, 33, 44])

    def test_saturation(self):
        a = [100, -100]
        b = [100, -100]
        out = residual_add(a, b, shift=0)
        self.assertEqual(out[0], 127)   # clamped up
        self.assertEqual(out[1], -128)  # clamped down

    def test_shift(self):
        a = [4, 8, 12]
        b = [4, 8, 12]
        out = residual_add(a, b, shift=1)  # >>1 after add
        self.assertEqual(out, [4, 8, 12])


if __name__ == "__main__":
    unittest.main(verbosity=2)
