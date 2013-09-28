#ifndef DISCOVERY_H
#define DISCOVERY_H

#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#define TRUE                1
#define FALSE               0

#define HIGH                1
#define LOW                 0

#define LED_GREEN           GPIO_Pin_12
#define LED_ORANGE          GPIO_Pin_13
#define LED_RED             GPIO_Pin_14
#define LED_BLUE            GPIO_Pin_15
#define LED_ALL             (LED_GREEN | LED_ORANGE | LED_RED | LED_BLUE)
#define PUSHBUTTON          GPIO_Pin_0

#define LED_PORT            (GPIOD)
#define PUSHBUTTON_PORT     (GPIOA)

void LED_Init(void);
void LED_Set(uint32_t led);
void LED_Reset(uint32_t led);
void LED_Toggle(uint32_t led);

void PUSHBUTTON_Init(void);
uint8_t PUSHBUTTON_Read(void);

#endif
