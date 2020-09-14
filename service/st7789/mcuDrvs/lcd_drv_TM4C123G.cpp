extern "C"{
#include "../lcd_drv.h"
}

//spi引脚名
//SCL=SCLK
//SDA=MOSI


#ifdef TM4C123G
void LCD_GPIO_Init(void){
}

void LCD_setRes(unsigned char state){
}

void LCD_setDC(unsigned char state){
}

void LCD_setBLK(unsigned char state){
}

#endif

