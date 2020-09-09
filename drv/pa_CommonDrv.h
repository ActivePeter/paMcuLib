#ifndef __pa_CommonDrv_h__
#define __pa_CommonDrv_h__
//hasRTOS
// #define hasRTOS
/////////////////////////////////////////////////////
// #define MSP432P//select Board(选择板子)
// #define ESP32
/////////////////////////////////////////////////////////////////////
// includes //////////////////
#ifdef MSP432P
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#endif
#ifdef ESP32
#include "esp32-hal.h"
#endif
#ifdef TM4C123G
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#endif
extern "C"
{
#include "pa_HardwareSPI/pa_HardwareSPI.h"
#include "pa_HardwareIIC/pa_HardwareIIC.h"
}
////////////////////////

//common Funcs（通用函数）/////////////////////////////////////////////
    void pa_CommonInit();
    
    void pa_delayMs(unsigned int ms);

    void pa_delayUs(unsigned int us);

    void pa_millis();

/////////////////////////////////////////////////////////
typedef enum
{
    Protocal_SPI=1,
    Protocal_IIC
}Protocal;

typedef enum {
    GpioInputMode_pullup=1,
    GpioInputMode_pulldown,
    GpioInputMode_hang,
}GpioInputMode;

typedef enum {
    GpioPortOrPin_Port=1,
    GpioPortOrPin_Pin,
}GpioPortOrPin;

typedef enum {
    Direction_Increase=1,
    Direction_Decrease,
}Direction;

#endif