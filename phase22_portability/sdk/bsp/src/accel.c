/* accel.c — AI Accelerator v3 driver */
#include <string.h>
#include "accel.h"
#include "soc.h"

#define ACCEL_REG(off)  REG32(ACCEL_BASE, (off))
#define ACCEL_SP(off)   REG32(ACCEL_BASE + ACCEL_SCRATCHPAD, (off))

void accel_init(void) {
    ACCEL_REG(ACCEL_CTRL) = ACCEL_CTRL_RST;
    ACCEL_REG(ACCEL_CTRL) = 0;
    /* Clear scratchpad */
    volatile uint32_t *sp = (volatile uint32_t *)(ACCEL_BASE + ACCEL_SCRATCHPAD);
    for (int i = 0; i < 1024; i++) sp[i] = 0;
}

static int _launch(const int4x2_t *A, const int4x2_t *B, int32_t *C,
                   uint32_t M, uint32_t K, uint32_t N, int blocking) {
    /* Pack A and B into scratchpad.
     * Layout: A at offset 0, B after A. */
    uint32_t a_bytes = (M * K + 1) / 2;  /* INT4 packed: 2 per byte */
    uint32_t b_bytes = (K * N + 1) / 2;
    uint32_t a_off   = 0;
    uint32_t b_off   = (a_bytes + 3) & ~3u;  /* word-align */

    volatile uint8_t *sp = (volatile uint8_t *)(ACCEL_BASE + ACCEL_SCRATCHPAD);
    for (uint32_t i = 0; i < a_bytes; i++) sp[a_off + i] = (uint8_t)A[i];
    for (uint32_t i = 0; i < b_bytes; i++) sp[b_off + i] = (uint8_t)B[i];

    ACCEL_REG(ACCEL_DIM_M)  = M;
    ACCEL_REG(ACCEL_DIM_K)  = K;
    ACCEL_REG(ACCEL_DIM_N)  = N;
    ACCEL_REG(ACCEL_A_ADDR) = ACCEL_BASE + ACCEL_SCRATCHPAD + a_off;
    ACCEL_REG(ACCEL_B_ADDR) = ACCEL_BASE + ACCEL_SCRATCHPAD + b_off;
    ACCEL_REG(ACCEL_C_ADDR) = (uint32_t)C;
    ACCEL_REG(ACCEL_CTRL)   = ACCEL_CTRL_START;

    if (!blocking) return 0;

    /* Blocking wait */
    while (!(ACCEL_REG(ACCEL_STATUS) & ACCEL_STATUS_DONE)) {}
    if (ACCEL_REG(ACCEL_STATUS) & ACCEL_STATUS_ERR) return -1;
    return 0;
}

int accel_matmul_int4(const int4x2_t *A, const int4x2_t *B,
                      int32_t *C, uint32_t M, uint32_t K, uint32_t N) {
    return _launch(A, B, C, M, K, N, 1);
}

int accel_matmul_async(const int4x2_t *A, const int4x2_t *B,
                       int32_t *C, uint32_t M, uint32_t K, uint32_t N) {
    return _launch(A, B, C, M, K, N, 0);
}

int accel_poll_done(void) {
    return (ACCEL_REG(ACCEL_STATUS) & ACCEL_STATUS_DONE) != 0;
}

uint32_t accel_cycles(void) {
    return ACCEL_REG(ACCEL_CYCLES);
}
