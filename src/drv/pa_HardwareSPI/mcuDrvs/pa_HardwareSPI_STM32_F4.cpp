extern "C"
{
    #include "../pa_HardwareSPI.h"
}
#ifdef STM32_F4
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
extern SPI_HandleTypeDef hspi1;
//1.5clk,1.6mosi
//![Simple SPI Config]
void pa_spiInit(){
}
// #include <ti/devices/msp432p4xx/driverlib/eusci.h>
void pa_spiTransmit(unsigned char * data,unsigned int len){
    HAL_SPI_Transmit(&hspi1, data,len, 100);
}
void pa_spiReceive(unsigned char * data,unsigned int len){
    HAL_SPI_Receive(&hspi1, data,len, 100);
}
#endif