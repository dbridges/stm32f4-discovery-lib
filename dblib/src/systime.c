#include "systime.h"
#include "stm32f4xx.h"
#include "time.h"

static volatile uint32_t counter = 0;

void SysTime_Init(void)
{
    counter = 0;
    SysTick_Config(SystemCoreClock/(1000*SYSTIME_COUNTS_PER_MS));
}

void SysTime_Handler(void)
{
    counter++;
}

uint32_t systime(void)
{
    return counter;
}

uint32_t millis(void)
{
    return counter / SYSTIME_COUNTS_PER_MS;
}

void delay(uint32_t ms)
{
    uint32_t current = millis();
    while (millis() - current < ms);
}
