#include "pa_Defines.h"

#ifdef INPUT_USE_TOUCHSCREEN


#include "../pa_touchScreen.h"

/****************************************************
 * driver 层代码
 * ***************************************************/

#ifdef STM32_H7

#define pa_touchScreen_CS_port GPIOE
#define pa_touchScreen_CS_pin GPIO_PIN_10
#define pa_touchScreen_IRQ_port GPIOE
#define pa_touchScreen_IRQ_pin GPIO_PIN_9
void pa_touchScreen::Hardware_Init() 
{
    //32啥也不用初始化
}

uint8_t pa_touchScreen::Hardware_ReadIRQ() 
{
    return ((uint8_t)HAL_GPIO_ReadPin(pa_touchScreen_IRQ_port,pa_touchScreen_IRQ_pin));
}

void pa_touchScreen::Hardware_SetCS(uint8_t state) 
{
    HAL_GPIO_WritePin(pa_touchScreen_CS_port,pa_touchScreen_CS_pin,(GPIO_PinState)state);
}


#endif

#endif