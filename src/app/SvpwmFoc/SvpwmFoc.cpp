#include "SvpwmFoc.h"
#include "pa_CommonLib/src/drv/pa_PWM/pa_PWM.h"
SvpwmFoc::SvpwmFoc()
{
}

void SvpwmFoc::init(char pwmId_A, char pwmId_B, char pwmId_C)
{
    pwmIds[0] = pwmId_A;
    pwmIds[1] = pwmId_B;
    pwmIds[2] = pwmId_C;
}

//循环调用。用于更新pwm状态
void SvpwmFoc::controlTick()
{
    float angleInPhase = fmodf(curEularAngle, 60);
    int phase = curEularAngle / 60;

    angleInPhase = angleInPhase / 180 * PI;

    float T1 = sinf(angleInPhase);
    float T2 = sinf(PI_3 - angleInPhase);
    float T3 = 1 - T1 - T2;
    // float T3 = 0; //零向量维持时间，可以调整。对整体不会产生影响。无非是全开通和全关断的区别
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

    // switch (phase)
    // {
    // case 0:
    //     PWMA = 0;
    //     PWMB = 0;
    //     PWMC = 0.86602540378;
    //     break;
    // case 1:
    //     PWMA = 0;
    //     PWMB = 0.86602540378;
    //     PWMC = 0.86602540378;
    //     break;
    // case 2:
    //     PWMA = 0;
    //     PWMB = 0.86602540378;
    //     PWMC = 0;
    //     break;
    // case 3:
    //     PWMA = 0.86602540378;
    //     PWMB = 0.86602540378;
    //     PWMC = 0;
    //     break;
    // case 4:
    //     PWMA = 0.86602540378;
    //     PWMB = 0;
    //     PWMC = 0;
    //     break;
    // case 5:
    //     PWMA = 0.86602540378;
    //     PWMB = 0;
    //     PWMC = 0.86602540378;
    //     break;
    // default:
    //     PWMA = PWMB = PWMC = 0;
    // }
    // T1=;
    // T2=;
    // PWMA = 0;
    // PWMB = 0;
    // PWMC = 0.86602540378;
    updateMotor(PWMA, PWMB, PWMC);
}
/** 
 * @brief 测试函数.以固定频率调用，实现固定转速。
 * @param callRate_UsPerTime    调用此函数的实践间隔us
 * @param msPerRound    每圈几毫秒        
 */
void SvpwmFoc::plusAngleTest(float callRate_UsPerTime, float msPerRound)
{
    // curEularAngle = 15;
    float dAngle = 2 * 360 / (msPerRound * 1000 / callRate_UsPerTime);
    curEularAngle += dAngle;
    if (curEularAngle > 360)
    {
        curEularAngle -= 360;
    }
}

float SvpwmFoc::getCurEularAngle()
{
    return curEularAngle;
}

void SvpwmFoc::updateMotor(float a, float b, float c)
{
    pa_PWM::setPWMDuty(pwmIds[0], a);
    pa_PWM::setPWMDuty(pwmIds[1], b);
    pa_PWM::setPWMDuty(pwmIds[2], c);
}
