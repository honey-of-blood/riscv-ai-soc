#ifndef PORTMACRO_H
#define PORTMACRO_H

/* ── RISC-V M-mode FreeRTOS port macros ─────────────────────────────────── */

/* Type definitions. */
#define portSTACK_TYPE     uint32_t
#define portBASE_TYPE      int32_t
#define portUBASE_TYPE     uint32_t
#define portMAX_DELAY      (TickType_t)0xffffffffUL

typedef portSTACK_TYPE   StackType_t;
typedef portBASE_TYPE    BaseType_t;
typedef portUBASE_TYPE   UBaseType_t;
typedef uint32_t         TickType_t;

/* Stack grows downward on RISC-V. */
#define portSTACK_GROWTH          (-1)
#define portTICK_PERIOD_MS        ((TickType_t)1000 / configTICK_RATE_HZ)
#define portBYTE_ALIGNMENT        16
#define portBYTE_ALIGNMENT_MASK   (portBYTE_ALIGNMENT - 1)

/* ── Critical sections ───────────────────────────────────────────────────── */
/* Disable machine-mode interrupts (clear MIE in mstatus). */
#define portDISABLE_INTERRUPTS()                        \
    do { __asm__ volatile ("csrci mstatus, 8" ::: "memory"); } while (0)

/* Enable machine-mode interrupts (set MIE in mstatus). */
#define portENABLE_INTERRUPTS()                         \
    do { __asm__ volatile ("csrsi mstatus, 8" ::: "memory"); } while (0)

extern void vPortEnterCritical(void);
extern void vPortExitCritical(void);

#define portENTER_CRITICAL()   vPortEnterCritical()
#define portEXIT_CRITICAL()    vPortExitCritical()

/* ── Task yield ─────────────────────────────────────────────────────────── */
/* Trigger machine software interrupt (MSIP) to request a context switch. */
extern void vPortYield(void);
#define portYIELD()            vPortYield()
#define portYIELD_FROM_ISR(x)  do { if (x) vPortYield(); } while (0)

/* ── Misc ────────────────────────────────────────────────────────────────── */
#define portNOP()              __asm__ volatile ("nop")
#define portINLINE             __inline__
#define portFORCE_INLINE       __attribute__((always_inline))

/* No MPU on this core. */
#define portUSING_MPU_WRAPPERS  0

/* Limit recursive API calls to protect stack. */
#define portRESET_READY_PRIORITY(uxPriority, uxTopReadyPriority) \
    do { (void)(uxPriority); (void)(uxTopReadyPriority); } while (0)

/* Architecture-specific task init hook (none needed). */
#define portTASK_USES_FLOATING_POINT()

#endif /* PORTMACRO_H */
