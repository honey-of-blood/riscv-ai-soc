/* crypto.h — AES-128/256 and SHA-256 hardware accelerator API */
#ifndef CRYPTO_H_
#define CRYPTO_H_

#include <stdint.h>
#include "soc.h"

/* ── AES register map (base = AES_BASE = 0x5000_1000) ─────────────────── */
#define AES_CTRL         0x00U  /* [1:0]=mode (0=ECB,1=CBC,2=CTR) [2]=enc/dec [3]=start */
#define AES_STATUS       0x04U  /* [0]=busy [1]=done */
#define AES_KEY_BASE     0x10U  /* 16-byte (AES-128) or 32-byte (AES-256) key */
#define AES_IV_BASE      0x30U  /* 16-byte IV for CBC/CTR modes */
#define AES_DIN_BASE     0x40U  /* 16-byte plaintext input */
#define AES_DOUT_BASE    0x50U  /* 16-byte ciphertext output */

#define AES_MODE_ECB     0u
#define AES_MODE_CBC     1u
#define AES_MODE_CTR     2u
#define AES_DIR_ENCRYPT  0u
#define AES_DIR_DECRYPT  1u

/* ── SHA-256 register map (base = SHA256_BASE = 0x5000_2000) ─────────── */
#define SHA256_CTRL      0x00U  /* [0]=start [1]=reset */
#define SHA256_STATUS    0x04U  /* [0]=busy [1]=done */
#define SHA256_DIN_BASE  0x08U  /* 64-byte (512-bit) input block */
#define SHA256_DOUT_BASE 0x48U  /* 32-byte (256-bit) digest */

/* ── API ─────────────────────────────────────────────────────────────────── */

/**
 * aes128_ecb_encrypt - encrypt a single 16-byte block with AES-128 ECB
 * @key: 16-byte key
 * @in:  16-byte plaintext
 * @out: 16-byte ciphertext output
 */
void aes128_ecb_encrypt(const uint8_t *key, const uint8_t *in, uint8_t *out);

/**
 * aes128_ecb_decrypt - decrypt a single 16-byte block with AES-128 ECB
 */
void aes128_ecb_decrypt(const uint8_t *key, const uint8_t *in, uint8_t *out);

/**
 * aes128_cbc_encrypt - encrypt len bytes in CBC mode (len must be multiple of 16)
 * @key: 16-byte key
 * @iv:  16-byte IV (updated in-place for chaining)
 */
void aes128_cbc_encrypt(const uint8_t *key, uint8_t *iv,
                        const uint8_t *in, uint8_t *out, uint32_t len);

/**
 * sha256_hash - compute SHA-256 of arbitrary-length input
 * @data:   input buffer
 * @len:    byte length of input
 * @digest: 32-byte output buffer for the hash
 *
 * This function performs SW padding and feeds 512-bit blocks to the HW core.
 */
void sha256_hash(const uint8_t *data, uint32_t len, uint8_t *digest);

/**
 * sha256_verify - constant-time comparison of two 32-byte SHA-256 digests
 * Returns 0 if equal, -1 if different (timing-safe).
 */
int sha256_verify(const uint8_t *a, const uint8_t *b);

#endif /* CRYPTO_H_ */
