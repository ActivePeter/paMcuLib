#include "pa_Motor.h"
extern "C"
{
#include "math.h"
}
pa_Motor::pa_Motor()
{
}

void pa_Motor::setSpeed(int in, char dasi, int speed)
{
    if (!dasi)
    {
        GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5, 0);
        MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
                             ((int)(MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 2) * speed / 10 - in * 70 * speed / 9));
        MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,
                             (int)(MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 2) * speed / 10 + in * 70 * speed / 9);
    }
    else
    {
        int value,value2;
        switch (dasi)
        {
        case 1:
            value = 20000;
            value2= 24000;
            break;
        case 2:
            value = 12000;
            value2= 20000;
            break;
        case 3:
            
            value = 5000;
            value2= 12000;
            break;
        case 4:
            
            value = 2000;
            value2= 7000;
            break;
        case 5:
            
            value = 1000;
            value2= 5000;
            break;
        }
        if (in < 0)
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, 0);
            MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
                                 value2);
            MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,
                                 value);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5);
            GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, 0);
            MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
                                 value);
            MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,
                                 24000);
        }
        // pa_delayMs(1000);
    }

    // // char dir = speed > 0;

    // // speed=fabs(speed);
    // switch (motor)
    // {
    // case Motor_L:
    //     MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
    //                      MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);
    // MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,
    //                      MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);
    //     // GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4 * dir);
    //     break;

    // case Motor_R:

    //     // GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5 * dir);
    //     break;
    // }
}
void pa_Motor::stop()
{

    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
                         0);
    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,
                         0);
    // // char dir = speed > 0;

    // // speed=fabs(speed);
    // switch (motor)
    // {
    // case Motor_L:
    //     MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0,
    //                      MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);
    // MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1,
    //                      MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);
    //     // GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_PIN_4 * dir);
    //     break;

    // case Motor_R:

    //     // GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5, GPIO_PIN_5 * dir);
    //     break;
    // }
}
void pa_Motor::initHardware()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)) //|SYSCTL_PERIPH_GPIOB|SYSCTL_PERIPH_GPIOA|SYSCTL_PERIPH_GPIOC|SYSCTL_PERIPH_GPIOD|SYSCTL_PERIPH_GPIOE))
    {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_5);

    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5, 0);
    //////////////////////////////
    initLinerDetect();
}
void LinerDetectInitGPIO(uint32_t port, uint32_t pin)
{
}
#define IRLight_Port GPIO_PORTB_BASE
#define IRLight_Pin GPIO_PIN_1
uint32_t LinerDetect_GetPortOrPin(GpioPortOrPin pop, char index);

void pa_Motor::initLinerDetect()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(IRLight_Port, IRLight_Pin);
    GPIOPinWrite(IRLight_Port, IRLight_Pin, 0);

    for (int i = 0; i < 8; i++)
    {
        uint32_t port = LinerDetect_GetPortOrPin(GpioPortOrPin_Port, i);
        uint8_t pin = LinerDetect_GetPortOrPin(GpioPortOrPin_Pin, i);
        GPIOPinTypeGPIOInput(port, pin);
    }
    // GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_3);
    // GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_2);
    // GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_4);
    // GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_1);
    // GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_2);
    // GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_3);
    // GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_4);
    // GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_5);
    //     // GPIOPUR
    // HWREG(GPIO_PORTB_BASE + GPIO_O_PUR) = (HWREG(GPIO_PORTB_BASE + GPIO_O_PUR) | GPIO_PIN_3);
}

void LinerDetect_SetOutput()
{
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_3, GPIO_PIN_3);
}

unsigned char pa_Motor::readLinerDetect()
{
    unsigned char a = readLinerDetectPin(0);
    GPIOPinWrite(IRLight_Port, IRLight_Pin, IRLight_Pin);
    // pa_delayUs(10);
    // GPIODirModeSet(GPIO_PORTB_BASE, GPIO_PIN_3,GPIO_DIR_MODE_OUT);
    for (size_t i = 0; i < 8; i++)
    {
        uint32_t port = LinerDetect_GetPortOrPin(GpioPortOrPin_Port, i);
        uint8_t pin = LinerDetect_GetPortOrPin(GpioPortOrPin_Pin, i);
        GPIOPinTypeGPIOOutput(port, pin);
        GPIOPinWrite(port, pin, pin);
    }

    pa_delayUs(10);
    for (size_t i = 0; i < 8; i++)
    {
        uint32_t port = LinerDetect_GetPortOrPin(GpioPortOrPin_Port, i);
        uint8_t pin = LinerDetect_GetPortOrPin(GpioPortOrPin_Pin, i);
        // GPIOPinTypeGPIOOutput(port, pin);
        // GPIOPinWrite(port, pin, pin);
        GPIOPinTypeGPIOInput(port, pin);
    }

    // GPIODirModeSet(GPIO_PORTB_BASE, GPIO_PIN_3,GPIO_DIR_MODE_IN);
    pa_delayMs(1);

    GPIOPinWrite(IRLight_Port, IRLight_Pin, 0);
    return a;
}

unsigned char pa_Motor::readLinerDetectPin(char index)
{
    // switch (index)
    // {
    // case 0:
    //     return GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_3);
    // case 1:
    //     return GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_2);
    // case 2:
    //     return GPIOPinRead(GPIO_PORTB_BASE, GPIO_PIN_4);
    // case 3:
    //     return GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_1); /* code */
    // case 4:
    //     return GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_2);
    // case 5:
    //     return GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_3);
    // case 6:
    //     return GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_4);
    // case 7:
    //     return GPIOPinRead(GPIO_PORTE_BASE, GPIO_PIN_5);
    // }
    uint32_t port = LinerDetect_GetPortOrPin(GpioPortOrPin_Port, index);
    uint8_t pin = LinerDetect_GetPortOrPin(GpioPortOrPin_Pin, index);
    return GPIOPinRead(port, pin);
}
pa_Motor pa_Motor::instance = pa_Motor();

uint32_t LinerDetect_GetPortOrPin(GpioPortOrPin pop, char index)
{
    switch (index)
    {
    case 0:
        switch (pop)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTB_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_3;
        }
    case 1:
        switch (pop)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTB_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_2;
        }
    case 2:
        switch (pop)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTB_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_4;
        }
    case 3:
        switch (pop)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTE_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_1;
        }
    case 4:
        switch (pop)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTE_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_2;
        }
    case 5:
        switch (pop)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTE_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_3;
        }
    case 6:
        switch (pop)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTE_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_4;
        }
    case 7:
        switch (pop)
        {
        case GpioPortOrPin_Port:
            return GPIO_PORTE_BASE;
        case GpioPortOrPin_Pin:
            return GPIO_PIN_5;
        }
    }
}