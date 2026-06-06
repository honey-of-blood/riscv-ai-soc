#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define I2C_BASE        0x10008000UL

#define I2C_CTRL        (*(volatile uint32_t *)(I2C_BASE + 0x00))
#define I2C_ADDR        (*(volatile uint32_t *)(I2C_BASE + 0x04))
#define I2C_DATA        (*(volatile uint32_t *)(I2C_BASE + 0x08))
#define I2C_CMD         (*(volatile uint32_t *)(I2C_BASE + 0x0C))
#define I2C_STATUS      (*(volatile uint32_t *)(I2C_BASE + 0x10))
#define I2C_PRESCALE    (*(volatile uint32_t *)(I2C_BASE + 0x14))

#define I2C_CTRL_EN     (1u << 0)
#define I2C_CTRL_IRQEN  (1u << 1)
#define I2C_CTRL_FAST   (1u << 2)

#define I2C_CMD_START   (1u << 0)
#define I2C_CMD_STOP    (1u << 1)
#define I2C_CMD_READ    (1u << 2)
#define I2C_CMD_WRITE   (1u << 3)
#define I2C_CMD_MACK    (1u << 4)

#define I2C_ST_BUSY     (1u << 0)
#define I2C_ST_ARBLOST  (1u << 1)
#define I2C_ST_NACK     (1u << 2)
#define I2C_ST_IRQ      (1u << 3)

static inline void i2c_init(uint32_t prescale) {
    I2C_PRESCALE = prescale;
    I2C_CTRL     = I2C_CTRL_EN;
}

static inline void i2c_wait_busy(void) {
    while (I2C_STATUS & I2C_ST_BUSY) {}
}

static inline void i2c_start(void) {
    I2C_CMD = I2C_CMD_START;
    i2c_wait_busy();
}

static inline void i2c_stop(void) {
    I2C_CMD = I2C_CMD_STOP;
    i2c_wait_busy();
}

static inline int i2c_write(uint8_t byte) {
    I2C_DATA = byte;
    I2C_CMD  = I2C_CMD_WRITE;
    i2c_wait_busy();
    return (I2C_STATUS & I2C_ST_NACK) ? -1 : 0;
}

static inline uint8_t i2c_read_ack(void) {
    I2C_CMD = I2C_CMD_READ;           /* send ACK */
    i2c_wait_busy();
    return (uint8_t)(I2C_DATA & 0xFF);
}

static inline uint8_t i2c_read_nack(void) {
    I2C_CMD = I2C_CMD_READ | I2C_CMD_MACK;   /* send NACK = last byte */
    i2c_wait_busy();
    return (uint8_t)(I2C_DATA & 0xFF);
}

#endif /* I2C_H */
