#include "../pa_CommonDrv.h"
extern "C"
{
#include "stdarg.h"
#include <stdio.h>
#include <stdlib.h>
}

#ifdef MSP432E

static void (*ptr_CallBack_1ms)(void);
static void (*ptr_CallBack_100us)(void);
void timer100usCallback(Timer_Handle myHandle)
{
    static char cnt = 0;
    cnt++;
    ptr_CallBack_100us();
    if (cnt == 10)
    {
        ptr_CallBack_1ms();
        cnt = 0;
    }
}
//设置1ms的回调函数
void pa_setTimerCallback(void (*CallBack_100us)(void), void (*CallBack_1ms)(void))
{
    ptr_CallBack_1ms = CallBack_1ms;
    ptr_CallBack_100us = CallBack_100us;
    Timer_init();
    Timer_Handle handle;
    Timer_Params params;
    Timer_Params_init(&params);
    params.periodUnits = Timer_PERIOD_US;
    params.period = 100; //100us
    params.timerMode = Timer_CONTINUOUS_CALLBACK;
    params.timerCallback = timer100usCallback;
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

void pa_Debug(const char *data)
{
    // uint8_t *cntPtr = (uint8_t *)data;
    // int len = 0;
    // while (*cntPtr)
    // {
    //     len++;
    //     cntPtr++;
    // }
    // printf("data");
    // while (CDC_Transmit_FS((uint8_t *)data, len))
    //     ;
}

#endif
