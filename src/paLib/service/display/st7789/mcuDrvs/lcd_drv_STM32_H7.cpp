#include "all_config.h"

#ifdef DISPLAY_USE_ST7789
extern "C"
{
#include "../lcd_drv.h"
}

//spi引脚名
//SCL=SCLK
//SDA=MOSI
#define pa_ST7789_BLK_GPIO GPIOB
#define pa_ST7789_BLK_PIN GPIO_PIN_0

#define pa_ST7789_DC_GPIO GPIOB
#define pa_ST7789_DC_PIN GPIO_PIN_1

#define pa_ST7789_RES_GPIO GPIOB
#define pa_ST7789_RES_PIN GPIO_PIN_2

#ifdef STM32_H7
void LCD_GPIO_Init(void)
{
}

void LCD_setRes(unsigned char state)
{
    HAL_GPIO_WritePin(pa_ST7789_RES_GPIO, pa_ST7789_RES_PIN, (GPIO_PinState)state);
}

void LCD_setDC(unsigned char state)
{
    HAL_GPIO_WritePin(pa_ST7789_DC_GPIO, pa_ST7789_DC_PIN, (GPIO_PinState)state);
}

void LCD_setBLK(unsigned char state)
{
    HAL_GPIO_WritePin(pa_ST7789_BLK_GPIO, pa_ST7789_BLK_PIN, (GPIO_PinState)state);
}

#endif

#endif