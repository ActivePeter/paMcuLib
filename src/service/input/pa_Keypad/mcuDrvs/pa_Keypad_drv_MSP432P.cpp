#include "pa_Defines.h"

#ifdef INPUT_USE_KEYPAD

#include "../pa_Keypad.h"

/****************************************************
 * driver 层代码
 * ***************************************************/

#ifdef MSP432P

uint_fast8_t Keypad_OutputPorts[Keypad_Output_Cnt];
uint_fast16_t Keypad_OutputPins[Keypad_Output_Cnt];

uint_fast8_t Keypad_InputPorts[Keypad_Input_Cnt];
uint_fast16_t Keypad_InputPins[Keypad_Input_Cnt];



 //初始化引脚
void pa_Keypad::hardwareInit() {
    {
        Keypad_OutputPorts[0] = GPIO_PORT_P3;       
        Keypad_OutputPins[0] = GPIO_PIN7;
        //---------------------------
        Keypad_OutputPorts[1] = GPIO_PORT_P3;                    
        Keypad_OutputPins[1] = GPIO_PIN5;
        //---------------------------
        Keypad_OutputPorts[2] = GPIO_PORT_P5;                    
        Keypad_OutputPins[2] = GPIO_PIN1;
        //---------------------------
        Keypad_OutputPorts[3] = GPIO_PORT_P2;         
        Keypad_OutputPins[3] = GPIO_PIN3;
        //---------------------------
        Keypad_InputPorts[0] = GPIO_PORT_P6;        
        Keypad_InputPins[0] = GPIO_PIN7;
        //---------------------------
        Keypad_InputPorts[1] = GPIO_PORT_P6;           
        Keypad_InputPins[1] = GPIO_PIN6;
        //---------------------------
        Keypad_InputPorts[2] = GPIO_PORT_P5;          
        Keypad_InputPins[2] = GPIO_PIN6;
        //---------------------------
        Keypad_InputPorts[3] = GPIO_PORT_P2;                 
        Keypad_InputPins[3] = GPIO_PIN4;
    }
    
    initInput();
    initOutput();
}


void pa_Keypad::initInput() {
    for (int i = 0; i < Keypad_Input_Cnt; i++) {
        if (isPullup) {
            GPIO_setAsInputPinWithPullUpResistor(Keypad_InputPorts[i], Keypad_InputPins[i]);
        }
        else {
            GPIO_setAsInputPinWithPullDownResistor(Keypad_InputPorts[i], Keypad_InputPins[i]);
        }
    }
}
void pa_Keypad::initOutput() {
    for (int i = 0; i < Keypad_Output_Cnt; i++) {
        GPIO_setAsOutputPin(Keypad_OutputPorts[i], Keypad_OutputPins[i]);
    }
}

//设置行
void pa_Keypad::setOutput(unsigned char index, unsigned char state) {
    if (state) {
        MAP_GPIO_setOutputHighOnPin(Keypad_OutputPorts[index], Keypad_OutputPins[index]);
    }
    else {
        MAP_GPIO_setOutputLowOnPin(Keypad_OutputPorts[index], Keypad_OutputPins[index]);
    }
}
//设置列
unsigned char pa_Keypad::readInput(unsigned char index) {
    return MAP_GPIO_getInputPinValue(Keypad_InputPorts[index], Keypad_InputPins[index]);
}



#endif // MSP432P



#endif