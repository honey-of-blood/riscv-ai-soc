#include "FreeRTOS.h"
#include "task.h"
#include "port.h"

/* ── MMIO helper ─────────────────────────────────────────────────────────── */
#define MMIO32(addr)  (*(volatile uint32_t *)(uintptr_t)(addr))

/* ── CLINT register offsets (from configCLINT_BASE_ADDRESS) ─────────────── */
#define CLINT_MSIP        0x00u   /* machine software interrupt pending [0]  */
#define CLINT_MTIME_LO    0x04u   /* mtime[31:0]                             */
#define CLINT_MTIME_HI    0x08u   /* mtime[63:32]                            */
#define CLINT_MTIMECMP_LO 0x0Cu   /* mtimecmp[31:0]                          */
#define CLINT_MTIMECMP_HI 0x10u   /* mtimecmp[63:32]                         */

static inline uint64_t clint_read_mtime(void)
{
    /* Read 64-bit timer safely: re-read high word if it changed mid-read. */
    uint32_t hi0, lo, hi1;
    do {
        hi0 = MMIO32(configCLINT_BASE_ADDRESS + CLINT_MTIME_HI);
        lo  = MMIO32(configCLINT_BASE_ADDRESS + CLINT_MTIME_LO);
        hi1 = MMIO32(configCLINT_BASE_ADDRESS + CLINT_MTIME_HI);
    } while (hi0 != hi1);
    return ((uint64_t)hi0 << 32) | lo;
}

static inline void clint_set_timecmp(uint64_t cmp)
{
    /* Write high word to 0xFFFF_FFFF first to avoid spurious interrupt
       when cmp_lo is temporarily less than mtime_lo during update.     */
    MMIO32(configCLINT_BASE_ADDRESS + CLINT_MTIMECMP_HI) = 0xFFFFFFFFu;
    MMIO32(configCLINT_BASE_ADDRESS + CLINT_MTIMECMP_LO) = (uint32_t)(cmp);
    MMIO32(configCLINT_BASE_ADDRESS + CLINT_MTIMECMP_HI) = (uint32_t)(cmp >> 32);
}

/* ── Critical section nesting ────────────────────────────────────────────── */
static volatile UBaseType_t uxCriticalNesting = 0xAAAAAAAAu;

void vPortEnterCritical(void)
{
    portDISABLE_INTERRUPTS();
    uxCriticalNesting++;
    __asm__ volatile ("" ::: "memory");
}

void vPortExitCritical(void)
{
    configASSERT(uxCriticalNesting > 0u);
    uxCriticalNesting--;
    if (uxCriticalNesting == 0u)
        portENABLE_INTERRUPTS();
}

/* ── Stack initialisation ────────────────────────────────────────────────── */
/*
 * Build the initial stack frame for a new task.  The frame must look exactly
 * like one saved by portSAVE_CONTEXT so that the first context-restore works.
 *
 * pxTopOfStack points to the highest free word on the stack (stack grows down).
 * We fill from top toward bottom; return the new stack pointer (lowest word).
 *
 * Frame layout (word 0 = lowest addr = new SP):
 *   [0]  mstatus   (MIE=1, MPP=11 for M-mode)
 *   [1]  mepc      = pxCode (task entry point)
 *   [2]  x1  (ra)  = 0
 *   [3]  x5..x7  (t0-t2) = 0
 *   ...  [see port.h for full layout]
 *   [27] x31 (t6) = 0
 *   [28] x10 (a0) = pvParameters
 *   [29] x11 (a1) = 0
 *   Total 30 words, SP aligned to 16 bytes.
 */
