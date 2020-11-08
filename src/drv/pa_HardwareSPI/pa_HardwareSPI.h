#include "pa_Defines.h"

#ifndef __pa_HardwareSPI_h__
#define __pa_HardwareSPI_h__

#include "../pa_CommonDrv/pa_CommonDrv.h"

typedef enum
{
    SpiSpeed_About1mhz,
    SpiSpeed_About10mhz_default
} pa_SpiSpeed;

void pa_spiInit();
void pa_spiTransmitInSpecialSpeed(unsigned char *data, unsigned int len, pa_SpiSpeed speed);
void pa_spiTransmit(unsigned char *data, unsigned int len);
void pa_spiReceiveInSpecialSpeed(unsigned char *data, unsigned int len, pa_SpiSpeed speed);
void pa_spiReceive(unsigned char *data, unsigned int len);
#endif