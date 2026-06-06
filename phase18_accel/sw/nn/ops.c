#include "ops.h"
#include <math.h>
#include <string.h>

// ── Softmax (float32) ────────────────────────────────────────────────────
void softmax_f32(float *x, int n) {
    float max_val = x[0];
    for (int i = 1; i < n; i++)
        if (x[i] > max_val) max_val = x[i];

    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        x[i] = expf(x[i] - max_val);
        sum += x[i];
    }
    for (int i = 0; i < n; i++)
        x[i] /= sum;
}

// ── Layer-norm (quantised INT8) ──────────────────────────────────────────
void layernorm_q(int8_t *x, int n, float scale_out) {
    // Compute mean and variance
    int32_t sum = 0;
    for (int i = 0; i < n; i++) sum += x[i];
    float mean = (float)sum / n;

    float var = 0.0f;
    for (int i = 0; i < n; i++) {
        float d = x[i] - mean;
        var += d * d;
    }
    var = var / n + 1e-5f;
    float inv_std = 1.0f / sqrtf(var);

    for (int i = 0; i < n; i++) {
        float norm = ((float)x[i] - mean) * inv_std * scale_out;
        // Saturate to [-128, 127]
        int32_t q = (int32_t)roundf(norm);
        if (q >  127) q =  127;
        if (q < -128) q = -128;
        x[i] = (int8_t)q;
    }
}

// ── Max-pool 2D ──────────────────────────────────────────────────────────
void maxpool2d(const int8_t *in, int8_t *out,
               int H, int W, int kH, int kW) {
    int outH = H / kH, outW = W / kW;
    for (int oh = 0; oh < outH; oh++) {
        for (int ow = 0; ow < outW; ow++) {
            int8_t mx = -128;
            for (int kh = 0; kh < kH; kh++) {
                for (int kw = 0; kw < kW; kw++) {
                    int8_t v = in[(oh*kH + kh)*W + (ow*kW + kw)];
                    if (v > mx) mx = v;
                }
            }
            out[oh*outW + ow] = mx;
        }
    }
}

// ── Avg-pool 2D ──────────────────────────────────────────────────────────
void avgpool2d(const int8_t *in, int8_t *out,
               int H, int W, int kH, int kW) {
    int outH = H / kH, outW = W / kW;
    int area = kH * kW;
    for (int oh = 0; oh < outH; oh++) {
        for (int ow = 0; ow < outW; ow++) {
            int32_t acc = 0;
            for (int kh = 0; kh < kH; kh++) {
                for (int kw = 0; kw < kW; kw++) {
                    acc += in[(oh*kH + kh)*W + (ow*kW + kw)];
                }
            }
            int32_t avg = acc / area;
            if (avg >  127) avg =  127;
            if (avg < -128) avg = -128;
            out[oh*outW + ow] = (int8_t)avg;
        }
    }
}

// ── Depthwise Conv2D ─────────────────────────────────────────────────────
void depthwise_conv2d(const int8_t *in, const int8_t *weight,
                      const int32_t *bias, int8_t *out,
                      int H, int W, int C, int kH, int kW, int shift) {
    int padH = kH / 2, padW = kW / 2;
    for (int h = 0; h < H; h++) {
        for (int w = 0; w < W; w++) {
            for (int c = 0; c < C; c++) {
                int32_t acc = bias ? bias[c] : 0;
                for (int kh = 0; kh < kH; kh++) {
                    for (int kw = 0; kw < kW; kw++) {
                        int ih = h + kh - padH;
                        int iw = w + kw - padW;
                        if (ih >= 0 && ih < H && iw >= 0 && iw < W) {
                            int8_t iv = in[(ih*W + iw)*C + c];
                            int8_t wv = weight[(kh*kW + kw)*C + c];
                            acc += (int32_t)iv * wv;
                        }
                    }
                }
                acc >>= shift;
                if (acc >  127) acc =  127;
                if (acc < -128) acc = -128;
                out[(h*W + w)*C + c] = (int8_t)acc;
            }
        }
    }
}

// ── Residual add ────────────────────────────────────────────────────────
void residual_add(const int8_t *a, const int8_t *b, int8_t *out,
                  int n, int shift) {
    for (int i = 0; i < n; i++) {
        int32_t s = ((int32_t)a[i] + (int32_t)b[i]) >> shift;
        if (s >  127) s =  127;
        if (s < -128) s = -128;
        out[i] = (int8_t)s;
    }
}
