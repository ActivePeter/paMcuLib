#ifndef __GPIO_H__
#define __GPIO_H__

#include "paLib/drv/pa_BaseDrv/pa_BaseDrv.h"

typedef enum
{
    GpioMode_Input_PullDown,
    GpioMode_Input_PullUp,
    GpioMode_Input_Float,
    GpioMode_OutPut_OD,
    GpioMode_Output_PP,
} GpioMode;

#if mcu_stm32_h7
#include "mcuDrv/Gpio_stm32_h7.h"
#endif

#endif // __GPIO_H__