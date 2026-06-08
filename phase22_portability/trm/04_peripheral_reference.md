# 4. Peripheral Reference

## UART {#uart}

**Base address:** `0x1000_1000`  
**Compatible:** NS16550A  
**Clock:** 25 MHz (`clk_peri`)  
**Register stride:** 4 bytes (reg-shift = 2)

### Register Map

| Offset | Name | Access | Reset | Description |
|--------|------|--------|-------|-------------|
| 0x00 | RBR / THR | R / W | — | Receive Buffer (R) / Transmit Holding (W), DLAB=0 |
| 0x04 | IER | R/W | 0x00 | Interrupt Enable: [0]=RX_DR [1]=TX_THRE [2]=RX_ERR |
| 0x08 | IIR (R) / FCR (W) | R / W | 0x01 | Interrupt ID (R) / FIFO Control (W) |
| 0x0C | LCR | R/W | 0x00 | Line Control: [1:0]=WLS [2]=STB [3]=PEN [7]=DLAB |
| 0x10 | MCR | R/W | 0x00 | Modem Control: [0]=DTR [1]=RTS [4]=LOOP |
| 0x14 | LSR | R | 0x60 | Line Status: [0]=DR [5]=THRE [6]=TEMT |
| 0x18 | MSR | R | 0x00 | Modem Status |
| 0x00 | DLL | R/W | — | Divisor Latch Low (DLAB=1) |
| 0x04 | DLH | R/W | — | Divisor Latch High (DLAB=1) |

### Baud Rate Formula

```
divisor = PERI_HZ / (16 × baud_rate)
         = 25_000_000 / (16 × 115200) = 13 (error < 0.1%)
```

### Usage Example

```c
uart_init(115200);
uart_puts("Hello!\r\n");
```

---

## GPIO {#gpio}

**Base address:** `0x1000_2000`  
**Width:** 16 bits

### Register Map

| Offset | Name | Access | Reset | Description |
|--------|------|--------|-------|-------------|
| 0x00 | DIR | R/W | 0x0000 | Direction: 1 = output, 0 = input (per bit) |
| 0x04 | OUT | R/W | 0x0000 | Output data |
| 0x08 | IN | R | — | Input data (sampled each clock) |
| 0x0C | IE | R/W | 0x0000 | Interrupt enable (per bit) |
| 0x10 | EDGE | R/W | 0x0000 | Edge select: 1 = rising, 0 = falling |
| 0x14 | PEND | R/W1C | 0x0000 | Interrupt pending; write 1 to clear |

---

## Timer / CLINT {#timer}

**Timer base:** `0x1000_3000`  **CLINT base:** `0x1000_5000`

### CLINT Register Map

| Offset | Name | Access | Reset | Description |
|--------|------|--------|-------|-------------|
| 0x000 | msip | R/W | 0 | Machine software interrupt pending (bit 0) |
| 0x004 | — | — | — | Reserved |
| 0x008 | mtimecmp_lo | R/W | 0xFFFF_FFFF | Timer compare low 32 bits |
| 0x00C | mtimecmp_hi | R/W | 0xFFFF_FFFF | Timer compare high 32 bits |
| 0x010 | mtime_lo | R/W | 0 | Real-time counter low 32 bits |
| 0x014 | mtime_hi | R/W | 0 | Real-time counter high 32 bits |

**Usage:** Timer interrupt fires when `mtime >= mtimecmp`. Write `mtime + period` to `mtimecmp` to schedule next tick.

---

## SPI {#spi}

**Base address:** `0x1000_4000`  
**Mode:** Master; CPHA=0 CPOL=0 default; 8-bit frames

### Register Map

| Offset | Name | Access | Reset | Description |
|--------|------|--------|-------|-------------|
| 0x00 | CTRL | R/W | 0x0000 | [0]=EN [1]=IE [7:4]=divider (SCK = PERI_HZ >> divider) |
| 0x04 | STATUS | R | 0x01 | [0]=TX_DONE [1]=RX_VALID [2]=BUSY |
| 0x08 | TX | W | — | Write to transmit and start transfer |
| 0x08 | RX | R | — | Read received byte |
| 0x0C | CS | R/W | 0x01 | Chip-select (active low, bit 0 = CS_N) |

---

## PLIC {#plic}

**Base address:** `0x1000_6000`  
**Sources:** 8 (IRQ 1–8)  
**Priorities:** 8 levels (0 = disabled)

### Register Map

| Offset | Name | Access | Reset | Description |
|--------|------|--------|-------|-------------|
| 0x00–0x1C | priority[1..7] | R/W | 0 | Per-source priority (0 = disable) |
| 0x20 | pending | R | 0 | Interrupt pending bitmap [7:1] |
| 0x24 | enable | R/W | 0 | Interrupt enable bitmap [7:1] |
| 0x28 | threshold | R/W | 0 | Priority threshold (interrupts ≤ threshold ignored) |
| 0x2C | claim | R/W | 0 | Read = highest-priority pending IRQ; Write = complete |

---

## I2C {#i2c}

**Base address:** `0x1000_7000`  
**Compatible:** OpenCores i2c_master_top  
**Speed:** Standard (100 kHz) and Fast (400 kHz)

### Register Map

| Offset | Name | Access | Reset | Description |
|--------|------|--------|-------|-------------|
| 0x00 | PRESCALE_LO | R/W | 0xFF | Clock prescaler [7:0] |
| 0x04 | PRESCALE_HI | R/W | 0xFF | Clock prescaler [15:8] |
| 0x08 | CONTROL | R/W | 0x00 | [7]=EN [6]=IEN |
| 0x0C | TX / RX | W / R | — | Transmit data (W); received data (R) |
| 0x10 | CMD / STATUS | W / R | — | Command (W); status (R) |

**CMD bits:** [7]=STA [6]=STO [5]=RD [4]=WR [3]=ACK [0]=IACK  
**Status bits:** [7]=RXNACK [6]=BUSY [5]=AL [1]=TIP [0]=IF

---

## WDT {#wdt}

**Base address:** `0x1000_8000`

### Register Map

| Offset | Name | Access | Reset | Description |
|--------|------|--------|-------|-------------|
| 0x00 | CTRL | R/W | 0x00 | [0]=EN [1]=INT_EN (interrupt before reset) |
| 0x04 | TIMEOUT | R/W | 0xFFFF | Timeout in peripheral clock cycles |
| 0x08 | KICK | W | — | Write any value to reset watchdog counter |
| 0x0C | STATUS | R | 0x00 | [0]=EXPIRED [1]=INT_PENDING |
