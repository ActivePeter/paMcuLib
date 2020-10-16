#include "../pa_CommonDrv.h"
extern "C"
{
#include "stdarg.h"
#include <stdio.h>
#include <stdlib.h>
}

#ifdef MSP432E

void (*callback_1ms)(void);
void timerCallback(Timer_Handle myHandle)
{
    callback_1ms();
}
void pa_set1MsCallback(void (*callback)(void))
{
    Timer_init();
    callback_1ms = callback;
    Timer_Handle handle;
    Timer_Params params;
    Timer_Params_init(&params);
    params.periodUnits = Timer_PERIOD_HZ;
    params.period = 1000;
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timerCallback;
    handle = Timer_open(CONFIG_TIMER_0, &params);
    if (handle == NULL)
    {
        // Timer_open() failed
        while (1)
            ;
    }
    int32_t status = Timer_start(handle);
    if (status == Timer_STATUS_ERROR)
    {
        //Timer_start() failed
        while (1)
            ;
    }
}
void pa_CommonInit()
{
}
void pa_delayMs(unsigned int ms)
{
    unsigned int s = ms / 1000;
    unsigned int us = (ms % 1000) * 1000;

    if (s > 0)
    {
        sleep(s);
    }
    usleep(us);
}

void pa_delayUs(unsigned int us)
{
    usleep(us);
}

uint64_t pa_millis()
{
}

void pa_printf(const char *format, ...)
{
    // char loc_buf[64];
    // char * temp = loc_buf;
    // va_list arg;
    // va_list copy;
    // va_start(arg, format);
    // va_copy(copy, arg);
    // int len = vsnprintf(temp, sizeof(loc_buf), format, copy);
    // va_end(copy);
    // if(len < 0) {
    //     va_end(arg);
    //     return;
    // };
    // if(len >= sizeof(loc_buf)){
    //     temp = (char*) malloc(len+1);
    //     if(temp == NULL) {
    //         va_end(arg);
    //         return;
    //     }
    //     len = vsnprintf(temp, len+1, format, arg);
    // }
    // va_end(arg);
    // // UARTwrite(temp, len);
    // // len = write((uint8_t*)temp, len);
    // if(temp != loc_buf){
    //     free(temp);
    // }
    // return len;
}

#endif