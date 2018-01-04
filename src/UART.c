#include "UART.h"

char USART1_RX[15];
uint8_t USART1_RX_Index=0;

void USART1_Configure_GPIO(void){
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
		/*Configure USART1 Tx (PB_06) as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		/*Configure USART1 Rx (PB_07) as input floating */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		//Because we use PB_06 and PB_07 for USART1 (no default USART1 pins (PA_09, PA_10) so we have to remap them)
		GPIO_PinRemapConfig(GPIO_Remap_USART1,ENABLE);
}

void USART1_Configure_USART1(void){
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		USART_InitTypeDef USART_InitStructure;
		USART_InitStructure.USART_BaudRate            = 115200;
		USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits            = USART_StopBits_1;   
		USART_InitStructure.USART_Parity              = USART_Parity_No ;    
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_InitStructure);
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//Enable Interrupt
		USART_Cmd(USART1, ENABLE);  
}

void USART1_Configure_NVIC(void){
		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
}

void USART1_Configuration(void){
		USART1_Configure_GPIO();
		USART1_Configure_USART1();
		USART1_Configure_NVIC();
}
void USART_SendChar(USART_TypeDef* USARTx, uint8_t data){
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
		USART_SendData(USARTx,data);	
}

void USART_SendString(USART_TypeDef* USARTx, uint8_t *str){
		while (*str)   { 
			 USART_SendChar(USARTx,*str); 
			 str++;
		}
}
