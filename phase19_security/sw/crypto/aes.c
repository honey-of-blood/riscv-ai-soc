#include "aes.h"

#define KEY_REG(i)  (*(volatile uint32_t *)(AES_BASE + 0x04 + (i)*4))
#define IV_REG(i)   (*(volatile uint32_t *)(AES_BASE + 0x14 + (i)*4))
#define DIN_REG(i)  (*(volatile uint32_t *)(AES_BASE + 0x24 + (i)*4))
#define DOUT_REG(i) (*(volatile uint32_t *)(AES_BASE + 0x34 + (i)*4))

static void run(uint32_t ctrl) {
    AES_CTRL = ctrl | AES_START;
    while (!(AES_STATUS & AES_DONE));
}

void aes128_ecb_encrypt(const uint32_t key[4], const uint32_t pt[4], uint32_t ct[4]) {
    for (int i=0;i<4;i++) KEY_REG(i) = key[i];
    for (int i=0;i<4;i++) DIN_REG(i) = pt[i];
    run(AES_ECB);
    for (int i=0;i<4;i++) ct[i] = DOUT_REG(i);
}

void aes128_ecb_decrypt(const uint32_t key[4], const uint32_t ct[4], uint32_t pt[4]) {
    for (int i=0;i<4;i++) KEY_REG(i) = key[i];
    for (int i=0;i<4;i++) DIN_REG(i) = ct[i];
    run(AES_ECB | AES_DECRYPT);
    for (int i=0;i<4;i++) pt[i] = DOUT_REG(i);
}

void aes128_cbc_encrypt(const uint32_t key[4], uint32_t iv[4],
                        const uint32_t pt[4], uint32_t ct[4]) {
    for (int i=0;i<4;i++) KEY_REG(i) = key[i];
    for (int i=0;i<4;i++) IV_REG(i)  = iv[i];
    for (int i=0;i<4;i++) DIN_REG(i) = pt[i];
    run(AES_CBC);
    for (int i=0;i<4;i++) { ct[i] = DOUT_REG(i); iv[i] = ct[i]; }
}

void aes128_cbc_decrypt(const uint32_t key[4], uint32_t iv[4],
                        const uint32_t ct[4], uint32_t pt[4]) {
    for (int i=0;i<4;i++) KEY_REG(i) = key[i];
    for (int i=0;i<4;i++) IV_REG(i)  = iv[i];
    for (int i=0;i<4;i++) DIN_REG(i) = ct[i];
    run(AES_CBC | AES_DECRYPT);
    for (int i=0;i<4;i++) { pt[i] = DOUT_REG(i); iv[i] = ct[i]; }
}

void aes128_ctr_keystream(const uint32_t key[4], uint32_t ctr[4],
                          const uint32_t in[4], uint32_t out[4]) {
    for (int i=0;i<4;i++) KEY_REG(i) = key[i];
    for (int i=0;i<4;i++) IV_REG(i)  = ctr[i];
    for (int i=0;i<4;i++) DIN_REG(i) = in[i];
    run(AES_CTR);
    for (int i=0;i<4;i++) out[i] = DOUT_REG(i);
    ctr[3]++;  /* mirror the hardware IV increment */
}
