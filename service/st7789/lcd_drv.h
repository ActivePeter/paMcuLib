#ifndef __LCD_drv_H
#define __LCD_drv_H

#include "../../drv/pa_CommonDrv.h"

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#define LCD_W 240
#define LCD_H 240

void LCD_GPIO_Init(void);//初始化GPIO

void LCD_setRes(unsigned char);
void LCD_setDC(unsigned char);
void LCD_setBLK(unsigned char);

#define LCD_RES_Clr() LCD_setRes(0)
#define LCD_RES_Set()  LCD_setRes(1)

#define LCD_DC_Clr()   LCD_setDC(0)
#define LCD_DC_Set()   LCD_setDC(1)

#define LCD_BLK_Clr()  LCD_setBLK(0)//BLK
#define LCD_BLK_Set()  LCD_setBLK(1)

#endif




