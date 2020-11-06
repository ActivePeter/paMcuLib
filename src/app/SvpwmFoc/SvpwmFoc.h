#ifndef __SVPWMFOC_H__
#define __SVPWMFOC_H__
#include "pa_CommonLib/src/drv/pa_CommonDrv/pa_CommonDrv.h"
#include "pa_CommonLib/src/util/pa_Math/pa_Math.h"

class SvpwmFoc
{
public:
    SvpwmFoc();
    static SvpwmFoc instance;
    void controlTick();
    void openLoopPlusAngleTest();
    float getCurEularAngle();
private:
    float curAngle;
    void updateMotor(float a, float b, float c);
};
#endif // __SVPWMFOC_H__