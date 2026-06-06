#include "conv2d.h"

// ── Accelerator primitives ────────────────────────────────────────────────

void accel_load_weights(const uint16_t *weights_packed) {
    for (int r = 0; r < TILE_N; r++)
        ACCEL_W_ROW(r) = weights_packed[r];
}

void accel_load_patch(uint16_t a_vec_packed) {
    ACCEL_A_VEC = a_vec_packed;
}

void accel_run(int relu_en) {
    uint32_t ctrl = ACCEL_CTRL_START | (relu_en ? ACCEL_CTRL_RELU : 0u);
    ACCEL_CTRL = ctrl;
    // Poll done
    while (!(ACCEL_CTRL & ACCEL_CTRL_DONE)) {}
    // Deassert start so the array returns to IDLE
    ACCEL_CTRL = relu_en ? ACCEL_CTRL_RELU : 0u;
}

void accel_read_output(int32_t *out) {
    for (int c = 0; c < TILE_N; c++)
        out[c] = (int32_t)ACCEL_Y(c);
}

// ── Output-stationary Conv2D tile ─────────────────────────────────────────
// Computes Y[oc] = Σ_k  W[oc][k] * patch[k]  for oc = 0..OC-1.
// Each tile of TILE_N output channels is run as one systolic array pass.
//
// In an output-stationary dataflow the partial sums stay in the accumulator
// registers; here we approximate this by accumulating across patch elements
// on the host and issuing one accel_run per (OC_tile, patch_element) pair.
// A future revision can use the scratchpad DMA for full systolic utilisation.
void conv2d_tile(const uint16_t *in_patch, const uint16_t *weights,
                 int32_t *out, int OC, int patch_elems) {
    int n_tiles = (OC + TILE_N - 1) / TILE_N;

    for (int t = 0; t < n_tiles; t++) {
        // Accumulate partial sums for this OC tile
        int32_t acc[TILE_N] = {0};

        for (int k = 0; k < patch_elems; k++) {
            // weights for this tile, patch element k:
            // layout: [n_tiles][patch_elems][TILE_N rows] packed rows
            const uint16_t *tile_w = weights + (t * patch_elems + k) * TILE_N;
            accel_load_weights(tile_w);
            accel_load_patch(in_patch[k]);
            accel_run(0);

            int32_t y[TILE_N];
            accel_read_output(y);
            for (int c = 0; c < TILE_N; c++) acc[c] += y[c];
        }

        int oc_base = t * TILE_N;
        int oc_end  = (oc_base + TILE_N < OC) ? oc_base + TILE_N : OC;
        for (int c = 0; c < oc_end - oc_base; c++)
            out[oc_base + c] = acc[c];
    }
}
