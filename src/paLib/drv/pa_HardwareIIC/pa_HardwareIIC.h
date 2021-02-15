#ifndef _pa_IIC_H
#define _pa_IIC_H

#include "paLib/drv/pa_BaseDrv/pa_BaseDrv.h"
#if drv_iic
typedef struct
{
     unsigned short delay;
} pa_IICSettingStruct;
typedef enum
{
     iic_succ,
     iic_fail
} iic_status;
iic_status pa_IIC_init(unsigned char iicId);
/** 
     * @brief 写iic
     * @param addr   器件地址
     * @param headByte   头字节
     * @param length   数据体长度，可以为0
     * @param data_t   数据体指针
     */
iic_status pa_IIC_writeLen(unsigned char iicId, unsigned char addr, unsigned char headByte, unsigned char length, unsigned char *data_t);
/** 
     * @brief 读iic
     * @param addr   器件地址
     * @param headByte   头字节
     * @param length   数据体长度，最小为1
     * @param data_t   数据体指针
     */
iic_status pa_IIC_readLen(unsigned char iicId, unsigned char addr, unsigned char headByte, unsigned char length, unsigned char *data_t);

iic_status pa_IIC_directly_write(unsigned char iicId, unsigned char addr, unsigned char length, unsigned char *data_t);
iic_status pa_IIC_directly_read(unsigned char iicId, unsigned char addr, unsigned char length, unsigned char *data_t);
#endif
#endif
