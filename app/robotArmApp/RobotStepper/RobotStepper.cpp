#include "RobotStepper.h"

RobotStepper::RobotStepper() {}

void RobotStepper::setId(char a) 
{
    id=a;
}

char RobotStepper::getId() 
{
    return id;
}
