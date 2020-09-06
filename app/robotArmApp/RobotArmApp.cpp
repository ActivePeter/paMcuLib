#include "RobotArmApp.h"

RobotArmApp RobotArmApp::instance = RobotArmApp();
RobotArmApp::RobotArmApp() {}

void RobotArmApp::onTimerTick() 
{
    doStepperEvent(robotStepper1);
    doStepperEvent(robotStepper1);
    doStepperEvent(robotStepper1);

    if(currentTick==tickCountInOneMove){
        prepareNextMove();
    }
    currentTick++;
}

void RobotArmApp::prepareNextMove() 
{
    //tick计数清0
    currentTick=0;
    //先计算下一次步进完成所需要的步进数
    this->tickCountInOneMove=1;

}

void RobotArmApp::doStepperEvent(RobotStepper & stepper) 
{
    if(stepper.curStepInOneMove!=stepper.totalStepInOneMove){
        //当前tick帧是否为脉冲上升帧
        if((currentTick-1)*currentStep1/totalStep1){

        }
    }    
}

