#ifndef __PA_MOTOR_H__
#define __PA_MOTOR_H__


extern "C" {
#include "../../drv/pa_CommonDrv.h"

}

class pa_Motor
{
public:
	pa_Motor();
	static pa_Motor instance;

	enum Motor{
		Motor_L,
		Motor_R
	};
	void setSpeed(int in,char dasi,int speed);
	void stop();
	void initHardware();
	void initLinerDetect();
	unsigned char readLinerDetect();
	unsigned char readLinerDetectPin(char index);
	/*void setKeypadCallback(void (*keypadCallback)(unsigned char x, unsigned char y));*/
private:
};

#endif // __PA_MOTOR_H__