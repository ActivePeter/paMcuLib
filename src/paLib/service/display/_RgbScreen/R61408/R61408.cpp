#include "R61408.h"
#if DISPLAY_USE_R61408
R61408 *R61408::getInstance()
{
    static R61408 r61408;
    return &r61408;
}

void R61408::SPI_writeByte(unsigned char byte)
{
    unsigned char n;

    for (n = 0; n < 8; n++)
    {
        if (byte & 0x80)
        {
            SPI_SDA(1);
        }
        else
        {
            SPI_SDA(0);
        }
        byte <<= 1;

        SPI_DCLK(0);
        SPI_DCLK(1);
    }
}
void tkdelay()
{
    int a = 200000;
    while (a)
    {
        a--;
    }
}
void R61408::SPI_writeComm(uint16_t CMD)
{
    SPI_CS(0);
    tkdelay();
    SPI_SDA(0);
    SPI_DCLK(0);
    SPI_DCLK(1);
    SPI_writeByte(CMD);
    SPI_CS(1);

    // SPI_CS(0);
    // tkdelay();
    // SPI_writeByte(0x70);
    // SPI_writeByte(CMD);
    // SPI_CS(1);
}

void R61408::SPI_writeData(uint16_t tem_data)
{
    SPI_CS(0);
    tkdelay();
    SPI_SDA(1);
    SPI_DCLK(0);
    SPI_DCLK(1);
    SPI_writeByte(tem_data);
    SPI_CS(1);
    // SPI_CS(0);
    // tkdelay();
    // SPI_writeByte(0x72);
    // SPI_writeByte(tem_data);
    // SPI_CS(1);
}

