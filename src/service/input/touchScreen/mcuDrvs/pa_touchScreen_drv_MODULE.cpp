#include "../pa_touchScreen.h"

#ifdef INPUT_USE_TOUCHSCREEN

/****************************************************
 * driver 层代码
 * ***************************************************/

#ifdef MODULE

void pa_touchScreen::Hardware_Init()
{
}

uint8_t pa_touchScreen::Hardware_ReadIRQ()
{
}

void pa_touchScreen::Hardware_SetCS(uint8_t state)
{
}

void pa_touchScreen::Hardware_setMOSI(uint8_t state)
{
}

uint8_t pa_touchScreen::Hardware_ReadMISO()
{
}

void pa_touchScreen::Hardware_setCLK(uint8_t state)
{
}

#endif

#endif