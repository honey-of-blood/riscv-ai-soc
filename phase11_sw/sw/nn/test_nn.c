/*
 * test_nn.c — aggressive host-side validation of Phase 11 nn library.
 *
 * Compile:
 *   gcc -O2 -Wall -Wextra -DTEST_HOST -I. test_nn.c nn_host.c -o build/test_nn
 *
 * Coverage:
 *   A) nn_fc_forward  — 29 cases from test_vectors.h
 *   B) nn_requantize  — 10 cases from test_vectors.h + len=0
 *   C) nn_forward     — 5 multi-layer chain cases
 *   D) pxPortInitialiseStack — 5 frame-layout checks
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "nn.h"
#include "test_vectors.h"

static int g_pass = 0;
static int g_fail = 0;

#define CHECK(cond, fmt, ...) do {                              \
    if (cond) { g_pass++; }                                     \
    else { g_fail++;                                            \
           printf("  FAIL: " fmt "\n", ##__VA_ARGS__); }        \
} while (0)

static void section(const char *n) { printf("\n── %s ──\n", n); }

/* ══════════════════════════════════════════════════════════════════════════
 * A) nn_fc_forward
 * ══════════════════════════════════════════════════════════════════════════ */
static void test_fc_forward(void)
{
    section("A) nn_fc_forward");
    printf("%-4s %-24s %-10s %-6s  Result\n",
           "T", "Label", "Shape", "ReLU");
    printf("%-4s %-24s %-10s %-6s  ------\n",
           "---","------------------------","----------","------");

    for (int t = 0; t < NUM_FC_CASES; t++) {
        fc_case_t *tc = &fc_cases[t];
        nn_layer_t layer = { tc->in_size, tc->out_size,
                             tc->weights, tc->bias, tc->relu };

        int32_t *out = (int32_t *)calloc(tc->out_size, sizeof(int32_t));
        nn_fc_forward(&layer, tc->input, out);

        int ok = 1;
        for (uint32_t i = 0; i < tc->out_size; i++) {
            if (out[i] != tc->ref[i]) {
                printf("  [A T%d %s] out[%u]=%d exp=%d\n",
                       t, tc->label, i, out[i], tc->ref[i]);
                if (i >= 3) { printf("  ...\n"); }
                ok = 0; break;
            }
        }
        free(out);

        char shape[20];
        snprintf(shape, sizeof(shape), "%u→%u", tc->in_size, tc->out_size);
        printf("T%-3d %-24s %-10s %-6d  %s\n",
               t, tc->label, shape, (int)tc->relu, ok ? "PASS" : "FAIL");
        if (ok) g_pass++; else g_fail++;
    }
}

/* ══════════════════════════════════════════════════════════════════════════
 * B) nn_requantize
 * ══════════════════════════════════════════════════════════════════════════ */
static void test_requantize(void)
{
    section("B) nn_requantize");

    for (int t = 0; t < NUM_RQ_CASES; t++) {
        rq_case_t *tc = &rq_cases[t];

        int8_t *out = (int8_t *)calloc(tc->len + 1, 1);
        out[tc->len] = 0x5A; /* sentinel */
        nn_requantize(tc->in, out, tc->scale_q16, tc->zero_point, tc->len);

        int ok = 1;
        for (uint32_t i = 0; i < tc->len; i++) {
            if (out[i] != tc->ref[i]) {
                printf("  [B T%d %s] out[%u]=%d exp=%d\n",
                       t, tc->label, i, (int)out[i], (int)tc->ref[i]);
                ok = 0; break;
            }
        }
        if (out[tc->len] != 0x5A) {
            printf("  [B T%d] sentinel clobbered\n", t);
            ok = 0;
        }
        free(out);

        printf("RQ T%-2d %-26s  %s\n", t, tc->label, ok ? "PASS" : "FAIL");
        if (ok) g_pass++; else g_fail++;
    }

    /* len=0 must not crash */
    nn_requantize(NULL, NULL, 65536, 0, 0);
    printf("RQ T%-2d %-26s  PASS\n", NUM_RQ_CASES, "len=0 no crash");
    g_pass++;
}

/* ══════════════════════════════════════════════════════════════════════════
 * C) nn_forward — multi-layer chaining
 * ══════════════════════════════════════════════════════════════════════════ */
