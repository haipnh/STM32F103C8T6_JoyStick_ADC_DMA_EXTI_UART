/************************************************************************************************************************
DEFINING FILE AND INCLUDING LIBRARIES 
*************************************************************************************************************************/
#ifndef LiquidCrystalDisplay_h
#define LiquidCrystalDisplay_h
#include "stm32f10x.h" 
#include "delay.h"
#include "DEF_STM32.h"

/************************************************************************************************************************
DEFINING ADDRESS OF GPIO PINS THAT USED FOR CONTROLLING THE LCD 
*************************************************************************************************************************/

#define	LCD_RS							PORTA_0
#define LCD_RW							PORTA_1
#define LCD_E								PORTA_2
		
#define LCD_D4 							PORTA_3
#define LCD_D5 							PORTA_4
#define LCD_D6 							PORTA_5
#define LCD_D7 							PORTA_6

#define LCD_FUNCTION_SET 				0x2C	//Che do 4 bit, hien thi 2 hang, font 5x8
#define LCD_DISPLAY_CONTROL    	0x0C	//Cho phep hien thi, khong hien thi con tro
#define LCD_CLEAR_DISPLAY      	0x01	//Xoa man hinh
#define LCD_ENTRY_MODE         	0x06	//               
#define LCD_SHIFT_LEFT         	0x18	//
#define LCD_SHIFT_RIGHT        	0x1C	//

#define LCD_ADDR_LINE1 					0X80
#define LCD_ADDR_LINE2 					0XC0
#define LCD_ADDR_LINE3 					0X94
#define LCD_ADDR_LINE4 					0XD4

/************************************************************************************************************************
CONSTANTS and VARIABLES DEFINITION
*************************************************************************************************************************/

const static uint8_t LCD_Row[]={0x80,0xC0,0x94,0xD4};                  
const static uint8_t LCD_Ma8Doan[] = {
   0x07,0x0F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,  	//DOAN F - 0
   0x1F,0x1F,0x1F,0X00,0X00,0X00,0X00,0X00,  	//DOAN A - 1
   0x1C,0x1E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,  	//DOAN B - 2
   0X00,0X00,0X00,0X00,0X00,0x1F,0x1F,0x1F,  	//DOAN D - 3        		
	 0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1E,0x1C,		//DOAN C - 4
	 0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x0F,0x07,		//DOAN E - 5
   0x1F,0x1F,0x1F,0X00,0X00,0X00,0x1F,0x1F,  	//DOAN G+D-6 
   0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,  	//DOAN I  -7
   }; 

const static uint8_t LCD_SO_X[10][6] ={
                  0,1,2,5,3,4,               // SO 0
                  1,2,32,3,7,3,              // SO 1
                  6,6,2,5,3,3,               // SO 2
                  6,6,2,3,3,4,               // SO 3
                  7,3,7,32,32,7,             // SO 4
                  7,6,6,3,3,4,               // SO 5
                  0,6,6,5,3,4,               // SO 6
                  1,1,7,32,32,7,             // SO 7
                  0,6,2,5,3,4,               // SO 8
                  0,6,2,3,3,4					       // SO 9
                  };
/************************************************************************************************************************
FUNCTIONS PROTOTYPES
*************************************************************************************************************************/									
void LCD_Configure_GPIO(void);
void LCD_4Bit(uint8_t);   //Gui 4 bit
void LCD_8Bit(uint8_t);   //Gui 8 bit su dung ham gui 4 bit
void LCD_Command(uint8_t);//Gui ma lenh den LCD
void LCD_Data(uint8_t);		//Gui du lieu 8 bit
void LCD_Init4BitMode(void);    //Khoi tao che do 4 bit va thiet lap LCD		
void LCD_Clear(void);						//Xoa man hinh
void LCD_PutC(uint8_t);		//Viet mot ki tu len LCD
void LCD_PutS(uint8_t*);  //Viet mot chuoi len LCD
void LCD_GotoXY(uint8_t,uint8_t);	
void LCD_CGRAMInit(void);
void LCD_SoLon(uint8_t, uint8_t, uint8_t);
				
#endif

/************************************************************************************************************************
END FILE
*************************************************************************************************************************/
