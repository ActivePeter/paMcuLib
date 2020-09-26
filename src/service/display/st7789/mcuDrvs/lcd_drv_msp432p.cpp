#include "pa_CommonLib/src/pa_Defines.h"

#ifdef DISPLAY_USE_ST7789
extern "C"{
#include "../lcd_drv.h"
}

//spi引脚名
//SCL=SCLK
//SDA=MOSI

#ifdef MSP432P

#define LCD_RES_Port GPIO_PORT_P4
#define LCD_RES_Pin GPIO_PIN0

#define LCD_DC_Port GPIO_PORT_P4
#define LCD_DC_Pin GPIO_PIN2

#define LCD_BLK_Port GPIO_PORT_P4
#define LCD_BLK_Pin GPIO_PIN1

void LCD_GPIO_Init(void){
	GPIO_setAsOutputPin(LCD_RES_Port,LCD_RES_Pin);
	GPIO_setAsOutputPin(LCD_DC_Port,LCD_DC_Pin);
	GPIO_setAsOutputPin(LCD_BLK_Port,LCD_BLK_Pin);
}

void LCD_setRes(unsigned char state){
	if(state){
		GPIO_setOutputHighOnPin(LCD_RES_Port,LCD_RES_Pin);
	}else{
		GPIO_setOutputLowOnPin(LCD_RES_Port,LCD_RES_Pin);
	}

}

void LCD_setDC(unsigned char state){
	if(state){
		GPIO_setOutputHighOnPin(LCD_DC_Port,LCD_DC_Pin);
	}else{
		GPIO_setOutputLowOnPin(LCD_DC_Port,LCD_DC_Pin);
	}
}

void LCD_setBLK(unsigned char state){
	if(state){
		GPIO_setOutputHighOnPin(LCD_BLK_Port,LCD_BLK_Pin);
	}else{
		GPIO_setOutputLowOnPin(LCD_BLK_Port,LCD_BLK_Pin);
	}
}

#endif

/**********************************************
 * 
 * 
 * 移植模板
 * 
 * 
#ifdef MSP432P
void LCD_GPIO_Init(void){

}

void LCD_setRes(unsigned char state){

}
void LCD_setDC(unsigned char state){

}
void LCD_setBLK(unsigned char state){

}

#endif
********************************************/
#endif