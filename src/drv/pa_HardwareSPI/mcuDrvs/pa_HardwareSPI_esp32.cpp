extern "C"
{
    #include "../pa_HardwareSPI.h"
}

#ifdef ESP32
#include "SPI.h"
#include "Arduino.h"

#define TFT_MOSI            19
#define TFT_SCLK            18
#define SPI_FREQUENCY  40000000
#define TFT_SPI_MODE SPI_MODE3

// SPIClass spi;
//![Simple SPI Config]
void pa_spiInit(){

    SPI.begin(TFT_SCLK, -1, TFT_MOSI, -1);//18 sck    19 miso/sdi
}
void pa_spiTransmit(unsigned char * data,unsigned int len){
    SPI.beginTransaction(SPISettings(SPI_FREQUENCY, MSBFIRST, TFT_SPI_MODE));
    // while (len)
    // {
    //     len--;
    //     SPI.transfer(*data);    
    //     data++;
    //     /* code */
    // }
    SPI.transfer(data,len);    
    
    SPI.endTransaction();
}
#endif