static void test_forward(void)
{
    section("C) nn_forward");

#define FWD_CHECK(label, cond)                                  \
    do { int _ok = (cond);                                      \
         printf("FC %-4s %-26s  %s\n", #label, label,          \
                _ok ? "PASS" : "FAIL");                         \
         if (_ok) g_pass++; else g_fail++; } while (0)

    /* C1: single layer — diagonal weight, bias. */
    {
        static int8_t  W[4][4] = {{1,0,0,0},{0,2,0,0},{0,0,3,0},{0,0,0,4}};
        static int32_t B[4]    = {10, 20, 30, 40};
        int8_t  x[4] = {1, 2, 3, 4};
        nn_layer_t L[1] = {{4,4,(int8_t*)W,B,0}};
        int32_t out[4], ref[4] = {11, 24, 39, 56};
        nn_forward(L, 1, x, out);
        FWD_CHECK("C1 1-layer diag", memcmp(out,ref,sizeof(ref))==0);
    }

    /* C2: two layers no relu — layer0=identity, layer1=2×+1. */
    {
        static int8_t  W0[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
        static int32_t B0[4]    = {0,0,0,0};
        static int8_t  W1[4][4] = {{2,0,0,0},{0,2,0,0},{0,0,2,0},{0,0,0,2}};
        static int32_t B1[4]    = {1,1,1,1};
        int8_t  x[4] = {3,5,7,9};
        nn_layer_t L[2] = {{4,4,(int8_t*)W0,B0,0},{4,4,(int8_t*)W1,B1,0}};
        int32_t out[4], ref[4] = {7,11,15,19};
        nn_forward(L, 2, x, out);
        FWD_CHECK("C2 2-layer diag", memcmp(out,ref,sizeof(ref))==0);
    }

    /* C3: two layers, relu in layer 0 kills all (negate input, then relu → 0). */
    {
        static int8_t  W0[4][4] = {{-1,0,0,0},{0,-1,0,0},{0,0,-1,0},{0,0,0,-1}};
        static int32_t B0[4]    = {0,0,0,0};
        static int8_t  W1[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
        static int32_t B1[4]    = {5,10,15,20};
        int8_t  x[4] = {3,5,7,9};
        nn_layer_t L[2] = {{4,4,(int8_t*)W0,B0,1},{4,4,(int8_t*)W1,B1,0}};
        int32_t out[4], ref[4] = {5,10,15,20};
        nn_forward(L, 2, x, out);
        FWD_CHECK("C3 relu kills layer0", memcmp(out,ref,sizeof(ref))==0);
    }

    /* C4: three layers — identity+bias at each, input [1,2,3,4]. */
    {
        static int8_t  WI[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
        static int32_t BI[4]    = {1,1,1,1};
        int8_t  x[4] = {1,2,3,4};
        nn_layer_t L[3] = {
            {4,4,(int8_t*)WI,BI,0},
            {4,4,(int8_t*)WI,BI,0},
            {4,4,(int8_t*)WI,BI,0},
        };
        int32_t out[4], ref[4] = {4,5,6,7};
        nn_forward(L, 3, x, out);
        FWD_CHECK("C4 3-layer id+bias", memcmp(out,ref,sizeof(ref))==0);
    }

    /* C5: 4→1 single output neuron. */
    {
        static int8_t  W[1][4] = {{1,2,3,4}};
        static int32_t B[1]    = {0};
        int8_t  x[4] = {1,2,3,4};
        nn_layer_t L[1] = {{4,1,(int8_t*)W,B,0}};
        int32_t out[1];
        nn_forward(L, 1, x, out);
        /* 1+4+9+16 = 30 */
        FWD_CHECK("C5 4→1 dot product", out[0] == 30);
    }
}

/* ══════════════════════════════════════════════════════════════════════════
 * D) pxPortInitialiseStack — stack frame layout
 * ══════════════════════════════════════════════════════════════════════════ */

typedef uint32_t StackType_t;
typedef void (*TaskFunction_t)(void *);
#define PORT_CONTEXT_WORDS      32   /* 32×4=128 bytes — multiple of 16 (RISC-V ABI) */
#define portBYTE_ALIGNMENT_MASK 15u

/* Inline reimplementation matching port.c exactly — no FreeRTOS dependency. */
static StackType_t *pxPortInitialiseStack_host(StackType_t *pxTopOfStack,
                                               TaskFunction_t pxCode,
                                               void *pvParameters)
{
    pxTopOfStack = (StackType_t *)
        (((uintptr_t)pxTopOfStack) & ~((uintptr_t)portBYTE_ALIGNMENT_MASK));
    pxTopOfStack -= PORT_CONTEXT_WORDS;
    pxTopOfStack[0] = 0x00001880u;
    pxTopOfStack[1] = (StackType_t)(uintptr_t)pxCode;
    for (int i = 2; i < PORT_CONTEXT_WORDS; i++) pxTopOfStack[i] = 0u;
    pxTopOfStack[8] = (StackType_t)(uintptr_t)pvParameters;
    return pxTopOfStack;
}

static void dummy_task(void *p) { (void)p; }

static void test_port_stack(void)
{
    section("D) pxPortInitialiseStack");

    static StackType_t stack[64];
    void *param = (void *)0xDEADBEEFu;
    StackType_t *sp = pxPortInitialiseStack_host(&stack[63], dummy_task, param);

    CHECK(((uintptr_t)sp & 15u) == 0,
          "D1 SP 16-byte aligned (sp=%p)", (void *)sp);
    CHECK((sp[0] & 0x1800u) == 0x1800u,
          "D2 mstatus MPP=11: got 0x%08x", sp[0]);
    CHECK((sp[0] & 0x80u) != 0,
          "D3 mstatus MPIE=1: got 0x%08x", sp[0]);
    CHECK((uint32_t)sp[1] == (uint32_t)(uintptr_t)dummy_task,
          "D4 mepc=pxCode: got 0x%08x exp 0x%08x",
          sp[1], (uint32_t)(uintptr_t)dummy_task);
    CHECK((uint32_t)sp[8] == (uint32_t)(uintptr_t)param,
          "D5 sp[8]=pvParameters: got 0x%08x exp 0x%08x",
          sp[8], (uint32_t)(uintptr_t)param);

    int all_zero = 1;
    for (int i = 2; i < PORT_CONTEXT_WORDS; i++) {
        if (i == 8) continue;
        if (sp[i] != 0) { all_zero = 0;
            printf("  D6 sp[%d]=0x%08x expected 0\n", i, sp[i]); }
    }
    CHECK(all_zero, "D6 all other regs = 0");
}

/* ══════════════════════════════════════════════════════════════════════════
 * main
 * ══════════════════════════════════════════════════════════════════════════ */
int main(void)
{
    printf("Phase 11 nn + port test suite\n");
    printf("================================\n");
    test_fc_forward();
    test_requantize();
    test_forward();
    test_port_stack();
    printf("\n================================\n");
    printf("TOTAL: %d / %d passed", g_pass, g_pass + g_fail);
    if (g_fail == 0) printf("  ✓ ALL PASS\n");
    else             printf("  ✗ %d FAILED\n", g_fail);
    return g_fail ? 1 : 0;
}
