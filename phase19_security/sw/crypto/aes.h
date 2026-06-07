#pragma once
#include <stdint.h>

#define AES_BASE    0x60010000UL
#define AES_CTRL    (*(volatile uint32_t *)(AES_BASE + 0x00))
#define AES_STATUS  (*(volatile uint32_t *)(AES_BASE + 0x44))

#define AES_START   (1u << 0)
#define AES_DECRYPT (1u << 1)
#define AES_ECB     (0u << 2)
#define AES_CBC     (1u << 2)
#define AES_CTR     (2u << 2)
#define AES_DONE    (1u << 0)

/* key and iv: arrays of 4 × uint32_t big-endian words */
void aes128_ecb_encrypt(const uint32_t key[4], const uint32_t pt[4], uint32_t ct[4]);
void aes128_ecb_decrypt(const uint32_t key[4], const uint32_t ct[4], uint32_t pt[4]);
void aes128_cbc_encrypt(const uint32_t key[4], uint32_t iv[4],
                        const uint32_t pt[4], uint32_t ct[4]);
void aes128_cbc_decrypt(const uint32_t key[4], uint32_t iv[4],
                        const uint32_t ct[4], uint32_t pt[4]);
void aes128_ctr_keystream(const uint32_t key[4], uint32_t ctr[4],
                          const uint32_t in[4], uint32_t out[4]);
