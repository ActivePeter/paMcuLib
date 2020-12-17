#include "../R61408.h"
#ifdef DISPLAY_USE_R61408
#ifdef STM32_H7

#define R61408_SPI_CS_Pin GPIO_PIN_2
#define R61408_SPI_CS_GPIO_Port GPIOE

#define R61408_RST_Pin GPIO_PIN_3
#define R61408_RST_GPIO_Port GPIOE

#define R61408_T_INPUT_Pin GPIO_PIN_4
#define R61408_T_INPUT_GPIO_Port GPIOE

#define R61408_SPI_SDA_T_SCL_Pin GPIO_PIN_6
#define R61408_SPI_SDA_T_SCL_GPIO_Port GPIOB

#define R61408_SPI_DCLK_T_SDA_Pin GPIO_PIN_7
#define R61408_SPI_DCLK_T_SDA_GPIO_Port GPIOB

void R61408::initHardWare(void)
{
}

void R61408::SPI_DCLK(int state)
{
    HAL_GPIO_WritePin(R61408_SPI_DCLK_T_SDA_GPIO_Port, R61408_SPI_DCLK_T_SDA_Pin, (GPIO_PinState)state);
}

void R61408::SPI_SDA(int state)
{
    HAL_GPIO_WritePin(R61408_SPI_SDA_T_SCL_GPIO_Port, R61408_SPI_SDA_T_SCL_Pin, (GPIO_PinState)state);
}

void R61408::SPI_CS(int state)
{
    HAL_GPIO_WritePin(R61408_SPI_CS_GPIO_Port, R61408_SPI_CS_Pin, (GPIO_PinState)state);
}

void R61408::LCD_setReset(int state)
{
    HAL_GPIO_WritePin(R61408_RST_GPIO_Port, R61408_RST_Pin, (GPIO_PinState)state);
}
void R61408::drawPixel(uint16_t x, uint16_t y, int Color)
{

    // LTDC_Buf[y+YSIZE_PHYS*x] = Color;
}
#endif
#endif