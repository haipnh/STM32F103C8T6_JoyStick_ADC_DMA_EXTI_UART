/************************************************************************************************************************
INCLUDING HEADER
*************************************************************************************************************************/
#include "LiquidCrystalDisplay.h"
/************************************************************************************************************************
FUNCTION	: LCD_Configure_GPIO
PARAMETERS: None
RETURN		: None
PURPOSE 	: Configuring GPIO Pins to control LCD
*************************************************************************************************************************/
void LCD_Configure_GPIO(void){
		GPIO_InitTypeDef LCD_GPIO;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		LCD_GPIO.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
		LCD_GPIO.GPIO_Mode = GPIO_Mode_Out_PP;
		LCD_GPIO.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &LCD_GPIO);	
}
/************************************************************************************************************************
FUNCTION	: LCD_4Bit
PARAMETERS: One 4-unsigned-bit
RETURN		: None
PURPOSE 	: Sending 4 bits to LCD  (Seek in HD44780 (LCD Controller) Datasheet)
*************************************************************************************************************************/
void LCD_4Bit(uint8_t data4bit){
		LCD_E = 1;
		DelayUs(3);
		LCD_D7 = (data4bit & 0x08)>>3;
		LCD_D6 = (data4bit & 0x04)>>2;
		LCD_D5 = (data4bit & 0x02)>>1;
		LCD_D4 = (data4bit & 0x01);
		LCD_E = 0;
		DelayUs(50);
}
/************************************************************************************************************************
FUNCTION	: LCD_8Bit
PARAMETERS: One 8-unsigned-bit
RETURN		: None
PURPOSE 	: Sending 8 bits to LCD (Seek in HD44780 (LCD Controller) Datasheet)
*************************************************************************************************************************/
void LCD_8Bit(uint8_t data8bit){
		LCD_4Bit(data8bit>>4);
		DelayUs(200);
		LCD_4Bit(data8bit);
		DelayUs(200);
}
/************************************************************************************************************************
FUNCTION	: LCD_Command
PARAMETERS: One 8-unsigned-bit command
RETURN		: None
PURPOSE 	: Sending 8-unsigned-bit COMMAND to LCD (Seek in HD44780 (LCD Controller) Datasheet)
*************************************************************************************************************************/
void LCD_Command(uint8_t command){
		LCD_RS = 0;
		LCD_RW = 0;
		LCD_8Bit(command);
		DelayMs(2);
}
/************************************************************************************************************************
FUNCTION	: LCD_Data
PARAMETERS: One 8-unsigned-bit data
RETURN		: None
PURPOSE 	: Sending 8-unsigned-bit DATA to LCD (Seek in HD44780 (LCD Controller) Datasheet)
*************************************************************************************************************************/
void LCD_Data(uint8_t data){
		LCD_RS = 1;
		LCD_RW = 0;
		LCD_8Bit(data);
		DelayUs(20);
		LCD_RS = 0;
}
/************************************************************************************************************************
FUNCTION	: LCD_Clear
PARAMETERS: None
RETURN		: None
PURPOSE 	: Sending command LCD_CLEAR_DISPLAY (0x01) to clear screen
*************************************************************************************************************************/
void LCD_Clear(void){
		LCD_Command(LCD_CLEAR_DISPLAY);
		DelayMs(2);
}
/************************************************************************************************************************
FUNCTION	: LCD_Init4BitMode
PARAMETERS: None
RETURN		: None
PURPOSE 	: Initializing the LCD to work with 4-bit mode
*************************************************************************************************************************/
void LCD_Init4BitMode(void){
		LCD_Configure_GPIO();
		LCD_RS = 0;				LCD_RW = 0;		LCD_4Bit(0x0);
		DelayMs(20);
		LCD_4Bit(0x3);
		DelayMs(5);
		LCD_4Bit(0x3);
		DelayUs(100);
		LCD_4Bit(0x3);
		DelayMs(5);
		LCD_4Bit(0x2);
		LCD_Command(0x28);
		LCD_Command(0x0C);		
		LCD_Command(0x01);	//Clear Display
		LCD_Command(0x06);	//Entry mode set
}	
/************************************************************************************************************************
FUNCTION	: LCD_PutC
PARAMETERS: One 8-unsigned-bit ASCII character 
RETURN		: None
PURPOSE 	: Writing an ASCII character at present cursor position on LCD 
*************************************************************************************************************************/
void LCD_PutC(uint8_t myChar){
		LCD_Data(myChar);
}
/************************************************************************************************************************
FUNCTION	: LCD_PutS
PARAMETERS: A string (array of chars) 
RETURN		: None
PURPOSE 	: Writing a string at present cursor position on LCD 
*************************************************************************************************************************/
void LCD_PutS(uint8_t *myString){
		while(*myString){
			LCD_PutC(*myString);
			myString++;
		}
}
/************************************************************************************************************************
FUNCTION	: LCD_GotoXY
PARAMETERS: 8-unsigned-bit column value (0-19)
						8-unsigned-bit row value		(0-3)
RETURN		: None
PURPOSE 	: Setting the cursor position on LCD
*************************************************************************************************************************/
void LCD_GotoXY(uint8_t col,uint8_t row){
		LCD_Command(LCD_Row[row]+col);
}
/************************************************************************************************************************
FUNCTION	: LCD_CGRAMInit
PARAMETERS: None
RETURN		: None
PURPOSE 	: Initializing 10 custom characters in LCD CGRAM
*************************************************************************************************************************/
void LCD_CGRAMInit(void){
		LCD_Command(0x40);
		for(int i = 0; i<64;i++){
				LCD_Data(LCD_Ma8Doan[i]);
		}
		LCD_Clear();
}
/************************************************************************************************************************
FUNCTION	: LCD_SoLon
PARAMETERS: 8-unsigned-bit number (0-9)
						8-unsigned-bit column value (0-19)
						8-unsigned-bit row value (0-3)
RETURN		: None
PURPOSE 	: Writing a big number at specific position on LCD
*************************************************************************************************************************/
void LCD_SoLon(uint8_t x, uint8_t col, uint8_t row){
		LCD_GotoXY(row,col);
		for(int i = 0; i<6; i++){
				if(i==3)		LCD_GotoXY(row+1,col);
				LCD_Data(LCD_SO_X[x][i]);
		}
}
/************************************************************************************************************************
END FILE
*************************************************************************************************************************/
