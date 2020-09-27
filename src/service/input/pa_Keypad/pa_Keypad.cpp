#include "pa_Defines.h"

#ifdef INPUT_USE_KEYPAD
#include "pa_Keypad.h"
#include "string.h"
/****************************************************
 * logic 层代码
 * ***************************************************/
pa_Keypad pa_Keypad::instance = pa_Keypad();

pa_Keypad::pa_Keypad() {

}

void pa_Keypad::init(GpioInputMode mode) {
	memset(keyStateArr,0,sizeof(keyStateArr));
	//this->callback = callback;
	isPullup = (mode == GpioInputMode_pullup);
	hardwareInit();
	if (isPullup) {
		for (int i = 0; i < Keypad_Output_Cnt; i++) {
			setOutput(i, 1);
		}
	}
	else {
		for (int i = 0; i < Keypad_Output_Cnt; i++) {

			setOutput(i, 0);
		}
	}
}
void pa_Keypad::loop() {
	if (isPullup) {
		for (int i = 0; i < Keypad_Output_Cnt; i++) {
			setOutput(i, 0);
			for (int j = 0; j < Keypad_Input_Cnt; j++) {
				if (!readInput(j)) {
					if (keyStateArr[i][j] < 200) {
						keyStateArr[i][j]++;
					}
					if (keyStateArr[i][j] == Keypad_Trig_Cnt) {
						this->keypadCallback(i, j);
						//this->callback(i, j);
					}
				}
				else {
					keyStateArr[i][j] = 0;
				}
			}
			setOutput(i, 1);
		}
	}
	else {
		for (int i = 0; i < Keypad_Output_Cnt; i++) {
			setOutput(i, 1);
			for (int j = 0; j < Keypad_Input_Cnt; j++) {
				if (readInput(j)) {
					if (keyStateArr[i][j] < 200) {
						keyStateArr[i][j]++;
					}
					if (keyStateArr[i][j] == Keypad_Trig_Cnt) {
						//this->callback(i, j);
						this->keypadCallback(i, j);
					}
				}
				else {
					keyStateArr[i][j] = 0;
				}
			}
			setOutput(i, 0);
		}
	}
}

#endif
