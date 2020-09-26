#include "pa_CommonLib/src/pa_Defines.h"

#ifndef __pa_Ads1112_H__
#define __pa_Ads1112_H__
extern "C" {
#include "../../../drv/pa_CommonDrv.h"

}

class pa_Ads1112
{
public:
	pa_Ads1112();
	static pa_Ads1112 instance;
	void init(unsigned char A0, unsigned char A1);
	void selectChannel(unsigned char channel, unsigned char gain, unsigned char mode);
	double readADC();
	//引脚状态
	static const unsigned char L = 0;
	static const unsigned char H = 1;
	static const unsigned char F = 2;

	//模式
	static const unsigned char MODE_UNIPOLAR = 0;//单端
	static const unsigned char MODE_BIPOLAR = 1;//差分

	static const unsigned char CHANNEL_0 = 0;
	static const unsigned char CHANNEL_1 = 1;
	static const unsigned char CHANNEL_2 = 2;

	static const unsigned char GAIN_1 = 0;
	static const unsigned char GAIN_2 = 1;
	static const unsigned char GAIN_4 = 2;
	static const unsigned char GAIN_8 = 3;

	/*void setKeypadCallback(void (*keypadCallback)(unsigned char x, unsigned char y));*/
private:
	static const unsigned char BIT_ST_DRDY = 7; //data ready
	static const unsigned char BIT_INP1 = 6; //input channel select
	static const unsigned char BIT_INP0 = 5; //input channel select
	static const unsigned char BIT_SC = 4; //conversion mode (single/continuous)
	static const unsigned char BIT_DR1 = 3; //data rate
	static const unsigned char BIT_DR0 = 2; //data rate
	static const unsigned char BIT_PGA1 = 1; //gain
	static const unsigned char BIT_PGA0 = 0; //gain

	char I2C_ADDRESS;
};

#endif