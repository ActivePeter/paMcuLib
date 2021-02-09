#ifndef __PA_GPIO_TYPES_H__
#define __PA_GPIO_TYPES_H__

#include "paLib/drv/pa_BaseDrv/nativeInterface.h"

typedef enum
{
    GpioMode_Input_PullDown,
    GpioMode_Input_PullUp,
    GpioMode_Input_Float,
    GpioMode_OutPut_OD,
    GpioMode_Output_PP,
} GpioMode;

#endif // __PA_GPIO_TYPES_H__