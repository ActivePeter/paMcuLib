#ifndef __SVPWMFOC_H__
#define __SVPWMFOC_H__
#include "pa_CommonLib/src/drv/pa_CommonDrv/pa_CommonDrv.h"
#include "pa_CommonLib/src/util/pa_Math/pa_Math.h"

class SvpwmFoc
{
public:
    SvpwmFoc();
    void init(char pwmId_A, char pwmId_B, char pwmId_C);
    void controlTick();
    void plusAngleTest(float callRate_UsPerTime, float msPerRound);
    float getCurEularAngle();

private:
    char pwmIds[3];
    float curEularAngle;
    void updateMotor(float a, float b, float c);
};
#endif // __SVPWMFOC_H__
