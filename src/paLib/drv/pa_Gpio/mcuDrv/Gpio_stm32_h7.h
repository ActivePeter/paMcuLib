#ifndef __GPIO_STM32_H7_H__
#define __GPIO_STM32_H7_H__

#include "paLib/drv/pa_BaseDrv/pa_BaseDrv.h"
void Gpio_write(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t state);
char Gpio_read(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif // __GPIO_STM32_H7_H__