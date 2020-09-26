#include "pa_CommonLib/src/pa_Defines.h"

#ifdef DISPLAY_USE_ST7789
extern "C"{
#include "../lcd_drv.h"
}

//spi引脚名
//SCL=SCLK
//SDA=MOSI


#ifdef STM32_F4
void LCD_GPIO_Init(void){
}

void LCD_setRes(unsigned char state){
}

void LCD_setDC(unsigned char state){
}

void LCD_setBLK(unsigned char state){
}

#endif

#endif