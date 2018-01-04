#include "ProjectFunctions.h"

Direction presentDirection;
Direction newDirection;
Direction newDirection_UART;
char USART1_TX_Buffer[15];
char LCD_buffer[15];

void LCD_Display_Direction_Init(void){
		LCD_GotoXY(12,2);
		LCD_PutS((uint8_t*)"Servo:");
}

void LCD_Display_Direction(){
		LCD_GotoXY(18,2);
		LCD_PutS((uint8_t*)"  ");
		LCD_GotoXY(18,2);
		switch(presentDirection){
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

void LCD_Display_USART1_Init(){
		LCD_GotoXY(0,0);
		LCD_PutS("Rx:");
		LCD_GotoXY(0,1);
		LCD_PutS("Tx:");
}

void LCD_Display_USART1_RX(){
		LCD_GotoXY(3,0);
		LCD_PutS((uint8_t*)"                 ");
		LCD_GotoXY(3,0);
		LCD_PutS((uint8_t*)USART1_RX);
}

void LCD_Display_USART1_TX(){
		LCD_GotoXY(3,0);
		LCD_PutS((uint8_t*)"                 ");
		LCD_GotoXY(3,1);
		LCD_PutS((uint8_t*)USART1_TX_Buffer);
}

void USART1_Send_PresentState(void){
		sprintf(USART1_TX_Buffer,"servo_%d#",presentDirection);
		USART_SendString(USART1,(uint8_t*)USART1_TX_Buffer);
		LCD_Display_USART1_TX();
}

void USART1_Send_Error(void){
		sprintf(USART1_TX_Buffer,"servo_error#");
		USART_SendString(USART1,(uint8_t*)USART1_TX_Buffer);
		LCD_Display_USART1_TX();
}

void USART1_Command_Handler(){
		if(strncmp(USART1_RX,"servo_",6)==0){
				if(strncmp(USART1_RX,"servo_connect#",14)==0){
						PROJECT_Sync();
				}
				else if(strncmp(USART1_RX,"servo_n#",8)>0){
						USART1_Send_Error();						
				}
				else{
						newDirection_UART = (Direction)(USART1_RX[6] - 48);	//Character-numeric conversion
						if(newDirection_UART<=8){
								if(newDirection_UART!=presentDirection){
										presentDirection = newDirection_UART;
										PROJECT_Sync();
								}
						}
						else{
								USART1_Send_Error();
						}
				}
		}
		else{
				USART1_Send_Error();
		}
}

void PROJECT_Init(void){
		DelayMs(5);
		Joystick_Init();								DelayMs(5);
		LCD_Init4BitMode(); 						DelayMs(5);
		LCD_Display_USART1_Init(); 			DelayMs(5);
		Joystick_InitDisplay_Info(); 		DelayMs(5);
		USART1_Configuration(); 				DelayMs(5);
		LCD_Display_USART1_Init(); 			DelayMs(5);
		LCD_Display_Direction_Init();		DelayMs(5);
		presentDirection=ND;
		USART1_Send_PresentState();
		LCD_Display_Direction();	
}

void PROJECT_Sync(void){
		LCD_Display_Direction();
		USART1_Send_PresentState();		
}
