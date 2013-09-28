#include <stdlib.h>
#include "usart.h"
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

/* USART interface functions. All buffers are circular,
 * with read and write pointers.
 */

/* USART 3 */

void USART3_IRQHandler(void)
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
        /*uint8_t data;*/
        /*data = USART_ReceiveData(USART3) & 0xff;*/
        /*if (!Enqueue(&UART2_RXq, data))*/
            /*RxOverflow = 1;*/
    }
    if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET) {
        /* Write one byte to the transmit data register */
        if (USART3_tx_read_ptr != USART3_tx_write_ptr) {
            USART_SendData(USART3, USART3_tx_buffer[USART3_tx_read_ptr]);
            USART3_tx_read_ptr++;
            if (USART3_tx_read_ptr == USART3_BUFFER_SIZE)
                USART3_tx_read_ptr = 0;
        } else {
            /* All done transmitting, disable transmit interrupt */
            USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
            USART3_tx_primed = 0;
        }
} }

void USART3_Init(uint32_t baudrate)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);

    USART_InitStruct.USART_BaudRate = baudrate;	
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART3, &USART_InitStruct);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART3, USART_IT_TXE, DISABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART3, ENABLE);
}

void USART3_Write(uint8_t c)
{
    USART3_tx_buffer[USART3_tx_write_ptr] = c;
    USART3_tx_write_ptr++;
    if (USART3_tx_write_ptr == USART3_BUFFER_SIZE)
        USART3_tx_write_ptr = 0;
    /*if (USART3_tx_write_ptr == USART3_tx_read_ptr)*/
        /*while (1);*/
    if (!USART3_tx_primed) {
        USART3_tx_primed = 1;
        USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
    }
}

void USART3_Print(char *buff)
{
    uint32_t n = 0;
    while (buff[n] != '\0') {
        USART3_Write((uint8_t) buff[n]);
        n++;
    }
}

void USART3_WriteUnsignedInt(uint32_t val)
{
    
}

uint8_t USART3_Read(void)
{
    return 0;
}

