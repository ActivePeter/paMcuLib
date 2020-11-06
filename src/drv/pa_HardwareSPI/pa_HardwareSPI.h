#include "pa_Defines.h"

#ifndef __pa_HardwareSPI_h__
#define __pa_HardwareSPI_h__

#include "../pa_CommonDrv/pa_CommonDrv.h"

void pa_spiInit();
void pa_spiTransmit(unsigned char *data, unsigned int len);
void pa_spiReceive(unsigned char *data, unsigned int len);
#endif