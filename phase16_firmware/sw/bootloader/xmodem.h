#ifndef XMODEM_H
#define XMODEM_H

#include <stdint.h>
#include <stddef.h>

/* Standard XMODEM (128-byte blocks, 8-bit checksum).
 *
 * Receive flow:
 *   1. Send NAK to initiate.
 *   2. For each incoming SOH packet: verify block# / ~block# / checksum.
 *      ACK on pass, NAK on error (up to XMODEM_MAX_RETRIES retries per block).
 *   3. EOT → send ACK, return total bytes written.
 *   4. On CAN or too many errors → return -1.
 */

#define XMODEM_SOH          0x01
#define XMODEM_EOT          0x04
#define XMODEM_ACK          0x06
#define XMODEM_NAK          0x15
#define XMODEM_CAN          0x18

#define XMODEM_BLOCK_SIZE   128
#define XMODEM_MAX_RETRIES  10
#define XMODEM_TIMEOUT_MS   3000

/* Receive a full XMODEM stream into buf (max buf_size bytes).
 * Returns number of bytes received on success, -1 on error/cancel. */
int xmodem_receive(uint8_t *buf, size_t buf_size);

#endif /* XMODEM_H */
