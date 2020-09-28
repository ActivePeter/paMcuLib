#include "pa_Defines.h"

#ifdef INPUT_USE_KEYPAD

#ifndef __pa_Keypad_H__
#define __pa_Keypad_H__
extern "C" {
#include "../../../drv/pa_CommonDrv/pa_CommonDrv.h"

}
// #include "pa_Keypad_drv.h"

class pa_Keypad
{
public:
	pa_Keypad();
	static pa_Keypad instance;
	void init(GpioInputMode mode);
	void loop();
	void (*keypadCallback)(unsigned char x, unsigned char y);
	/*void setKeypadCallback(void (*keypadCallback)(unsigned char x, unsigned char y));*/
private:
	char Keypad_Output_Cnt =4;
	char Keypad_Input_Cnt =4;
	short Keypad_Trig_Cnt =100; //修改这个来调整按键灵敏度

	void hardwareInit();
	void initInput();
	void initOutput();
	void setOutput(unsigned char index, unsigned char state);
	unsigned char readInput(unsigned char index);
	bool isPullup;
	unsigned char keyStateArr[Keypad_Output_Cnt][Keypad_Input_Cnt];
};

#endif
#endif