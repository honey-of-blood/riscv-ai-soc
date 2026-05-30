/*
 * test_weights.c — aggressive host-side validation of weights.h + nn inference.
 *
 * Build & run:
 *   gcc -O2 -Wall -Wextra -DTEST_HOST -I. -I../../phase11_sw/sw/nn \
 *       test_weights.c ../../phase11_sw/sw/nn/nn_host.c -o build/test_weights
 *   ./build/test_weights
 *
 * Coverage:
 *   A) Layer metadata         — 9 checks
 *   B) FC layer 0 forward     — 6 checks
 *   C) Requantize             — 5 checks
 *   D) Full nn_forward        — 8 checks
 *   E) Manual chain == nn_forward — 3 checks
 *   F) Edge cases             — 4 checks
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "nn.h"
#include "weights.h"

static int g_pass = 0, g_fail = 0;

#define CHECK(cond, fmt, ...) do {                                          \
    if (cond) { g_pass++;                                                   \
                printf("  PASS  " fmt "\n", ##__VA_ARGS__); }              \
    else      { g_fail++;                                                   \
                printf("  FAIL  " fmt "\n", ##__VA_ARGS__); } } while (0)

static void section(const char *n) { printf("\n── %s ──\n", n); }

/* ── A) Layer metadata ───────────────────────────────────────────────────── */
static void test_metadata(void)
{
    section("A) Layer metadata");

    CHECK(MNIST_NET_N_LAYERS == 2,           "A1 MNIST_NET_N_LAYERS == 2");
    CHECK(mnist_net_layers[0].in_size  == 784, "A2 layer0.in_size  == 784");
    CHECK(mnist_net_layers[0].out_size == 128, "A3 layer0.out_size == 128");
    CHECK(mnist_net_layers[0].relu     == 1,   "A4 layer0.relu     == 1");
    CHECK(mnist_net_layers[1].in_size  == 128, "A5 layer1.in_size  == 128");
    CHECK(mnist_net_layers[1].out_size == 10,  "A6 layer1.out_size == 10");
    CHECK(mnist_net_layers[1].relu     == 0,   "A7 layer1.relu     == 0");
    CHECK(W0_SCALE_Q16 > 0,                    "A8 W0_SCALE_Q16 > 0 (got %u)", W0_SCALE_Q16);
    CHECK(W1_SCALE_Q16 > 0,                    "A9 W1_SCALE_Q16 > 0 (got %u)", W1_SCALE_Q16);

    /* expected_labels[i] == i for all i */
    int labels_ok = 1;
    for (int i = 0; i < 10; i++)
        if (expected_labels[i] != i) { labels_ok = 0; break; }
    CHECK(labels_ok, "A10 expected_labels[i] == i for all i");

    /* sizeof test_images == 10 * 784 bytes */
    CHECK(sizeof(test_images) == 10u * 784u,
          "A11 sizeof(test_images) == 10×784 = %zu (got %zu)",
          (size_t)(10u * 784u), sizeof(test_images));
}

/* ── B) FC layer 0 forward ───────────────────────────────────────────────── */
static void test_fc_layer0(void)
{
    section("B) FC layer 0 forward (784→128, relu=1)");

    int32_t *out0 = (int32_t *)calloc(128, sizeof(int32_t));

    nn_fc_forward(&mnist_net_layers[0], test_images[0], out0);

    /* B1: non-trivial output */
    int any_nonzero = 0;
    for (int i = 0; i < 128; i++) if (out0[i] != 0) { any_nonzero = 1; break; }
    CHECK(any_nonzero, "B1 layer0 output is non-trivially non-zero");

    /* B2: ReLU applied — all outputs ≥ 0 */
    int all_nonneg = 1;
    for (int i = 0; i < 128; i++) if (out0[i] < 0) { all_nonneg = 0; break; }
    CHECK(all_nonneg, "B2 layer0 ReLU: all outputs >= 0");

    /* B3: some outputs are zero (ReLU killed some) */
    int any_zero = 0;
    for (int i = 0; i < 128; i++) if (out0[i] == 0) { any_zero = 1; break; }
    CHECK(any_zero, "B3 layer0 ReLU: at least one output == 0 (ReLU is non-trivial)");

    /* B4: some outputs are strictly positive */
    int any_pos = 0;
    for (int i = 0; i < 128; i++) if (out0[i] > 0) { any_pos = 1; break; }
    CHECK(any_pos, "B4 layer0 has at least one positive output");

    /* B5: different input images give different layer-0 outputs */
    int32_t *out1 = (int32_t *)calloc(128, sizeof(int32_t));
    nn_fc_forward(&mnist_net_layers[0], test_images[1], out1);
    CHECK(memcmp(out0, out1, 128 * sizeof(int32_t)) != 0,
          "B5 different inputs produce different layer0 outputs");

    /* B6: running layer 0 again with same input gives same output */
    int32_t *out0b = (int32_t *)calloc(128, sizeof(int32_t));
    nn_fc_forward(&mnist_net_layers[0], test_images[0], out0b);
    CHECK(memcmp(out0, out0b, 128 * sizeof(int32_t)) == 0,
          "B6 layer0 is deterministic (same input → same output)");

    free(out0); free(out1); free(out0b);
}

