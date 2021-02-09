#ifndef __RGBCONFIG_Hpp__
#define __RGBCONFIG_Hpp__

#include "paLib/drv/pa_BaseDrv/pa_BaseDrv.h"
#if UseRgbScreen

class RgbConfig
{
public:
    /*****************************************************
    *  @brief     初始化rgbConfig
    *  @param      HBP HSYNC后的无效像素 水平
    *  @param      VBP VSYNC后的无效行数
    *  @param      HSW HSYNC宽度
    *  @param      VSW VSYNC宽度
    *  @param      HFP HSYNC前的无效像素
    *  @param      VFP VSYNC前的无效行数   
    *  @note      用于传递参数于rgb屏幕初始化的时候 
    *****************************************************/
    RgbConfig(uint16_t HBP1, uint16_t VBP,
              uint16_t HSW1, uint16_t VSW,
              uint16_t HFP1, uint16_t VFP);

    uint16_t HBP; //HSYNC后的无效像素 水平
    uint16_t VBP; //VSYNC后的无效行数

    uint16_t HSW; //HSYNC宽度
    uint16_t VSW; //VSYNC宽度

    uint16_t HFP; //HSYNC前的无效像素
    uint16_t VFP; //VSYNC前的无效行数
};
#endif
#endif // __RGBCONFIG_H__
