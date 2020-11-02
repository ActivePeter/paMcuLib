#include "Tk032rb422.h"
#ifdef DISPLAY_USE_Tk032rb422
void Tk032rb422::SPI_writeByte(unsigned char byte)
{
    unsigned char n;

    for (n = 0; n < 8; n++)
    {
        if (byte & 0x80)
            SPI_SDA(1)
        else
            SPI_SDA(0)
        byte <<= 1;

        SPI_DCLK(0);
        SPI_DCLK(1);
    }
}

void Tk032rb422::SPI_writeComm(u16 CMD)
{
    SPI_CS(0);
    SPI_writeByte(0x70);
    SPI_writeByte(CMD);
    SPI_CS(1);
}

void Tk032rb422::SPI_writeData(u16 tem_data)
{
    SPI_CS(0);
    SPI_writeByte(0x72);
    SPI_writeByte(tem_data);
    SPI_CS(1);
}

void Tk032rb422::LCD_setup(void)
{
    SPI_CS(1);
    LCD_delay(20);
    SPI_CS(0);
    LCD_Reset();

    SPI_writeComm(0x20); //exit_invert_mode
    SPI_writeComm(0x29); //set_display_on
    SPI_writeComm(0x3A); //set_pixel_format
    SPI_writeData(0x77); //70   0X60 26k

    SPI_writeComm(0xB1); //RGB Interface Setting
    SPI_writeData(0x00);
    SPI_writeData(0x14);
    SPI_writeData(0x06);

    SPI_writeComm(0xB2); //Panel Characteristics Setting
    SPI_writeData(0x10); //480 pixels
    SPI_writeData(0xC8); //800 pixels

    SPI_writeComm(0xB3); //Panel Drive Setting    Set the inversion mode

    SPI_writeData(0x00); //1-dot inversion 0x01

    SPI_writeComm(0xB4); //Display Mode Control
    SPI_writeData(0x04); //Dither disable.

    SPI_writeComm(0xB5); //Display Mode and Frame Memory Write Mode Setting
    SPI_writeData(0x10);
    SPI_writeData(0x30);
    SPI_writeData(0x30);
    SPI_writeData(0x00);
    SPI_writeData(0x00);

    SPI_writeComm(0xB6); //Display Control 2 ( GIP Specific )
    SPI_writeData(0x01);
    SPI_writeData(0x18);
    SPI_writeData(0x02);
    SPI_writeData(0x40);
    SPI_writeData(0x10);
    SPI_writeData(0x00);

    SPI_writeComm(0xc0);
    SPI_writeData(0x01);
    SPI_writeData(0x18);

    SPI_writeComm(0xC3);
    SPI_writeData(0x03);
    SPI_writeData(0x04);
    SPI_writeData(0x03);
    SPI_writeData(0x03);
    SPI_writeData(0x03);

    LCD_delay(40);

    SPI_writeComm(0xC4); //VDD Regulator setting
    SPI_writeData(0x02);
    SPI_writeData(0x23); //GDC AP
    SPI_writeData(0x11); //VRH1  Vreg1out=1.533xVCI(10)
    SPI_writeData(0x12); //VRH2  Vreg2out=-1.533xVCI(10)
    SPI_writeData(0x02); //BT 5 VGH/VGL  6/-4
    SPI_writeData(0x77); //DDVDH 6C//0x56
    LCD_delay(20);

    SPI_writeComm(0xC5);
    SPI_writeData(0x73);
    LCD_delay(10);

    SPI_writeComm(0xC6);
    SPI_writeData(0x24); //VCI 23
    SPI_writeData(0x60); //RESET RCO 53
    SPI_writeData(0x00); //SBC GBC
    LCD_delay(10);
    //GAMMA SETTING
    SPI_writeComm(0xD0);
    SPI_writeData(0x14);
    SPI_writeData(0x01);
    SPI_writeData(0x53);
    SPI_writeData(0x25);
    SPI_writeData(0x02);
    SPI_writeData(0x02);
    SPI_writeData(0x66);
    SPI_writeData(0x14);
    SPI_writeData(0x03);

    SPI_writeComm(0xD1);
    SPI_writeData(0x14);
    SPI_writeData(0x01);
    SPI_writeData(0x53);
    SPI_writeData(0x07);
    SPI_writeData(0x02);
    SPI_writeData(0x02);
    SPI_writeData(0x66);
    SPI_writeData(0x14);
    SPI_writeData(0x03);

    SPI_writeComm(0xD2);
    SPI_writeData(0x14);
    SPI_writeData(0x01);
    SPI_writeData(0x53);
    SPI_writeData(0x25);
    SPI_writeData(0x02);
    SPI_writeData(0x02);
    SPI_writeData(0x66);
    SPI_writeData(0x14);
    SPI_writeData(0x03);

    SPI_writeComm(0xD3);
    SPI_writeData(0x14);
    SPI_writeData(0x01);
    SPI_writeData(0x53);
    SPI_writeData(0x07);
    SPI_writeData(0x02);
    SPI_writeData(0x02);
    SPI_writeData(0x66);
    SPI_writeData(0x14);
    SPI_writeData(0x03);

    SPI_writeComm(0xD4);
    SPI_writeData(0x14);
    SPI_writeData(0x01);
    SPI_writeData(0x53);
    SPI_writeData(0x25);
    SPI_writeData(0x02);
    SPI_writeData(0x02);
    SPI_writeData(0x66);
    SPI_writeData(0x14);
    SPI_writeData(0x03);

    SPI_writeComm(0xD5);
    SPI_writeData(0x14);
    SPI_writeData(0x01);
    SPI_writeData(0x53);
    SPI_writeData(0x07);
    SPI_writeData(0x02);
    SPI_writeData(0x02);
    SPI_writeData(0x66);
    SPI_writeData(0x14);
    SPI_writeData(0x03);

    //DISPLAY ON

    SPI_writeComm(0x11);
    LCD_delay(10);
    LCD_Light_ON;

    SPI_writeComm(0x3A);
    SPI_writeData(0x77); //set_pixel_format
    SPI_writeComm(0x36);
    SPI_writeData(0x0A);
}

void Tk032rb422::LCD_delay(int ms)
{
    pa_delayMs(ms);
}

void Tk032rb422::LCD_Reset()
{
}

void Tk032rb422::LCD_init(void)
{
    initHardWare();
    LCD_setup();
    //打开背光,代码未写
}

void Tk032rb422::drawPixel(u16 x, u16 y, int Color)
{
    // LTDC_Buf[y+YSIZE_PHYS*x] = Color;
}
/**********************************************
函数名：Lcd矩形填充函数

入口参数：xStart x方向的起始点
          ySrart y方向的终止点
          xLong 要选定矩形的x方向长度
          yLong  要选定矩形的y方向长度
返回值：无
***********************************************/
void Graphic_ColorBox(u16 xStart, u16 yStart, u16 xLong, u16 yLong, u32 Color)
{
    u16 i, j;
    u32 temp;
    temp = YSIZE_PHYS * xStart;
    for (i = 0; i < yLong; i++)
    {
        for (j = 0; j < xLong; j++)
        {
            drawPixel(i, j, Color);
            // LTDC_Buf[yStart + i + YSIZE_PHYS * j + temp] = Color;
        }
    }

    //	u16 i,j;
    //	u32 temp;
    //	temp = YSIZE_PHYS*yStart;
    //	for(i=0;i<yLong;i++)
    //	{
    //		for(j=0;j<xLong;j++)
    //		LTDC_Buf[xStart+j+YSIZE_PHYS*i+temp]=Color;
    //	}
}
#endif
