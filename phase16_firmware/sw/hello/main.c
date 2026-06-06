/* Hello World demo — exercises printf (→ UART via _write stub) and malloc. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    printf("Hello from RV32 SoC!\r\n");

    /* Exercise malloc / free via newlib + _sbrk stub. */
    char *buf = malloc(64);
    if (!buf) {
        printf("malloc failed\r\n");
        return 1;
    }
    snprintf(buf, 64, "printf(\"Hello %%d\\n\", %d) works!", 42);
    printf("%s\r\n", buf);
    free(buf);

    /* Fibonacci sequence — exercises basic computation. */
    printf("Fibonacci: ");
    int a = 0, b = 1;
    for (int i = 0; i < 10; i++) {
        printf("%d ", a);
        int tmp = a + b;
        a = b;
        b = tmp;
    }
    printf("\r\n");

    return 0;
}
