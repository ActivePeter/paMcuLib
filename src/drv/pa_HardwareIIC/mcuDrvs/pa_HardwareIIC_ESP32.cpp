extern "C"
{
#include "../pa_HardwareIIC.h"
}
#ifdef ESP32
#include <wire.h>
#include "Arduino.h"  
//esp32 一般的iic是 21:sda 和22:scl
    // #include <LQ_SOFTI2C.h>
    void pa_IIC_init(){
        Wire.begin();
        // if(iic_inited==0){
        //     IIC_Init();
        //     iic_inited=1;
        // }
        
    }
    void pa_IIC_writeLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char* data_t,pa_IICSettingStruct pa_IICSettingStruct){
        // IIC_WriteMultByteToSlave( addr,  reg,  length, data_t,pa_IICSettingStruct.delay);
        // addr>>=1;
        Wire.beginTransmission(addr);
        Wire.write(reg);
        while (length)
        {
            length--;
            Wire.write(*data_t);
            data_t++;
            /* code */
        }
        
        // Wire.write(data_t,length);
        
        Wire.endTransmission();
    }
    void pa_IIC_readLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char* data_t,pa_IICSettingStruct pa_IICSettingStruct){
        // IIC_ReadMultByteFromSlave( addr,  reg,  length, data_t,pa_IICSettingStruct.delay);
    }
#endif