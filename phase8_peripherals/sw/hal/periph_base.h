#ifndef PERIPH_BASE_H
#define PERIPH_BASE_H

#define UART_BASE    0x10001000u
#define GPIO_BASE    0x10002000u
#define TIMER_BASE   0x10003000u
#define SPI_BASE     0x10004000u
#define CLINT_BASE   0x10005000u
#define PLIC_BASE    0x10006000u

#define MMIO32(addr)  (*(volatile unsigned int *)(addr))

#endif