StackType_t *pxPortInitialiseStack(StackType_t *pxTopOfStack,
                                   TaskFunction_t pxCode,
                                   void          *pvParameters)
{
    /* Align stack pointer to 16-byte boundary (RISC-V ABI requirement). */
    pxTopOfStack = (StackType_t *)
        (((uintptr_t)pxTopOfStack) & ~((uintptr_t)portBYTE_ALIGNMENT_MASK));

    /* Descend one full frame. */
    pxTopOfStack -= PORT_CONTEXT_WORDS;

    /* mstatus: MPP=11 (M-mode), MIE=1 (interrupts enabled on task entry). */
    pxTopOfStack[0]  = 0x00001880u;  /* MPIE=1, MPP=11, MIE=1               */

    /* mepc = task function address. */
    pxTopOfStack[1]  = (StackType_t)(uintptr_t)pxCode;

    /* All general-purpose registers (x1, x5-x31) start at 0. */
    for (int i = 2; i < PORT_CONTEXT_WORDS; i++)
        pxTopOfStack[i] = 0u;

    /* x10 (a0) = task parameter (frame index: mstatus=0, mepc=1, x1=2,
       then registers follow in the order stored by portSAVE_CONTEXT).
       In our layout, x10 is at index 10 (after mstatus,mepc,x1,t0-t2,s0,s1). */
    pxTopOfStack[10] = (StackType_t)(uintptr_t)pvParameters;

    return pxTopOfStack;
}

/* ── Scheduler start ─────────────────────────────────────────────────────── */
BaseType_t xPortStartScheduler(void)
{
    /* Initialise critical-section nesting count. */
    uxCriticalNesting = 0u;

    /* Configure timer interrupt. */
    vPortSetupTimerInterrupt();

    /* Install trap handler into mtvec (direct mode). */
    __asm__ volatile (
        "la   t0, vPortTrapHandler  \n"
        "csrw mtvec, t0             \n"
        ::: "t0", "memory"
    );

    /* Enable machine timer interrupt (MTIE) and machine software interrupt
       (MSIE) in mie, then enable global MIE in mstatus. */
    __asm__ volatile (
        "li   t0, 0x88              \n"   /* MTIE=bit3, MSIE=bit0 → 0x88? */
        "csrs mie, t0               \n"
        "csrsi mstatus, 8           \n"   /* MIE bit in mstatus             */
        ::: "t0", "memory"
    );

    /* Restore the context of the first task — jump to it via mret. */
    extern void vPortRestoreFirstTask(void);
    vPortRestoreFirstTask();

    /* Never reached. */
    return pdFALSE;
}

void vPortEndScheduler(void)
{
    /* Not supported on bare-metal. */
    configASSERT(pdFALSE);
}

/* ── Timer setup ─────────────────────────────────────────────────────────── */
void vPortSetupTimerInterrupt(void)
{
    /* Schedule first tick one period from now. */
    uint64_t now  = clint_read_mtime();
    uint64_t next = now + (configCPU_CLOCK_HZ / configTICK_RATE_HZ);
    clint_set_timecmp(next);
}

/* ── Yield (machine software interrupt) ─────────────────────────────────── */
void vPortYield(void)
{
    /* Set MSIP to trigger machine software interrupt immediately. */
    MMIO32(configCLINT_BASE_ADDRESS + CLINT_MSIP) = 1u;
    /* Compiler barrier — ensure the write is not reordered. */
    __asm__ volatile ("" ::: "memory");
}

/* ── Timer tick handler ──────────────────────────────────────────────────── */
/*
 * Called from vPortTrapHandler when mcause == 0x80000007 (machine timer).
 * Must NOT be declared __attribute__((interrupt)) — vPortTrapHandler already
 * saves and restores the full context.
 */
void vPortTimerHandler(void)
{
    /* Reload timer compare for the next tick. */
    uint64_t next = clint_read_mtime()
                    + (uint64_t)(configCPU_CLOCK_HZ / configTICK_RATE_HZ);
    clint_set_timecmp(next);

    /* Inform FreeRTOS kernel; triggers context switch if a higher-priority
       task has become ready. */
    if (xTaskIncrementTick() != pdFALSE)
        vTaskSwitchContext();
}

