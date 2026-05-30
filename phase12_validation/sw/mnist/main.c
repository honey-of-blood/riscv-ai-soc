/*
 * mnist/main.c — Phase 12 MNIST digit classification demo.
 *
 * Runs 10 inference passes (one per test image in weights.h) and prints
 * the predicted digit class over UART.  With real trained weights produced
 * by train_mnist.py + quantize.py, expected accuracy ≥ 97% on held-out images.
 *
 * UART output (115200 8N1):
 *   MNIST Inference Demo
 *   ====================
 *   Image 0: predicted=X  expected=0  [OK / WRONG]
 *   ...
 *   Image 9: predicted=X  expected=9  [OK / WRONG]
 *   ====================
 *   Accuracy: N/10
 *
 * Build:
 *   riscv32-unknown-elf-gcc -O2 -march=rv32im -mabi=ilp32 \
 *     -I../../../phase11_sw/sw/nn -I../../../phase8_peripherals/sw/hal \
 *     -nostdlib -nostartfiles -T ../../../../phase7_fpga/sw/linker.ld \
 *     ../../../phase7_fpga/sw/crt0.S main.c \
 *     ../../../phase11_sw/sw/nn/nn.c \
 *     -o mnist.elf
 */

#include <stdint.h>
#include "nn.h"
#include "periph_base.h"
#include "uart.h"
#include "../weights.h"

/* ── Integer print helpers ───────────────────────────────────────────────── */

static void uart_digit(int v) { uart_putc('0' + (v & 0xF)); }

static void uart_int(int v)
{
    if (v < 0) { uart_putc('-'); v = -v; }
    char buf[12];
    int n = 0;
    if (v == 0) { uart_putc('0'); return; }
    while (v) { buf[n++] = '0' + (v % 10); v /= 10; }
    for (int i = n - 1; i >= 0; i--) uart_putc(buf[i]);
}

/* ── Argmax over INT32 array ─────────────────────────────────────────────── */
static int argmax(const int32_t *arr, int len)
{
    int best = 0;
    for (int i = 1; i < len; i++)
        if (arr[i] > arr[best]) best = i;
    return best;
}

/* ── Output buffers (static — avoids stack overflow on embedded) ─────────── */
static int32_t output[10];   /* final INT32 logits */

/* ── main ────────────────────────────────────────────────────────────────── */
int main(void)
{
    uart_puts("\r\nMNIST Inference Demo\r\n");
    uart_puts("====================\r\n");

    int correct = 0;

    for (int img = 0; img < 10; img++) {
        /* Run the full two-layer network. */
        nn_forward(mnist_net_layers, MNIST_NET_N_LAYERS,
                   test_images[img], output);

        int predicted = argmax(output, 10);
        int expected  = expected_labels[img];
        int ok        = (predicted == expected);
        if (ok) correct++;

        uart_puts("Image ");
        uart_digit(img);
        uart_puts(": predicted=");
        uart_digit(predicted);
        uart_puts("  expected=");
        uart_digit(expected);
        uart_puts(ok ? "  [OK]\r\n" : "  [WRONG]\r\n");
    }

    uart_puts("====================\r\n");
    uart_puts("Accuracy: ");
    uart_int(correct);
    uart_puts("/10\r\n");

    /* Print raw logits for the last image to aid debugging. */
    uart_puts("Logits[9]: ");
    for (int i = 0; i < 10; i++) {
        uart_int(output[i]);
        uart_putc(' ');
    }
    uart_puts("\r\n");

    for (;;) {}
    return 0;
}
