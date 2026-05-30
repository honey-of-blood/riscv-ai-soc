/*
 * test_nn.c — host-side validation of nn_fc_forward against numpy reference.
 *
 * This test runs on a PC (x86/arm) to verify the C logic in nn.c before
 * deploying to the SoC. It replaces the MMIO calls to the systolic accelerator
 * with a pure software emulation of the same computation.
 *
 * Compile:
 *   gcc -O2 -Wall -Wextra -DTEST_HOST -I. test_nn.c nn_host.c \
 *       -o test_nn && ./test_nn
 *
 * On the SoC, link nn.c instead of nn_host.c. nn_host.c provides the same
 * nn_fc_forward/nn_requantize/nn_forward symbols but uses scalar C arithmetic
 * instead of MMIO, so host tests can run without hardware.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "nn.h"
#include "test_vectors.h"

/* ── Test runner ─────────────────────────────────────────────────────────── */

int main(void)
{
    int pass = 0, fail = 0;

    printf("nn_fc_forward unit tests\n");
    printf("%-6s %-10s %-6s %s\n", "Case", "Shape", "ReLU", "Result");
    printf("------ ---------- ------ ------\n");

    for (int t = 0; t < NUM_TEST_CASES; t++) {
        test_case_t *tc = &test_cases[t];

        /* Build nn_layer_t from test case. */
        nn_layer_t layer = {
            .in_size  = tc->in_size,
            .out_size = tc->out_size,
            .weights  = tc->weights,
            .bias     = tc->bias,
            .relu     = tc->relu,
        };

        int32_t output[512];
        memset(output, 0, sizeof(output));

        nn_fc_forward(&layer, tc->input, output);

        /* Compare against numpy reference. */
        int ok = 1;
        for (uint32_t i = 0; i < tc->out_size; i++) {
            if (output[i] != tc->ref[i]) {
                ok = 0;
                printf("  MISMATCH at output[%u]: got %d  expected %d\n",
                       i, output[i], tc->ref[i]);
                break;
            }
        }

        printf("T%-5d %4u→%-5u %-6d %s\n",
               t, tc->in_size, tc->out_size, (int)tc->relu,
               ok ? "PASS" : "FAIL");

        if (ok) pass++; else fail++;
    }

    printf("\n%d / %d passed\n", pass, pass + fail);
    return fail ? 1 : 0;
}
