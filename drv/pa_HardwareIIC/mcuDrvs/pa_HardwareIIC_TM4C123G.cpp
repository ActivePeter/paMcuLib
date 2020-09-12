

//龙湫tc264
#ifdef TM4C123G
extern "C"
{
#include "../pa_HardwareIIC.h"
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
}
void pa_IIC_init()
{
    //enable i2c0 module
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

    //reset module
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

    //enable GPIO that contains I2C0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

    //clear I2C FIFOs
    HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;
}
void pa_IIC_writeLen(unsigned char addr, unsigned char headByte, unsigned char length, unsigned char *data_t, pa_IICSettingStruct pa_IICSettingStruct)
{
    I2CMasterSlaveAddrSet(I2C0_BASE, addr, false);
    I2CMasterDataPut(I2C0_BASE, headByte);
    if (length == 0)
    {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
        while (I2CMasterBusy(I2C0_BASE))
            ;
        return;
    }
    //Initialize sending data from the MCU
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    //wait while MCU is done transferring
    while (I2CMasterBusy(I2C0_BASE))
        ;
    while (length > 1)
    {
        I2CMasterDataPut(I2C0_BASE, *data_t);
        //Initialize sending data from the MCU
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
        //wait while MCU is done transferring
        while (I2CMasterBusy(I2C0_BASE))
            ;
        data_t++;
        length--;
    }
    I2CMasterDataPut(I2C0_BASE, *data_t);
    //Initialize sending data from the MCU
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    //wait while MCU is done transferring
    while (I2CMasterBusy(I2C0_BASE))
        ;
}
void pa_IIC_readLen(unsigned char addr, unsigned char headByte, unsigned char length, unsigned char *data_t, pa_IICSettingStruct pa_IICSettingStruct)
{
    I2CMasterSlaveAddrSet(I2C1_BASE, addr, false);           //set dia chi slave, che do write
    I2CMasterDataPut(I2C1_BASE, headByte);                   //dat dia chi thanh ghi slave vao thanh ghi data
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND); //goi tin hieu send data
    while (I2CMasterBusy(I2C1_BASE))
        ; //cho goi xong

    if (length == 1)
    {
        I2CMasterSlaveAddrSet(I2C1_BASE, addr, true);               //cai dat read slave
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE); //tell master read data
        while (I2CMasterBusy(I2C1_BASE))
            ; //cho truyen xong
        data_t[0] = I2CMasterDataGet(I2C0_BASE);
    }
    else
    {
        I2CMasterSlaveAddrSet(I2C1_BASE, addr, true);                    //cai dat read slave
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START); //tell master read data
        while (I2CMasterBusy(I2C1_BASE))
            ;
        *data_t = I2CMasterDataGet(I2C0_BASE);
        data_t++;
        length--;
        while (length > 1)
        {
            I2CMasterSlaveAddrSet(I2C1_BASE, addr, true);                    //cai dat read slave
            I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT); //tell master read data
            while (I2CMasterBusy(I2C1_BASE))
                ;
            *data_t = I2CMasterDataGet(I2C0_BASE);
            data_t++;
            length--;
        }
        I2CMasterSlaveAddrSet(I2C1_BASE, addr, true);                    //cai dat read slave
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH); //tell master read data
        while (I2CMasterBusy(I2C1_BASE))
            ;
        *data_t = I2CMasterDataGet(I2C0_BASE);
    }
}
#endif