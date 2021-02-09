
#include "Gpio_stm32_hal.h"
#if mcu_stm32_h7
void Gpio_setMode(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GpioMode mode, GpioSpeed speed)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // GPIO_InitStruct.Pin = stepperMs1_Pin | stepperMs2_Pin | stepperMs3_Pin;
    switch (mode)
    {
    case GpioMode_Input_Float:
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        break;
    case GpioMode_Input_PullDown:
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        break;
    case GpioMode_Input_PullUp:
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        break;
    case GpioMode_OutPut_OD:
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        break;
    case GpioMode_Output_PP:
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        break;
    default:

        return;
    }
    switch (speed)
    {
    case GpioSpeed_Low:
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        break;
    case GpioSpeed_Medium:
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
        break;
    case GpioSpeed_Fast:
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        break;
    case GpioSpeed_VeryFast:
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        break;
    default:
        break;
    }

    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
void Gpio_write(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t state)
{
    if (state != 0)
    {
        GPIOx->BSRR = GPIO_Pin;
    }
    else
    {
        GPIOx->BSRR = (uint32_t)GPIO_Pin << 16;
    }
}
char Gpio_read(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    /* Check the parameters */
    assert_param(IS_GPIO_PIN(GPIO_Pin));

    if ((GPIOx->IDR & GPIO_Pin) != 0x00U)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
#endif
