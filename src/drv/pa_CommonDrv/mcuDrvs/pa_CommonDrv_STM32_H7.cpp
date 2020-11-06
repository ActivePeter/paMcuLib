
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
static void (*ptr_CallBack_1ms)(void);
static void (*ptr_CallBack_100us)(void);

//设置1ms的回调函数
void pa_setTimerCallback(void (*CallBack_100us)(void), void (*CallBack_1ms)(void))
{
    ptr_CallBack_1ms = CallBack_1ms;
    ptr_CallBack_100us = CallBack_100us;
    HAL_TIM_Base_Start_IT(&htim2);
}
//必须设置一个100us定时器中断 并调用此函数
void pa_CallBack_100us()
{
    static char cnt = 0;
    ptr_CallBack_100us();
    cnt++;
    if (cnt == 10)
    {
        ptr_CallBack_1ms();
        cnt = 0;
    }
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
