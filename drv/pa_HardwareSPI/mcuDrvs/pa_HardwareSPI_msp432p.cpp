extern "C"
{
    #include "../pa_HardwareSPI.h"
}
#ifdef MSP432P
//![Simple SPI Config]
/* SPI Master Configuration Parameter */
const eUSCI_SPI_MasterConfig spiMasterConfig =
{
    EUSCI_B_SPI_CLOCKSOURCE_SMCLK,             // SMCLK Clock Source
    3000000,                                   // SMCLK = DCO = 3MHZ
    3000000,                                    // SPICLK = 500khz
    EUSCI_B_SPI_MSB_FIRST,                     // MSB First
    EUSCI_B_SPI_PHASE_DATA_CAPTURED_ONFIRST_CHANGED_ON_NEXT,// EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    // Phase
    EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH, // High polarity
    EUSCI_B_SPI_3PIN                           // 3Wire SPI Mode
};

//1.5clk,1.6mosi
//![Simple SPI Config]
void pa_spiInit(){
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,
            GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);
    SPI_initMaster(EUSCI_B0_BASE, &spiMasterConfig);

    /* Enable SPI module */
    SPI_enableModule(EUSCI_B0_BASE);
}
#include <ti/devices/msp432p4xx/driverlib/eusci.h>
void pa_spiTransmit(unsigned char * data,unsigned int len){
    while(len){
        len--;
        // SPI_transmitData(EUSCI_B0_BASE, *data);
        EUSCI_B_CMSIS(EUSCI_B0_BASE)->TXBUF = *data;
        data++;
    }
    // for(int i=0;i<len;i++){
    //     SPI_transmitData(EUSCI_B0_BASE, data->i);
    // }
}
#endif