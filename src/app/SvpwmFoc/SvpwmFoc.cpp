#include "SvpwmFoc.h"

SvpwmFoc::SvpwmFoc()
{
}

//循环调用。用于更新pwm状态
void SvpwmFoc::controlTick()
{
    float angleInPhase = fmodf(curAngle, PI_3);
    int phase = curAngle / PI_3;

    float T1 = sinf(angleInPhase);
    float T2 = sinf(PI_3 - angleInPhase);
    // float T3 = 1 - T1 - T2;
    float T3 = 0; //零向量维持时间，可以调整。对整体不会产生影响。无非是全开通和全关断的区别
    float PWMA, PWMB, PWMC;

    switch (phase)
    {
    case 0:
        PWMA = T3;
        PWMB = T3 + T2;
        PWMC = T3 + T1 + T2;
        break;
    case 1:
        PWMA = T3 + T1;
        PWMB = T3;
        PWMC = T3 + T2 + T1;
        break;
    case 2:
        PWMA = T3 + T1 + T2;
        PWMB = T3;
        PWMC = T3 + T2;
        break;
    case 3:
        PWMA = T3 + T1 + T2;                       
        PWMB = T3 + T1;
        PWMC = T3;
        break;
    case 4:
        PWMA = T3 + T2;
        PWMB = T3 + T1 + T2;
        PWMC = T3;
        break;
    case 5:
        PWMA = T3;
        PWMB = T3 + T1 + T2;
        PWMC = T3 + T1;
        break;
    default:
        PWMA = PWMB = PWMC = 0;
    }
    updateMotor(PWMA, PWMB, PWMC);
}

void SvpwmFoc::openLoopPlusAngleTest()
{

    // curAngle+=PI/
}                             

float SvpwmFoc::getCurEularAngle()
{
    return curAngle / PI * 180;
}

void SvpwmFoc::updateMotor(float a, float b, float c)
{

}