/* ── Trap handler ────────────────────────────────────────────────────────── */
/*
 * vPortTrapHandler — M-mode trap entry point (placed in mtvec).
 *
 * Saves the full RISC-V context to the current task stack, dispatches
 * the interrupt, then restores the context of the (possibly new) current task.
 *
 * Context save/restore uses raw assembly so we control the exact stack layout
 * defined in port.h.  The compiler must not insert its own prologue/epilogue,
 * hence __attribute__((naked)).
 *
 * mie bit layout relevant here:
 *   bit 3 (MSIE) — machine software interrupt
 *   bit 7 (MTIE) — machine timer interrupt
 */
__attribute__((naked)) void vPortTrapHandler(void)
{
    __asm__ volatile (
        /* ── Save context ─────────────────────────────────────────── */
        "addi sp, sp, -(30*4)   \n"     /* allocate frame (30 words)      */
        /* mstatus and mepc */
        "csrr t0, mstatus       \n"
        "sw   t0,  0(sp)        \n"
        "csrr t0, mepc          \n"
        "sw   t0,  4(sp)        \n"
        /* x1 (ra) */
        "sw   x1,  8(sp)        \n"
        /* temporaries: t0-t2 = x5-x7 */
        "sw   x5, 12(sp)        \n"
        "sw   x6, 16(sp)        \n"
        "sw   x7, 20(sp)        \n"
        /* saved regs: s0-s1 = x8-x9 */
        "sw   x8, 24(sp)        \n"
        "sw   x9, 28(sp)        \n"
        /* arg regs: a0-a7 = x10-x17 */
        "sw  x10, 32(sp)        \n"
        "sw  x11, 36(sp)        \n"
        "sw  x12, 40(sp)        \n"
        "sw  x13, 44(sp)        \n"
        "sw  x14, 48(sp)        \n"
        "sw  x15, 52(sp)        \n"
        "sw  x16, 56(sp)        \n"
        "sw  x17, 60(sp)        \n"
        /* saved regs: s2-s11 = x18-x27 */
        "sw  x18, 64(sp)        \n"
        "sw  x19, 68(sp)        \n"
        "sw  x20, 72(sp)        \n"
        "sw  x21, 76(sp)        \n"
        "sw  x22, 80(sp)        \n"
        "sw  x23, 84(sp)        \n"
        "sw  x24, 88(sp)        \n"
        "sw  x25, 92(sp)        \n"
        "sw  x26, 96(sp)        \n"
        "sw  x27,100(sp)        \n"
        /* temporaries: t3-t6 = x28-x31 */
        "sw  x28,104(sp)        \n"
        "sw  x29,108(sp)        \n"
        "sw  x30,112(sp)        \n"
        "sw  x31,116(sp)        \n"

        /* ── Save SP to current TCB ───────────────────────────────── */
        /* pxCurrentTCB points to the TCB; first field is pxTopOfStack. */
        "la   t0, pxCurrentTCB  \n"
        "lw   t0, 0(t0)         \n"     /* t0 = pxCurrentTCB->pxTopOfStack  */
        "sw   sp, 0(t0)         \n"     /* save sp into TCB                 */

        /* ── Dispatch ────────────────────────────────────────────── */
        "csrr a0, mcause        \n"     /* a0 = mcause                       */
        "li   t1, 0x80000007    \n"     /* machine timer interrupt           */
        "beq  a0, t1, 1f        \n"
        /* Machine software interrupt (yield request): clear MSIP first. */
        "li   t1, 0x80000003    \n"     /* machine software interrupt        */
        "bne  a0, t1, 2f        \n"
        /* Clear MSIP. */
        "li   t0, 0x10005000    \n"     /* configCLINT_BASE_ADDRESS          */
        "sw   x0, 0(t0)         \n"     /* MSIP = 0                          */
        "call vTaskSwitchContext \n"    /* software yield — switch tasks     */
        "j    2f                \n"
        "1:                     \n"     /* timer interrupt                   */
        "call vPortTimerHandler \n"
        "2:                     \n"     /* done dispatching                  */

        /* ── Restore context of (possibly new) current task ─────── */
        "la   t0, pxCurrentTCB  \n"
        "lw   t0, 0(t0)         \n"
        "lw   sp, 0(t0)         \n"     /* restore sp from TCB               */

        "lw   t0,  0(sp)        \n"     /* mstatus                           */
        "csrw mstatus, t0       \n"
        "lw   t0,  4(sp)        \n"     /* mepc                              */
        "csrw mepc, t0          \n"
        "lw   x1,  8(sp)        \n"
        "lw   x5, 12(sp)        \n"
        "lw   x6, 16(sp)        \n"
        "lw   x7, 20(sp)        \n"
        "lw   x8, 24(sp)        \n"
        "lw   x9, 28(sp)        \n"
        "lw  x10, 32(sp)        \n"
        "lw  x11, 36(sp)        \n"
        "lw  x12, 40(sp)        \n"
        "lw  x13, 44(sp)        \n"
        "lw  x14, 48(sp)        \n"
        "lw  x15, 52(sp)        \n"
        "lw  x16, 56(sp)        \n"
        "lw  x17, 60(sp)        \n"
        "lw  x18, 64(sp)        \n"
        "lw  x19, 68(sp)        \n"
        "lw  x20, 72(sp)        \n"
        "lw  x21, 76(sp)        \n"
        "lw  x22, 80(sp)        \n"
        "lw  x23, 84(sp)        \n"
        "lw  x24, 88(sp)        \n"
        "lw  x25, 92(sp)        \n"
        "lw  x26, 96(sp)        \n"
        "lw  x27,100(sp)        \n"
        "lw  x28,104(sp)        \n"
        "lw  x29,108(sp)        \n"
        "lw  x30,112(sp)        \n"
        "lw  x31,116(sp)        \n"
        "addi sp, sp, (30*4)    \n"     /* deallocate frame                  */
        "mret                   \n"     /* return to task (restores PC+MIE)  */
        ::: "memory"
    );
}

