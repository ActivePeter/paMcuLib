extern "C"
{
// #include "../pa_CommonDrv.h"
#include "stdarg.h"
#include <stdio.h>
#include <stdlib.h>
}

#ifdef ESP32
// #include <ti/devices/msp432p4xx/driverlib/driverlib.h>
void pa_CommonInit()
{
    // Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);

    // Timer32_disableInterrupt(TIMER32_0_BASE);
}
void pa_delayMs(unsigned int ms)
{
// delayms(ms);
#ifdef hasRTOS

#else
    delay(ms);
    // pa_delayUs(ms*1000);
#endif
}

void pa_delayUs(unsigned int us)
{
    // // STM_DelayUs(STM0, us);
    // Timer32_haltTimer (TIMER32_0_BASE);

    // Timer32_setCount  (TIMER32_0_BASE, 3 * us);

    // Timer32_startTimer(TIMER32_0_BASE, true);

    // while (Timer32_getValue(TIMER32_0_BASE) > 0);
}

void pa_millis()
{
}

#endif