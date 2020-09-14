#include "RobotStepper.h"


#ifdef MSP432P
//引脚映射函数。没用数组是为了省内存
int RobotStepper_getStepPortOrPinById(GpioPortOrPin portOrPin,char id){
    switch (id)
    {
    case 1:
        switch (portOrPin)
        {
        case GpioPortOrPin::GpioPortOrPin_Pin:
            return ;
        case GpioPortOrPin::GpioPortOrPin_Port:
            return ;
        }
    case 2:
        switch (portOrPin)
        {
        case GpioPortOrPin::GpioPortOrPin_Pin:
            return ;
        case GpioPortOrPin::GpioPortOrPin_Port:
            return ;
        }
    case 3:
        switch (portOrPin)
        {
        case GpioPortOrPin::GpioPortOrPin_Pin:
            return ;
        case GpioPortOrPin::GpioPortOrPin_Port:
            return ;
        }
    }
}
int RobotStepper_getDirPortOrPinById(GpioPortOrPin portOrPin,char id){
    switch (id)
    {
    case 1:
        switch (portOrPin)
        {
        case GpioPortOrPin::GpioPortOrPin_Pin:
            return ;
        case GpioPortOrPin::GpioPortOrPin_Port:
            return ;
        }
    case 2:
        switch (portOrPin)
        {
        case GpioPortOrPin::GpioPortOrPin_Pin:
            return ;
        case GpioPortOrPin::GpioPortOrPin_Port:
            return ;
        }
    case 3:
        switch (portOrPin)
        {
        case GpioPortOrPin::GpioPortOrPin_Pin:
            return ;
        case GpioPortOrPin::GpioPortOrPin_Port:
            return ;
        }
    }
}
void RobotStepper::setStepPin(char state) 
{
    int port=RobotStepper_getStepPortOrPinById(GpioPortOrPin::GpioPortOrPin_Port,id);
    int pin=RobotStepper_getStepPortOrPinById(GpioPortOrPin::GpioPortOrPin_Pin,id);
    if (state) {
        MAP_GPIO_setOutputHighOnPin(port, pin);
    }
    else {
        MAP_GPIO_setOutputLowOnPin(port, pin);
    }
}
void RobotStepper::setDirPin(char state) 
{
    int port=RobotStepper_getDirPortOrPinById(GpioPortOrPin::GpioPortOrPin_Port,id);
    int pin=RobotStepper_getDirPortOrPinById(GpioPortOrPin::GpioPortOrPin_Pin,id);
    if (state) {
        stepDirection=Direction::Direction_Increase;
        MAP_GPIO_setOutputHighOnPin(port, pin);
    }
    else {
        stepDirection=Direction::Direction_Decrease;
        MAP_GPIO_setOutputLowOnPin(port, pin);
    }
}
#endif