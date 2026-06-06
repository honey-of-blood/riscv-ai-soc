#ifndef TRNG_H
#define TRNG_H

#include <stdint.h>

#define TRNG_BASE       0x1000A000UL

#define TRNG_DATA       (*(volatile uint32_t *)(TRNG_BASE + 0x00))
#define TRNG_STATUS     (*(volatile uint32_t *)(TRNG_BASE + 0x04))
#define TRNG_CTRL       (*(volatile uint32_t *)(TRNG_BASE + 0x08))

#define TRNG_ST_READY   (1u << 0)
#define TRNG_ST_HERR    (1u << 1)
#define TRNG_ST_ENABLED (1u << 2)

static inline void trng_init(void) {
    TRNG_CTRL = 0x1;   /* enable */
}

/* Blocking read — waits until a new random word passes health test. */
static inline uint32_t trng_read(void) {
    while (!(TRNG_STATUS & TRNG_ST_READY)) {}
    return TRNG_DATA;
}

static inline int trng_health_err(void) {
    return (TRNG_STATUS & TRNG_ST_HERR) ? 1 : 0;
}

#endif /* TRNG_H */
