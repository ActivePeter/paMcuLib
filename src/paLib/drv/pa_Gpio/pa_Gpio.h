#ifndef __PA_GPIO_H__
#define __PA_GPIO_H__
#include "paLib/drv/pa_BaseDrv/pa_BaseDrv.h"

typedef enum
{
    GpioMode_Input_PullDown,
    GpioMode_Input_PullUp,
    GpioMode_Input_Float,
    GpioMode_OutPut_OD, //开漏输出
    GpioMode_Output_PP  //推腕输出
} GpioMode;
typedef enum
{
    GpioSpeed_Low,
    GpioSpeed_Medium,
    GpioSpeed_Fast,
    GpioSpeed_VeryFast,
    // GpioMode_Output_PP
} GpioSpeed;
// #include "pa_Gpio_drv.h"
#if mcu_stm32_h7
#include "mcuDrvs/Gpio_stm32_hal.h"
#endif
#endif // __PA_GPIO_H__