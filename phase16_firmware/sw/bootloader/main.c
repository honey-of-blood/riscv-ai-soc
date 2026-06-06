#include <stdint.h>
#include "uart.h"
#include "xmodem.h"

/* Bootloader image area starts immediately above the 4 KB bootloader ROM.
 * On FPGA the instruction BRAM (instr_bram.sv) is dual-ported:
 *   Port A → CPU instruction fetch
 *   Port B → this data write (accessible at BRAM_WR_BASE via AXI S3)
 * Writing here overwrites instruction memory; jumping to APP_ENTRY executes it. */
#define BRAM_WR_BASE  0x20000000UL   /* AXI S3 — boot-write port of instr_bram */
#define APP_ENTRY     0x00001000UL   /* App code starts 4 KB into instruction BRAM */
#define APP_MAX_BYTES (60 * 1024)    /* 60 KB of the 64 KB BRAM for the app */

/* ELF32 magic: 0x7f 'E' 'L' 'F' */
#define ELF_MAGIC  0x464C457FUL

static uint8_t rx_buf[APP_MAX_BYTES];

static void jump_to_app(void) {
    void (*entry)(void) = (void (*)(void))APP_ENTRY;
    entry();
    /* Should never return; halt the CPU if it does. */
    while (1) __asm__ volatile ("wfi");
}

void boot(void) {
    uart_puts("\r\nRV32 Bootloader v1.0\r\n"
              "Send XMODEM image or wait 3 s to boot existing app\r\n");

    /* Wait up to 3 s for the first NAK-trigger byte from the host. */
    int first = uart_getc_timeout(3000);
    if (first < 0) {
        /* No host — boot whatever is already in the app region. */
        uart_puts("Timeout — jumping to app\r\n");
        jump_to_app();
    }

    /* Host connected: re-push the byte we consumed (it was just a presence
     * signal) and start XMODEM.  xmodem_receive sends its own NAK first. */
    int received = xmodem_receive(rx_buf, sizeof(rx_buf));
    if (received <= 0) {
        uart_puts("Transfer failed\r\n");
        return;
    }

    /* ELF magic check. */
    uint32_t magic;
    __builtin_memcpy(&magic, rx_buf, 4);
    if (magic != ELF_MAGIC) {
        uart_puts("Bad ELF magic — rejected\r\n");
        return;
    }

    uart_puts("ELF received, writing to BRAM...\r\n");

    /* Write received image to the instruction BRAM via Port B (AXI S3).
     * We skip the first 4 KB (offset 0x1000) so the bootloader itself
     * is not overwritten; apps must be linked at 0x0000_1000. */
    volatile uint32_t *bram = (volatile uint32_t *)BRAM_WR_BASE;
    uint32_t *src = (uint32_t *)rx_buf;
    int words = (received + 3) / 4;
    /* App starts at word offset 0x400 (= 4 KB / 4). */
    for (int i = 0; i < words; i++)
        bram[0x400 + i] = src[i];

    uart_puts("OK — jumping to app at 0x00001000\r\n");
    jump_to_app();
}

/* Entry point called by crt0.S after BSS clear. */
int main(void) {
    boot();
    return 0;
}
