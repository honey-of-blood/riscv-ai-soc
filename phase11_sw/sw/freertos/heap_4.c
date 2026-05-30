/*
 * FreeRTOS heap_4 — first-fit allocator with block coalescence.
 *
 * This is a standalone implementation matching the FreeRTOS heap_4 algorithm.
 * The heap is carved from a statically allocated array of size
 * configTOTAL_HEAP_SIZE bytes.
 *
 * Differences from the upstream FreeRTOS heap_4.c:
 *   - No MPU region tracking (not needed for M-mode bare-metal).
 *   - configAPPLICATION_ALLOCATED_HEAP is not supported; the heap lives in BSS.
 */

#include "FreeRTOS.h"
#include "task.h"

/* Block sizes must be a multiple of portBYTE_ALIGNMENT. */
#define heapBITS_PER_BYTE        ((size_t)8)
#define heapSTRUCT_SIZE          (sizeof(BlockLink_t))
#define heapMINIMUM_BLOCK_SIZE   (heapSTRUCT_SIZE * 2)

/* Marks the high bit of a block's xBlockSize field to indicate allocated. */
#define heapBLOCK_ALLOCATED_BITMASK  \
    (((size_t)1) << ((sizeof(size_t) * heapBITS_PER_BYTE) - 1))

#define heapFREE_BLOCK(pxBlock)  \
    ((((pxBlock)->xBlockSize) & heapBLOCK_ALLOCATED_BITMASK) == 0)

/* ── Block link structure ────────────────────────────────────────────────── */
typedef struct A_BLOCK_LINK {
    struct A_BLOCK_LINK *pxNextFreeBlock;
    size_t               xBlockSize;
} BlockLink_t;

/* ── Heap storage ────────────────────────────────────────────────────────── */
static uint8_t ucHeap[configTOTAL_HEAP_SIZE]
    __attribute__((aligned(portBYTE_ALIGNMENT)));

/* Free list sentinels. */
static BlockLink_t xStart;
static BlockLink_t *pxEnd = NULL;

static size_t xFreeBytesRemaining      = 0u;
static size_t xMinimumEverFreeBytesRemaining = 0u;
static size_t xBlockAllocatedBit       = 0u;

/* ── Internal helpers ────────────────────────────────────────────────────── */

static void prvInsertBlockIntoFreeList(BlockLink_t *pxBlockToInsert)
{
    BlockLink_t *pxIterator;

    /* Walk the free list to find the insertion point (ascending address). */
    for (pxIterator = &xStart;
         pxIterator->pxNextFreeBlock < pxBlockToInsert;
         pxIterator = pxIterator->pxNextFreeBlock)
        ;

    /* Merge with next block if adjacent. */
    if ((uint8_t *)pxBlockToInsert + pxBlockToInsert->xBlockSize
            == (uint8_t *)pxIterator->pxNextFreeBlock) {
        if (pxIterator->pxNextFreeBlock != pxEnd) {
            pxBlockToInsert->xBlockSize +=
                pxIterator->pxNextFreeBlock->xBlockSize;
            pxBlockToInsert->pxNextFreeBlock =
                pxIterator->pxNextFreeBlock->pxNextFreeBlock;
        } else {
            pxBlockToInsert->pxNextFreeBlock = pxEnd;
        }
    } else {
        pxBlockToInsert->pxNextFreeBlock = pxIterator->pxNextFreeBlock;
    }

    /* Merge with previous block if adjacent. */
    if ((uint8_t *)pxIterator + pxIterator->xBlockSize
            == (uint8_t *)pxBlockToInsert) {
        if (pxIterator != &xStart) {
            pxIterator->xBlockSize += pxBlockToInsert->xBlockSize;
            pxIterator->pxNextFreeBlock = pxBlockToInsert->pxNextFreeBlock;
            return;
        }
    }

    pxIterator->pxNextFreeBlock = pxBlockToInsert;
}

static void prvHeapInit(void)
{
    BlockLink_t *pxFirstFreeBlock;
    uint8_t     *pucAlignedHeap;
    size_t       uxAddress;
    size_t       xTotalHeapSize = configTOTAL_HEAP_SIZE;

    /* Align heap start. */
    uxAddress = (size_t)ucHeap;
    if ((uxAddress & portBYTE_ALIGNMENT_MASK) != 0) {
        uxAddress  += portBYTE_ALIGNMENT - 1;
        uxAddress  &= ~((size_t)portBYTE_ALIGNMENT_MASK);
        xTotalHeapSize -= uxAddress - (size_t)ucHeap;
    }
    pucAlignedHeap = (uint8_t *)uxAddress;

    /* xStart sentinel. */
    xStart.pxNextFreeBlock = (BlockLink_t *)pucAlignedHeap;
    xStart.xBlockSize = 0;

    /* pxEnd sentinel at the very end of the heap. */
    uxAddress = (size_t)pucAlignedHeap + xTotalHeapSize;
    uxAddress -= heapSTRUCT_SIZE;
    uxAddress &= ~((size_t)portBYTE_ALIGNMENT_MASK);
    pxEnd = (BlockLink_t *)uxAddress;
    pxEnd->xBlockSize = 0;
    pxEnd->pxNextFreeBlock = NULL;

    /* One large free block spanning the whole heap. */
    pxFirstFreeBlock = (BlockLink_t *)pucAlignedHeap;
    pxFirstFreeBlock->xBlockSize      = (size_t)(uxAddress - (size_t)pucAlignedHeap);
    pxFirstFreeBlock->pxNextFreeBlock = pxEnd;

    xFreeBytesRemaining = xMinimumEverFreeBytesRemaining
                        = pxFirstFreeBlock->xBlockSize;

    xBlockAllocatedBit = heapBLOCK_ALLOCATED_BITMASK;
}

