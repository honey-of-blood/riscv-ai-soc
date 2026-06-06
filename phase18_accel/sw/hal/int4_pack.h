#ifndef INT4_PACK_H
#define INT4_PACK_H
// INT4 pack/unpack helpers for the Phase 18 AI accelerator.
// Two signed INT4 values are stored per byte: high nibble = element[2k+1],
// low nibble = element[2k].  Sign extension uses the 4th bit as sign bit.

#include <stdint.h>

// Pack two INT4 values into one byte (hi in [7:4], lo in [3:0])
static inline uint8_t pack_int4(int8_t hi, int8_t lo) {
    return (uint8_t)(((hi & 0xF) << 4) | (lo & 0xF));
}

// Unpack high nibble (sign-extended to int8_t)
static inline int8_t unpack_int4_hi(uint8_t packed) {
    int8_t v = (int8_t)(packed >> 4);
    if (v & 0x8) v |= (int8_t)0xF0;  // sign extend
    return v;
}

// Unpack low nibble (sign-extended to int8_t)
static inline int8_t unpack_int4_lo(uint8_t packed) {
    int8_t v = (int8_t)(packed & 0xF);
    if (v & 0x8) v |= (int8_t)0xF0;
    return v;
}

// Pack an array of n INT8 values (clamped to INT4 range -8..7) into packed bytes.
// out must hold ceil(n/2) bytes.
static inline void pack_int4_array(const int8_t *in, uint8_t *out, int n) {
    for (int i = 0; i < n; i += 2) {
        int8_t lo = (i     < n) ? in[i]     : 0;
        int8_t hi = (i + 1 < n) ? in[i + 1] : 0;
        // Clamp to [-8, 7]
        if (lo >  7) lo =  7;
        if (lo < -8) lo = -8;
        if (hi >  7) hi =  7;
        if (hi < -8) hi = -8;
        out[i / 2] = pack_int4(hi, lo);
    }
}

// Unpack ceil(n/2) packed bytes back into n INT8 values.
static inline void unpack_int4_array(const uint8_t *in, int8_t *out, int n) {
    for (int i = 0; i < n; i += 2) {
        out[i]     = unpack_int4_lo(in[i / 2]);
        if (i + 1 < n)
            out[i + 1] = unpack_int4_hi(in[i / 2]);
    }
}

// Build a 16-bit (N=4, ACT_W=4) packed weight word for one row.
// Elements: {w3[3:0], w2[3:0], w1[3:0], w0[3:0]}
static inline uint16_t pack_weight_row4(int8_t w0, int8_t w1, int8_t w2, int8_t w3) {
    return (uint16_t)(
        ((w3 & 0xF) << 12) | ((w2 & 0xF) << 8) |
        ((w1 & 0xF) <<  4) | ((w0 & 0xF) <<  0)
    );
}

#endif /* INT4_PACK_H */
