#ifndef __PA_PWMCONTROL_H__
#define __PA_PWMCONTROL_H__
extern "C"
{
#include "../pa_CommonDrv/pa_CommonDrv.h"
}
namespace pa_PWM
{
    void initPWMs();
    void setPWMDuty(char index,float duty);
} // namespace PWM

#endif // __PA_PWMCONTROL_H__