#ifndef __PA_PWMCONTROL_H__
#define __PA_PWMCONTROL_H__

#include "../pa_BaseDrv/pa_BaseDrv.h"
#if drv_pwm
namespace pa_PWM
{
    void initPWM(char index);
    void setPWMDuty(char index, float duty);
} // namespace pa_PWM
#endif
#endif // __PA_PWMCONTROL_H__