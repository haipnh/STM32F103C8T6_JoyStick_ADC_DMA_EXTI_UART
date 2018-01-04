#include "Joystick.h"

uint8_t JOYSTICK_DEBUG=1;
uint16_t Joystickval[2];		
char buffer[5];
Joystick myJoystick;
Joystick lastStateJoystick;

void Joystick_Configure_GPIO(void){
		GPIO_InitTypeDef Joystick_Button;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
		Joystick_Button.GPIO_Pin = GPIO_Pin_7;
		Joystick_Button.GPIO_Mode = GPIO_Mode_IPU;
		Joystick_Button.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&Joystick_Button);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);
}

void Joystick_Configure_AFIO(void){
		GPIO_InitTypeDef Joystick_ADC;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_ADC1|RCC_APB2Periph_AFIO,ENABLE);
		Joystick_ADC.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
		Joystick_ADC.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOB,&Joystick_ADC);
}

void Joystick_Configure_ADC(void){
		/*INIT ADC*/
		ADC_InitTypeDef Joystick_ADC;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
		Joystick_ADC.ADC_Mode = ADC_Mode_FastInterl;
		Joystick_ADC.ADC_ScanConvMode = ENABLE;
		//SCAN MODE ON
		Joystick_ADC.ADC_ContinuousConvMode = ENABLE;
		Joystick_ADC.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
		Joystick_ADC.ADC_DataAlign = ADC_DataAlign_Right;
		Joystick_ADC.ADC_NbrOfChannel = 2;
		ADC_Init(ADC1,&Joystick_ADC);
		
		ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_239Cycles5);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_9,2,ADC_SampleTime_239Cycles5);
	
		ADC_AnalogWatchdogThresholdsConfig(ADC1,4095,0);
		ADC_AnalogWatchdogSingleChannelConfig(ADC1,ADC_Channel_8);
		ADC_AnalogWatchdogSingleChannelConfig(ADC1,ADC_Channel_9);
	
		ADC_Cmd(ADC1,ENABLE);
		ADC_DMACmd(ADC1,ENABLE);
		ADC_ResetCalibration(ADC1);
		while(ADC_GetResetCalibrationStatus(ADC1));
		ADC_StartCalibration(ADC1);
		while(ADC_GetCalibrationStatus(ADC1));
		ADC_SoftwareStartConvCmd(ADC1,ENABLE);		
		DMA_Cmd(DMA1_Channel1,ENABLE);
}
void Joystick_Configure_DMA(void){
		/*INIT DMA*/
		DMA_InitTypeDef Joystick_DMA;
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
		//Configure DMA1_Channel1	for ADC1
		DMA_DeInit(DMA1_Channel1);
		Joystick_DMA.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;
		Joystick_DMA.DMA_MemoryBaseAddr = (u32)&Joystickval;
		Joystick_DMA.DMA_DIR = DMA_DIR_PeripheralSRC;
		Joystick_DMA.DMA_BufferSize = 2;
		Joystick_DMA.DMA_PeripheralInc = DMA_PeripheralInc_Disable;			//Disable
		Joystick_DMA.DMA_MemoryInc = DMA_MemoryInc_Enable;
		Joystick_DMA.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
		Joystick_DMA.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
		Joystick_DMA.DMA_Mode = DMA_Mode_Circular;
		Joystick_DMA.DMA_Priority = DMA_Priority_High;
		Joystick_DMA.DMA_M2M = DMA_M2M_Disable;		//Disable
		DMA_Init(DMA1_Channel1,&Joystick_DMA);	
		//ENABLE DMA Interrupt 
		DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);
		DMA_Cmd(DMA1_Channel1,ENABLE);
}

void Joystick_Configure_EXTI(void){
		EXTI_InitTypeDef Joystick_EXTI;
		Joystick_EXTI.EXTI_Line = EXTI_Line7;
		Joystick_EXTI.EXTI_Mode = EXTI_Mode_Interrupt;
		Joystick_EXTI.EXTI_Trigger = EXTI_Trigger_Falling;
		Joystick_EXTI.EXTI_LineCmd = ENABLE;
		EXTI_Init(&Joystick_EXTI);
}

void Joystick_Configure_NVIC(void){
		NVIC_InitTypeDef Joystick_NVIC;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		Joystick_NVIC.NVIC_IRQChannel = EXTI9_5_IRQn;
		Joystick_NVIC.NVIC_IRQChannelPreemptionPriority = 0;
		Joystick_NVIC.NVIC_IRQChannelSubPriority=0;
		Joystick_NVIC.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&Joystick_NVIC);
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		Joystick_NVIC.NVIC_IRQChannel = DMA1_Channel1_IRQn;
		Joystick_NVIC.NVIC_IRQChannelPreemptionPriority = 0;
		Joystick_NVIC.NVIC_IRQChannelSubPriority=1;
		Joystick_NVIC.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&Joystick_NVIC);
}



