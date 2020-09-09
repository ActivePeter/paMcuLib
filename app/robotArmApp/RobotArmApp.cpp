#include "RobotArmApp.h"

RobotArmApp RobotArmApp::instance = RobotArmApp();
RobotArmApp::RobotArmApp() {}

void RobotArmApp::onTimerTick() 
{
    doStepperEvent(robotStepper1);
    doStepperEvent(robotStepper2);
    doStepperEvent(robotStepper3);

    if(currentTick==tickCountInOneMove){
        prepareNextMove();
    }
    currentTick++;
}

void RobotArmApp::prepareNextMove() 
{
    //tick计数清0
    currentTick=0;
    //先赋值下一次步进完成所需要的时间 tickCountInOneMove
    this->tickCountInOneMove=1;
    //步进值计数复位  stepper.curStepInOneMove;
    robotStepper1.curStepInOneMove=0;
    robotStepper2.curStepInOneMove=0;
    robotStepper3.curStepInOneMove=0;
    //然后计算三个步进所需要的步进数 stepper.totalStepInOneMove
    calcAndSetStep(robotStepper1);
    calcAndSetStep(robotStepper2);
    calcAndSetStep(robotStepper3);

    //设置三个步进的步进方向 

}

void RobotArmApp::doStepperEvent(RobotStepper & stepper) 
{
    if(stepper.curStepInOneMove!=stepper.totalStepInOneMove){
        //当前tick帧是否为脉冲上升帧
        if(currentTick==(tickCountInOneMove-1)*stepper.curStepInOneMove/stepper.totalStepInOneMove){
            stepper.setStepPin(1);
            stepper.curStepInOneMove++;
        }else{
            stepper.setStepPin(0);
        }
    }    
}

void RobotArmApp::calcAndSetStep(RobotStepper & stepper) 
{
    switch (stepper.getId())
    {
    case 1:
    
        break;
    }
    //根据stepper的id来计算对应的步进值
    int step;
    robotStepper1.setDirPin(step>0);
    robotStepper1.totalStepInOneMove=step>0?step:-step;
}