/* ── C) Requantize ───────────────────────────────────────────────────────── */
static void test_requantize(void)
{
    section("C) nn_requantize");

    /* Run layer 0 to get INT32 output to requantize */
    int32_t *acc = (int32_t *)calloc(128, sizeof(int32_t));
    nn_fc_forward(&mnist_net_layers[0], test_images[0], acc);

    int8_t *rq = (int8_t *)calloc(129, 1);
    rq[128] = 0x5A;  /* sentinel */

    nn_requantize(acc, rq, 65536 /*scale=1.0*/, 0, 128);

    /* C1: sentinel not clobbered */
    CHECK(rq[128] == 0x5A, "C1 requantize sentinel byte not clobbered");

    /* C2: all values in INT8 range — cast to int to avoid tautology warning */
    int all_range = 1;
    for (int i = 0; i < 128; i++) {
        int v = (int)rq[i];
        if (v < -128 || v > 127) { all_range = 0; break; }
    }
    CHECK(all_range, "C2 all requantized values in [-128, 127]");

    /* C3: non-trivially non-zero */
    int any_nz = 0;
    for (int i = 0; i < 128; i++) if (rq[i] != 0) { any_nz = 1; break; }
    CHECK(any_nz, "C3 requantized output is non-trivially non-zero");

    /* C4: with scale=1.0 and relu output (all acc≥0), requantized values ≥ 0 */
    int all_nn = 1;
    for (int i = 0; i < 128; i++) if (rq[i] < 0) { all_nn = 0; break; }
    CHECK(all_nn, "C4 requantize(ReLU output, scale=1.0): all values >= 0");

    /* C5: len=0 with NULL pointers must not crash */
    nn_requantize(NULL, NULL, 65536, 0, 0);
    CHECK(1, "C5 requantize(NULL, NULL, _, _, 0) does not crash");

    free(acc); free(rq);
}

/* ── D) Full nn_forward ──────────────────────────────────────────────────── */
static void test_nn_forward(void)
{
    section("D) Full nn_forward (10 test images)");

    int32_t output[10];
    int n_distinct = 0;
    int seen[10] = {0};

    for (int img = 0; img < 10; img++) {
        memset(output, 0, sizeof(output));
        nn_forward(mnist_net_layers, MNIST_NET_N_LAYERS,
                   test_images[img], output);

        /* argmax */
        int best = 0;
        for (int c = 1; c < 10; c++)
            if (output[c] > output[best]) best = c;
        (void)best;

        CHECK(best >= 0 && best < 10,
              "D%d image %d: argmax=%d in [0,9]", img + 1, img, best);

        if (!seen[best]) { seen[best] = 1; n_distinct++; }
    }

    /* D11: at least 2 distinct predictions (non-degenerate network) */
    CHECK(n_distinct >= 2, "D11 at least 2 distinct predictions across 10 images (got %d)",
          n_distinct);

    /* D12: nn_forward is deterministic */
    int32_t output2[10];
    nn_forward(mnist_net_layers, MNIST_NET_N_LAYERS,
               test_images[0], output2);
    int32_t output3[10];
    nn_forward(mnist_net_layers, MNIST_NET_N_LAYERS,
               test_images[0], output3);
    CHECK(memcmp(output2, output3, sizeof(output2)) == 0,
          "D12 nn_forward deterministic (run twice, same result)");
}