/* ── First task launch ───────────────────────────────────────────────────── */
/*
 * Restore context of the first task and jump into it via mret.
 * Called once at scheduler start; after this we never return.
 */
__attribute__((naked)) void vPortRestoreFirstTask(void)
{
    __asm__ volatile (
        "la   t0, pxCurrentTCB  \n"
        "lw   t0, 0(t0)         \n"     /* t0 = *pxCurrentTCB               */
        "lw   sp, 0(t0)         \n"     /* sp = pxCurrentTCB->pxTopOfStack   */
        "lw   t0,  0(sp)        \n"     /* mstatus                           */
        "csrw mstatus, t0       \n"
        "lw   t0,  4(sp)        \n"     /* mepc = task entry point           */
        "csrw mepc, t0          \n"
        "lw   x1,  8(sp)        \n"
        "lw   x5, 12(sp)        \n"
        "lw   x6, 16(sp)        \n"
        "lw   x7, 20(sp)        \n"
        "lw   x8, 24(sp)        \n"
        "lw   x9, 28(sp)        \n"
        "lw  x10, 32(sp)        \n"     /* a0 = pvParameters                 */
        "lw  x11, 36(sp)        \n"
        "lw  x12, 40(sp)        \n"
        "lw  x13, 44(sp)        \n"
        "lw  x14, 48(sp)        \n"
        "lw  x15, 52(sp)        \n"
        "lw  x16, 56(sp)        \n"
        "lw  x17, 60(sp)        \n"
        "lw  x18, 64(sp)        \n"
        "lw  x19, 68(sp)        \n"
        "lw  x20, 72(sp)        \n"
        "lw  x21, 76(sp)        \n"
        "lw  x22, 80(sp)        \n"
        "lw  x23, 84(sp)        \n"
        "lw  x24, 88(sp)        \n"
        "lw  x25, 92(sp)        \n"
        "lw  x26, 96(sp)        \n"
        "lw  x27,100(sp)        \n"
        "lw  x28,104(sp)        \n"
        "lw  x29,108(sp)        \n"
        "lw  x30,112(sp)        \n"
        "lw  x31,116(sp)        \n"
        "addi sp, sp, (30*4)    \n"
        "mret                   \n"
        ::: "memory"
    );
}
