/* soc.h — RV32 AI SoC MMIO base addresses and register access macros */
#ifndef SOC_H_
#define SOC_H_

#include <stdint.h>

/* ── Register access helpers ────────────────────────────────────────────── */
#define REG32(base, off)    (*(volatile uint32_t *)((base) + (off)))
#define REG32_RD(base, off) (REG32((base), (off)))
#define REG32_WR(base, off, v) (REG32((base), (off)) = (uint32_t)(v))

/* ── MMIO base addresses ─────────────────────────────────────────────────── */
#define UART_BASE     0x10001000U
#define GPIO_BASE     0x10002000U
#define TIMER_BASE    0x10003000U
#define SPI_BASE      0x10004000U
#define CLINT_BASE    0x10005000U
#define PLIC_BASE     0x10006000U
#define I2C_BASE      0x10007000U
#define WDT_BASE      0x10008000U
#define ACCEL_BASE    0x50000000U
#define AES_BASE      0x50001000U
#define SHA256_BASE   0x50002000U

/* ── Interrupt numbers ───────────────────────────────────────────────────── */
#define IRQ_UART      1
#define IRQ_GPIO      2
#define IRQ_SPI       3
#define IRQ_I2C       4
#define IRQ_TIMER     5
#define IRQ_ACCEL     6
#define IRQ_WDT       7

/* ── CPU clock frequency (Hz) ────────────────────────────────────────────── */
#define CPU_HZ        100000000UL
#define PERI_HZ       25000000UL

/* ── RISC-V CSR helpers ──────────────────────────────────────────────────── */
#define CSR_READ(csr)        ({ uint32_t _v; __asm__ volatile("csrr %0," #csr : "=r"(_v)); _v; })
#define CSR_WRITE(csr, val)  __asm__ volatile("csrw " #csr ", %0" :: "r"((uint32_t)(val)))
#define CSR_SET(csr, mask)   __asm__ volatile("csrs " #csr ", %0" :: "r"((uint32_t)(mask)))
#define CSR_CLR(csr, mask)   __asm__ volatile("csrc " #csr ", %0" :: "r"((uint32_t)(mask)))

/* ── Global interrupt enable/disable ────────────────────────────────────── */
#define IRQ_ENABLE()   CSR_SET(mstatus, 0x8)   /* mstatus.MIE = 1 */
#define IRQ_DISABLE()  CSR_CLR(mstatus, 0x8)   /* mstatus.MIE = 0 */

#endif /* SOC_H_ */
