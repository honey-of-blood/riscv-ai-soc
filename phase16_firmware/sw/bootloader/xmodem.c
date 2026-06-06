#include "xmodem.h"
#include "uart.h"
#include <string.h>

static uint8_t checksum8(const uint8_t *buf, size_t len) {
    uint8_t s = 0;
    for (size_t i = 0; i < len; i++)
        s += buf[i];
    return s;
}

int xmodem_receive(uint8_t *buf, size_t buf_size) {
    uint8_t  block[XMODEM_BLOCK_SIZE];
    int      total     = 0;
    uint8_t  expected  = 1;
    int      retries   = 0;
    int      c;

    /* Kick-start the sender with NAK. */
    uart_putc(XMODEM_NAK);

    while (1) {
        c = uart_getc_timeout(XMODEM_TIMEOUT_MS);
        if (c < 0) {
            /* Timeout — NAK again if still waiting for first block. */
            if (total == 0 && retries < XMODEM_MAX_RETRIES) {
                retries++;
                uart_putc(XMODEM_NAK);
                continue;
            }
            return -1;
        }

        if (c == XMODEM_EOT) {
            uart_putc(XMODEM_ACK);
            return total;
        }

        if (c == XMODEM_CAN) {
            return -1;
        }

        if (c != XMODEM_SOH) {
            /* Garbage byte — ignore. */
            continue;
        }

        /* Read block# and complement. */
        int blk = uart_getc_timeout(XMODEM_TIMEOUT_MS);
        int inv = uart_getc_timeout(XMODEM_TIMEOUT_MS);
        if (blk < 0 || inv < 0 || ((blk ^ inv) != 0xFF)) {
            uart_putc(XMODEM_NAK);
            retries++;
            if (retries >= XMODEM_MAX_RETRIES) return -1;
            continue;
        }

        /* Read 128 data bytes. */
        for (int i = 0; i < XMODEM_BLOCK_SIZE; i++) {
            c = uart_getc_timeout(XMODEM_TIMEOUT_MS);
            if (c < 0) { uart_putc(XMODEM_NAK); goto retry; }
            block[i] = (uint8_t)c;
        }

        /* Read checksum. */
        int csum = uart_getc_timeout(XMODEM_TIMEOUT_MS);
        if (csum < 0 || (uint8_t)csum != checksum8(block, XMODEM_BLOCK_SIZE)) {
            uart_putc(XMODEM_NAK);
            retries++;
            if (retries >= XMODEM_MAX_RETRIES) return -1;
            continue;
        }

        /* Duplicate block (sender retransmitted after a lost ACK) — ACK silently. */
        if ((uint8_t)blk == (uint8_t)(expected - 1)) {
            uart_putc(XMODEM_ACK);
            continue;
        }

        if ((uint8_t)blk != expected) {
            /* Wrong block — cancel. */
            uart_putc(XMODEM_CAN);
            return -1;
        }

        /* Good block — copy to caller's buffer. */
        size_t room = buf_size - (size_t)total;
        size_t copy = (room < XMODEM_BLOCK_SIZE) ? room : XMODEM_BLOCK_SIZE;
        memcpy(buf + total, block, copy);
        total   += (int)copy;
        expected = (uint8_t)(expected + 1);
        retries  = 0;
        uart_putc(XMODEM_ACK);
        continue;

retry:
        retries++;
        if (retries >= XMODEM_MAX_RETRIES) return -1;
    }
}
