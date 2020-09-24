#ifndef __pa_Keypad_H__
#define __pa_Keypad_H__
extern "C" {
#include "../../drv/pa_CommonDrv.h"

}
#include "pa_Keypad_drv.h"

class pa_Keypad
{
public:
	pa_Keypad();
	static pa_Keypad instance;
	void init(GpioInputMode mode);
	void loop();
	void (*keypadCallback)(unsigned char x, unsigned char y);
	void (*keypadLongCallback)(unsigned char x, unsigned char y);
	/*void setKeypadCallback(void (*keypadCallback)(unsigned char x, unsigned char y));*/
private:
	void hardwareInit();
	void initInput();
	void initOutput();
	void setOutput(unsigned char index, unsigned char state);
	unsigned char readInput(unsigned char index);
	bool isPullup;
	unsigned int keyStateArr[Keypad_Output_Cnt][Keypad_Input_Cnt];
};

#endif