void Joystick_Init(void){
		Joystick_Configure_GPIO();
		Joystick_Configure_AFIO();
		Joystick_Configure_ADC();
		Joystick_Configure_DMA();
		Joystick_Configure_EXTI();
		Joystick_Configure_NVIC();		
}

/****************************************************************************************************
Name 				: Joystick_Handler
Parameters 	: None
Returns			: None
Purpose			: Handling the x,y value from ADC, moving them into Descartes coordinates	then calculate 
							the direction of joystick.
****************************************************************************************************/
void Joystick_Handler(void){
		//GET RESULT
		myJoystick.x = Joystickval[0];		
		myJoystick.y = Joystickval[1];
		//MOVE TO NEW AXIS VALUE
		myJoystick.x=myJoystick.x-2048; 
		myJoystick.y=2048-myJoystick.y;			
		
		if((abs(lastStateJoystick.x-myJoystick.x)>JOYSTICK_OFFSET)||(abs(lastStateJoystick.y-myJoystick.y)>JOYSTICK_OFFSET)) 
		{		
				lastStateJoystick.x = myJoystick.x;
				lastStateJoystick.y = myJoystick.y;
				//KIEM TRA CAC HUONG BEN PHAI : UP RIGHT, DOWN RIGHT, RIGHT 
				if(myJoystick.x>1792){
						if(myJoystick.y>1792){
								myJoystick.direction = UR;	//UP RIGHT
						}
						else if(myJoystick.y<-1792){
								myJoystick.direction = DR;	//DOWN RIGHT
						}
						else{
								myJoystick.direction = RT;	//RIGHT
						}
				}
				//KIEM TRA CAC HUONG BEN TRAI : UP LEFT, DOWN LEFT, LEFT
				else if(myJoystick.x<-1792){
						if(myJoystick.y>1792){
								myJoystick.direction = UL;
						}
						else if(myJoystick.y<-1792){
								myJoystick.direction = DL;
						}
						else
								myJoystick.direction = LT;
				}
				//KIEM TRA CAC HUONG TREN VA DUOI : UP, DOWN, NO DIRECTION
				else{
						if(myJoystick.y>1792){
								myJoystick.direction = UP;
						}
						else if(myJoystick.y<-1792){
								myJoystick.direction = DW;
						}
						else
								myJoystick.direction = ND;
				}
				if(JOYSTICK_DEBUG) Joystick_Display_Info();
		}
}

/****************************************************************************************************
Name 				: Joystick_InitDisplayDebug
Parameters 	: None
Returns			: None
Purpose			: Displaying joystick's unchanged information
****************************************************************************************************/
void Joystick_InitDisplay_Info(void){
		if(JOYSTICK_DEBUG){
				LCD_GotoXY(0,2);
				LCD_PutS((uint8_t*)"x=");
				LCD_GotoXY(0,3);
				LCD_PutS((uint8_t*)"y=");
		}
}
/****************************************************************************************************
Name 				: Joystick_DeInitDisplayDebug
Parameters 	: None
Returns			: None
Purpose			: Clearing joystick's information
****************************************************************************************************/
void Joystick_DeInitDisplay_Info(void){
		LCD_GotoXY(0,2);
		for(int i=0;i<10;i++){
				LCD_PutC(' ');
		}
		LCD_GotoXY(0,3);
		for(int i=0;i<10;i++){
				LCD_PutC(' ');
		}
}
/****************************************************************************************************
Name 				: Joystick_DisplayDebug
Parameters 	: None
Returns			: None
Purpose			: Displaying joystick's x,y value and direction on LCD
****************************************************************************************************/
void Joystick_Display_Info(void){	
		sprintf(buffer,"%5d",myJoystick.x);
		LCD_GotoXY(2,2);
		LCD_PutS((uint8_t*)buffer);
		sprintf(buffer,"%5d",myJoystick.y);
		LCD_GotoXY(2,3);
		LCD_PutS((uint8_t*)buffer);
		LCD_GotoXY(8,2);
		switch(myJoystick.direction){
				case UP:	LCD_PutS((uint8_t*)"UP");		break;
				case DW:	LCD_PutS((uint8_t*)"DW");		break;
				case LT:	LCD_PutS((uint8_t*)"LT");		break;
				case RT:	LCD_PutS((uint8_t*)"RT");		break;
				case UL:	LCD_PutS((uint8_t*)"UL");		break;
				case UR:	LCD_PutS((uint8_t*)"UR");		break;
				case DL:	LCD_PutS((uint8_t*)"DL");		break;
				case DR:	LCD_PutS((uint8_t*)"DR");		break;
				case ND:	LCD_PutS((uint8_t*)"ND");		break;
				default	:	break;
		}		
}
