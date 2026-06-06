/* newlib syscall stubs for the RV32 SoC BSP.
 *
 * GCC's newlib (used for printf, malloc, etc.) calls these seven platform
 * functions.  Without them, linking any standard-library program fails.
 *
 *   _sbrk   — heap allocator backend (used by malloc/free)
 *   _write  — write bytes (routes stdout/stderr to UART0)
 *   _read   — read bytes from UART0
 *   _close  — no file system → ENOSYS
 *   _fstat  — report fd as character device (required for printf to work)
 *   _isatty — always a TTY
 *   _lseek  — no file system → ENOSYS
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdint.h>

/* _heap_start and _heap_end are provided by linker_app.ld. */
extern char _heap_start;
extern char _heap_end;

static char *heap_ptr = &_heap_start;

void *_sbrk(int incr) {
    char *prev = heap_ptr;
    if (heap_ptr + incr > &_heap_end) {
        errno = ENOMEM;
        return (void *)-1;
    }
    heap_ptr += incr;
    return (void *)prev;
}

/* UART0 TX register — write a byte to the transmit FIFO. */
#define UART_BASE   0x10001000UL
#define UART_TXDATA (*(volatile uint32_t *)(UART_BASE + 0x00))
#define UART_STATUS (*(volatile uint32_t *)(UART_BASE + 0x08))
#define UART_TX_FULL (1u << 2)
#define UART_RXDATA (*(volatile uint32_t *)(UART_BASE + 0x04))
#define UART_RX_VALID (1u << 1)

static void _putc(char c) {
    while (UART_STATUS & UART_TX_FULL)
        ;
    UART_TXDATA = (uint8_t)c;
}

static int _getc(void) {
    while (!(UART_STATUS & UART_RX_VALID))
        ;
    return (uint8_t)(UART_RXDATA & 0xFF);
}

int _write(int fd, char *buf, int len) {
    (void)fd;
    for (int i = 0; i < len; i++)
        _putc(buf[i]);
    return len;
}

int _read(int fd, char *buf, int len) {
    (void)fd;
    for (int i = 0; i < len; i++)
        buf[i] = (char)_getc();
    return len;
}

int _close(int fd) {
    (void)fd;
    errno = ENOSYS;
    return -1;
}

int _fstat(int fd, struct stat *st) {
    (void)fd;
    st->st_mode = S_IFCHR;   /* character device — makes printf line-buffer correctly */
    return 0;
}

int _isatty(int fd) {
    (void)fd;
    return 1;
}

int _lseek(int fd, int off, int whence) {
    (void)fd; (void)off; (void)whence;
    errno = ENOSYS;
    return -1;
}

/* _exit — called by exit() / abort(). */
void _exit(int status) {
    (void)status;
    while (1) __asm__ volatile ("wfi");
}

/* _kill / _getpid — required by some newlib configurations. */
int _kill(int pid, int sig) {
    (void)pid; (void)sig;
    errno = ENOSYS;
    return -1;
}

int _getpid(void) {
    return 1;
}
