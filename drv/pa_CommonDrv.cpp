extern "C"
{
#include "pa_CommonDrv.h"
}
#ifdef TM4C123G
#define TickPerSecond (1000)                //每秒Tick数（中断次数）
#define usPerTick (1000000 / TickPerSecond) //每个Tick对应的微秒数
void SysTickIntHandler(void);
void pa_CommonInit()
{
    {
        //设置重装值
        SysTickPeriodSet(SysCtlClockGet() / TickPerSecond);
        //注册中断
        SysTickIntRegister(SysTickIntHandler);
        //开启CPU中断处理器
        IntMasterEnable();
        //使能中断
        SysTickIntEnable();
        //开启系统定时器
        SysTickEnable();
    }
}
/**
 * 由于TickPerSecond = 1000，一秒恰被分为1000份，
 * 即1Tick周期为1ms，所以取系统时间单位为ms。
 */
static volatile uint32_t SysTime_ms; //系统时间(ms)

//【2】系统定时器中断
void SysTickIntHandler(void)
{
    SysTime_ms++;
}

//【3】获取系统时间(ms)
uint32_t GetSysTime_ms(void)
{
    return SysTime_ms;
}

//【4】获取系统时间(us)
uint32_t GetSysTime_us(void)
{
    register uint32_t ms, us;

    do
    {
        ms = SysTime_ms;
        us = ((SysTickValueGet() / SysTickPeriodGet()) * usPerTick) + ms * usPerTick;
    } while (ms != SysTime_ms);

    return us;
}
void pa_delayMs(unsigned int ms)
{
    uint32_t delayTime = GetSysTime_ms() + ms;
    while (GetSysTime_ms() < delayTime)
        ;
}
void pa_delayUs(unsigned int us)
{
    uint32_t delayTime = GetSysTime_us() + us;
    while (GetSysTime_us() < delayTime)
        ;
}
unsigned long pa_millis()
{
    return GetSysTime_ms();
}

#elif MSP432P
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
void pa_CommonInit()
{
    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT, TIMER32_PERIODIC_MODE);

    Timer32_disableInterrupt(TIMER32_0_BASE);
}
void pa_delayMs(unsigned int ms)
{
// delayms(ms);
#ifdef hasRTOS

#else
    pa_delayUs(ms * 1000);
#endif
}

void pa_delayUs(unsigned int us)
{
    // STM_DelayUs(STM0, us);
    Timer32_haltTimer(TIMER32_0_BASE);

    Timer32_setCount(TIMER32_0_BASE, 3 * us);

    Timer32_startTimer(TIMER32_0_BASE, true);

    while (Timer32_getValue(TIMER32_0_BASE) > 0)
        ;
}

void pa_millis()
{
}

#elif ESP32
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