void R61408::LCD_setup(void)
{
    LCD_Reset();
    SPI_writeComm(0x11); // Sleep Mode Off
    LCD_delay(125);      // Sleep Out

    SPI_writeComm(0xB0); // MCAP(Let Command Protect Off)
    SPI_writeData(0x04); //

    SPI_writeComm(0xB3); //
    SPI_writeData(0x12); // EPF[1:0]=00DM[1:0]=00(OSC)WEMODE=10;
    SPI_writeData(0x00); //

    SPI_writeComm(0xB6); //
    SPI_writeData(0x52); //
    SPI_writeData(0x83); //

    SPI_writeComm(0xB7); //
    SPI_writeData(0x00); //
    SPI_writeData(0x00); //
    SPI_writeData(0x11); //
    SPI_writeData(0x25); //

    SPI_writeComm(0xBD); //
    SPI_writeData(0x00); //

    SPI_writeComm(0xC0); //
    SPI_writeData(0x02); //
    SPI_writeData(0x87); //

    SPI_writeComm(0xC1); // Panel Driving Setting 2
    SPI_writeData(0x42); // WCVDC2=1,REV=0,BGR=1,SS=0(36h[6]=1S1->S1440)
    SPI_writeData(0x31); //
    SPI_writeData(0x00); //
    SPI_writeData(0x21); //
    SPI_writeData(0x21); //
    SPI_writeData(0x32); //
    SPI_writeData(0x12); //
    SPI_writeData(0x28); //
    SPI_writeData(0x4A); //
    SPI_writeData(0x1E); //
    SPI_writeData(0xA5); //
    SPI_writeData(0x0F); //
    SPI_writeData(0x58); //
    SPI_writeData(0x21); //
    SPI_writeData(0x01); //

    SPI_writeComm(0xC2); //
    SPI_writeData(0x28); // [5:3]=101:Column inversion 	PSEN=0:spatial configuration mode 1
    SPI_writeData(0x06); //
    SPI_writeData(0x06); //
    SPI_writeData(0x01); //
    SPI_writeData(0x03); //
    SPI_writeData(0x00); //

    SPI_writeComm(0xC6); //
    SPI_writeData(0x00); //
    SPI_writeData(0x00); //

    SPI_writeComm(0xC8); // Gamma Setting
    SPI_writeData(0x00); // P0
    SPI_writeData(0x15); // P1
    SPI_writeData(0x22); // P2
    SPI_writeData(0x2C); // P3
    SPI_writeData(0x39); // P4
    SPI_writeData(0x54); // P5
    SPI_writeData(0x34); // P6
    SPI_writeData(0x21); // P7
    SPI_writeData(0x16); // P8
    SPI_writeData(0x11); // P9
    SPI_writeData(0x08); // P10
    SPI_writeData(0x05); // P11
    SPI_writeData(0x00); // N0
    SPI_writeData(0x15); // N1
    SPI_writeData(0x22); // N2
    SPI_writeData(0x2C); // N3
    SPI_writeData(0x39); // N4
    SPI_writeData(0x54); // N5
    SPI_writeData(0x34); // N6
    SPI_writeData(0x21); // N7
    SPI_writeData(0x16); // N8
    SPI_writeData(0x11); // N9
    SPI_writeData(0x08); // N10
    SPI_writeData(0x05); // N11

    SPI_writeComm(0xC9); // Gamma Setting
    SPI_writeData(0x00); // P0
    SPI_writeData(0x15); // P1
    SPI_writeData(0x22); // P2
    SPI_writeData(0x2C); // P3
    SPI_writeData(0x39); // P4
    SPI_writeData(0x54); // P5
    SPI_writeData(0x34); // P6
    SPI_writeData(0x21); // P7
    SPI_writeData(0x16); // P8
    SPI_writeData(0x11); // P9
    SPI_writeData(0x08); // P10
    SPI_writeData(0x05); // P11
    SPI_writeData(0x00); // N0
    SPI_writeData(0x15); // N1
    SPI_writeData(0x22); // N2
    SPI_writeData(0x2C); // N3
    SPI_writeData(0x39); // N4
    SPI_writeData(0x54); // N5
    SPI_writeData(0x34); // N6
    SPI_writeData(0x21); // N7
    SPI_writeData(0x16); // N8
    SPI_writeData(0x11); // N9
    SPI_writeData(0x08); // N10
    SPI_writeData(0x05); // N11

    SPI_writeComm(0xCA); // Gamma Setting
    SPI_writeData(0x00); // P0
    SPI_writeData(0x15); // P1
    SPI_writeData(0x22); // P2
    SPI_writeData(0x2C); // P3
    SPI_writeData(0x39); // P4
    SPI_writeData(0x54); // P5
    SPI_writeData(0x34); // P6
    SPI_writeData(0x21); // P7
    SPI_writeData(0x16); // P8
    SPI_writeData(0x11); // P9
    SPI_writeData(0x08); // P10
    SPI_writeData(0x05); // P11
    SPI_writeData(0x00); // N0
    SPI_writeData(0x15); // N1
    SPI_writeData(0x22); // N2
    SPI_writeData(0x2C); // N3
    SPI_writeData(0x39); // N4
    SPI_writeData(0x54); // N5
    SPI_writeData(0x34); // N6
    SPI_writeData(0x21); // N7
    SPI_writeData(0x16); // N8
    SPI_writeData(0x11); // N9
    SPI_writeData(0x08); // N10
    SPI_writeData(0x05); // N11

    SPI_writeComm(0xD0); // Charge Pump Setting
    SPI_writeData(0x29);
    SPI_writeData(0x03);
    SPI_writeData(0xCE); //VLMT4[2:0]=VCI-VCL=-2.79V;VLMT1[2:0]=VSP When a switching regulator is used.Set to 3'h6 when a charge pump is used.
    SPI_writeData(0xA6); //VLMT1M[2:0]=VSN When a switching regulator is used.Set to 3'h6 when a charge pump is used.
    SPI_writeData(0x00); //SWRON=0(VSPㄏノCharge Pump)SWRONM=0(VSNㄏノCharge Pump)
    SPI_writeData(0x71); //VC3[2:0]=VGL=(-VCI2x2)-VCI3=-4.03x2-5.17=-13.23V;VC2[2:0]=VGH=VCI2x4=4.24x4=16.96V
    SPI_writeData(0x20);
    SPI_writeData(0x10);
    SPI_writeData(0x01);
    SPI_writeData(0x00);
    SPI_writeData(0x01);
    SPI_writeData(0x01);
    SPI_writeData(0x00);
    SPI_writeData(0x03);
    SPI_writeData(0x01);
    SPI_writeData(0x00);

    SPI_writeComm(0xFD); //砞﹚Test VPLVL
    SPI_writeData(0x00);
    SPI_writeData(0x00);
    SPI_writeData(0x70);
    SPI_writeData(0x00);
    SPI_writeData(0x32);
    SPI_writeData(0x31);
    SPI_writeData(0x34);
    SPI_writeData(0x36);

    SPI_writeComm(0xD3); //
    SPI_writeData(0x33); //

    SPI_writeComm(0xD5); // VPLVL/VNLVL Setting
    SPI_writeData(0x1A); // PVH[6:0]=VPLVL=5.218V
    SPI_writeData(0x1A); // PNH[6:0]=VNLVL=-5.218V

    SPI_writeComm(0xD6); //
    SPI_writeData(0xA8); //

    SPI_writeComm(0xDE); // SET VCOM
    SPI_writeData(0x01); //
    SPI_writeData(0x52); //  VDC[7:0]=VNLVLX0.274=-5.218Vx0.256=-1.33V

    SPI_writeComm(0xE0); //
    SPI_writeData(0x00); //
    SPI_writeData(0x00); //
    SPI_writeData(0x00); //
    SPI_writeData(0x00); //

    SPI_writeComm(0xE1); //
    SPI_writeData(0x00); //
    SPI_writeData(0x00); //
    SPI_writeData(0x00); //
    SPI_writeData(0x00); //
    SPI_writeData(0x00); //
    SPI_writeData(0x00); //

    SPI_writeComm(0xFA); //
    SPI_writeData(0x03); //

    SPI_writeComm(0xB0); // MCAP(Let Command Protect On)
    SPI_writeData(0x03); //
    //-------------------------------------------
    //Set GRAM Area
    SPI_writeComm(0x2A); // Column address set (2Ah) Source=480
    SPI_writeData(0x00); //
    SPI_writeData(0x00); //
    SPI_writeData(0x01); //
    SPI_writeData(0xDF); //

    SPI_writeComm(0x2B); // Page address set (2Bh) Gate=800
    SPI_writeData(0x00); //
    SPI_writeData(0x00); //
    SPI_writeData(0x03); //
    SPI_writeData(0x1F); //

    SPI_writeComm(0x36); // set_address_mode
    SPI_writeData(0x48); // Top->DownRight->LeftBGR=0

    SPI_writeComm(0x3A); // SET COLOR
    SPI_writeData(0x77); // 24bits/pixel

    SPI_writeComm(0x35); // TEAR ON
    SPI_writeData(0x00); //

    SPI_writeComm(0x29); // display on
    LCD_delay(50);

    SPI_writeComm(0x2c);
    LCD_delay(50);
}

