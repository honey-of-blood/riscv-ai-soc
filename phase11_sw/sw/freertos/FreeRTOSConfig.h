#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* ── RISC-V SoC FreeRTOS configuration ──────────────────────────────────── */

/* Scheduler. */
#define configUSE_PREEMPTION                    1
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0
#define configUSE_CO_ROUTINES                   0
#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             0
#define configUSE_COUNTING_SEMAPHORES           1
#define configUSE_TASK_NOTIFICATIONS            1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES   1
#define configUSE_TRACE_FACILITY                0
#define configUSE_STATS_FORMATTING_FUNCTIONS    0
#define configCHECK_FOR_STACK_OVERFLOW          2   /* stack paint + check */

/* Clock and tick. */
#define configCPU_CLOCK_HZ          100000000u  /* 100 MHz system clock   */
#define configTICK_RATE_HZ          1000u        /* 1 ms tick period        */

/* Tasks. */
#define configMAX_PRIORITIES        8
#define configMINIMAL_STACK_SIZE    128          /* words (512 bytes)       */
#define configMAX_TASK_NAME_LEN     16
#define configIDLE_TASK_STACK_SIZE  configMINIMAL_STACK_SIZE

/* Memory. */
#define configSUPPORT_STATIC_ALLOCATION     0
#define configSUPPORT_DYNAMIC_ALLOCATION    1
#define configTOTAL_HEAP_SIZE               (32 * 1024)  /* 32 KB heap     */

/* Timers. */
#define configUSE_TIMERS                    0

/* Queue. */
#define configQUEUE_REGISTRY_SIZE           0

/* CLINT base address (matches phase8 periph_base.h CLINT_BASE). */
#define configCLINT_BASE_ADDRESS            0x10005000u

/* ── API inclusion ───────────────────────────────────────────────────────── */
#define INCLUDE_vTaskDelay              1
#define INCLUDE_vTaskDelayUntil         1
#define INCLUDE_uxTaskGetStackHighWaterMark 1
#define INCLUDE_vTaskDelete             1
#define INCLUDE_vTaskSuspend            1
#define INCLUDE_xTaskGetHandle          0
#define INCLUDE_xResumeFromISR          1
#define INCLUDE_xTaskGetSchedulerState  1

/* ── Port-specific ───────────────────────────────────────────────────────── */
/* mtvec must point to vPortTrapHandler. */
#define configISR_STACK_SIZE_WORDS      256      /* dedicated ISR stack     */

#endif /* FREERTOS_CONFIG_H */
