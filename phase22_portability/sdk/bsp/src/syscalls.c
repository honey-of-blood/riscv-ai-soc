/* syscalls.c — newlib minimal syscall stubs for RV32 SoC bare-metal */
#include <sys/stat.h>
#include <sys/times.h>
#include <errno.h>
#include <stdint.h>
#include "uart.h"

/* ── Heap (grows up from _end, declared in linker script) ──────────────── */
extern char _end;
static char *heap_ptr = &_end;

extern char _stack_top;

void *_sbrk(ptrdiff_t incr) {
    char *prev = heap_ptr;
    if (heap_ptr + incr > &_stack_top - 256) {
        errno = ENOMEM;
        return (void *)-1;
    }
    heap_ptr += incr;
    return prev;
}

/* ── I/O (stdout/stderr → UART) ────────────────────────────────────────── */
int _write(int fd, const char *buf, int len) {
    (void)fd;
    for (int i = 0; i < len; i++) uart_putchar(buf[i]);
    return len;
}

int _read(int fd, char *buf, int len) {
    (void)fd;
    for (int i = 0; i < len; i++) buf[i] = uart_getchar();
    return len;
}

/* ── Stubs ──────────────────────────────────────────────────────────────── */
void _exit(int status) {
    (void)status;
    /* Halt: spin in a tight loop so JTAG can inspect state */
    while (1) __asm__ volatile("wfi");
}

int _close(int fd)         { (void)fd; return -1; }
int _fstat(int fd, struct stat *st) { (void)fd; st->st_mode = S_IFCHR; return 0; }
int _isatty(int fd)        { (void)fd; return 1; }
int _lseek(int fd, int offset, int whence) { (void)fd; (void)offset; (void)whence; return 0; }
int _getpid(void)          { return 1; }
int _kill(int pid, int sig){ (void)pid; (void)sig; errno = EINVAL; return -1; }
int _open(const char *path, int flags, ...) { (void)path; (void)flags; return -1; }
clock_t _times(struct tms *buf) {
    if (buf) { buf->tms_utime = buf->tms_stime = buf->tms_cutime = buf->tms_cstime = 0; }
    return (clock_t)-1;
}
