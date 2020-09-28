#include "pa_Defines.h"

#ifdef INPUT_USE_KEYPAD

#include "../pa_Keypad.h"

/****************************************************
 * driver 层代码
 * ***************************************************/

#ifdef STM32_H7

//初始化引脚
void pa_Keypad::hardwareInit()
{
}

void pa_Keypad::initInput()
{
}
void pa_Keypad::initOutput()
{
}

//设置行
void pa_Keypad::setOutput(unsigned char index, unsigned char state)
{
}
//设置列
unsigned char pa_Keypad::readInput(unsigned char index)
{
}

#endif // MSP432P
#endif