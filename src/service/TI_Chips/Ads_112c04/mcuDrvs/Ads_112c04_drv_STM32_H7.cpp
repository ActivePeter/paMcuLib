#include "pa_Defines.h"

#include "../Ads_112c04.h"

#ifdef STM32_H7
uint32_t Ads_112c04_getPinOrPortByAdd(GpioPortOrPin pop, char add)
{
    switch (add)
    {
    case 64:
        switch (pop)
        {
        case GpioPortOrPin::GpioPortOrPin_Port:
            return (uint32_t)GPIOD;
        case GpioPortOrPin::GpioPortOrPin_Pin:
            return GPIO_PIN_11;
        }
    }
    return 0;
}
void Ads_112c04::initHardware()
{
}

char Ads_112c04::getDrdyState()
{
    GPIO_TypeDef *port = (GPIO_TypeDef *)Ads_112c04_getPinOrPortByAdd(GpioPortOrPin::GpioPortOrPin_Port, this->I2C_ADDRESS);
    uint16_t pin = Ads_112c04_getPinOrPortByAdd(GpioPortOrPin::GpioPortOrPin_Pin, this->I2C_ADDRESS);
    return (char)HAL_GPIO_ReadPin(port, pin);
}
#endif