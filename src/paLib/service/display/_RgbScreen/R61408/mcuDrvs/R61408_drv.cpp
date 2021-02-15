#include "../R61408.h"
#if DISPLAY_USE_R61408
void R61408::initHardWare(void)
{
    SPI_DCLK(1);
    SPI_SDA(1);
    SPI_CS(1);
    LCD_setReset(1);
    SPI_CS(1);
    Gpio_setMode(R61408_SPI_DCLK, GpioMode::GpioMode_Output_PP, GpioSpeed_Medium);
    Gpio_setMode(R61408_SPI_SDA, GpioMode::GpioMode_Output_PP, GpioSpeed_Medium);
    Gpio_setMode(R61408_SPI_CS, GpioMode::GpioMode_Output_PP, GpioSpeed_Medium);
    Gpio_setMode(R61408_RST, GpioMode::GpioMode_Output_PP, GpioSpeed_Medium);
}

inline void R61408::SPI_DCLK(int state)
{
    Gpio_write(R61408_SPI_DCLK, state);
}

inline void R61408::SPI_SDA(int state)
{
    Gpio_write(R61408_SPI_SDA, state);
}

inline void R61408::SPI_CS(int state)
{
    Gpio_write(R61408_SPI_CS, state);
}

inline void R61408::LCD_setReset(int state)
{
    Gpio_write(R61408_RST, state);
}
void R61408::drawPixel(uint16_t x, uint16_t y, int Color)
{

    // LTDC_Buf[y+YSIZE_PHYS*x] = Color;
}
#endif
