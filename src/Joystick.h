#ifndef JOYSTICK_H
#define	JOYSTICK_H

#include "stm32f10x.h"					// Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_dma.h"              // Keil::Device:StdPeriph Drivers:DMA  
#include "DEF_STM32.h"
#include "LiquidCrystalDisplay.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define JOYSTICK_OFFSET	25		
/****************************************************************************************************
*****************************************************************************************************
CUSTOM DATA TYPES and STRUCTURES
*****************************************************************************************************
****************************************************************************************************/
typedef enum{
		UP =0,	//UP
		UR,			//UP RIGHT
		RT,			//RIGHT
		DR,			//DW RIGHT
		DW,			//DOWN
		DL,			//DW LEFT
		LT,			//LEFT		
		UL,			//UP LEFT	
		ND			//NO DIRECTION
}Direction;

typedef struct{
		int16_t		x,y;				//x,y coordinate values
		Direction direction;	//Direction of joystick
}Joystick;
/****************************************************************************************************
*****************************************************************************************************
VARIABLES DEFINITION
*****************************************************************************************************
****************************************************************************************************/
extern uint8_t JOYSTICK_DEBUG;				//Enable/Disable display information. 
																			//Set the value in Joystick.c : 1 - ENABLE, 0 - DISABLE
																			//You can change this value later while programming
extern uint16_t Joystickval[2];				//Storing results from ADC via DMA 
extern char buffer[5];								//For displaying the information with sprintf() 
extern Joystick myJoystick;						//Present status of joystick
extern Joystick lastStateJoystick;		//Last status of joystick
/****************************************************************************************************
*****************************************************************************************************
FUNCTION PROTOTYPES
*****************************************************************************************************
****************************************************************************************************/
void Joystick_Configure_GPIO(void);
void Joystick_Configure_AFIO(void);
void Joystick_Configure_ADC(void);
void Joystick_Configure_DMA(void);
void Joystick_Configure_NVIC(void);
void Joystick_Init(void);
void Joystick_Handler(void);
void Joystick_InitDisplay_Info(void);
void Joystick_DeInitDisplay_Info(void);
void Joystick_Display_Info(void);

#endif
