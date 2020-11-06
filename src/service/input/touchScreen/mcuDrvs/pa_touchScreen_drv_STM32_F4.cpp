#include "../pa_touchScreen.h"

#ifdef INPUT_USE_TOUCHSCREEN

/****************************************************
 * driver 层代码
 * ***************************************************/

#ifdef STM32_F4

#define pa_touchScreen_CS_port GPIOE
#define pa_touchScreen_CS_pin GPIO_PIN_10

#define pa_touchScreen_IRQ_port GPIOE
#define pa_touchScreen_IRQ_pin GPIO_PIN_9

#define pa_touchScreen_MOSI_port GPIOE
#define pa_touchScreen_MOSI_pin GPIO_PIN_11

#define pa_touchScreen_MISO_port GPIOE
#define pa_touchScreen_MISO_pin GPIO_PIN_12

#define pa_touchScreen_CLK_port GPIOE
#define pa_touchScreen_CLK_pin GPIO_PIN_13

void pa_touchScreen::Hardware_Init()
{
    //32啥也不用初始化
}

uint8_t pa_touchScreen::Hardware_ReadIRQ()
{
    return ((uint8_t)HAL_GPIO_ReadPin(pa_touchScreen_IRQ_port, pa_touchScreen_IRQ_pin));
}

void pa_touchScreen::Hardware_SetCS(uint8_t state)
{
    HAL_GPIO_WritePin(pa_touchScreen_CS_port, pa_touchScreen_CS_pin, (GPIO_PinState)state);
}

void pa_touchScreen::Hardware_setMOSI(uint8_t state)
{
    HAL_GPIO_WritePin(pa_touchScreen_MOSI_port, pa_touchScreen_MOSI_pin, (GPIO_PinState)state);
}

uint8_t pa_touchScreen::Hardware_ReadMISO()
{
    return (uint8_t)HAL_GPIO_ReadPin(pa_touchScreen_MISO_port, pa_touchScreen_MISO_pin);
}

void pa_touchScreen::Hardware_setCLK(uint8_t state)
{
    HAL_GPIO_WritePin(pa_touchScreen_CLK_port, pa_touchScreen_CLK_pin, (GPIO_PinState)state);
}

#endif

#endif