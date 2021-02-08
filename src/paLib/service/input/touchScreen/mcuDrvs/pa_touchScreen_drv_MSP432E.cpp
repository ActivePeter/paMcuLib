#include "../pa_touchScreen.h"

#ifdef INPUT_USE_TOUCHSCREEN

/****************************************************
 * driver 层代码
 * ***************************************************/

#ifdef MSP432E

void pa_touchScreen::Hardware_Init()
{
}

uint8_t pa_touchScreen::Hardware_ReadIRQ()
{
    GPIO_read(TouchScreen_IRQ);
}

void pa_touchScreen::Hardware_SetCS(uint8_t state)
{
    GPIO_write(TouchScreen_CS, state > 0);
}

void pa_touchScreen::Hardware_setMOSI(uint8_t state)
{
    GPIO_write(TouchScreen_MOSI, state > 0);
}

uint8_t pa_touchScreen::Hardware_ReadMISO()
{
    GPIO_read(TouchScreen_MISO);
}

void pa_touchScreen::Hardware_setCLK(uint8_t state)
{
    GPIO_write(TouchScreen_CLK, state > 0);
}

#endif

#endif