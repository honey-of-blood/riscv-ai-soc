/* gpio.c — GPIO driver implementation */
#include "gpio.h"
#include "soc.h"

#define GPIO_REG(off) REG32(GPIO_BASE, (off))

void    gpio_set_dir(uint16_t mask)        { GPIO_REG(GPIO_DIR)  = mask; }
void    gpio_write  (uint16_t val)         { GPIO_REG(GPIO_OUT)  = val; }
uint16_t gpio_read  (void)                 { return (uint16_t)GPIO_REG(GPIO_IN); }
void    gpio_set    (uint16_t mask)        { GPIO_REG(GPIO_OUT) |=  mask; }
void    gpio_clr    (uint16_t mask)        { GPIO_REG(GPIO_OUT) &= ~mask; }
void    gpio_toggle (uint16_t mask)        { GPIO_REG(GPIO_OUT) ^=  mask; }

void gpio_irq_enable(uint16_t mask, uint8_t rising) {
    GPIO_REG(GPIO_EDGE) = rising ? mask : 0;
    GPIO_REG(GPIO_IE)  |= mask;
}

uint16_t gpio_irq_pending(void) {
    uint16_t p = (uint16_t)GPIO_REG(GPIO_PEND);
    GPIO_REG(GPIO_PEND) = p;  /* write 1 to clear */
    return p;
}
