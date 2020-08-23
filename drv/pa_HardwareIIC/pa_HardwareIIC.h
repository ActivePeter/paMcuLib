#ifndef _pa_IIC_H
#define _pa_IIC_H
extern "C"
{
#include "../pa_CommonDrv.h"
}
    typedef struct{
        unsigned short delay;
    }pa_IICSettingStruct;
    void pa_IIC_init();
    void pa_IIC_write8(unsigned char addr,unsigned char reg,unsigned char value,pa_IICSettingStruct pa_IICSettingStruct);
    unsigned char pa_IIC_read8(unsigned char addr,unsigned char reg,pa_IICSettingStruct pa_IICSettingStruct);
    void pa_IIC_writeLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char* data_t,pa_IICSettingStruct pa_IICSettingStruct);
    void pa_IIC_readLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char* data_t,pa_IICSettingStruct pa_IICSettingStruct);
#endif