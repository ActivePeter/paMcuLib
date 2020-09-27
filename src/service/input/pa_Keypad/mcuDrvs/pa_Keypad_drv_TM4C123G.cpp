#include "pa_Defines.h"

#ifdef INPUT_USE_KEYPAD

#include "../pa_Keypad.h"

/****************************************************
 * driver 层代码
 * ***************************************************/

#ifdef TM4C123G
uint32_t pa_Keypad_getInputPortOrPinByIndex(int index, GpioPortOrPin gpioPortOrPin)
{
    switch (index)
    {
    case 0:
        switch (gpioPortOrPin)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTA_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_7;
        }
    case 1:
        switch (gpioPortOrPin)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTA_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_6;
        }
    case 2:
        switch (gpioPortOrPin)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTA_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_6;
        }
    case 3:
        switch (gpioPortOrPin)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTB_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_4;
        }
    }
    return 0;
}
uint32_t pa_Keypad_getOutputPortOrPinByIndex(int index, GpioPortOrPin gpioPortOrPin)
{
    switch (index)
    {
    case 0:
        switch (gpioPortOrPin)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTE_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_5;
        }
    case 1:
        switch (gpioPortOrPin)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTE_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_4;
        }
    case 2:
        switch (gpioPortOrPin)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTB_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_1;
        }
    case 3:
        switch (gpioPortOrPin)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTB_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_0;
        }
    }
    return 0;
}
//初始化引脚
void pa_Keypad::hardwareInit()
{
    initInput();
    initOutput();
}

void pa_Keypad::initInput()
{
    for (int i = 0; i < Keypad_Input_Cnt; i++)
    {
        uint32_t pin = pa_Keypad_getInputPortOrPinByIndex(i, GpioPortOrPin_Pin);
        uint32_t port = pa_Keypad_getInputPortOrPinByIndex(i, GpioPortOrPin_Port);
        GPIOPinTypeGPIOInput(port, pin);
        // GPIOPUR
        //GPIO_O_PUR = 0x11;
        if (this->isPullup)
            HWREG(port + GPIO_O_PUR) = (HWREG(port + GPIO_O_PUR) | pin);
    }
}
void pa_Keypad::initOutput()
{
    for (int i = 0; i < Keypad_Input_Cnt; i++)
    {
        uint32_t pin = pa_Keypad_getOutputPortOrPinByIndex(i, GpioPortOrPin_Pin);
        uint32_t port = pa_Keypad_getOutputPortOrPinByIndex(i, GpioPortOrPin_Port);
        GPIOPinTypeGPIOOutput(port, pin);
    }
}

//设置行
void pa_Keypad::setOutput(unsigned char index, unsigned char state)
{
    uint32_t pin = pa_Keypad_getOutputPortOrPinByIndex(index, GpioPortOrPin_Pin);
    uint32_t port = pa_Keypad_getOutputPortOrPinByIndex(index, GpioPortOrPin_Port);
    GPIOPinWrite(port, pin, pin * state);
}
//设置列
unsigned char pa_Keypad::readInput(unsigned char index)
{
    uint32_t pin = pa_Keypad_getInputPortOrPinByIndex(index, GpioPortOrPin_Pin);
    uint32_t port = pa_Keypad_getInputPortOrPinByIndex(index, GpioPortOrPin_Port);
    return GPIOPinRead(port, pin) > 0;
}

#endif // MSP432P
#endif