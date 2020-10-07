extern "C"
{
#include "GY906.h"
#include "pa_CommonLib/src/drv/pa_CommonDrv/pa_CommonDrv.h"
}
namespace GY906
{
#define GY906_I2CADDR 0x00

// RAM
#define GY906_RAWIR1 0x04
#define GY906_RAWIR2 0x05
#define GY906_TA 0x06
#define GY906_TOBJ1 0x07
#define GY906_TOBJ2 0x08
// EEPROM
#define GY906_TOMAX 0x20
#define GY906_TOMIN 0x21
#define GY906_PWMCTRL 0x22
#define GY906_TARANGE 0x23
#define GY906_EMISS 0x24
#define GY906_CONFIG 0x25
#define GY906_ADDR 0x0E
#define GY906_ID1 0x3C
#define GY906_ID2 0x3D
#define GY906_ID3 0x3E
#define GY906_ID4 0x3F
    /*红外测温*/
    double readTemp(uint8_t reg);
    //目标物体温度
    double readObjectTempC(void)
    {
        return readTemp(GY906_TOBJ1);
    }
    //环境温度
    double readAmbientTempC(void)
    {
        return readTemp(GY906_TA);
    }
    double readTemp(uint8_t reg)
    {
        double temp;
        uint8_t rdtemp[3];
        pa_IICSettingStruct a;
        pa_IIC_readLen(GY906_I2CADDR, reg, 3, rdtemp,a);
        temp = (rdtemp[0]) | (rdtemp[1] << 8);
        temp *= .02;
        temp -= 273.15;
        return temp;
    }
} // namespace GY906