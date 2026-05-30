/*
 * benchmark.c — Phase 12 inference latency benchmark.
 *
 * Measures and prints the cycle count and wall-clock time for:
 *   B1: FC 784 → 128 (one layer forward pass)
 *   B2: FC 128 → 10  (one layer forward pass)
 *   B3: Full MNIST forward pass (both layers, nn_forward)
 *
 * Output over UART (115200 8N1):
 *   BENCH FC 784->128 :  N cycles =  X.XXX ms
 *   BENCH FC 128-> 10 :  N cycles =  X.XXX ms
 *   BENCH MNIST fwd   :  N cycles =  X.XXX ms
 *   BENCH UART        :  N cycles =  X.XXX ms
 *
 * Build:
 *   riscv32-unknown-elf-gcc -O2 -march=rv32im -mabi=ilp32 \
 *     -I../../phase11_sw/sw/nn -I../../phase8_peripherals/sw/hal \
 *     -nostdlib -nostartfiles -T ../../../phase7_fpga/sw/linker.ld \
 *     ../../phase7_fpga/sw/crt0.S benchmark.c \
 *     ../../phase11_sw/sw/nn/nn.c \
 *     -o benchmark.elf
 */

#include <stdint.h>
#include "nn.h"
#include "periph_base.h"
#include "uart.h"
#include "clint.h"
#include "weights.h"

#define SYSCLK_HZ  100000000ULL   /* 100 MHz */

/* ── Integer formatting (no libc printf) ────────────────────────────────── */

static void uart_uint(uint32_t v)
{
    char buf[12];
    int n = 0;
    if (v == 0) { uart_putc('0'); return; }
    while (v) { buf[n++] = '0' + (v % 10); v /= 10; }
    while (n--) uart_putc(buf[n + 1]);  /* buf is reversed */
}

/* Print u32 as "X.XXX ms" where SYSCLK_HZ = 100 MHz, cycles to µs = /100. */
static void uart_cycles_ms(uint32_t cycles)
{
    /* ms = cycles / 100000, frac = (cycles % 100000) / 100 */
    uint32_t ms   = cycles / 100000;
    uint32_t frac = (cycles % 100000) / 100;   /* 0..999 */
    uart_uint(ms);
    uart_putc('.');
    /* zero-pad frac to 3 digits */
    if (frac < 100) uart_putc('0');
    if (frac <  10) uart_putc('0');
    uart_uint(frac);
    uart_puts(" ms");
}

static void report(const char *label, uint32_t cycles)
{
    uart_puts("BENCH ");
    uart_puts(label);
    uart_putc(':');
    uart_putc(' ');
    uart_uint(cycles);
    uart_puts(" cycles = ");
    uart_cycles_ms(cycles);
    uart_puts("\r\n");
}

/* ── Scratch buffers (static — avoids large stack frames) ───────────────── */
static int32_t acc0[128];   /* INT32 output of layer 0          */
static int8_t  rq0[128];    /* requantized INT8 inter-layer act  */
static int32_t acc1[10];    /* INT32 output of layer 1           */

/* Use first synthetic test image (class 0) as benchmark input. */
static const int8_t *bench_input = test_images[0];

/* ── main ────────────────────────────────────────────────────────────────── */
int main(void)
{
    uint64_t t0, t1;
    uint32_t cycles;

    uart_puts("\r\nPhase 12 Inference Benchmark\r\n");
    uart_puts("=============================\r\n");

    /* ── B1: FC 784 → 128 ─────────────────────────────────────────────── */
    t0 = clint_read_mtime();
    nn_fc_forward(&mnist_net_layers[0], bench_input, acc0);
    t1 = clint_read_mtime();
    cycles = (uint32_t)(t1 - t0);
    report("FC 784->128", cycles);

    /* ── B2: FC 128 → 10 ──────────────────────────────────────────────── */
    nn_requantize(acc0, rq0, W0_SCALE_Q16, 0, 128);   /* reuse layer-0 output */
    t0 = clint_read_mtime();
    nn_fc_forward(&mnist_net_layers[1], rq0, acc1);
    t1 = clint_read_mtime();
    cycles = (uint32_t)(t1 - t0);
    report("FC 128-> 10", cycles);

    /* ── B3: full two-layer MNIST forward pass ────────────────────────── */
    t0 = clint_read_mtime();
    nn_forward(mnist_net_layers, MNIST_NET_N_LAYERS, bench_input, acc1);
    t1 = clint_read_mtime();
    cycles = (uint32_t)(t1 - t0);
    report("MNIST fwd  ", cycles);

    /* ── B4: UART throughput — 100-byte burst ────────────────────────── */
    t0 = clint_read_mtime();
    for (int i = 0; i < 100; i++) uart_putc('X');
    t1 = clint_read_mtime();
    cycles = (uint32_t)(t1 - t0);
    uart_puts("\r\n");
    report("UART 100B  ", cycles);

    uart_puts("=============================\r\n");
    uart_puts("DONE\r\n");
    for (;;) {}
    return 0;
}
