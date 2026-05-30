#include "nn.h"

/* ── MMIO helpers ────────────────────────────────────────────────────────── */
#define MMIO32(addr)  (*(volatile uint32_t *)(uintptr_t)(addr))
#define MMIO32R(addr) (*(const volatile uint32_t *)(uintptr_t)(addr))

/* ── Internal helpers ────────────────────────────────────────────────────── */

/*
 * accel_run_tile — run one NN_N-output × NN_N-input tile through the accelerator.
 *
 * Activation staggering: the Phase 9 accelerator reads NN_N scratchpad rows per
 * invocation. At feed cycle r+1, a_feed[r] = sp_rdata[r*8 +: 8] from scratchpad
 * row r. For the diagonal pattern used here, byte r of row r = input[i+r], all
 * other bytes are 0. This ensures each row r of the systolic array sees exactly
 * one non-zero activation, producing the correct dot product after NN_N cycles.
 *
 * The weight packing: W_row[r] byte c = weights[(j+c)*in + (i+r)], connecting
 * input (i+r) to output (j+c). After all input tiles accumulate, output[j+c] =
 * sum_i weights[j+c][i] * input[i].
 *
 * Returns nothing; caller reads ACCEL_Y(c) after this call.
 */
static void accel_run_tile(uint32_t         j,
                           uint32_t         i,
                           uint32_t         in_size,
                           uint32_t         out_size,
                           const int8_t    *weights,
                           const int8_t    *input)
{
    /* Write staggered activations to scratchpad rows 0..NN_N-1.
       Scratchpad row r sits at SP_BASE + r*8 (stride = 8 bytes confirmed
       by Phase 9 firmware: rows at 0x5001_0000, +8, +16, +24).
       Byte r of the 32-bit word = activation a[i+r]; other bytes = 0.   */
    for (int r = 0; r < NN_N; r++) {
        uint32_t ai = (i + r < in_size) ? (uint32_t)(uint8_t)input[i + r] : 0u;
        MMIO32(SP_BASE + (uint32_t)r * 8u) = ai << ((uint32_t)r * 8u);
    }

    /* Load weight rows: W_row[r] byte c = weights[(j+c)*in + (i+r)].  */
    for (int r = 0; r < NN_N; r++) {
        uint32_t wrow = 0u;
        for (int c = 0; c < NN_N; c++) {
            if (j + (uint32_t)c < out_size && i + (uint32_t)r < in_size) {
                uint32_t wb = (uint32_t)(uint8_t)
                              weights[((j + (uint32_t)c) * in_size)
                                      + (i + (uint32_t)r)];
                wrow |= wb << ((uint32_t)c * 8u);
            }
        }
        MMIO32(ACCEL_BASE + ACCEL_WROW(r)) = wrow;
    }

    /* ACT_BASE = 0 (always use scratchpad rows 0..NN_N-1).             */
    MMIO32(ACCEL_BASE + ACCEL_ACT) = 0u;

    /* Start. */
    MMIO32(ACCEL_BASE + ACCEL_CTRL) = 1u;

    /* Poll done bit (bit 1). */
    while (!(MMIO32R(ACCEL_BASE + ACCEL_CTRL) & 2u))
        ;

    /* Clear start so FSM returns to IDLE for next tile.                 */
    MMIO32(ACCEL_BASE + ACCEL_CTRL) = 0u;
}

/* ── Public API ──────────────────────────────────────────────────────────── */

void nn_fc_forward(const nn_layer_t *layer,
                   const int8_t     *input,
                   int32_t          *output)
{
    uint32_t in  = layer->in_size;
    uint32_t out = layer->out_size;

    for (uint32_t j = 0; j < out; j += NN_N) {
        /* Software accumulators for this output tile. */
        int32_t acc[NN_N] = {0, 0, 0, 0};

        /* Accumulate over input tiles of NN_N.                          */
        for (uint32_t i = 0; i < in; i += NN_N) {
            accel_run_tile(j, i, in, out, layer->weights, input);

            for (int c = 0; c < NN_N; c++) {
                if (j + (uint32_t)c < out)
                    acc[c] += (int32_t)MMIO32R(ACCEL_BASE + ACCEL_Y(c));
            }
        }

        /* Add bias and (optionally) apply ReLU, write to output.        */
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
        /* Fixed-point multiply: scale is Q16 (65536 = 1.0).            */
        int32_t v = ((int64_t)in[k] * scale) >> 16;
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
    /* Static ping-pong INT8 buffers for inter-layer activations.
       Maximum supported intermediate width = 512 neurons.              */
    static int8_t  buf0[512];
    static int8_t  buf1[512];
    static int32_t tmp[512];

    const int8_t *cur_in = input;
    int8_t       *cur_out = buf0;
    int8_t       *next_out = buf1;

    for (int l = 0; l < n_layers; l++) {
        int32_t *dst = (l == n_layers - 1) ? output : tmp;

        nn_fc_forward(&layers[l], cur_in, dst);

        if (l < n_layers - 1) {
            /* Requantize INT32 → INT8 for the next layer.
               scale = 65536 (1.0) and zero_point = 0 is a passthrough
               for already-bounded values; replace with calibrated values
               from quantize.py for accurate inference.                  */
            nn_requantize(tmp, cur_out,
                          65536 /*scale Q16*/, 0 /*zero_point*/,
                          layers[l].out_size);
            cur_in  = cur_out;
            /* Swap ping-pong buffers. */
            int8_t *swap = cur_out; cur_out = next_out; next_out = swap;
        }
    }
}