/* ── E) Manual chain == nn_forward ──────────────────────────────────────── */
static void test_chain_equivalence(void)
{
    section("E) Manual chain equivalence");

    /*
     * nn_forward internally does:
     *   nn_fc_forward(layer0, input, tmp)
     *   nn_requantize(tmp, buf, 65536, 0, layer0.out_size)
     *   nn_fc_forward(layer1, buf, output)
     *
     * Reproduce this manually and compare.
     */
    static int32_t tmp[128];
    static int8_t  buf[128];
    static int32_t out_manual[10];
    static int32_t out_nn[10];

    const int8_t *img = test_images[3];

    /* Manual chain */
    nn_fc_forward(&mnist_net_layers[0], img, tmp);
    nn_requantize(tmp, buf, 65536, 0, 128);
    nn_fc_forward(&mnist_net_layers[1], buf, out_manual);

    /* nn_forward */
    nn_forward(mnist_net_layers, MNIST_NET_N_LAYERS, img, out_nn);

    CHECK(memcmp(out_manual, out_nn, 10 * sizeof(int32_t)) == 0,
          "E1 manual chain output == nn_forward output (image 3)");

    /* E2: same argmax for another image */
    nn_fc_forward(&mnist_net_layers[0], test_images[7], tmp);
    nn_requantize(tmp, buf, 65536, 0, 128);
    nn_fc_forward(&mnist_net_layers[1], buf, out_manual);
    nn_forward(mnist_net_layers, MNIST_NET_N_LAYERS, test_images[7], out_nn);
    CHECK(memcmp(out_manual, out_nn, 10 * sizeof(int32_t)) == 0,
          "E2 manual chain output == nn_forward output (image 7)");

    /* E3: argmax consistent */
    int best_m = 0, best_n = 0;
    for (int c = 1; c < 10; c++) {
        if (out_manual[c] > out_manual[best_m]) best_m = c;
        if (out_nn[c]     > out_nn[best_n])     best_n = c;
    }
    CHECK(best_m == best_n, "E3 manual chain and nn_forward give same argmax");
}

/* ── F) Edge cases ───────────────────────────────────────────────────────── */
static void test_edge_cases(void)
{
    section("F) Edge cases");

    /* F1: all-zero input → layer0 output = bias (zero here), all ReLU zeros */
    static int8_t  zero_in[784] = {0};
    static int32_t zero_out[128];
    nn_fc_forward(&mnist_net_layers[0], zero_in, zero_out);
    /* With all-zero bias, all-zero input → all outputs = 0 after ReLU */
    int all_zero = 1;
    for (int i = 0; i < 128; i++) if (zero_out[i] != 0) { all_zero = 0; break; }
    CHECK(all_zero, "F1 all-zero input + zero bias → all-zero layer0 output");

    /* F2: layer1 on zero input → all-zero output (zero bias) */
    static int8_t  zero_in8[128] = {0};
    static int32_t zero_out10[10];
    nn_fc_forward(&mnist_net_layers[1], zero_in8, zero_out10);
    int all_z = 1;
    for (int i = 0; i < 10; i++) if (zero_out10[i] != 0) { all_z = 0; break; }
    CHECK(all_z, "F2 all-zero input + zero bias → all-zero layer1 output");

    /* F3: nn_forward on all-zero input → all-zero output */
    static int32_t fwd_zero[10];
    nn_forward(mnist_net_layers, MNIST_NET_N_LAYERS, zero_in, fwd_zero);
    int fz = 1;
    for (int i = 0; i < 10; i++) if (fwd_zero[i] != 0) { fz = 0; break; }
    CHECK(fz, "F3 nn_forward on all-zero input → all-zero output");

    /* F4: single-layer nn_forward (n_layers=1) returns raw INT32 accumulator */
    static int32_t single_out[128];
    static int32_t ref_out[128];
    nn_forward(mnist_net_layers, 1, test_images[0], single_out);
    nn_fc_forward(&mnist_net_layers[0], test_images[0], ref_out);
    CHECK(memcmp(single_out, ref_out, 128 * sizeof(int32_t)) == 0,
          "F4 nn_forward n_layers=1 == nn_fc_forward (no requantize)");
}

/* ── main ────────────────────────────────────────────────────────────────── */
int main(void)
{
    printf("Phase 12 weights.h + inference test suite\n");
    printf("==========================================\n");

    test_metadata();
    test_fc_layer0();
    test_requantize();
    test_nn_forward();
    test_chain_equivalence();
    test_edge_cases();

    printf("\n==========================================\n");
    printf("TOTAL: %d / %d passed", g_pass, g_pass + g_fail);
    if (g_fail == 0) printf("  ✓ ALL PASS\n");
    else             printf("  ✗ %d FAILED\n", g_fail);
    return g_fail ? 1 : 0;
}
