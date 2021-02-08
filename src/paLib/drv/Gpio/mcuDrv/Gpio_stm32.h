#ifndef __GPIO_STM32_H__
#define __GPIO_STM32_H__

#include "paLib/drv/pa_BaseDrv/nativeInterface.h"

#define WriteGpio(gpio, pin, state) HAL_GPIO_WritePin(gpio, pin, state)
#define ReadGpio(gpio, pin) HAL_GPIO_ReadPin(gpio, pin)
#endif // __GPIO_STM32_H__