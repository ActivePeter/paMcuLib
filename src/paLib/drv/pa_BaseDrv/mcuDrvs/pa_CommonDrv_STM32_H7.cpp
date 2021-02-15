
#include "../pa_BaseDrv.h"

#if mcu_stm32_h7
// #include ""

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
static uint64_t pa_millis_cnt = 0;
//必须设置一个100us定时器中断 并调用此函数
void pa_CallBack_100us()
{
    static char cnt = 0;
    ptr_CallBack_100us();
    cnt++;
    if (cnt == 10)
    {
        pa_millis_cnt++;
        ptr_CallBack_1ms();
        cnt = 0;
    }
}
void pa_delayMs(unsigned int ms)
{
    osDelay(ms);
    // HAL_Delay(ms);
}

void pa_delayUs(unsigned int us)
{
    osDelay(us);
}

uint64_t pa_millis()
{
    return pa_millis_cnt;
}

#endif
