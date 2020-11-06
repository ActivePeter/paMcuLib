#include "../pa_ILI9341.h"

#ifdef DISPLAY_USE_ILI9341

/****************************************************
 * driver 层代码
 * ***************************************************/

#ifdef STM32_F4

#define pa_ILI9341_CS_GPIO GPIOB
#define pa_ILI9341_CS_PIN GPIO_PIN_0

#define pa_ILI9341_DC_GPIO GPIOB
#define pa_ILI9341_DC_PIN GPIO_PIN_1

#define pa_ILI9341_RST_GPIO GPIOB
#define pa_ILI9341_RST_PIN GPIO_PIN_2

void pa_ILI9341::setCS(uint8_t state)
{
    HAL_GPIO_WritePin(pa_ILI9341_CS_GPIO, pa_ILI9341_CS_PIN, (GPIO_PinState)state);
}

void pa_ILI9341::setDC(uint8_t state)
{
    HAL_GPIO_WritePin(pa_ILI9341_DC_GPIO, pa_ILI9341_DC_PIN, (GPIO_PinState)state);
}

void pa_ILI9341::setRST(uint8_t state)
{
    HAL_GPIO_WritePin(pa_ILI9341_RST_GPIO, pa_ILI9341_RST_PIN, (GPIO_PinState)state);
}

#endif // MSP432P

#endif