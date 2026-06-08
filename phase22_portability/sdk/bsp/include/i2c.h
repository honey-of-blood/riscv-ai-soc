/* i2c.h — I2C master driver API */
#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "soc.h"

/* ── Register offsets ────────────────────────────────────────────────────── */
#define I2C_PRESCALE_LO  0x00U   /* Clock prescaler low byte */
#define I2C_PRESCALE_HI  0x04U   /* Clock prescaler high byte */
#define I2C_CONTROL      0x08U   /* Control register */
#define I2C_TX           0x0CU   /* Transmit data / address */
#define I2C_RX           0x0CU   /* Received data (read) */
#define I2C_CMD          0x10U   /* Command register (write) */
#define I2C_STATUS       0x10U   /* Status register (read) */

/* ── Control bits ────────────────────────────────────────────────────────── */
#define I2C_CTL_EN   (1u << 7)  /* Core enable */
#define I2C_CTL_IEN  (1u << 6)  /* Interrupt enable */

/* ── Command bits ────────────────────────────────────────────────────────── */
#define I2C_CMD_STA  (1u << 7)  /* Generate START */
#define I2C_CMD_STO  (1u << 6)  /* Generate STOP */
#define I2C_CMD_RD   (1u << 5)  /* Read from slave */
#define I2C_CMD_WR   (1u << 4)  /* Write to slave */
#define I2C_CMD_ACK  (1u << 3)  /* Send ACK (0=ACK, 1=NACK) */
#define I2C_CMD_IACK (1u << 0)  /* Interrupt ACK */

/* ── Status bits ─────────────────────────────────────────────────────────── */
#define I2C_STAT_RXNACK (1u << 7)  /* Received NACK from slave */
#define I2C_STAT_BUSY   (1u << 6)  /* Bus busy */
#define I2C_STAT_AL     (1u << 5)  /* Arbitration lost */
#define I2C_STAT_TIP    (1u << 1)  /* Transfer in progress */
#define I2C_STAT_IF     (1u << 0)  /* Interrupt flag */

/* ── Return codes ────────────────────────────────────────────────────────── */
#define I2C_OK      0
#define I2C_NACK   -1
#define I2C_BUSY   -2
#define I2C_ERROR  -3

/* ── API ─────────────────────────────────────────────────────────────────── */

/**
 * i2c_init - initialise I2C core at the given bit rate
 * @hz: bit rate in Hz (e.g. 100000 for 100 kHz standard mode)
 */
void i2c_init(uint32_t hz);

/**
 * i2c_write - write len bytes to the slave at addr (7-bit)
 * Returns I2C_OK on success, I2C_NACK if the slave NACKs, I2C_ERROR on bus fault.
 */
int i2c_write(uint8_t addr, const uint8_t *buf, uint32_t len);

/**
 * i2c_read - read len bytes from the slave at addr (7-bit)
 * Returns I2C_OK on success, negative on error.
 */
int i2c_read(uint8_t addr, uint8_t *buf, uint32_t len);

/**
 * i2c_write_read - write wlen bytes then read rlen bytes (register read)
 */
int i2c_write_read(uint8_t addr,
                   const uint8_t *wbuf, uint32_t wlen,
                   uint8_t *rbuf,       uint32_t rlen);

#endif /* I2C_H_ */
