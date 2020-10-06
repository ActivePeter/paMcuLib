#include "pa_Defines.h"
#ifdef DISPLAY_USE_SSD1306

#ifndef __PA_OLED_DRV_H__
#define __PA_OLED_DRV_H__
#include "../../../drv/pa_CommonDrv/pa_CommonDrv.h"
void OLED_initSpiGpio();
void OLED_setCS(char state);
void OLED_setDC(char state);
void OLED_setRST(char state);
#endif // __PA_OLED_DRV_H__

#endif