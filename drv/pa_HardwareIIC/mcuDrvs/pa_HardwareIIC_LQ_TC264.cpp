extern "C"
{
#include "../pa_HardwareIIC.h"
}
//龙湫tc264
#ifdef LQ_TC264
    #include <LQ_SOFTI2C.h>
    void pa_IIC_init(){
        IIC_Init();
    }
    void pa_IIC_write8(unsigned char addr,unsigned char reg,unsigned char value,pa_IICSettingStruct pa_IICSettingStruct){
        IIC_WriteByteToSlave(addr, reg, value,pa_IICSettingStruct.delay);
    }
    unsigned char pa_IIC_read8(unsigned char addr,unsigned char reg,pa_IICSettingStruct pa_IICSettingStruct){
        unsigned char value[1];
        IIC_ReadMultByteFromSlave(addr, reg, 1, value,pa_IICSettingStruct.delay);
        return value[0];
    }
    void pa_IIC_writeLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char* data_t,pa_IICSettingStruct pa_IICSettingStruct){
        IIC_WriteMultByteToSlave( addr,  reg,  length, data_t,pa_IICSettingStruct.delay);
    }
    void pa_IIC_readLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char* data_t,pa_IICSettingStruct pa_IICSettingStruct){
        IIC_ReadMultByteFromSlave( addr,  reg,  length, data_t,pa_IICSettingStruct.delay);
    }
#endif