/* ── Public API ──────────────────────────────────────────────────────────── */

void *pvPortMalloc(size_t xWantedSize)
{
    BlockLink_t *pxBlock, *pxPreviousBlock, *pxNewBlockLink;
    void        *pvReturn = NULL;

    vTaskSuspendAll();
    {
        if (pxEnd == NULL)
            prvHeapInit();

        if ((xWantedSize & heapBLOCK_ALLOCATED_BITMASK) == 0) {
            /* Adjust for block header and alignment. */
            if ((xWantedSize > 0) &&
                (xWantedSize <= (configTOTAL_HEAP_SIZE - heapSTRUCT_SIZE))) {
                xWantedSize += heapSTRUCT_SIZE;
                if ((xWantedSize & portBYTE_ALIGNMENT_MASK) != 0) {
                    xWantedSize += portBYTE_ALIGNMENT
                                   - (xWantedSize & portBYTE_ALIGNMENT_MASK);
                }
            }

            if ((xWantedSize > 0) && (xWantedSize <= xFreeBytesRemaining)) {
                /* First-fit search. */
                pxPreviousBlock = &xStart;
                pxBlock = xStart.pxNextFreeBlock;

                while ((pxBlock->xBlockSize < xWantedSize)
                        && (pxBlock->pxNextFreeBlock != NULL)) {
                    pxPreviousBlock = pxBlock;
                    pxBlock         = pxBlock->pxNextFreeBlock;
                }

                if (pxBlock != pxEnd) {
                    pvReturn = (void *)((uint8_t *)pxPreviousBlock->pxNextFreeBlock
                                        + heapSTRUCT_SIZE);

                    /* Unlink from free list. */
                    pxPreviousBlock->pxNextFreeBlock = pxBlock->pxNextFreeBlock;

                    /* Split if remainder is large enough. */
                    if ((pxBlock->xBlockSize - xWantedSize) > heapMINIMUM_BLOCK_SIZE) {
                        pxNewBlockLink = (BlockLink_t *)
                            ((uint8_t *)pxBlock + xWantedSize);
                        pxNewBlockLink->xBlockSize =
                            pxBlock->xBlockSize - xWantedSize;
                        pxBlock->xBlockSize = xWantedSize;
                        prvInsertBlockIntoFreeList(pxNewBlockLink);
                    }

                    xFreeBytesRemaining -= pxBlock->xBlockSize;
                    if (xFreeBytesRemaining < xMinimumEverFreeBytesRemaining)
                        xMinimumEverFreeBytesRemaining = xFreeBytesRemaining;

                    /* Mark allocated. */
                    pxBlock->xBlockSize |= xBlockAllocatedBit;
                    pxBlock->pxNextFreeBlock = NULL;
                }
            }
        }

        configASSERT((((size_t)pvReturn) & portBYTE_ALIGNMENT_MASK) == 0);
    }
    (void)xTaskResumeAll();

    return pvReturn;
}

void vPortFree(void *pv)
{
    uint8_t     *puc = (uint8_t *)pv;
    BlockLink_t *pxLink;

    if (pv == NULL) return;

    /* Step back to the block header. */
    puc    -= heapSTRUCT_SIZE;
    pxLink  = (BlockLink_t *)puc;

    configASSERT((pxLink->xBlockSize & heapBLOCK_ALLOCATED_BITMASK) != 0);
    configASSERT(pxLink->pxNextFreeBlock == NULL);

    if ((pxLink->xBlockSize & heapBLOCK_ALLOCATED_BITMASK) != 0) {
        if (pxLink->pxNextFreeBlock == NULL) {
            /* Clear allocated bit, return to free list. */
            pxLink->xBlockSize &= ~heapBLOCK_ALLOCATED_BITMASK;

            vTaskSuspendAll();
            {
                xFreeBytesRemaining += pxLink->xBlockSize;
                prvInsertBlockIntoFreeList(pxLink);
            }
            (void)xTaskResumeAll();
        }
    }
}

size_t xPortGetFreeHeapSize(void)
{
    return xFreeBytesRemaining;
}

size_t xPortGetMinimumEverFreeHeapSize(void)
{
    return xMinimumEverFreeBytesRemaining;
}

void vPortInitialiseBlocks(void)
{
    /* Nothing to do — heap is initialised lazily on first pvPortMalloc(). */
}
