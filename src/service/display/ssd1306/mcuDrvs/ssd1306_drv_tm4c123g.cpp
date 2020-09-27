#include "pa_Defines.h"

#ifdef DISPLAY_USE_SSD1306

extern "C"{
    #include "../pa_oled_drv.h"
}

#ifdef TM4C123G
#define OLED_CS_Port GPIO_PORTD_BASE
#define OLED_CS_Pin GPIO_PIN_0

#define OLED_DC_Port GPIO_PORTD_BASE
#define OLED_DC_Pin GPIO_PIN_1

#define OLED_RST_Port GPIO_PORTD_BASE
#define OLED_RST_Pin GPIO_PIN_2

// D0                         4 线 ISP 接口模式：时钟线（CLK）
// D1                         4 线 ISP 接口模式：串行数据线（MOSI）
void OLED_initSpiGpio(){
    GPIOPinTypeGPIOOutput(OLED_DC_Port, OLED_DC_Pin);   
    GPIOPinTypeGPIOOutput(OLED_CS_Port, OLED_CS_Pin);   
    
    GPIOPinTypeGPIOOutput(OLED_RST_Port, OLED_RST_Pin); 
}

void OLED_setCS(char state){
    GPIOPinWrite(OLED_CS_Port, OLED_CS_Pin, state*OLED_CS_Pin);
}

void OLED_setDC(char state){
    GPIOPinWrite(OLED_DC_Port, OLED_DC_Pin, state*OLED_DC_Pin);
}

void OLED_setRST(char state){
    GPIOPinWrite(OLED_RST_Port, OLED_RST_Pin, state*OLED_RST_Pin);
}
#endif

#endif