#include "SSD1963.h"
#ifdef DISPLAY_USE_SSD1963

SSD1963 SSD1963::instance;
void SSD1963::init(uint16_t screenW, uint16_t screenH, RgbConfig rgbConf,
                   ScreenDataType screenDataType)
{
    init_hardWare();
    setCS(0);

    setRST(1);
    pa_delayMs(100);

    setRST(0);
    pa_delayMs(800);

    setRST(1);
    pa_delayMs(800);

    //SSD1963,800*480
    //SSD1963,800*480

    write_cmd(0x00E2);  //set_pll_mn
    write_data(0x0030); //M=0x23=35, VCO = Reference input clock x (M + 1),PLL multiplier, set PLL clock to 120M
    write_data(0x0001); //N=0x02=2,	 PLL frequency  = VCO / (N + 1)
    write_data(0x0004); //0x36 for 6.5M, 0x23 for 10M crystal

    write_cmd(0x00E0); //set_pll
    write_data(0x0001);
    pa_delayMs(1);
    write_cmd(0x00E0);
    write_data(0x0003);
    pa_delayMs(5);

    write_cmd(0x0001); // software	reset
    pa_delayMs(5);

    write_cmd(0x00E6);  //set_lshift_freq ,PLL setting for PCLK, depends on resolution
    write_data(0x0001); //4.94M	 //01
    write_data(0x00aa); //50  aa
    write_data(0x0aa);  //94

    write_cmd(0x00B0);  //set_lcd_mode
    write_data(0x0024); //18BIT  Data latch in rising edge
    write_data(0x0000);
    uint16_t syncMove = 0;
    uint16_t HDP = screenW;
    write_data((HDP >> 8) & 0X00FF); //Set HDP
    write_data(HDP & 0X00FF);
    uint16_t VDP = screenH;
    write_data((VDP >> 8) & 0X00FF); //Set VDP
    write_data(VDP & 0X00FF);
    write_data(0x0000);
    pa_delayMs(5);
    uint16_t HT = HDP +
                  rgbConf.HFP +
                  rgbConf.HSW +
                  rgbConf.HBP;
    write_cmd(0x00B4);              //set_hori_period,HSYNC
    write_data((HT >> 8) & 0X00FF); //Set HT
    write_data(HT & 0X00FF);
    uint16_t HPS = syncMove + rgbConf.HSW + rgbConf.HBP;
    write_data((HPS >> 8) & 0X00FF); //Set HPS
    write_data(HPS & 0X00FF);
    uint16_t HPW = rgbConf.HSW;
    write_data(HPW); //Set HPW
    ///////////////////////////////////////////////

    uint16_t LPS = syncMove;
    //////////////////////////////////////////////
    write_data((LPS >> 8) & 0X00FF); //SetLPS
    write_data(LPS & 0X00FF);
    write_data(0x0000);

    write_cmd(0x00B6); //set_vert_period,VSYNC
    uint16_t VT = VDP +
                  rgbConf.VFP +
                  rgbConf.VSW +
                  rgbConf.VBP;
    write_data((VT >> 8) & 0X00FF); //Set VT
    write_data(VT & 0X00FF);
    uint16_t VPS = syncMove + rgbConf.VSW + rgbConf.VBP;
    write_data((VPS >> 8) & 0X00FF); //Set VPS
    write_data(VPS & 0X00FF);
    uint16_t VPW = rgbConf.VSW;
    write_data(VPW); //Set VPW
    uint16_t FPS = syncMove;
    write_data((FPS >> 8) & 0X00FF); //Set FPS
    write_data(FPS & 0X00FF);

    //	write_cmd(0x0021);

    write_cmd(0x00F0); //set_pixel_data_interface
    switch (screenDataType)
    {
    case ScreenDataType_565:
        write_data(0x0003); //0x03:16-bit(565 format);0x04:18bit;0x05:24bit
        break;
    case ScreenDataType_666:
        write_data(0x0004); //0x03:16-bit(565 format);0x04:18bit;0x05:24bit
        break;
    case ScreenDataType_888:
        write_data(0x0005); //0x03:16-bit(565 format);0x04:18bit;0x05:24bit
        break;
    default:
        break;
    }

    pa_delayMs(5);

    // ClearAll();

    write_cmd(0x0029); //set_display_on
}
void SSD1963::write_data(uint32_t data)
{
    // setCS(0);             //开始片选
    // setDC(1);             //写数据
    // setRD(1);             //禁止读
    // update8080data(data); //输出数据
    // setWR(0);             //写入开始
    // setWR(1);             //写入结束
    // setCS(1);             //结束片选

    setDC(1);             //写数据
    setRD(1);             //禁止读
    update8080data(data); //输出数据
    setWR(0);             //写入开始
    setCS(0);             //开始片选
    setCS(1);             //结束片选
    setWR(1);             //写入结束
}

void SSD1963::write_cmd(uint32_t cmd)
{
    setDC(0);            //写命令
    setRD(1);            //禁止读
    update8080data(cmd); //输出数据
    setWR(0);            //写入开始
    setCS(0);            //开始片选
    setCS(1);            //结束片选
    setWR(1);            //写入结束
}

#endif
