#ifndef __ROBOTARMAPP_H__
#define __ROBOTARMAPP_H__

class RobotArmApp
{
public:
	RobotArmApp();
	static RobotArmApp instance;
    void onTimerTick();
private:
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
    int maxDeltaTickCount=0;
    //当前tick计数
    int currentTick=0;
    void prepareNextMove();
};

#endif // __ROBOTARMAPP_H__