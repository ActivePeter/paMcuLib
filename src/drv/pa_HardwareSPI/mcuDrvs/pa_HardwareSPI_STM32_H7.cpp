
#include "../pa_HardwareSPI.h"

#ifdef STM32_H7
//![Simple SPI Config]
/* SPI Master Configuration Parameter */
// const eUSCI_SPI_MasterConfig spiMasterConfig =
// {
//     EUSCI_B_SPI_CLOCKSOURCE_SMCLK,             // SMCLK Clock Source
//     3000000,                                   // SMCLK = DCO = 3MHZ
//     3000000,                                    // SPICLK = 500khz
//     EUSCI_B_SPI_MSB_FIRST,                     // MSB First
//     EUSCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,// EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    // Phase
//     EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH, // High polarity
//     EUSCI_B_SPI_3PIN                           // 3Wire SPI Mode
// };
extern SPI_HandleTypeDef hspi1; //about 10mhz
extern SPI_HandleTypeDef hspi2; //about 1mhz
//1.5clk,1.6mosi
//![Simple SPI Config]
void pa_spiInit()
{
}
// #include <ti/devices/msp432p4xx/driverlib/eusci.h>
void pa_spiTransmit(unsigned char *data, unsigned int len)
{
    HAL_SPI_Transmit(&hspi1, data, len, 100);
    // HAL_SPI_Transmit_DMA(&hspi1, data,len);
    // hal_spi
}
void pa_spiReceive(unsigned char *data, unsigned int len)
{
    HAL_SPI_Receive(&hspi1, data, len, 100);
}

void pa_spiTransmitInSpecialSpeed(unsigned char *data, unsigned int len, pa_SpiSpeed speed)
{
    switch (speed)
    {
    case pa_SpiSpeed::SpiSpeed_About1mhz:
    {
        HAL_StatusTypeDef hst = HAL_SPI_Transmit(&hspi2, data, len, 100);
        if (hst != HAL_StatusTypeDef::HAL_OK)
        {
            pa_Debug("spi tran error\r\n");
        }
        else
        {
            pa_Debug("spi tran succ\r\n");
        }
        break;
    }

    default:
    {
        pa_spiTransmit(data, len);
        break;
    }
    }
}

void pa_spiReceiveInSpecialSpeed(unsigned char *data, unsigned int len, pa_SpiSpeed speed)
{
    switch (speed)
    {
    case pa_SpiSpeed::SpiSpeed_About1mhz:
    {
        HAL_StatusTypeDef hst = HAL_SPI_TransmitReceive(&hspi2, data, data, len, 100);
        if (hst != HAL_StatusTypeDef::HAL_OK)
        {

            pa_Debug("spi rec error\r\n");
        }
        else
        {

            pa_Debug("spi tran succ\r\n");
        }
        break;
    }

    default:
        pa_spiReceive(data, len);
        break;
    }
}

#endif