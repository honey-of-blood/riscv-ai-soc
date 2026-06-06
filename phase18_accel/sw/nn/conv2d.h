#ifndef CONV2D_H
#define CONV2D_H
// Output-stationary Conv2D tiling for the Phase 18 systolic array.
// The outer loop tiles output channels in groups of N (array width).
// For each tile the functions call the accelerator HAL:
//   accel_load_weights  – DMA packed INT4 weights to accelerator
//   accel_load_patch    – DMA a receptive-field patch to scratchpad
//   accel_run           – start the systolic array and poll done
//   accel_read_output   – read N INT32 accumulator outputs

#include <stdint.h>
#include "../hal/int4_pack.h"

// Accelerator base address (mapped via AXI4 crossbar at Phase 9 slot)
#define ACCEL_BASE      0x50000000UL
#define ACCEL_CTRL      (*(volatile uint32_t *)(ACCEL_BASE + 0x00))
#define ACCEL_W_ROW(r)  (*(volatile uint32_t *)(ACCEL_BASE + 0x08 + (r)*4))
#define ACCEL_A_VEC     (*(volatile uint32_t *)(ACCEL_BASE + 0x28))
#define ACCEL_Y(c)      (*(volatile uint32_t *)(ACCEL_BASE + 0x100 + (c)*4))

#define ACCEL_CTRL_START  (1u << 0)
#define ACCEL_CTRL_DONE   (1u << 1)
#define ACCEL_CTRL_RELU   (1u << 2)
#define TILE_N            4         // array dimension (must match RTL parameter N)

// Load N weight rows (each row is N INT4 packed into VEC_W bits).
// weights: packed array, one 16-bit word per row.
void accel_load_weights(const uint16_t *weights_packed);

// Load one activation patch vector (N INT4 packed).
void accel_load_patch(uint16_t a_vec_packed);

// Start and poll done.
void accel_run(int relu_en);

// Read N INT32 outputs into out[0..N-1].
void accel_read_output(int32_t *out);

// High-level output-stationary Conv2D tiling.
// Computes a single output spatial position for all OC output channels.
// in_patch: flattened receptive field, kH*kW*IC INT4 elements packed.
// weights: [OC/TILE_N][TILE_N][kH*kW*IC] INT4 packed tiles.
// out: OC INT32 partial sums (caller adds bias / requantises).
void conv2d_tile(const uint16_t *in_patch, const uint16_t *weights,
                 int32_t *out, int OC, int patch_elems);

#endif /* CONV2D_H */
