#ifndef __ROBOTARMAPP_H__
#define __ROBOTARMAPP_H__
#include "RobotStepper/RobotStepper.h"
class RobotArmApp
{
public:
	RobotArmApp();
	static RobotArmApp instance;
    void onTimerTick();
    
private:
    RobotStepper robotStepper1;
    RobotStepper robotStepper2;
    RobotStepper robotStepper3;

    //电机1当前步进数
    int step1=0;
    //电机2当前步进数
    int step2=0;
    //电机3当前步进数
    int step3=0;

    //电机1目标步进数
    int targetStep1=0;
    //电机1目标步进数
    int targetStep2=0;
    //电机1目标步进数
    int targetStep3=0;

    int currentStep1=0;

    //电机1 位移所需总步进数
    int totalStep1=0;
    //电机2 位移所需总步进数
    int totalStep2=0;
    //电机3 位移所需总步进数
    int totalStep3=0;

    //决定了完成总的步进需要花费的tick
    int tickCountInOneMove=0;
    //当前tick计数
    int currentTick=0;
    void prepareNextMove();
    void doStepperEvent(RobotStepper & stepper);
    void calcAndSetStep(RobotStepper & stepper);
};

#endif // __ROBOTARMAPP_H__