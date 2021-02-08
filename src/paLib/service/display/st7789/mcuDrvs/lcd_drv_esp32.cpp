#include "pa_Defines.h"

#ifdef DISPLAY_USE_ST7789
extern "C"{
#include "../lcd_drv.h"
}

//spi引脚名
//SCL=SCLK
//SDA=MOSI


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
#endif