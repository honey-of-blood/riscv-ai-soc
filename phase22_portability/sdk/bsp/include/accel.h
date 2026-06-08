/* accel.h — AI Accelerator v3 (INT4 systolic array) driver API */
#ifndef ACCEL_H_
#define ACCEL_H_

#include <stdint.h>
#include "soc.h"

/* ── Accelerator register map (base = ACCEL_BASE = 0x5000_0000) ─────────── */
#define ACCEL_CTRL       0x000U  /* Control: [0]=start [1]=reset [2]=ie */
#define ACCEL_STATUS     0x004U  /* Status:  [0]=busy [1]=done [2]=error */
#define ACCEL_DIM_M      0x008U  /* Output rows M (1..64) */
#define ACCEL_DIM_K      0x00CU  /* Inner dimension K (1..64) */
#define ACCEL_DIM_N      0x010U  /* Output cols N (1..64) */
#define ACCEL_A_ADDR     0x014U  /* SRAM byte address of matrix A (INT4, packed) */
#define ACCEL_B_ADDR     0x018U  /* SRAM byte address of matrix B (INT4, packed) */
#define ACCEL_C_ADDR     0x01CU  /* SRAM byte address of output C (INT32) */
#define ACCEL_CYCLES     0x020U  /* Cycle counter for the last operation (RO) */
#define ACCEL_SCRATCHPAD 0x1000U /* 4 KB INT4 scratchpad (byte-addressable) */

/* ── Status bits ─────────────────────────────────────────────────────────── */
#define ACCEL_STATUS_BUSY  (1u << 0)
#define ACCEL_STATUS_DONE  (1u << 1)
#define ACCEL_STATUS_ERR   (1u << 2)

/* ── Control bits ────────────────────────────────────────────────────────── */
#define ACCEL_CTRL_START (1u << 0)
#define ACCEL_CTRL_RST   (1u << 1)
#define ACCEL_CTRL_IE    (1u << 2)

/* ── Data types ──────────────────────────────────────────────────────────── */
/* INT4 is packed two nibbles per byte: byte = {hi_nibble, lo_nibble} */
typedef int8_t  int4x2_t;   /* two INT4 values packed in one byte */
typedef int32_t int32_t;

/* ── API ─────────────────────────────────────────────────────────────────── */

/** accel_init - reset accelerator and clear scratchpad */
void accel_init(void);

/**
 * accel_matmul_int4 - compute C = A × B where A is M×K and B is K×N (INT4)
 *
 * @A:   pointer to packed INT4 matrix A (row-major, 2 elements per byte)
 * @B:   pointer to packed INT4 matrix B
 * @C:   output buffer for INT32 result matrix (M×N words)
 * @M,K,N: matrix dimensions
 *
 * Copies A and B into the scratchpad, fires the accelerator, and
 * blocks until done.  Returns 0 on success, -1 on error.
 */
int accel_matmul_int4(const int4x2_t *A, const int4x2_t *B,
                      int32_t *C,
                      uint32_t M, uint32_t K, uint32_t N);

/**
 * accel_matmul_async - non-blocking version; call accel_poll_done() to wait
 */
int accel_matmul_async(const int4x2_t *A, const int4x2_t *B,
                       int32_t *C,
                       uint32_t M, uint32_t K, uint32_t N);

/** accel_poll_done - returns 1 when the accelerator has finished */
int accel_poll_done(void);

/** accel_cycles - returns cycle count of the last completed operation */
uint32_t accel_cycles(void);

#endif /* ACCEL_H_ */
