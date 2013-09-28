#ifndef SYSTIME_H
#define SYSTIME_H

#include <stdint.h>

#ifndef SYSTIME_COUNTS_PER_MS
#define SYSTIME_COUNTS_PER_MS       1
#endif

void SysTime_Init(void);
void SysTime_Handler(void);
uint32_t systime(void);
uint32_t millis(void);
void delay(uint32_t ms);

#endif
