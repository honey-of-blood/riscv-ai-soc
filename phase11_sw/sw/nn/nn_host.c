/*
 * nn_host.c — pure-software emulation of nn.c for host-side testing.
 *
 * Replaces the MMIO-based accelerator calls with scalar C arithmetic that
 * exactly matches the systolic array computation, including the tiled
 * NN_N×NN_N execution pattern.
 *
 * This file is only linked for host tests (TEST_HOST defined).
 * On the SoC, link nn.c instead.
 */

#ifdef TEST_HOST

#include "nn.h"
#include <string.h>

/*
 * Emulate one NN_N-output × NN_N-input accelerator tile.
 *
 * Mirrors accel_run_tile() from nn.c: compute
 *   y_reg[c] = sum_{r=0}^{NN_N-1} W_row[r][c] * a[r]
 * for c = 0..NN_N-1.
 */
static void accel_run_tile_host(
    uint32_t         j,
    uint32_t         i,
    uint32_t         in_size,
    uint32_t         out_size,
    const int8_t    *weights,
    const int8_t    *input,
    int32_t          y_reg[NN_N])
{
    for (int c = 0; c < NN_N; c++) {
        y_reg[c] = 0;
        for (int r = 0; r < NN_N; r++) {
            if (i + (uint32_t)r >= in_size)  continue;
            if (j + (uint32_t)c >= out_size) continue;
            int8_t ai = input[i + (uint32_t)r];
            int8_t wi = weights[((j + (uint32_t)c) * in_size)
                                + (i + (uint32_t)r)];
            y_reg[c] += (int32_t)wi * (int32_t)ai;
        }
    }
}

void nn_fc_forward(const nn_layer_t *layer,
                   const int8_t     *input,
                   int32_t          *output)
{
    uint32_t in  = layer->in_size;
    uint32_t out = layer->out_size;

    for (uint32_t j = 0; j < out; j += NN_N) {
        int32_t acc[NN_N] = {0, 0, 0, 0};

        for (uint32_t i = 0; i < in; i += NN_N) {
            int32_t y[NN_N];
            accel_run_tile_host(j, i, in, out, layer->weights, input, y);
            for (int c = 0; c < NN_N; c++) {
                if (j + (uint32_t)c < out)
                    acc[c] += y[c];
            }
        }

        for (int c = 0; c < NN_N; c++) {
            if (j + (uint32_t)c >= out) break;
            int32_t val = acc[c] + layer->bias[j + (uint32_t)c];
            if (layer->relu && val < 0) val = 0;
            output[j + (uint32_t)c] = val;
        }
    }
}

void nn_requantize(const int32_t *in,
                   int8_t        *out,
                   int32_t        scale,
                   int32_t        zero_point,
                   uint32_t       len)
{
    for (uint32_t k = 0; k < len; k++) {
        int64_t v = ((int64_t)in[k] * scale) >> 16;
        v += zero_point;
        if (v >  127) v =  127;
        if (v < -128) v = -128;
        out[k] = (int8_t)v;
    }
}

void nn_forward(const nn_layer_t *layers,
                int               n_layers,
                const int8_t     *input,
                int32_t          *output)
{
    static int8_t  buf0[512], buf1[512];
    static int32_t tmp[512];

    const int8_t *cur_in  = input;
    int8_t       *cur_out = buf0;
    int8_t       *nxt_out = buf1;

    for (int l = 0; l < n_layers; l++) {
        int32_t *dst = (l == n_layers - 1) ? output : tmp;
        nn_fc_forward(&layers[l], cur_in, dst);
        if (l < n_layers - 1) {
            nn_requantize(tmp, cur_out, 65536, 0, layers[l].out_size);
            cur_in = cur_out;
            int8_t *s = cur_out; cur_out = nxt_out; nxt_out = s;
        }
    }
}

#endif /* TEST_HOST */
