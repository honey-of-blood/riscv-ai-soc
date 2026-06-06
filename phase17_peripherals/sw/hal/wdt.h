#ifndef WDT_H
#define WDT_H

#include <stdint.h>

#define WDT_BASE        0x10009000UL

#define WDT_CTRL        (*(volatile uint32_t *)(WDT_BASE + 0x00))
#define WDT_TIMEOUT     (*(volatile uint32_t *)(WDT_BASE + 0x04))
#define WDT_KICK        (*(volatile uint32_t *)(WDT_BASE + 0x08))
#define WDT_STATUS      (*(volatile uint32_t *)(WDT_BASE + 0x0C))

#define WDT_CTRL_EN     (1u << 0)
#define WDT_CTRL_NMI    (1u << 1)

#define WDT_MAGIC1      0x1ACCE551UL
#define WDT_MAGIC2      0xDEAD5AFEUL

static inline void wdt_init(uint32_t timeout_cycles, int nmi_mode) {
    WDT_TIMEOUT = timeout_cycles;
    WDT_CTRL    = WDT_CTRL_EN | (nmi_mode ? WDT_CTRL_NMI : 0u);
}

static inline void wdt_kick(void) {
    WDT_KICK = WDT_MAGIC1;
    WDT_KICK = WDT_MAGIC2;
}

static inline void wdt_disable(void) {
    WDT_CTRL = 0;
}

static inline int wdt_timed_out(void) {
    return (WDT_STATUS & 0x1) ? 1 : 0;
}

static inline void wdt_clear_flag(void) {
    WDT_STATUS = 0x1;
}

#endif /* WDT_H */
