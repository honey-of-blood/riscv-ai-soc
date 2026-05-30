/*
 * test_weights.c — host-side smoke test for weights.h + nn_host.c.
 *
 * Compiles against nn_host.c (no MMIO) to verify that:
 *   1. weights.h compiles cleanly
 *   2. nn_forward() runs on all 10 test images without crashing
 *   3. nn_fc_forward() on layer 0 gives non-trivial output (not all-zero)
 *   4. nn_requantize() with layer 0's scale factor runs cleanly
 *
 * Does NOT check inference accuracy (weights are synthetic).
 *
 * Build & run:
 *   gcc -O2 -Wall -DTEST_HOST -I. -I../../phase11_sw/sw/nn \
 *       test_weights.c ../../phase11_sw/sw/nn/nn_host.c -o build/test_weights
 *   ./build/test_weights
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "nn.h"
#include "weights.h"

static int g_pass = 0, g_fail = 0;

#define CHECK(cond, fmt, ...) do {                                \
    if (cond) { g_pass++; printf("  PASS  " fmt "\n", ##__VA_ARGS__); } \
    else      { g_fail++; printf("  FAIL  " fmt "\n", ##__VA_ARGS__); } \
} while (0)

int main(void)
{
    printf("Phase 12 weights.h smoke test\n");
    printf("==============================\n\n");

    /* W1: weights.h defines the correct layer shapes */
    printf("── Layer metadata ──\n");
    CHECK(mnist_net_layers[0].in_size  == 784, "layer0.in_size  == 784 (got %u)",
          mnist_net_layers[0].in_size);
    CHECK(mnist_net_layers[0].out_size == 128, "layer0.out_size == 128 (got %u)",
          mnist_net_layers[0].out_size);
    CHECK(mnist_net_layers[0].relu     == 1,   "layer0.relu     == 1 (got %u)",
          mnist_net_layers[0].relu);
    CHECK(mnist_net_layers[1].in_size  == 128, "layer1.in_size  == 128 (got %u)",
          mnist_net_layers[1].in_size);
    CHECK(mnist_net_layers[1].out_size == 10,  "layer1.out_size == 10  (got %u)",
          mnist_net_layers[1].out_size);
    CHECK(mnist_net_layers[1].relu     == 0,   "layer1.relu     == 0 (got %u)",
          mnist_net_layers[1].relu);
    CHECK(MNIST_NET_N_LAYERS == 2, "MNIST_NET_N_LAYERS == 2 (got %d)",
          MNIST_NET_N_LAYERS);

    /* W2: W0_SCALE_Q16 > 0 */
    CHECK(W0_SCALE_Q16 > 0, "W0_SCALE_Q16 > 0 (got %u)", W0_SCALE_Q16);
    CHECK(W1_SCALE_Q16 > 0, "W1_SCALE_Q16 > 0 (got %u)", W1_SCALE_Q16);

    /* W3: nn_fc_forward layer 0 — output is non-trivially non-zero */
    printf("\n── FC layer 0 forward (784→128) ──\n");
    int32_t *out0 = (int32_t *)calloc(128, sizeof(int32_t));
    nn_fc_forward(&mnist_net_layers[0], test_images[0], out0);
    int any_nonzero = 0;
    for (int i = 0; i < 128; i++) if (out0[i] != 0) { any_nonzero = 1; break; }
    CHECK(any_nonzero, "layer0 output is non-trivially non-zero");

    int any_relu_positive = 0;
    for (int i = 0; i < 128; i++) if (out0[i] > 0) { any_relu_positive = 1; break; }
    CHECK(any_relu_positive, "layer0 has at least one positive output (ReLU active)");

    /* W4: requantize layer 0 output */
    printf("\n── Requantize layer 0 → INT8 ──\n");
    int8_t *rq0 = (int8_t *)calloc(129, 1);
    rq0[128] = 0x5A;  /* sentinel */
    nn_requantize(out0, rq0, (int32_t)W0_SCALE_Q16, 0, 128);
    CHECK(rq0[128] == 0x5A, "requantize did not overflow sentinel byte");
    int rq_nonzero = 0;
    for (int i = 0; i < 128; i++) if (rq0[i] != 0) { rq_nonzero = 1; break; }
    CHECK(rq_nonzero, "requantized layer0 output is non-trivially non-zero");
    free(out0);

    /* W5: nn_forward on all 10 images — no crash */
    printf("\n── Full nn_forward on 10 test images ──\n");
    int32_t final_out[10];
    int any_crash = 0;
    for (int img = 0; img < 10 && !any_crash; img++) {
        memset(final_out, 0, sizeof(final_out));
        nn_forward(mnist_net_layers, MNIST_NET_N_LAYERS,
                   test_images[img], final_out);
        /* argmax: just check it's a valid class index */
        int pred = 0;
        for (int c = 1; c < 10; c++)
            if (final_out[c] > final_out[pred]) pred = c;
        CHECK(pred >= 0 && pred < 10, "image %d: argmax=%d in [0,9]", img, pred);
    }

    free(rq0);

    printf("\n==============================\n");
    printf("TOTAL: %d / %d passed", g_pass, g_pass + g_fail);
    if (g_fail == 0) printf("  ✓ ALL PASS\n");
    else             printf("  ✗ %d FAILED\n", g_fail);
    return g_fail ? 1 : 0;
}
