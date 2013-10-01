#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "systime.h"

#define TRUE                1
#define FALSE               0

struct Task;
typedef void (*TaskCallback)(struct Task *);

typedef struct Task {
    uint32_t run_next;
    uint32_t period;
    TaskCallback callback;
    uint8_t enabled;
} Task;

void Scheduler_SetTaskEnabled(Task *t, uint8_t enable);
void Scheduler_SetTaskPeriod(Task *t, uint16_t period);

/* Scheuler functions */
void Scheduler_Run(uint32_t now);
Task * Scheduler_AddTask(uint32_t run_next, uint32_t period, 
                         TaskCallback callback, uint8_t enabled);

#endif
