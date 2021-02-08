#ifndef __SSD1963_H__
#define __SSD1963_H__
#include "paLib/drv/pa_BaseDrv/pa_BaseDrv.h"
#include "paLib/service/display/ScreenRelated.h"
#include "paLib/service/display/_RgbScreen/RgbConfig.h"
#ifdef DISPLAY_USE_SSD1963
//一个3。2寸 480*800 带电容触摸 的屏幕 淘宝搜索tiky
class SSD1963
{
public:
    static SSD1963 instance;
    void init(uint16_t screenW, uint16_t screenH, RgbConfig rgbConfig,
              ScreenDataType screenDataType);

private:
    void init_hardWare(void);
    //写数据
    void write_data(uint32_t data);
    //写指令
    void write_cmd(uint32_t cmd);
    //引脚操作RST
    void setRST(char state);
    //引脚操作RD
    void setRD(char state);
    //引脚操作WR
    void setWR(char state);
    //引脚操作DC
    void setDC(char state);
    //引脚操作CS
    void setCS(char state);
    //输出函数
    void update8080data(uint32_t data);
};
#endif
#endif // __TK032RB422_H__