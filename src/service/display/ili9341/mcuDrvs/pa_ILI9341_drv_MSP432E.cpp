
#include "../pa_ILI9341.h"
#ifdef DISPLAY_USE_ILI9341

/****************************************************
 * driver 层代码
 * ***************************************************/

#ifdef MSP432E

void pa_ILI9341::setCS(uint8_t state)
{
    GPIO_write(ILI9341_CS, state > 0);
}
 
void pa_ILI9341::setDC(uint8_t state)
{
    GPIO_write(ILI9341_DC, state > 0);
}

void pa_ILI9341::setRST(uint8_t state)
{
    GPIO_write(ILI9341_RST, state > 0);
}

#endif // MSP432P

#endif