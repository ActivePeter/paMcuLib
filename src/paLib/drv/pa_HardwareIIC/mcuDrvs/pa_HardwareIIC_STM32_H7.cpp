
#include "../pa_HardwareIIC.h"

#if mcu_stm32_h7
extern I2C_HandleTypeDef hi2c1;
void pa_IIC_init()
{
}
void pa_IIC_writeLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data_t, pa_IICSettingStruct pa_IICSettingStruct)
{
    addr <<= 1;
    HAL_I2C_Mem_Write(&hi2c1, addr, reg, 1, data_t, length, 100);
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
void pa_IIC_readLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data_t, pa_IICSettingStruct pa_IICSettingStruct)
{
    addr <<= 1;
    HAL_I2C_Mem_Read(&hi2c1, addr, reg, I2C_MEMADD_SIZE_8BIT, data_t, length, 1000);
    // HAL_I2C_Master_Transmit(&hi2c1, addr, &reg, 1, 1000);
    // HAL_I2C_Master_Receive(&hi2c1, addr, data_t, length, 1000);
    // HAL_I2C_Mem_Read(&hi2c1, addr, reg, I2C_MEMADD_SIZE_8BIT, data_t, length, 1000);
}
#endif
