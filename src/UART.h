#ifndef __UART_H
#define __UART_H

#include "stm32f10x.h"	   
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
//Buffer
extern char USART1_RX[15];
//extern char USART1_TX[];
extern uint8_t USART1_RX_Index;
void USART1_Configure_GPIO(void);
void USART1_Configure_USART1(void);
void USART1_Configure_NVIC(void);
void USART1_Configuration(void);
void USART_SendChar(USART_TypeDef* USARTx, uint8_t data);
void USART_SendString(USART_TypeDef* USARTx, uint8_t *str);



#endif
