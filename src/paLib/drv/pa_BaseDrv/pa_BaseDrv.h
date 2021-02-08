#ifndef __pa_CommonDrv_h__
#define __pa_CommonDrv_h__
#include "all_config.h"
#include "nativeInterface.h"
// #include pa_MEM_CUSTOM_INCLUDE l    .
//【必须】系统配置一个100us定时器来调用
void pa_CallBack_100us();

#include "paLib/drv/pa_HardwareSPI/pa_HardwareSPI.h"
#include "paLib/drv/pa_HardwareIIC/pa_HardwareIIC.h"

//common Funcs（通用函数）/////////////////////////////////////////////
void pa_CommonInit();
void pa_delayMs(unsigned int ms);
void pa_setTimerCallback(void (*CallBack_100us)(void), void (*CallBack_1ms)(void));
void pa_delayUs(unsigned int us);

uint64_t pa_millis();

void pa_printf(const char *format, ...);
void pa_Debug(const char *data);
void pa_Debug_len(const char *data, int len);

/////////////////////////////////////////////////////////
typedef enum
{
    protocal_SPI = 1,
    protocal_IIC
} Protocal;

typedef enum
{
    gpioInputMode_pullup = 1,
    gpioInputMode_pulldown,
    gpioInputMode_hang,
} GpioInputMode;

typedef enum
{
    direction_increase = 1,
    direction_decrease = 0,
} Direction;

#endif