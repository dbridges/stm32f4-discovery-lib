#ifndef USART_H
#define USART_H

#include <stdint.h>

#define USART3_BUFFER_SIZE      128

static uint8_t USART3_tx_buffer[USART3_BUFFER_SIZE];
static uint8_t USART3_rx_buffer[USART3_BUFFER_SIZE];

static uint16_t USART3_tx_read_ptr = 0;
static uint16_t USART3_tx_write_ptr = 0;
static uint16_t USART3_rx_read_ptr = 0;
static uint16_t USART3_rx_write_ptr = 0;
static uint8_t  USART3_tx_primed = 0;

void USART3_Init(uint32_t baudrate);
void USART3_Write(uint8_t c);
void USART3_Print(char *buff);
uint8_t USART3_Read(void);

#endif
