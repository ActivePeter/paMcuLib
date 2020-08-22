extern "C"
{
#include "pa_TFT18_drv.h"
}
#ifdef MSP432P


void pa_TFT_initGpio(){
    GPIO_setAsOutputPin(TFTSPI_CS_Port, TFTSPI_CS_Pin);   
    // GPIO_setAsOutputPin(TFTSPI_SCK_Port, TFTSPI_SCK_Pin); 
    // GPIO_setAsOutputPin(TFTSPI_SDI_Port, TFTSPI_SDI_Pin);
    GPIO_setAsOutputPin(TFTSPI_DC_Port, TFTSPI_DC_Pin);   
    GPIO_setAsOutputPin(TFTSPI_RST_Port, TFTSPI_RST_Pin); 
    // 	PIN_InitConfig(TFTSPI_CS, PIN_MODE_OUTPUT, 0);
	// PIN_InitConfig(TFTSPI_SCK, PIN_MODE_OUTPUT, 0);
	// PIN_InitConfig(TFTSPI_SDI, PIN_MODE_OUTPUT, 0);
	// PIN_InitConfig(TFTSPI_DC, PIN_MODE_OUTPUT, 0);
	// PIN_InitConfig(TFTSPI_RST, PIN_MODE_OUTPUT, 0);
}
#endif

#ifdef ESP32


void pa_TFT_initGpio(){
    
    pinMode(TFTSPI_CS_Port,  OUTPUT);
    pinMode(TFTSPI_DC_Port,  OUTPUT);
    pinMode(TFTSPI_RST_Port, OUTPUT);
    // GPIO_setAsOutputPin(TFTSPI_CS_Port, TFTSPI_CS_Pin);   
    // // GPIO_setAsOutputPin(TFTSPI_SCK_Port, TFTSPI_SCK_Pin); 
    // // GPIO_setAsOutputPin(TFTSPI_SDI_Port, TFTSPI_SDI_Pin);
    // GPIO_setAsOutputPin(TFTSPI_DC_Port, TFTSPI_DC_Pin);   
    // GPIO_setAsOutputPin(TFTSPI_RST_Port, TFTSPI_RST_Pin); 
    // // 	PIN_InitConfig(TFTSPI_CS, PIN_MODE_OUTPUT, 0);
	// // PIN_InitConfig(TFTSPI_SCK, PIN_MODE_OUTPUT, 0);
	// // PIN_InitConfig(TFTSPI_SDI, PIN_MODE_OUTPUT, 0);
	// // PIN_InitConfig(TFTSPI_DC, PIN_MODE_OUTPUT, 0);
	// // PIN_InitConfig(TFTSPI_RST, PIN_MODE_OUTPUT, 0);
}
#endif