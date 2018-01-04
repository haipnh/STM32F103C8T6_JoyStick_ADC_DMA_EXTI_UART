#include "ProjectFunctions.h"

//Interrupt functions
void EXTI9_5_IRQHandler(){
		if(EXTI_GetITStatus(EXTI_IMR_MR7)!=RESET){
				DelayMs(20);
				EXTI_ClearITPendingBit(EXTI_IMR_MR7);
				presentDirection=ND;
				PROJECT_Sync();
		}
}

void DMA1_Channel1_IRQHandler(){
		if(DMA_GetITStatus(DMA1_IT_TC1)==1){ 		//DMA_IT_TC
				DMA_ClearITPendingBit(DMA1_IT_TC1); //DMA_IT_TC						
				Joystick_Handler();
				newDirection=myJoystick.direction;
				if(newDirection!=ND){
						if(newDirection!=presentDirection){
								presentDirection=newDirection;
								PROJECT_Sync();
						}
				}		
		}
}

void USART1_IRQHandler(void){
		while(!USART_GetFlagStatus(USART1,USART_FLAG_RXNE)); 
				USART1_RX[USART1_RX_Index] = USART1->DR;
		if(USART1_RX[USART1_RX_Index]=='#'){
				USART1_RX[USART1_RX_Index+1]='\0';
				USART1_RX_Index=0;
				USART1_Command_Handler();
				LCD_Display_USART1_RX();
		}
		else{
				USART1_RX_Index++;
		}
}
//Main function
int main(void){
		SystemInit();
		PROJECT_Init();	
		while(1){}
}

/********************************* END OF FILE ********************************/
/******************************************************************************/
