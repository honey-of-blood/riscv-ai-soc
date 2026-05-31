/*
 * test_heap.c — host-side unit tests for heap_4.c (FreeRTOS first-fit allocator).
 *
 * Build & run:
 *   gcc -O2 -Wall -Wextra -DTEST_HOST \
 *       -I. -I../nn \
 *       test_heap.c heap_4.c -o build/test_heap
 *   ./build/test_heap
 *
 * Coverage:
 *   A) Basic alloc/free                — 6 checks
 *   B) Alignment                       — 4 checks
 *   C) Multi-alloc + data integrity    — 5 checks
 *   D) Block coalescence               — 4 checks
 *   E) Heap exhaustion                 — 3 checks
 *   F) Edge cases                      — 4 checks
 *   G) xPortGetMinimumEverFreeHeapSize — 3 checks
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"

/* Stub FreeRTOS scheduler guards — heap_4 calls these around free list ops. */
void vTaskSuspendAll(void) {}
BaseType_t xTaskResumeAll(void) { return 0; }

static int g_pass = 0, g_fail = 0;

#define CHECK(cond, fmt, ...) do {                                      \
    if (cond) { g_pass++;                                               \
                printf("  PASS  " fmt "\n", ##__VA_ARGS__); }          \
    else      { g_fail++;                                               \
                printf("  FAIL  " fmt "\n", ##__VA_ARGS__); }          \
} while (0)

static void section(const char *n) { printf("\n── %s ──\n", n); }

/* Declared in heap_4.c */
void  *pvPortMalloc(size_t xSize);
void   vPortFree(void *pv);
size_t xPortGetFreeHeapSize(void);
size_t xPortGetMinimumEverFreeHeapSize(void);

/* ── A) Basic alloc / free ───────────────────────────────────────────────── */
static void test_basic(void)
{
    section("A) Basic alloc/free");

    /* A1: alloc returns non-NULL */
    void *p = pvPortMalloc(64);
    CHECK(p != NULL, "A1 pvPortMalloc(64) != NULL");

    /* A2: free bytes decrease after alloc */
    size_t after_alloc = xPortGetFreeHeapSize();
    CHECK(after_alloc < configTOTAL_HEAP_SIZE,
          "A2 free heap decreases after alloc (now %zu)", after_alloc);

    /* A3: free returns bytes */
    vPortFree(p);
    size_t after_free = xPortGetFreeHeapSize();
    CHECK(after_free > after_alloc,
          "A3 free heap grows after vPortFree (was %zu, now %zu)",
          after_alloc, after_free);

    /* A4: vPortFree(NULL) does not crash */
    vPortFree(NULL);
    CHECK(1, "A4 vPortFree(NULL) does not crash");

    /* A5: alloc/free/alloc returns usable block (write + readback) */
    uint8_t *q = pvPortMalloc(32);
    CHECK(q != NULL, "A5 second alloc after free succeeds");
    if (q) {
        for (int i = 0; i < 32; i++) q[i] = (uint8_t)i;
        int ok = 1;
        for (int i = 0; i < 32; i++) if (q[i] != (uint8_t)i) { ok = 0; break; }
        CHECK(ok, "A5b readback of written data after reuse");
        vPortFree(q);
    }

    /* A6: heap size roughly restored after all frees */
    size_t final = xPortGetFreeHeapSize();
    CHECK(final > configTOTAL_HEAP_SIZE / 2,
          "A6 heap mostly restored after all frees (free=%zu)", final);
}

/* ── B) Alignment ────────────────────────────────────────────────────────── */
static void test_alignment(void)
{
    section("B) Alignment");

    void *ptrs[4];
    size_t sizes[] = {1, 3, 7, 15};

    for (int i = 0; i < 4; i++) {
        ptrs[i] = pvPortMalloc(sizes[i]);
        uintptr_t addr = (uintptr_t)ptrs[i];
        CHECK((addr & portBYTE_ALIGNMENT_MASK) == 0,
              "B%d pvPortMalloc(%zu) addr 0x%lx is %d-byte aligned",
              i + 1, sizes[i], (unsigned long)addr, portBYTE_ALIGNMENT);
    }
    for (int i = 0; i < 4; i++) vPortFree(ptrs[i]);
}

/* ── C) Multi-alloc + data integrity ────────────────────────────────────── */
static void test_multi(void)
{
    section("C) Multi-alloc + data integrity");

    enum { N = 8, SZ = 128 };
    void *ptrs[N];

    /* C1: allocate N blocks without failure */
    int all_ok = 1;
    for (int i = 0; i < N; i++) {
        ptrs[i] = pvPortMalloc(SZ);
        if (!ptrs[i]) { all_ok = 0; break; }
        memset(ptrs[i], (uint8_t)(0xA0 + i), SZ);
    }
    CHECK(all_ok, "C1 %d concurrent %d-byte allocs all succeed", N, SZ);

    /* C2: verify no block overlaps (each block contains its own fill pattern) */
    int no_overlap = 1;
    for (int i = 0; i < N && ptrs[i]; i++) {
        uint8_t *b = ptrs[i];
        for (int j = 0; j < SZ; j++) {
            if (b[j] != (uint8_t)(0xA0 + i)) { no_overlap = 0; break; }
        }
    }
    CHECK(no_overlap, "C2 no block overlap — each block retains its fill pattern");

    /* C3: blocks are at distinct addresses */
    int distinct = 1;
    for (int i = 0; i < N && ptrs[i]; i++)
        for (int j = i + 1; j < N && ptrs[j]; j++)
            if (ptrs[i] == ptrs[j]) { distinct = 0; break; }
    CHECK(distinct, "C3 all allocated blocks have distinct addresses");

    /* C4: free every other block, then reallocate without crash */
    for (int i = 0; i < N; i += 2) vPortFree(ptrs[i]);
    void *p = pvPortMalloc(SZ);
    CHECK(p != NULL, "C4 realloc after freeing alternating blocks succeeds");
    if (p) vPortFree(p);

    /* C5: free remaining blocks */
    for (int i = 1; i < N; i += 2) vPortFree(ptrs[i]);
    size_t after = xPortGetFreeHeapSize();
    CHECK(after > (size_t)(N * SZ / 2),
          "C5 heap size reasonable after full multi-block free (free=%zu)", after);
}

/* ── D) Block coalescence ────────────────────────────────────────────────── */
static void test_coalescence(void)
{
    section("D) Block coalescence");

    size_t before = xPortGetFreeHeapSize();

    /* Allocate three adjacent blocks */
    void *a = pvPortMalloc(64);
    void *b = pvPortMalloc(64);
    void *c = pvPortMalloc(64);
    CHECK(a && b && c, "D1 allocate three 64-byte blocks");

    /* Free middle block, then outer blocks — heap should coalesce */
    vPortFree(b);
    vPortFree(a);
    vPortFree(c);

    size_t after = xPortGetFreeHeapSize();
    CHECK(after >= before - 64,
          "D2 heap mostly restored after coalescing three blocks (before=%zu after=%zu)",
          before, after);

    /* D3: after coalescence, a large contiguous block is available */
    void *big = pvPortMalloc(150);
    CHECK(big != NULL, "D3 large alloc (150B) succeeds after coalescence");
    if (big) vPortFree(big);

    /* D4: alloc-free in reverse order also coalesces */
    void *x = pvPortMalloc(32);
    void *y = pvPortMalloc(32);
    vPortFree(y);
    vPortFree(x);
    void *z = pvPortMalloc(60);
    CHECK(z != NULL, "D4 60-byte alloc succeeds after reverse-order free (coalescence)");
    if (z) vPortFree(z);
}

/* ── E) Heap exhaustion ──────────────────────────────────────────────────── */
static void test_exhaustion(void)
{
    section("E) Heap exhaustion");

    /* Drain the heap with small blocks */
    enum { MAX_PTRS = 2048 };
    void **ptrs = malloc(MAX_PTRS * sizeof(void *));
    int n = 0;
    while (n < MAX_PTRS) {
        void *p = pvPortMalloc(64);
        if (!p) break;
        ptrs[n++] = p;
    }
    CHECK(n > 0, "E1 allocated %d blocks before exhaustion", n);

    /* E2: further alloc returns NULL (not a crash) */
    void *over = pvPortMalloc(1024);
    CHECK(over == NULL, "E2 pvPortMalloc returns NULL on heap exhaustion");

    /* E3: free all, then heap recovers */
    for (int i = 0; i < n; i++) vPortFree(ptrs[i]);
    free(ptrs);
    void *recover = pvPortMalloc(64);
    CHECK(recover != NULL, "E3 alloc succeeds after recovering from exhaustion");
    if (recover) vPortFree(recover);
}

/* ── F) Edge cases ───────────────────────────────────────────────────────── */
static void test_edge(void)
{
    section("F) Edge cases");

    /* F1: alloc size=0 — must not crash (returns NULL or valid ptr per impl) */
    void *p0 = pvPortMalloc(0);
    (void)p0;
    CHECK(1, "F1 pvPortMalloc(0) does not crash");
    if (p0) vPortFree(p0);

    /* F2: alloc size=1 (minimum useful) */
    uint8_t *p1 = pvPortMalloc(1);
    CHECK(p1 != NULL, "F2 pvPortMalloc(1) != NULL");
    if (p1) { *p1 = 0xBE; CHECK(*p1 == 0xBE, "F2b single-byte write/read"); vPortFree(p1); }

    /* F3: alloc very large block (> heap) returns NULL */
    void *huge = pvPortMalloc(configTOTAL_HEAP_SIZE + 1);
    CHECK(huge == NULL, "F3 pvPortMalloc(heap+1) returns NULL");

    /* F4: xPortGetFreeHeapSize is monotonically non-increasing during allocs */
    size_t s0 = xPortGetFreeHeapSize();
    void *pa = pvPortMalloc(256);
    size_t s1 = xPortGetFreeHeapSize();
    void *pb = pvPortMalloc(256);
    size_t s2 = xPortGetFreeHeapSize();
    CHECK(s0 >= s1 && s1 >= s2,
          "F4 free heap non-increasing during allocs (%zu >= %zu >= %zu)", s0, s1, s2);
    if (pa) vPortFree(pa);
    if (pb) vPortFree(pb);
}

/* ── G) xPortGetMinimumEverFreeHeapSize ─────────────────────────────────── */
static void test_watermark(void)
{
    section("G) xPortGetMinimumEverFreeHeapSize");

    size_t wm_before = xPortGetMinimumEverFreeHeapSize();

    /* G1: watermark is <= current free size */
    CHECK(wm_before <= xPortGetFreeHeapSize(),
          "G1 min_ever (%zu) <= current free (%zu)", wm_before, xPortGetFreeHeapSize());

    /* G2: watermark decreases (or stays) when we do a big alloc */
    void *big = pvPortMalloc(4096);
    size_t wm_after = xPortGetMinimumEverFreeHeapSize();
    CHECK(wm_after <= wm_before,
          "G2 min_ever non-increasing after large alloc (%zu → %zu)", wm_before, wm_after);
    if (big) vPortFree(big);

    /* G3: watermark does NOT increase after free */
    size_t wm_final = xPortGetMinimumEverFreeHeapSize();
    CHECK(wm_final <= wm_before,
          "G3 min_ever does not rise after free (%zu <= %zu)", wm_final, wm_before);
}

/* ── main ────────────────────────────────────────────────────────────────── */
int main(void)
{
    printf("Phase 11 heap_4 allocator test suite\n");
    printf("=====================================\n");

    test_basic();
    test_alignment();
    test_multi();
    test_coalescence();
    test_exhaustion();
    test_edge();
    test_watermark();

    printf("\n=====================================\n");
    printf("TOTAL: %d / %d passed", g_pass, g_pass + g_fail);
    if (g_fail == 0) printf("  ✓ ALL PASS\n");
    else             printf("  ✗ %d FAILED\n", g_fail);
    return g_fail ? 1 : 0;
}
