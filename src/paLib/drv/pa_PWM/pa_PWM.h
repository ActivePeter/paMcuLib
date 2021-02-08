#ifndef __PA_PWMCONTROL_H__
#define __PA_PWMCONTROL_H__
extern "C"
{
#include "../pa_CommonDrv/pa_CommonDrv.h"
}
namespace pa_PWM
{
    void initPWM(char index);
    void setPWMDuty(char index, float duty);
} // namespace pa_PWM

#endif // __PA_PWMCONTROL_H__