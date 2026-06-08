/* hello_world/main.c — UART Hello World for RV32 AI SoC
 * Quick-start: builds in < 5 seconds, upload with tools/upload.py.
 */
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "gpio.h"
#include "soc.h"

int main(void) {
    uart_init(115200);
    gpio_set_dir(0x00FF);  /* lower 8 bits = outputs (LEDs) */

    printf("=== RV32 AI SoC Hello World ===\r\n");
    printf("CPU clock : %lu MHz\r\n", CPU_HZ / 1000000UL);
    printf("UART baud : 115200\r\n");

    /* Fibonacci sequence */
    printf("Fibonacci : ");
    int a = 0, b = 1;
    for (int i = 0; i < 12; i++) {
        printf("%d ", a);
        int tmp = a + b; a = b; b = tmp;
    }
    printf("\r\n");

    /* LED blink loop (counts in binary on LEDs) */
    uint16_t count = 0;
    printf("Blinking LEDs — press any key to stop\r\n");
    while (!uart_rx_ready()) {
        gpio_write(count++ & 0xFF);
        /* Software delay ~0.1 s at 100 MHz */
        for (volatile int d = 0; d < 2500000; d++) {}
    }
    (void)uart_getchar();  /* consume key */

    printf("Done. Goodbye!\r\n");
    return 0;
}
