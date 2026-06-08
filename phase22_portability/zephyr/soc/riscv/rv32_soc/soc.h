/* soc.h — SoC-level definitions for Zephyr RV32 AI SoC port */
#ifndef ZEPHYR_SOC_RV32_SOC_SOC_H_
#define ZEPHYR_SOC_RV32_SOC_SOC_H_

/* ── MMIO base addresses ─────────────────────────────────────────────────── */
#define UART0_BASE_ADDR   0x10001000U
#define GPIO0_BASE_ADDR   0x10002000U
#define TIMER0_BASE_ADDR  0x10003000U
#define SPI0_BASE_ADDR    0x10004000U
#define CLINT_BASE_ADDR   0x10005000U
#define PLIC_BASE_ADDR    0x10006000U
#define I2C0_BASE_ADDR    0x10007000U
#define ACCEL_BASE_ADDR   0x50000000U

/* ── NS16550 register offsets (reg-shift = 2, so stride = 4 bytes) ─────── */
#define NS16550_RBR_OFFSET  0x00   /* Receiver Buffer Register (R) */
#define NS16550_THR_OFFSET  0x00   /* Transmitter Holding Register (W) */
#define NS16550_IER_OFFSET  0x04   /* Interrupt Enable Register */
#define NS16550_FCR_OFFSET  0x08   /* FIFO Control Register (W) */
#define NS16550_IIR_OFFSET  0x08   /* Interrupt Identification Register (R) */
#define NS16550_LCR_OFFSET  0x0C   /* Line Control Register */
#define NS16550_MCR_OFFSET  0x10   /* Modem Control Register */
#define NS16550_LSR_OFFSET  0x14   /* Line Status Register */
#define NS16550_MSR_OFFSET  0x18   /* Modem Status Register */
#define NS16550_DLL_OFFSET  0x00   /* Divisor Latch Low (LCR[7]=1) */
#define NS16550_DLH_OFFSET  0x04   /* Divisor Latch High (LCR[7]=1) */

#define NS16550_LSR_DR      BIT(0) /* Data Ready */
#define NS16550_LSR_THRE    BIT(5) /* TX Holding Register Empty */

/* ── Interrupt numbers (matches DTS interrupts = <N 1>) ────────────────── */
#define IRQ_UART0   1
#define IRQ_GPIO0   2
#define IRQ_SPI0    3
#define IRQ_I2C0    4
#define IRQ_TIMER0  5
#define IRQ_ACCEL   6

#endif /* ZEPHYR_SOC_RV32_SOC_SOC_H_ */
