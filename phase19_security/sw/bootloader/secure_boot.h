#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/* OTP region: write-once, holds golden SHA-256 digest of firmware */
#define OTP_BASE 0xF0000000UL

bool verify_firmware(const uint8_t *image, size_t len);
