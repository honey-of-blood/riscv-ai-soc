#ifndef OPS_H
#define OPS_H
// Operator library for the Phase 18 AI accelerator.
// Implements reference operators used in CNN inference:
//   softmax_f32, layernorm_q, maxpool2d, avgpool2d,
//   depthwise_conv2d, residual_add
//
// INT8 convention: int8_t values, scale factor applied externally.
// All operators work on flat buffers with explicit dimension parameters.

#include <stdint.h>
#include <stddef.h>

// ── Softmax (float32) ────────────────────────────────────────────────────
// Computes softmax in-place over a vector of n float32 values.
void softmax_f32(float *x, int n);

// ── Layer-norm (quantised INT8) ──────────────────────────────────────────
// Normalises n INT8 values in-place, requantised to INT8.
// scale_out: output scale (Q-format fraction, applied after normalisation).
void layernorm_q(int8_t *x, int n, float scale_out);

// ── Max-pool 2D ──────────────────────────────────────────────────────────
// in: HxW single-channel INT8 feature map (row-major)
// out: (H/kH) × (W/kW) result (integer-division)
void maxpool2d(const int8_t *in, int8_t *out,
               int H, int W, int kH, int kW);

// ── Avg-pool 2D ──────────────────────────────────────────────────────────
void avgpool2d(const int8_t *in, int8_t *out,
               int H, int W, int kH, int kW);

// ── Depthwise Conv2D ─────────────────────────────────────────────────────
// in: HxW, C channels, INT8 (layout: H,W,C = HWC)
// weight: kH×kW×C (one filter per channel)
// out: HxW, C channels (same spatial size, zero-pad)
// bias: C int32 biases (applied before activation)
// shift: right-shift after bias add (approximates scale)
void depthwise_conv2d(const int8_t *in, const int8_t *weight,
                      const int32_t *bias, int8_t *out,
                      int H, int W, int C, int kH, int kW, int shift);

// ── Residual add with INT8 saturation ────────────────────────────────────
// out[i] = saturate8(a[i] + b[i])  (requantised from INT8+INT8)
// shift: right-shift applied after add (requantisation approximation)
void residual_add(const int8_t *a, const int8_t *b, int8_t *out,
                  int n, int shift);

#endif /* OPS_H */
