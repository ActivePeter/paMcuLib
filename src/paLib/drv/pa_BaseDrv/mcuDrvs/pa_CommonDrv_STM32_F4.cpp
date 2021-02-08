extern "C"
{
#include "../pa_BaseDrv.h"
#include "stdarg.h"
#include <stdio.h>
#include <stdlib.h>
}

#ifdef STM32_F4
// #include <ti/devices/msp432p4xx/driverlib/driverlib.h>
void pa_CommonInit()
{
    // Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);

    // Timer32_disableInterrupt(TIMER32_0_BASE);
}
void pa_delayMs(unsigned int ms)
{
    osDelay(ms);
    // // delayms(ms);
    // #ifdef hasRTOS

    // #else
    //     HAL_Delay(ms);
    // #endif
}

void pa_delayUs(unsigned int us)
{
}
uint64_t pa_milliCnt = 0;
uint64_t pa_millis()
{
    return pa_milliCnt;
}

#endif