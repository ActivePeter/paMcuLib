extern "C"
{
#include "../pa_CommonDrv.h"
#include "stdarg.h"
#include <stdio.h>
#include <stdlib.h>
}

#ifdef STM32_H7
void pa_CommonInit()
{
}
void pa_delayMs(unsigned int ms)
{
     osDelay(ms);
//    HAL_Delay(ms);
}

void pa_delayUs(unsigned int us)
{

}

uint64_t pa_millis()
{
    
}

void pa_printf(const char *format,...) //需要修改
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
    // UARTwrite(temp, len);
    // len = write((uint8_t*)temp, len);
    if(temp != loc_buf){
        free(temp);
    }
    // return len;
}

#endif
