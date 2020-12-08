
#include "../pa_HardwareSPI.h"

#ifdef MSP432E
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
SPI_Handle masterSpi;
SPI_Params spiParams;
SPI_Transaction transaction;
void pa_spiInit()
{

    SPI_Params_init(&spiParams);
    spiParams.frameFormat = SPI_FrameFormat::SPI_POL1_PHA0;
    spiParams.bitRate = 25000000;
    spiParams.dataSize = 8;
    spiParams.mode = SPI_Mode::SPI_MASTER;
    spiParams.transferMode = SPI_TransferMode::SPI_MODE_BLOCKING;
    masterSpi = SPI_open(CONFIG_SPI_MASTER, &spiParams);
    if (masterSpi == NULL)
    {
        while (1)
            ;
    }
}
// #include <ti/devices/msp432p4xx/driverlib/eusci.h>

void pa_spiTransmit(unsigned char *data, unsigned int len)
{
    /* Initialize master SPI transaction structure */
    // masterTxBuffer[sizeof(MASTER_MSG) - 1] = (i % 10) + '0';
    // memset((void *) masterRxBuffer, 0, SPI_MSG_LENGTH);

    // data1[0]=0xa5;
    transaction.count = len;
    transaction.txBuf = (void *)data;

    /* Toggle user LED, indicating a SPI transfer is in progress */
    // GPIO_toggle(CONFIG_GPIO_LED_1);

    /* Perform SPI transfer */
    bool transferOK = SPI_transfer(masterSpi, &transaction);
    // if (transferOK) {
    //     Display_printf(display, 0, 0, "Master received: %s", masterRxBuffer);
    // }
    // else {
    //     Display_printf(display, 0, 0, "Unsuccessful master SPI transfer");
    // }
}
void pa_spiTransmitInSpecialSpeed(unsigned char *data, unsigned int len, pa_SpiSpeed speed)
{
}

void pa_spiReceiveInSpecialSpeed(unsigned char *transData, unsigned char *recData, unsigned int len, pa_SpiSpeed speed)
{
}
void pa_spiReceive(unsigned char *transData, unsigned char *recData, unsigned int len)
{
}
#endif
