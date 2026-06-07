#pragma once
#include <stdint.h>
#include <stddef.h>

#define SHA256_BASE     0x60000000UL
#define SHA256_CTRL     (*(volatile uint32_t *)(SHA256_BASE + 0x00))
#define SHA256_STATUS   (*(volatile uint32_t *)(SHA256_BASE + 0x64))

#define SHA256_START    (1u << 0)
#define SHA256_RESET    (1u << 1)
#define SHA256_DONE     (1u << 0)

void sha256_hw_block(const uint32_t msg[16], uint32_t digest[8]);
void sha256_hw_compute(const uint8_t *data, size_t len, uint8_t digest[32]);
