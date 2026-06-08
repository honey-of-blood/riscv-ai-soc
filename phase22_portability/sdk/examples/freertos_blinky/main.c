/* freertos_blinky/main.c — FreeRTOS LED blinky on RV32 AI SoC
 *
 * Two tasks: task_blink (toggles LEDs at 1 Hz) and task_uart (prints uptime).
 * Demonstrates: FreeRTOS port, task creation, vTaskDelay, UART from a task.
 *
 * Prerequisites: FreeRTOS source tree at ../../freertos/ (download separately).
 * See README_quickstart.md for setup instructions.
 */
#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include "gpio.h"
#include "soc.h"

#define LED_MASK  0x00FFu   /* lower 8 LEDs */
#define BLINK_HZ  1u        /* 1 Hz blink rate */

static void task_blink(void *param) {
    (void)param;
    gpio_set_dir(LED_MASK);
    uint16_t pattern = 0x01;
    for (;;) {
        gpio_write(pattern);
        /* Rotate pattern left */
        pattern = (uint16_t)(((pattern << 1) | (pattern >> 7)) & LED_MASK);
        vTaskDelay(pdMS_TO_TICKS(1000 / BLINK_HZ));
    }
}

static void task_uart(void *param) {
    (void)param;
    uint32_t seconds = 0;
    for (;;) {
        uart_printf("Uptime: %u s\r\n", seconds++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void) {
    uart_init(115200);
    uart_puts("FreeRTOS blinky starting...\r\n");

    xTaskCreate(task_blink, "blink", 128, NULL, 1, NULL);
    xTaskCreate(task_uart,  "uart",  256, NULL, 1, NULL);

    vTaskStartScheduler();

    /* Should never reach here */
    uart_puts("FATAL: scheduler returned!\r\n");
    for (;;) {}
}
