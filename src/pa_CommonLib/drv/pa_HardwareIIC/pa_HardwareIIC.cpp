extern "C"
{
#include "pa_HardwareIIC.h"
}
char iic_inited = 0;

//龙湫tc264
#ifdef LQ_TC264
    #include <LQ_SOFTI2C.h>
    void pa_IIC_init(){
        if(iic_inited==0){
            IIC_Init();
            iic_inited=1;
        }
        
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

#ifdef MSP432P
    #define i2cDeviceChosen EUSCI_B1_BASE
    unsigned char currentSlaveAddress=0;
    const eUSCI_I2C_MasterConfig i2cConfig =
    {
        EUSCI_B_I2C_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
        3000000,                                // SMCLK = 3MHz
        EUSCI_B_I2C_SET_DATA_RATE_100KBPS,      // Desired I2C Clock of 100khz
        0,                                      // No byte counter threshold
        EUSCI_B_I2C_NO_AUTO_STOP                // No Autostop
    };
    void pa_IIC_init(){
        if(i2cDeviceChosen==EUSCI_B1_BASE){
            MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
            GPIO_PIN4 + GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);
        }
        MAP_I2C_initMaster(i2cDeviceChosen, &i2cConfig);

        /* Specify slave address. For start we will do our first slave address */
        MAP_I2C_setSlaveAddress(i2cDeviceChosen, currentSlaveAddress);

        /* Set Master in transmit mode */
        // MAP_I2C_setMode(i2cDeviceChosen, EUSCI_B_I2C_TRANSMIT_MODE);

        /* Enable I2C Module to start operations */
        MAP_I2C_enableModule(i2cDeviceChosen);
            // if(iic_inited==0){
            //     IIC_Init();
            //     iic_inited=1;
        // }
        // MAP_I2C_clearInterruptFlag(i2cDeviceChosen,
        //     EUSCI_B_I2C_TRANSMIT_INTERRUPT1 + EUSCI_B_I2C_NAK_INTERRUPT);

        // /* Enable master transmit interrupt */
        // MAP_I2C_enableInterrupt(i2cDeviceChosen,
        //         EUSCI_B_I2C_TRANSMIT_INTERRUPT1 + EUSCI_B_I2C_NAK_INTERRUPT);
        // MAP_Interrupt_enableInterrupt(INT_EUSCIB1);
        
    }
    void EUSCIB1_IRQHandler(void)
    {
        uint_fast16_t status;

        status = MAP_I2C_getEnabledInterruptStatus(i2cDeviceChosen);

        if (status & EUSCI_B_I2C_NAK_INTERRUPT)
        {
            // MAP_I2C_masterSendStart(i2cDeviceChosen);
            // return;
        }
        MAP_Interrupt_disableSleepOnIsrExit();
        // /* Check the byte counter */
        // if (TXByteCtr)
        // {
        //     /* Send the next data and decrement the byte counter */
        //     MAP_I2C_masterSendMultiByteNext(EUSCI_B0_BASE, TXData++);
        //     TXByteCtr--;
        // }
        // else
        // {
        //     MAP_I2C_masterSendMultiByteStop(EUSCI_B0_BASE);
        //     sendStopCondition = true;
        //     sendToSlaveAddress2 = !sendToSlaveAddress2;
        //     MAP_Interrupt_disableSleepOnIsrExit();
        // }

    }

    void pa_IIC_write8(unsigned char addr,unsigned char reg,unsigned char value,pa_IICSettingStruct pa_IICSettingStruct){
        if(currentSlaveAddress!=addr){
            currentSlaveAddress=addr;
            MAP_I2C_setSlaveAddress(i2cDeviceChosen, currentSlaveAddress);
        }
        // MAP_I2C_masterSendStart(i2cDeviceChosen);
        MAP_I2C_masterSendMultiByteStart(i2cDeviceChosen, reg);
        MAP_I2C_masterSendMultiByteNext(i2cDeviceChosen, value);
        MAP_I2C_masterSendMultiByteStop(i2cDeviceChosen);
        // IIC_WriteByteToSlave(addr, reg, value,pa_IICSettingStruct.delay);
    }
    unsigned char pa_IIC_read8(unsigned char addr,unsigned char reg,pa_IICSettingStruct pa_IICSettingStruct){
        unsigned char value[1];
        // IIC_ReadMultByteFromSlave(addr, reg, 1, value,pa_IICSettingStruct.delay);
        return value[0];
    }
    void pa_IIC_writeLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char* data_t,pa_IICSettingStruct pa_IICSettingStruct){
        // IIC_WriteMultByteToSlave( addr,  reg,  length, data_t,pa_IICSettingStruct.delay);
        if(currentSlaveAddress!=addr){
            currentSlaveAddress=addr;
            MAP_I2C_setSlaveAddress(i2cDeviceChosen, currentSlaveAddress);
        }
        // MAP_I2C_masterSendStart(i2cDeviceChosen);
        MAP_I2C_masterSendMultiByteStart(i2cDeviceChosen, reg);
        while (length)
        {
            length--;
            MAP_I2C_masterSendMultiByteNext(i2cDeviceChosen, data_t);
            data_t++;
            /* code */
        }
        MAP_I2C_masterSendMultiByteStop(i2cDeviceChosen);
    }
    void pa_IIC_readLen(unsigned char addr, unsigned char reg, unsigned char length, unsigned char* data_t,pa_IICSettingStruct pa_IICSettingStruct){
        // IIC_ReadMultByteFromSlave( addr,  reg,  length, data_t,pa_IICSettingStruct.delay);
    }
#endif

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
    void pa_IIC_write8(unsigned char addr,unsigned char reg,unsigned char value,pa_IICSettingStruct pa_IICSettingStruct){
        Serial.printf("%x %x %x",addr,reg,value);
        // addr>>=1;
        // IIC_WriteByteToSlave(addr, reg, value,pa_IICSettingStruct.delay);
        Wire.beginTransmission(addr);
        Wire.write(reg);
        Wire.write(value);
        Wire.endTransmission();
    }
    unsigned char pa_IIC_read8(unsigned char addr,unsigned char reg,pa_IICSettingStruct pa_IICSettingStruct){
        unsigned char value[1];
        // IIC_ReadMultByteFromSlave(addr, reg, 1, value,pa_IICSettingStruct.delay);
        return value[0];
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