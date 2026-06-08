/* i2c.c — I2C master driver (OpenCores i2c_master_top compatible) */
#include "i2c.h"
#include "soc.h"

#define I2C_REG(off) REG32(I2C_BASE, (off))

static inline int _wait_tip(void) {
    int timeout = 100000;
    while ((I2C_REG(I2C_STATUS) & I2C_STAT_TIP) && --timeout) {}
    return timeout ? 0 : I2C_ERROR;
}

void i2c_init(uint32_t hz) {
    /* Prescaler = (PERI_HZ / (5 * hz)) - 1 */
    uint32_t prescale = (PERI_HZ / (5u * hz)) - 1u;
    I2C_REG(I2C_CONTROL)     = 0;  /* disable core first */
    I2C_REG(I2C_PRESCALE_LO) = prescale & 0xFF;
    I2C_REG(I2C_PRESCALE_HI) = (prescale >> 8) & 0xFF;
    I2C_REG(I2C_CONTROL)     = I2C_CTL_EN;
}

int i2c_write(uint8_t addr, const uint8_t *buf, uint32_t len) {
    /* Send START + address (write) */
    I2C_REG(I2C_TX)  = (addr << 1) | 0;
    I2C_REG(I2C_CMD) = I2C_CMD_STA | I2C_CMD_WR;
    if (_wait_tip()) return I2C_ERROR;
    if (I2C_REG(I2C_STATUS) & I2C_STAT_RXNACK) return I2C_NACK;

    for (uint32_t i = 0; i < len; i++) {
        I2C_REG(I2C_TX)  = buf[i];
        I2C_REG(I2C_CMD) = (i == len - 1) ? I2C_CMD_WR | I2C_CMD_STO : I2C_CMD_WR;
        if (_wait_tip()) return I2C_ERROR;
        if (I2C_REG(I2C_STATUS) & I2C_STAT_RXNACK) return I2C_NACK;
    }
    return I2C_OK;
}

int i2c_read(uint8_t addr, uint8_t *buf, uint32_t len) {
    I2C_REG(I2C_TX)  = (addr << 1) | 1;
    I2C_REG(I2C_CMD) = I2C_CMD_STA | I2C_CMD_WR;
    if (_wait_tip()) return I2C_ERROR;
    if (I2C_REG(I2C_STATUS) & I2C_STAT_RXNACK) return I2C_NACK;

    for (uint32_t i = 0; i < len; i++) {
        uint8_t nack = (i == len - 1) ? I2C_CMD_ACK : 0;
        uint8_t stop = (i == len - 1) ? I2C_CMD_STO : 0;
        I2C_REG(I2C_CMD) = I2C_CMD_RD | nack | stop;
        if (_wait_tip()) return I2C_ERROR;
        buf[i] = (uint8_t)I2C_REG(I2C_RX);
    }
    return I2C_OK;
}

int i2c_write_read(uint8_t addr,
                   const uint8_t *wbuf, uint32_t wlen,
                   uint8_t *rbuf,       uint32_t rlen) {
    int rc = i2c_write(addr, wbuf, wlen);
    if (rc) return rc;
    return i2c_read(addr, rbuf, rlen);
}
