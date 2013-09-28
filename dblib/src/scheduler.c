#include "scheduler.h"
#include "time.h"
#include "macros.h"

static uint8_t num_tasks = 0;
static Task tasks[10];

void Scheduler_SetTaskEnabled(Task *t, uint8_t enable)
{
    t->enabled = enable;
}

void Scheduler_SetTaskPeriod(Task *t, uint16_t period)
{
    /* set how often to run the task. */
    t->period = period;
}

void Scheduler_Run(uint32_t now)
{
    static uint32_t old_time = 0;
    
    if (now == old_time) return;

    for (int i = 0; i < num_tasks; i++) {
        if (tasks[i].run_next < now && 
                tasks[i].enabled) {
            tasks[i].callback(&tasks[i]);
            tasks[i].run_next = now + tasks[i].period;
            if (tasks[i].period == 0) {
                Scheduler_SetTaskEnabled(&tasks[i], FALSE);
            }
        }
    }

    old_time = now;
}

Task * Scheduler_AddTask(uint32_t run_next, uint32_t period, 
                         TaskCallback callback, uint8_t enabled) {
    tasks[num_tasks].run_next = run_next;
    tasks[num_tasks].period = period;
    tasks[num_tasks].callback = callback;
    tasks[num_tasks].enabled = enabled;

    return &tasks[num_tasks++];
}
