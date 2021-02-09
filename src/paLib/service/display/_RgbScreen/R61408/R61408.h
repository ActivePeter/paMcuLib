#ifndef __R61408_H__
#define __R61408_H__
#include "paLib/drv/pa_BaseDrv/pa_BaseDrv.h"
#include "../RgbConfig.hpp"
#if DISPLAY_USE_R61408
//一个3。2寸 480*800 带电容触摸 的屏幕 淘宝搜索tiky
class R61408
{
public:
    static R61408 *getInstance();
    void LCD_init(void);

    void Graphic_ColorBox(uint16_t xStart, uint16_t yStart, uint16_t xLong, uint16_t yLong, uint32_t Color);
    RgbConfig getRGBConfig();

private:
    //逻辑部分////////////////////////
    void SPI_writeByte(unsigned char byte);
    void SPI_writeComm(uint16_t CMD); //3线8bit 串行接口
    void SPI_writeData(uint16_t tem_data);
    void LCD_setup(void);
    void LCD_delay(int ms);
    void initHardWare(void);
    void drawPixel(uint16_t x, uint16_t y, int Color);
    void LCD_Reset();

    //硬件层部分////////////////////////
    void SPI_DCLK(int state);
    void SPI_SDA(int state);
    void SPI_CS(int state);
    void LCD_setReset(int state);
};
#endif
#endif // __TK032RB422_H__