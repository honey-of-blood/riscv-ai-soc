# 5. AI Accelerator Reference

## Architecture

The AI Accelerator v3 is a 16×16 systolic array that operates on INT4 (4-bit signed) operands.

```
  Control Regs (0x5000_0000)
          │
  ┌───────▼────────────────────────────────────┐
  │  DMA Engine                                 │
  │  ┌──────────┐  feeds   ┌──────────────────┐│
  │  │ Scratchpad│  ──────► │ 16×16 Systolic   ││
  │  │ 4 KB INT4 │          │ Array (INT4 MAC)  ││
  │  └──────────┘          │ C = A × B INT32   ││
  │                         └──────────────────┘│
  └─────────────────────────────────────────────┘
```

## Performance Model

Peak INT4 throughput: 16×16×2 = 512 INT4 MAC/cycle at 100 MHz = **51.2 GOPS**.

Effective throughput for M×K×N matmul:
- Cycles = M×N×K / 256 + 2×(M×K + K×N)/4 (load latency)

## Programming Model {#programming-model}

### Register Map

| Offset | Name | R/W | Description |
|--------|------|-----|-------------|
| 0x00 | CTRL | R/W | [0]=START [1]=RST [2]=IE |
| 0x04 | STATUS | R | [0]=BUSY [1]=DONE [2]=ERR |
| 0x08 | DIM_M | R/W | Output rows M (1..64) |
| 0x0C | DIM_K | R/W | Inner dimension K (1..64) |
| 0x10 | DIM_N | R/W | Output columns N (1..64) |
| 0x14 | A_ADDR | R/W | SRAM byte address of matrix A |
| 0x18 | B_ADDR | R/W | SRAM byte address of matrix B |
| 0x1C | C_ADDR | R/W | SRAM byte address of output C |
| 0x20 | CYCLES | R | Cycle count of last operation |
| 0x1000..0x1FFF | SCRATCHPAD | R/W | 4 KB INT4 scratchpad |

### Computation Sequence

```c
accel_init();

// 1. Write matrix A and B into scratchpad
memcpy((void *)(ACCEL_BASE + ACCEL_SCRATCHPAD), A, a_bytes);
memcpy((void *)(ACCEL_BASE + ACCEL_SCRATCHPAD + b_off), B, b_bytes);

// 2. Configure dimensions
REG32_WR(ACCEL_BASE, ACCEL_DIM_M, M);
REG32_WR(ACCEL_BASE, ACCEL_DIM_K, K);
REG32_WR(ACCEL_BASE, ACCEL_DIM_N, N);
REG32_WR(ACCEL_BASE, ACCEL_A_ADDR, ACCEL_BASE + ACCEL_SCRATCHPAD);
REG32_WR(ACCEL_BASE, ACCEL_B_ADDR, ACCEL_BASE + ACCEL_SCRATCHPAD + b_off);
REG32_WR(ACCEL_BASE, ACCEL_C_ADDR, (uint32_t)C_out);

// 3. Start and poll
REG32_WR(ACCEL_BASE, ACCEL_CTRL, ACCEL_CTRL_START);
while (!(REG32_RD(ACCEL_BASE, ACCEL_STATUS) & ACCEL_STATUS_DONE)) {}
```

## INT4 Data Format

INT4 is packed two values per byte: `byte = (b_hi << 4) | (b_lo & 0xF)`.  
Values are 4-bit signed two's-complement: range −8 to +7.

**Quantization:** Use `tools/onnx_to_c.py --quantize int4` to convert a trained ONNX model to INT4 C arrays. Scale factors are computed per-layer using symmetric min-max quantization.

## Quantization Guide

| Step | Description |
|------|-------------|
| 1 | Train FP32 model in PyTorch/ONNX |
| 2 | Run `onnx_to_c.py` to quantize weights to INT4 |
| 3 | Compute per-layer scale factors (stored in `weights_*.h`) |
| 4 | Dequantize outputs: `output_fp = int32_result × scale_A × scale_B` |
| 5 | Verify accuracy: target ≥ 95% on MNIST, ≥ 90% on CIFAR-10 |
