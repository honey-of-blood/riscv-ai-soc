#include "sha256.h"
#include <string.h>

#define MSG_REG(i)  (*(volatile uint32_t *)(SHA256_BASE + 0x04 + (i)*4))
#define HASH_REG(i) (*(volatile uint32_t *)(SHA256_BASE + 0x44 + (i)*4))

/* Process one pre-padded 512-bit block and read the digest. */
void sha256_hw_block(const uint32_t msg[16], uint32_t digest[8]) {
    SHA256_CTRL = SHA256_RESET;
    for (int i = 0; i < 16; i++) MSG_REG(i) = msg[i];
    SHA256_CTRL = SHA256_START;
    while (!(SHA256_STATUS & SHA256_DONE));
    for (int i = 0; i < 8; i++) digest[i] = HASH_REG(i);
}

/*
 * SHA-256 over arbitrary byte data.  Pads to 512-bit boundary per FIPS 180-4:
 *   - Append 0x80 byte
 *   - Zero-pad to 448 bits (56 bytes) mod 512
 *   - Append 64-bit big-endian bit-length
 */
void sha256_hw_compute(const uint8_t *data, size_t len, uint8_t digest[32]) {
    uint8_t  block[64];
    uint32_t msg[16];
    size_t   done = 0;
    uint64_t bit_len = (uint64_t)len * 8;

    /* Process full 64-byte blocks */
    while (done + 64 <= len) {
        memcpy(block, data + done, 64);
        for (int i = 0; i < 16; i++)
            msg[i] = ((uint32_t)block[i*4]<<24)|((uint32_t)block[i*4+1]<<16)|
                     ((uint32_t)block[i*4+2]<<8) | block[i*4+3];
        uint32_t tmp[8];
        sha256_hw_block(msg, tmp);
        done += 64;
    }

    /* Final block(s) with padding */
    size_t rem = len - done;
    memset(block, 0, 64);
    memcpy(block, data + done, rem);
    block[rem] = 0x80;

    if (rem >= 56) {
        /* Need an extra block */
        for (int i = 0; i < 16; i++)
            msg[i] = ((uint32_t)block[i*4]<<24)|((uint32_t)block[i*4+1]<<16)|
                     ((uint32_t)block[i*4+2]<<8) | block[i*4+3];
        uint32_t tmp[8];
        sha256_hw_block(msg, tmp);
        memset(block, 0, 64);
    }

    /* Append big-endian 64-bit bit length in last 8 bytes */
    block[56] = (uint8_t)(bit_len >> 56); block[57] = (uint8_t)(bit_len >> 48);
    block[58] = (uint8_t)(bit_len >> 40); block[59] = (uint8_t)(bit_len >> 32);
    block[60] = (uint8_t)(bit_len >> 24); block[61] = (uint8_t)(bit_len >> 16);
    block[62] = (uint8_t)(bit_len >>  8); block[63] = (uint8_t)(bit_len >>  0);

    for (int i = 0; i < 16; i++)
        msg[i] = ((uint32_t)block[i*4]<<24)|((uint32_t)block[i*4+1]<<16)|
                 ((uint32_t)block[i*4+2]<<8) | block[i*4+3];

    uint32_t tmp[8];
    sha256_hw_block(msg, tmp);

    /* Convert 32-bit words to bytes (big-endian) */
    for (int i = 0; i < 8; i++) {
        digest[i*4+0] = (uint8_t)(tmp[i] >> 24);
        digest[i*4+1] = (uint8_t)(tmp[i] >> 16);
        digest[i*4+2] = (uint8_t)(tmp[i] >>  8);
        digest[i*4+3] = (uint8_t)(tmp[i] >>  0);
    }
}
