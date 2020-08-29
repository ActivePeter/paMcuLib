#ifndef __Ads_112c04_H__
#define __Ads_112c04_H__
extern "C" {
#include "../../../drv/pa_CommonDrv.h"

}

class Ads_112c04
{
public:
	Ads_112c04();
	static Ads_112c04 instance;
	void init(unsigned char A0, unsigned char A1);
	void configRegister0(unsigned char channel, unsigned char gain, unsigned char mode);
	void configRegister1(unsigned char channel, unsigned char gain, unsigned char mode);
	void configRegister2(unsigned char channel, unsigned char gain, unsigned char mode);
	double readADC();
	void reset();
	//引脚状态
	static const unsigned char DGND = 0;
	static const unsigned char DVDD = 1;
	static const unsigned char SDA = 2;
	static const unsigned char SCL = 3;

	static const unsigned char CHANNEL_0 = 0;
	static const unsigned char CHANNEL_1 = 1;
	static const unsigned char CHANNEL_2 = 2;

	static const unsigned char GAIN_1 = 0;
	static const unsigned char GAIN_2 = 1;
	static const unsigned char GAIN_4 = 2;
	static const unsigned char GAIN_8 = 3;
	static const unsigned char GAIN_16 = 4;
	static const unsigned char GAIN_32 = 5;
	static const unsigned char GAIN_64 = 6;
	static const unsigned char GAIN_128 = 7;

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