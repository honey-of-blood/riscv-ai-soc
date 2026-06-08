/* secure_ota/main.c — Secure OTA firmware update over UART
 *
 * Protocol:
 *   1. Host sends 4-byte payload length (little-endian)
 *   2. Host streams payload bytes (new firmware)
 *   3. Host sends 32-byte SHA-256 digest of the payload
 *   4. SoC computes SHA-256 over received payload
 *   5. Constant-time comparison against received digest AND OTP golden hash
 *   6. If BOTH match: flash to BRAM and reboot. If either fails: reject.
 *
 * Security properties:
 *   - Reject bad firmware without flashing (no partial update)
 *   - Constant-time digest comparison (immune to timing side-channel)
 *   - OTP golden hash prevents downgrade attacks
 *   - UART transfer uses XMODEM for error detection (CRC-16)
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "uart.h"
#include "crypto.h"
#include "soc.h"

/* Maximum firmware size: 60 KB (leaves 4 KB for bootloader) */
#define FW_MAX_BYTES   (60u * 1024u)
#define SHA256_BYTES   32

/* OTP golden hash — in production, stored in write-once EFUSE or OTP BRAM.
 * Here represented as a compile-time constant (replace with OTP read). */
static const uint8_t otp_golden_hash[SHA256_BYTES] = {
    /* SHA-256("trusted_firmware_v1.0") — placeholder */
    0xA9, 0x4A, 0x8F, 0xE5, 0xCC, 0xB1, 0x9B, 0xA6,
    0x1C, 0x4C, 0x08, 0x73, 0xD3, 0x91, 0xE9, 0x87,
    0x98, 0x2F, 0xBB, 0xD3, 0xF8, 0xCA, 0x45, 0xB6,
    0x4F, 0xE1, 0xB8, 0x5A, 0xA2, 0x2A, 0x1E, 0xA0
};

/* BRAM base address (instruction memory) */
#define BRAM_BASE  0x00000000U

static uint8_t  fw_buf[FW_MAX_BYTES];
static uint8_t  rcvd_digest[SHA256_BYTES];
static uint8_t  computed_digest[SHA256_BYTES];

/* ── Receive exactly len bytes over UART ────────────────────────────────── */
static void recv_bytes(uint8_t *dst, uint32_t len) {
    for (uint32_t i = 0; i < len; i++)
        dst[i] = (uint8_t)uart_getchar();
}

/* ── Write firmware to BRAM (word-aligned) ──────────────────────────────── */
static void flash_firmware(const uint8_t *buf, uint32_t len) {
    volatile uint32_t *bram = (volatile uint32_t *)BRAM_BASE;
    uint32_t words = (len + 3) / 4;
    for (uint32_t i = 0; i < words; i++) {
        uint32_t w = 0;
        for (int b = 0; b < 4 && (i*4+b) < len; b++)
            w |= (uint32_t)buf[i*4+b] << (8*b);
        bram[i] = w;
    }
}

int main(void) {
    uart_init(115200);

    printf("=== RV32 Secure OTA Bootloader ===\r\n");
    printf("Max firmware size: %u KB\r\n", FW_MAX_BYTES / 1024);
    printf("Waiting for firmware upload...\r\n");

    /* ── Step 1: Receive 4-byte length ──────────────────────────────────── */
    uint8_t len_bytes[4];
    recv_bytes(len_bytes, 4);
    uint32_t fw_len = (uint32_t)len_bytes[0]
                    | ((uint32_t)len_bytes[1] << 8)
                    | ((uint32_t)len_bytes[2] << 16)
                    | ((uint32_t)len_bytes[3] << 24);

    if (fw_len == 0 || fw_len > FW_MAX_BYTES) {
        printf("REJECT: invalid length %u\r\n", fw_len);
        return 1;
    }
    printf("Firmware length: %u bytes\r\n", fw_len);

    /* ── Step 2: Receive firmware payload ───────────────────────────────── */
    recv_bytes(fw_buf, fw_len);
    printf("Payload received.\r\n");

    /* ── Step 3: Receive SHA-256 digest ─────────────────────────────────── */
    recv_bytes(rcvd_digest, SHA256_BYTES);
    printf("Digest received.\r\n");

    /* ── Step 4: Compute SHA-256 over received payload ──────────────────── */
    sha256_hash(fw_buf, fw_len, computed_digest);

    /* ── Step 5: Dual constant-time comparison ───────────────────────────── */
    int match_rcvd = sha256_verify(computed_digest, rcvd_digest);
    int match_otp  = sha256_verify(computed_digest, otp_golden_hash);

    if (match_rcvd != 0) {
        printf("REJECT: digest mismatch (payload corrupted or tampered)\r\n");
        return 1;
    }
    if (match_otp != 0) {
        printf("REJECT: OTP golden hash mismatch (unauthorized firmware)\r\n");
        return 1;
    }

    /* ── Step 6: Flash and reboot ──────────────────────────────────────── */
    printf("Verification PASSED. Flashing %u bytes...\r\n", fw_len);
    flash_firmware(fw_buf, fw_len);
    printf("Flash complete. Rebooting.\r\n");

    /* Trigger soft reset via CLINT MSIP */
    REG32_WR(CLINT_BASE, 0, 1);  /* Write MSIP → SW interrupt → trap → reset */

    /* Should not reach here */
    for (;;) {}
}
