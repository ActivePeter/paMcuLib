extern "C"
{
#include "../pa_HardwareSPI.h"
}
#ifdef TM4C123G
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

//1.5clk,1.6mosi
//![Simple SPI Config]
void pa_spiInit()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); //打开时钟
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
    GPIOPinConfigure(GPIO_PA3_SSI0FSS);
    GPIOPinConfigure(GPIO_PA4_SSI0RX);
    GPIOPinConfigure(GPIO_PA5_SSI0TX);                                                  //初始化引脚
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2); //配置引脚供SSI外设使用。
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
                       SSI_MODE_MASTER, 1000000, 8);
    SSIEnable(SSI0_BASE); //使能
    // GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
    //         GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    // SPI_initMaster(EUSCI_B0_BASE, &spiMasterConfig);

    // /* Enable SPI module */
    // SPI_enableModule(EUSCI_B0_BASE);
}
// #include <ti/devices/msp432p4xx/driverlib/eusci.h>
void pa_spiTransmit(unsigned char *data, unsigned int len)
{
    while (len)
    {
        len--;
        // SPI_transmitData(EUSCI_B0_BASE, *data);
        SSIDataPut(SSI0_BASE, *data);
        data++;
    }
    while (SSIBusy(SSI0_BASE))
    {
    }
}
void pa_spiTransmitInSpecialSpeed(unsigned char *data, unsigned int len, pa_SpiSpeed speed)
{
}
#endif
