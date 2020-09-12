extern "C"
{
#include "../pa_CommonDrv.h"
#include "stdarg.h"
#include <stdio.h>
#include <stdlib.h>
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
    } //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTStdioConfig(0, 115200, 16000000);
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
void pa_printf(const char *format,...) 
{
    char loc_buf[64];
    char * temp = loc_buf;
    va_list arg;
    va_list copy;
    va_start(arg, format);
    va_copy(copy, arg);
    int len = vsnprintf(temp, sizeof(loc_buf), format, copy);
    va_end(copy);
    if(len < 0) {
        va_end(arg);
        return;
    };
    if(len >= sizeof(loc_buf)){
        temp = (char*) malloc(len+1);
        if(temp == NULL) {
            va_end(arg);
            return;
        }
        len = vsnprintf(temp, len+1, format, arg);
    }
    va_end(arg);
    UARTwrite(temp, len);
    // len = write((uint8_t*)temp, len);
    if(temp != loc_buf){
        free(temp);
    }
    // return len;
}

////////////////////////////////////////////////////////////////////////////
uint32_t getSyscylOfGpioPort(uint32_t port)
{
    switch (port)
    {
    case GPIO_PORTA_BASE:
        return SYSCTL_PERIPH_GPIOA;
    case GPIO_PORTB_BASE:
        return SYSCTL_PERIPH_GPIOB;
    case GPIO_PORTC_BASE:
        return SYSCTL_PERIPH_GPIOC;
    case GPIO_PORTD_BASE:
        return SYSCTL_PERIPH_GPIOD;
    case GPIO_PORTE_BASE:
        return SYSCTL_PERIPH_GPIOE;
    case GPIO_PORTF_BASE:
        return SYSCTL_PERIPH_GPIOF;
    }
}
#endif