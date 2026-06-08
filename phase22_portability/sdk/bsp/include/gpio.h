/* gpio.h — 16-bit GPIO driver API */
#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "soc.h"

/* ── Register offsets ────────────────────────────────────────────────────── */
#define GPIO_DIR    0x00U   /* Direction: 1 = output, 0 = input (per bit) */
#define GPIO_OUT    0x04U   /* Output data register */
#define GPIO_IN     0x08U   /* Input data register (read-only) */
#define GPIO_IE     0x0CU   /* Interrupt enable (per bit) */
#define GPIO_EDGE   0x10U   /* Edge select: 1 = rising, 0 = falling */
#define GPIO_PEND   0x14U   /* Interrupt pending (write 1 to clear) */

/* ── API ─────────────────────────────────────────────────────────────────── */

/** gpio_set_dir - configure direction for a mask of pins (1=out, 0=in) */
void gpio_set_dir(uint16_t output_mask);

/** gpio_write - set output values for pins configured as outputs */
void gpio_write(uint16_t value);

/** gpio_read - read current input values for all 16 pins */
uint16_t gpio_read(void);

/** gpio_set - set specific output bits high */
void gpio_set(uint16_t mask);

/** gpio_clr - set specific output bits low */
void gpio_clr(uint16_t mask);

/** gpio_toggle - toggle specific output bits */
void gpio_toggle(uint16_t mask);

/** gpio_irq_enable - enable edge interrupt on the given pins */
void gpio_irq_enable(uint16_t mask, uint8_t rising);

/** gpio_irq_pending - return and clear the interrupt pending mask */
uint16_t gpio_irq_pending(void);

#endif /* GPIO_H_ */
