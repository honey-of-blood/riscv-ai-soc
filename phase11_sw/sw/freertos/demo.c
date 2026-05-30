/*
 * FreeRTOS two-task demo for the RISC-V SoC.
 *
 * Task A: blinks GPIO LED (pin 0) every 500 ms.
 * Task B: prints a UART message every 1000 ms.
 *
 * Both tasks run concurrently, demonstrating that the timer tick and
 * context switch work correctly on hardware.
 *
 * Build: link against FreeRTOS kernel sources + port.c + heap_4.c + HAL.
 *
 * Compile flags (GCC RISC-V bare-metal):
 *   riscv32-unknown-elf-gcc -march=rv32im -mabi=ilp32 -O2 -nostartfiles \
 *       -T link.ld demo.c port.c heap_4.c <FreeRTOS kernel .c files>    \
 *       -I. -I<FreeRTOS include path>                                    \
 *       -o demo.elf
 */

#include "FreeRTOS.h"
#include "task.h"

/* Phase 8 HAL headers — copied/symlinked from phase8_peripherals/sw/hal/. */
#include "periph_base.h"
#include "uart.h"
#include "gpio.h"

/* ── GPIO convenience ────────────────────────────────────────────────────── */
#define GPIO_DIR_REG  (GPIO_BASE + 0x04u)
#define GPIO_DATA_REG (GPIO_BASE + 0x00u)

static inline void gpio_set_pin(uint32_t pin) {
    MMIO32(GPIO_DATA_REG) |= (1u << pin);
}
static inline void gpio_clear_pin(uint32_t pin) {
    MMIO32(GPIO_DATA_REG) &= ~(1u << pin);
}

/* ── Task A — LED blink ──────────────────────────────────────────────────── */
static void vTaskLED(void *pvParameters)
{
    (void)pvParameters;

    /* Configure pin 0 as output. */
    MMIO32(GPIO_DIR_REG) |= 0x01u;

    for (;;) {
        gpio_set_pin(0);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_clear_pin(0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

/* ── Task B — UART heartbeat ─────────────────────────────────────────────── */
static void vTaskUART(void *pvParameters)
{
    (void)pvParameters;

    uint32_t tick_count = 0u;

    for (;;) {
        /* Basic decimal print via uart_putc — no printf dependency.    */
        uart_puts("heartbeat ");
        /* Print tick_count as decimal. */
        char buf[12];
        int  n   = 0;
        uint32_t v = tick_count;
        if (v == 0) { buf[n++] = '0'; }
        else {
            char tmp[10]; int t = 0;
            while (v) { tmp[t++] = '0' + (int)(v % 10); v /= 10; }
            while (t--) buf[n++] = tmp[t + 1]; /* reverse */
        }
        buf[n++] = '\r'; buf[n++] = '\n';
        for (int i = 0; i < n; i++) uart_putc(buf[i]);

        tick_count++;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/* ── main ────────────────────────────────────────────────────────────────── */
int main(void)
{
    /* Create tasks. Both at the same priority — FreeRTOS will time-slice. */
    xTaskCreate(vTaskLED,   "LED",  configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vTaskUART,  "UART", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    /* Start scheduler — never returns on success. */
    vTaskStartScheduler();

    /* Should never reach here. */
    for (;;) ;
}

/* ── FreeRTOS required hooks ─────────────────────────────────────────────── */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask; (void)pcTaskName;
    /* Halt — stack overflow is fatal. */
    for (;;) ;
}

void vApplicationMallocFailedHook(void)
{
    for (;;) ;
}
