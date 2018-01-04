#ifndef	PROJECTFUNCTIONS_H
#define	PROJECTDFUNCTIONS_H
//Standard Libraries
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_dma.h"              // Keil::Device:StdPeriph Drivers:DMA
#include "stm32f10x_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "misc.h"                       // Keil::Device:StdPeriph Drivers:Framework
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Custom Libraries
#include "DEF_STM32.h"
#include "delay.h"
#include "LiquidCrystalDisplay.h"
#include "Joystick.h"
#include "UART.h"

extern Direction presentDirection;		//Storing present state of controlled object
extern Direction newDirection;				//Storing new state of controling devices
extern Direction newDirection_UART;		//Storing new state of controling devices (PC or another devices via UART interface)
extern char USART1_TX_Buffer[15];
extern char LCD_buffer[15];

void LCD_Display_Direction(void);
void LCD_Display_USART1_Init(void);
void LCD_Display_USART1_RX(void);
void LCD_Display_USART1_TX(void);
void USART1_Send_PresentState(void);
void USART1_Send_Error(void);
void USART1_Command_Handler(void);	

void PROJECT_Init(void);
void PROJECT_Sync(void);
#endif
