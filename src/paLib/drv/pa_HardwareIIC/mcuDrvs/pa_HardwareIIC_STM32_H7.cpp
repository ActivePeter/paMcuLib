
#include "../pa_HardwareIIC.h"

#if mcu_stm32_h7
#if drv_iic
#include "main.h"
#if iic_using_id1
extern I2C_HandleTypeDef hi2c1;
// void MX_I2C1_Init(void);
#endif
iic_status pa_IIC_init(unsigned char iicId)
{
    switch (iicId)
    {
#if iic_using_id1
    case 1:
        MX_I2C1_Init();

        break;
#endif
    default:
        break;
    }
    return iic_succ;
    // HAL_GPIO_Init(g)
}

static I2C_HandleTypeDef *getHandle(uint8_t iicId)
{
    switch (iicId)
    {
#if iic_using_id1
    case 1:
        return &hi2c1;
        break;
#endif
    default:
        break;
    }
}

iic_status
pa_IIC_writeLen(unsigned char iicId, unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data_t)
{
    addr <<= 1;
    auto state = HAL_I2C_Mem_Write(getHandle(iicId), addr, reg, 1, data_t, length, 100);
    if (state == HAL_StatusTypeDef::HAL_OK)
    {
        return iic_succ;
    }
    else
    {
        return iic_fail;
    }
    // if (length == 1)
    // {
    //     unsigned char a[2];
    //     a[0] = reg;
    //     a[1] = data_t[0];
    //     HAL_I2C_Master_Transmit(&hi2c1, addr, a, 2, 10);
    //     return;
    // }
    // HAL_I2C_Master_Transmit(&hi2c1, addr, &reg, 1, 10);
    // HAL_I2C_Master_Transmit(&hi2c1, addr, data_t, length, 10);
}
iic_status pa_IIC_readLen(unsigned char iicId, unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data_t)
{
    addr <<= 1;
    auto state = HAL_I2C_Mem_Read(getHandle(iicId), addr, reg, I2C_MEMADD_SIZE_8BIT, data_t, length, 1000);
    if (state == HAL_StatusTypeDef::HAL_OK)
    {
        return iic_succ;
    }
    else
    {
        return iic_fail;
    }
    // HAL_I2C_Master_Transmit(&hi2c1, addr, &reg, 1, 1000);
    // HAL_I2C_Master_Receive(&hi2c1, addr, data_t, length, 1000);
    // HAL_I2C_Mem_Read(&hi2c1, addr, reg, I2C_MEMADD_SIZE_8BIT, data_t, length, 1000);
}
iic_status pa_IIC_directly_write(unsigned char iicId, unsigned char addr, unsigned char length, unsigned char *data_t)
{
    addr <<= 1;
    auto handle = getHandle(iicId);
    auto state = HAL_I2C_Master_Transmit(handle, addr, data_t, length, 500);
    if (state == HAL_StatusTypeDef::HAL_OK)
    {
        return iic_succ;
    }
    else
    {
        return iic_fail;
    }
}
iic_status pa_IIC_directly_read(unsigned char iicId, unsigned char addr, unsigned char length, unsigned char *data_t)
{
    addr <<= 1;
    auto handle = getHandle(iicId);
    auto state = HAL_I2C_Master_Receive(handle, addr, data_t, length, 500);
    if (state == HAL_StatusTypeDef::HAL_OK)
    {
        return iic_succ;
    }
    else
    {
        return iic_fail;
    }
}
#endif
#endif
