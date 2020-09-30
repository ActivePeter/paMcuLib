#include "../RobotStepper.h"


#ifdef MSP432E
//引脚映射函数。没用数组是为了省内存
int RobotStepper_getStepPortOrPinById(GpioPortOrPin portOrPin,char id){

}
int RobotStepper_getDirPortOrPinById(GpioPortOrPin portOrPin,char id){

}
void RobotStepper::setStepPin(char state) 
{

}
void RobotStepper::setDirPin(char state) 
{

}
#endif