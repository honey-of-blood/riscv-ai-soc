#ifndef NN_H
#define NN_H

#include <stdint.h>

/* ── Accelerator / scratchpad addresses ──────────────────────────────────── */
#define ACCEL_BASE    0x50000000u
#define SP_BASE       0x50010000u   /* scratchpad AXI write aperture          */

/* Accelerator register offsets from ACCEL_BASE */
#define ACCEL_CTRL    0x000u        /* [0]=start  [1]=done(RO)  [2]=relu_en   */
#define ACCEL_ACT     0x004u        /* ACT_BASE — scratchpad row # of act[0]  */
#define ACCEL_WROW(r) (0x008u + (r)*4u)  /* W_row[r], packed N INT8 weights  */
#define ACCEL_Y(c)    (0x100u + (c)*4u)  /* Y[c] — INT32 output column c     */

/* Systolic array dimension (must match RTL parameter N) */
#define NN_N  4

/* ── Layer descriptor ────────────────────────────────────────────────────── */
typedef struct {
    uint32_t  in_size;   /* input dimension                                  */
    uint32_t  out_size;  /* output dimension                                 */
    int8_t   *weights;   /* [out_size × in_size] INT8, row-major             */
    int32_t  *bias;      /* [out_size] INT32                                 */
    uint8_t   relu;      /* 1 = apply ReLU after accumulation                */
} nn_layer_t;

/* ── API ─────────────────────────────────────────────────────────────────── */

/*
 * nn_fc_forward — run one fully-connected layer through the systolic accelerator.
 *   layer  : layer descriptor
 *   input  : INT8 activations of length layer->in_size
 *   output : INT32 accumulator of length layer->out_size (written by this fn)
 */
void nn_fc_forward(const nn_layer_t *layer,
                   const int8_t     *input,
                   int32_t          *output);

/*
 * nn_requantize — clip INT32 accumulator to INT8 for the next layer.
 *   in          : INT32 inputs of length len
 *   out         : INT8  outputs of length len
 *   scale       : fixed-point scale factor (Q16: actual_scale = scale / 65536)
 *   zero_point  : INT32 zero-point added before clipping
 *   len         : number of elements
 */
void nn_requantize(const int32_t *in,
                   int8_t        *out,
                   int32_t        scale,
                   int32_t        zero_point,
                   uint32_t       len);

/*
 * nn_forward — run a complete multi-layer network.
 *   layers   : array of layer descriptors (n_layers elements)
 *   n_layers : number of layers
 *   input    : INT8 network input  (length layers[0].in_size)
 *   output   : INT32 final output  (length layers[n_layers-1].out_size)
 *
 * Intermediate INT32→INT8 requantization uses scale=65536 (1.0), zp=0.
 * For accurate multi-layer inference supply per-layer scales via a custom loop.
 */
void nn_forward(const nn_layer_t *layers,
                int               n_layers,
                const int8_t     *input,
                int32_t          *output);

#endif /* NN_H */
