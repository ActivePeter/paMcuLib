#ifndef __TK032RB422_H__
#define __TK032RB422_H__
#include "pa_CommonLib/src/drv/pa_CommonDrv/pa_CommonDrv.h"

#ifdef DISPLAY_USE_Tk032rb422
//一个3。2寸 480*800 带电容触摸 的屏幕 淘宝搜索tiky
class Tk032rb422
{
public:
    void LCD_init(void);

private:
    //逻辑部分////////////////////////
    void SPI_writeByte(unsigned char byte);
    void SPI_writeComm(u16 CMD); //3线8bit 串行接口
    void SPI_writeData(u16 tem_data);
    void LCD_setup(void);
    void LCD_delay(int ms);
    void initHardWare(void);
    void DrawPixel(u16 x, u16 y, int Color);
    void LCD_Reset();
    //硬件层部分////////////////////////
    void SPI_DCLK(int state);
    void SPI_SDA(int state);
    void SPI_CS(int state);
    void LCD_setReset(int state);
};
#endif
#endif // __TK032RB422_H__