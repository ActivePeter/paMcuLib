extern "C"
{
#include "../pa_HardwareIIC.h"
}
#ifdef STM32_F4
    void pa_IIC_init(){
        
    }
    void pa_IIC_writeLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char* data_t,pa_IICSettingStruct pa_IICSettingStruct){

    }
    void pa_IIC_readLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char* data_t,pa_IICSettingStruct pa_IICSettingStruct){
    }
#endif
