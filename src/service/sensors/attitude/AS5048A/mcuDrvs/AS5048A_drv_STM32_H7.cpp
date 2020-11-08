#include "../AS5048A.h"

#ifdef STM32_H7

void AS5048A::Hardware_init()
{
}

void AS5048A::setCS(char state)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, (GPIO_PinState)state);
}

#endif