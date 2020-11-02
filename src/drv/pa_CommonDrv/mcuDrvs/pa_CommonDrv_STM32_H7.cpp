
#include "../pa_CommonDrv.h"
extern "C"
{
#include "stdarg.h"
#include <stdio.h>
#include <stdlib.h>
}

#ifdef STM32_H7
void pa_CommonInit()
{
}
extern TIM_HandleTypeDef htim2;
void pa_set1MsCallback(void (*callback)(void))
{
    HAL_TIM_Base_Start_IT(&htim2);
    // Timer_init();
    // callback_1ms = callback;
    // Timer_Handle handle;
    // Timer_Params params;
    // Timer_Params_init(&params);
    // params.periodUnits = Timer_PERIOD_HZ;
    // params.period = 1000;
    // params.timerMode = Timer_CONTINUOUS_CALLBACK;
    // params.timerCallback = timerCallback;
    // handle = Timer_open(CONFIG_TIMER_0, &params);
    // if (handle == NULL)
    // {
    //     // Timer_open() failed
    //     while (1)
    //         ;
    // }
    // int32_t status = Timer_start(handle);
    // if (status == Timer_STATUS_ERROR)
    // {
    //     //Timer_start() failed
    //     while (1)
    //         ;
    // }
}
void pa_delayMs(unsigned int ms)
{
    osDelay(ms);
    //    HAL_Delay(ms);
}

void pa_delayUs(unsigned int us)
{
    osDelay(us);
}

uint64_t pa_millis()
{
}

void pa_printf(const char *format, ...) //需要修改内存管理
{
    char loc_buf[64];
    char *temp = loc_buf;
    va_list arg;
    va_list copy;
    va_start(arg, format);
    va_copy(copy, arg);
    int len = vsnprintf(temp, sizeof(loc_buf), format, copy);
    va_end(copy);
    if (len < 0)
    {
        va_end(arg);
        return;
    };
    if (len >= sizeof(loc_buf))
    {
        temp = (char *)malloc(len + 1);
        if (temp == NULL)
        {
            va_end(arg);
            return;
        }
        len = vsnprintf(temp, len + 1, format, arg);
    }
    va_end(arg);
    // UARTwrite(temp, len);
    // len = write((uint8_t*)temp, len);
    if (temp != loc_buf)
    {
        free(temp);
    }
    // return len;
}

#endif
