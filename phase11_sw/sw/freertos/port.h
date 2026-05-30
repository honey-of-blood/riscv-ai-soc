#ifndef PORT_H
#define PORT_H

#include "FreeRTOS.h"

/* ── Stack frame layout ──────────────────────────────────────────────────── */
/*
 * Saved context on the task stack (offsets in 32-bit words from SP):
 *
 *   SP+0   : mstatus  (machine status register)
 *   SP+4   : mepc     (machine exception PC — address to resume)
 *   SP+8   : x1  (ra)
 *   SP+12  : x5  (t0)
 *   SP+16  : x6  (t1)
 *   SP+20  : x7  (t2)
 *   SP+24  : x8  (s0/fp)
 *   SP+28  : x9  (s1)
 *   SP+32  : x10 (a0)
 *   SP+36  : x11 (a1)
 *   SP+40  : x12 (a2)
 *   SP+44  : x13 (a3)
 *   SP+48  : x14 (a4)
 *   SP+52  : x15 (a5)
 *   SP+56  : x16 (a6)
 *   SP+60  : x17 (a7)
 *   SP+64  : x18 (s2)
 *   SP+68  : x19 (s3)
 *   SP+72  : x20 (s4)
 *   SP+76  : x21 (s5)
 *   SP+80  : x22 (s6)
 *   SP+84  : x23 (s7)
 *   SP+88  : x24 (s8)
 *   SP+92  : x25 (s9)
 *   SP+96  : x26 (s10)
 *   SP+100 : x27 (s11)
 *   SP+104 : x28 (t3)
 *   SP+108 : x29 (t4)
 *   SP+112 : x30 (t5)
 *   SP+116 : x31 (t6)
 *   Total  : 30 words = 120 bytes
 */
#define PORT_CONTEXT_WORDS  30

/* ── Port function declarations ──────────────────────────────────────────── */

/* Called by FreeRTOS scheduler to set up the timer tick interrupt. */
void vPortSetupTimerInterrupt(void);

/* Critical section nesting counter operations. */
void vPortEnterCritical(void);
void vPortExitCritical(void);

/* Yield via MSIP. */
void vPortYield(void);

/* Machine-mode trap entry — called from mtvec table entry. */
void vPortTrapHandler(void) __attribute__((interrupt("machine")));

/* Called by trap handler for timer tick. */
void vPortTimerHandler(void);

#endif /* PORT_H */
