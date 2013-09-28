#include "discovery.h"

void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = LED_ALL;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(LED_PORT, &GPIO_InitStructure);
    GPIO_ResetBits(LED_PORT, LED_ALL);
}

void LED_Set(uint32_t led)
{
    GPIO_SetBits(LED_PORT, led);
}

void LED_Reset(uint32_t led)
{
    GPIO_ResetBits(LED_PORT, led);
}

void LED_Toggle(uint32_t led)
{
    GPIO_ToggleBits(LED_PORT, led);
}


void PUSHBUTTON_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = PUSHBUTTON;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_Init(PUSHBUTTON_PORT, &GPIO_InitStructure);
}

uint8_t PUSHBUTTON_Read(void)
{
    return GPIO_ReadInputDataBit(PUSHBUTTON_PORT, PUSHBUTTON);
}

