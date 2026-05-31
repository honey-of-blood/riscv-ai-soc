/*
 * task.h — minimal stub for host-side compilation of heap_4.c.
 * Declares the scheduler guard functions that heap_4 calls around
 * free-list mutations; the test binary provides no-op definitions.
 */
#ifndef TASK_H
#define TASK_H

#include "FreeRTOS.h"

void       vTaskSuspendAll(void);
BaseType_t xTaskResumeAll(void);

#endif /* TASK_H */
