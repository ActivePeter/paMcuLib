extern "C"{
#include "lcd_drv.h"
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

#ifdef ESP32

#define LCD_RES_Port 13

#define LCD_DC_Port 14

#define LCD_BLK_Port 12

void LCD_GPIO_Init(void){
	pinMode(LCD_RES_Port,  OUTPUT);
    pinMode(LCD_DC_Port,  OUTPUT);
    pinMode(LCD_BLK_Port,  OUTPUT);
}

void LCD_setRes(unsigned char state){
	digitalWrite(LCD_RES_Port, state);
}

void LCD_setDC(unsigned char state){
	digitalWrite(LCD_DC_Port, state);
}

void LCD_setBLK(unsigned char state){
	digitalWrite(LCD_BLK_Port, state);
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
