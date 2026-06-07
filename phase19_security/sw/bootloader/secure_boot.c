#include "secure_boot.h"
#include "../crypto/sha256.h"
#include <string.h>

/*
 * Verify firmware authenticity.
 *
 * The last 32 bytes of `image` are the SHA-256 digest appended by the
 * signing tool.  We recompute over the first (len-32) bytes and compare
 * against both the appended digest AND the golden digest stored in OTP.
 *
 * Constant-time compare: all 32 bytes are XOR'd into a single accumulator;
 * a zero result means they match.  This avoids early-exit timing oracles.
 */
bool verify_firmware(const uint8_t *image, size_t len) {
    if (len < 33) return false;   /* minimum: 1 payload byte + 32-byte digest */

    uint8_t computed[32];
    sha256_hw_compute(image, len - 32, computed);

    const uint8_t *appended = image + (len - 32);
    const uint8_t *golden   = (const uint8_t *)OTP_BASE;

    /* Constant-time compare: computed vs. appended digest */
    uint8_t diff1 = 0;
    for (int i = 0; i < 32; i++) diff1 |= computed[i] ^ appended[i];

    /* Constant-time compare: computed vs. OTP golden digest */
    uint8_t diff2 = 0;
    for (int i = 0; i < 32; i++) diff2 |= computed[i] ^ golden[i];

    return (diff1 == 0) && (diff2 == 0);
}
