/*
 * FreeRTOS.h — minimal stub for host-side compilation of heap_4.c.
 * Pulls in the project's own config and port headers.
 */
#ifndef FREERTOS_H
#define FREERTOS_H

#include <stdint.h>
#include <stddef.h>
#include "FreeRTOSConfig.h"
#include "portmacro.h"

/* Assert: on host just abort; on target this can be customised. */
#ifndef configASSERT
#include <assert.h>
#define configASSERT(x)  assert(x)
#endif

#endif /* FREERTOS_H */