void R61408::LCD_delay(int ms)
{
    pa_delayMs(ms);
}

void R61408::LCD_Reset()
{
    LCD_setReset(0);
    LCD_delay(1000);
    LCD_setReset(1);
    LCD_delay(1000);
}

void R61408::LCD_init(void)
{
    initHardWare();
    LCD_setup();
    //打开背光,代码未写
}

/**********************************************
函数名：Lcd矩形填充函数

入口参数：xStart x方向的起始点
          ySrart y方向的终止点
          xLong 要选定矩形的x方向长度
          yLong  要选定矩形的y方向长度
返回值：无
***********************************************/
void R61408::Graphic_ColorBox(uint16_t xStart, uint16_t yStart, uint16_t xLong, uint16_t yLong, uint32_t Color)
{
    uint16_t i, j;
    // uint32_t temp;
    // temp = YSIZE_PHYS * xStart;
    for (i = 0; i < yLong; i++)
    {
        for (j = 0; j < xLong; j++)
        {
            drawPixel(i, j, Color);
            // LTDC_Buf[yStart + i + YSIZE_PHYS * j + temp] = Color;
        }
    }

    //	uint16_t i,j;
    //	uint32_t temp;
    //	temp = YSIZE_PHYS*yStart;
    //	for(i=0;i<yLong;i++)
    //	{
    //		for(j=0;j<xLong;j++)
    //		LTDC_Buf[xStart+j+YSIZE_PHYS*i+temp]=Color;
    //	}
}

RgbConfig R61408::getRGBConfig()
{
    // return RgbConfig(
    //     40,
    //     32,
    //     10,
    //     1,
    //     48,
    //     13);
    return RgbConfig(
        40,
        10,
        5,
        1,
        50,
        10);
}
#endif
