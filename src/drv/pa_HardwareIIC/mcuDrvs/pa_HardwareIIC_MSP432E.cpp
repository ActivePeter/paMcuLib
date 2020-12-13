
#include "../pa_HardwareIIC.h"

#ifdef MSP432E
#include "FreeRTOS.h"
I2C_Handle i2c;
I2C_Params i2cParams;
I2C_Transaction i2cTransaction;
void pa_IIC_init()
{

    I2C_init();
    /* Create I2C for usage */
    I2C_Params_init(&i2cParams);
    i2cParams.bitRate = I2C_100kHz;

    i2c = I2C_open(CONFIG_I2C_0, &i2cParams);
    if (i2c == NULL)
    {
        // Display_printf(display, 0, 0, (char *)"Error Initializing I2C!\n");
        while (1)
            ;
    }
}
void pa_IIC_writeLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data_t, pa_IICSettingStruct pa_IICSettingStruct)
{
    unsigned char *buff = (unsigned char *)pvPortMalloc(length + 1);
    buff[0] = reg;
    for (int i = 0; i < length; i++)
    {
        buff[i + 1] = data_t[i];
    }
    i2cTransaction.slaveAddress = addr;
    i2cTransaction.writeBuf = (void *)buff;
    i2cTransaction.writeCount = length + 1;
    i2cTransaction.readCount = 0;
    I2C_transfer(i2c, &i2cTransaction);
    vPortFree(buff);
    // i2cTransaction.writeBuf = (void *)data_t;
    // i2cTransaction.writeCount = length;
    // i2cTransaction.readCount = 0;
    // I2C_transfer(i2c, &i2cTransaction);
}
void pa_IIC_readLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char *data_t, pa_IICSettingStruct pa_IICSettingStruct)
{
    i2cTransaction.slaveAddress = addr;
    i2cTransaction.writeBuf = &reg;
    i2cTransaction.writeCount = 1;
    // i2cTransaction.readCount = 0;
    i2cTransaction.readBuf = (void *)data_t;
    i2cTransaction.readCount = length;
    I2C_transfer(i2c, &i2cTransaction);

    // i2cTransaction.writeCount = 0;
    // i2cTransaction.readBuf = (void *)data_t;
    // i2cTransaction.readCount = length;
    // I2C_transfer(i2c, &i2cTransaction);
}
#endif
