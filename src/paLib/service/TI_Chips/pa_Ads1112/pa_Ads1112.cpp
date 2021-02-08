#include "pa_Defines.h"

#include "pa_Ads1112.h"
#include "string.h"
/****************************************************
 * logic 层代码
 * ***************************************************/
pa_Ads1112 pa_Ads1112::instance = pa_Ads1112();

pa_Ads1112::pa_Ads1112() {}

void pa_Ads1112::init(unsigned char A0, unsigned char A1) {
	if (A0 == L && A1 == L) I2C_ADDRESS = 72;
	else if (A0 == L && A1 == F) I2C_ADDRESS = 73;
	else if (A0 == L && A1 == H) I2C_ADDRESS = 74;
	else if (A0 == H && A1 == L) I2C_ADDRESS = 76;
	else if (A0 == H && A1 == F) I2C_ADDRESS = 77;
	else if (A0 == H && A1 == H) I2C_ADDRESS = 78;
	else if (A0 == F && A1 == L) I2C_ADDRESS = 75;
	else if (A0 == F && A1 == H) I2C_ADDRESS = 79;
}

void pa_Ads1112::selectChannel(unsigned char channel, unsigned char gain, unsigned char mode)
{
	unsigned char INP1 = 0, INP0 = 0;

	if (mode == MODE_UNIPOLAR) {
		if (channel == CHANNEL_0) {
			INP1 = 1;
			INP0 = 0;
		}
		else if (channel == CHANNEL_1) {
			INP1 = 1;
			INP0 = 1;
		}
		else if (channel == CHANNEL_2) {
			INP1 = 0;
			INP0 = 1;
		}
	}
	else { //bipolar
		if (channel == CHANNEL_0) {
			INP1 = 0;
			INP0 = 0;
		}
		else if (channel == CHANNEL_1) {
			INP1 = 0;
			INP0 = 1;
		}
	}

	//configuration register, assuming 16 bit resolution
	unsigned char reg = 1 << BIT_ST_DRDY |
		INP1 << BIT_INP1 |
		INP0 << BIT_INP0 |
		1 << BIT_DR1 |
		1 << BIT_DR0 |
		gain;

	// Wire.beginTransmission(I2C_ADDRESS);
	// Wire.write(reg);
	// Wire.endTransmission();
}

double pa_Ads1112::readADC()
{
	// Wire.requestFrom(I2C_ADDRESS, (byte)3);
	int h;
int l;
int r;
	//  h = Wire.read();
	//  l = Wire.read();
	//  r = Wire.read();

	long t = h << 8 | l;

	if (t >= 32768) t -= 65536l;

	double v = (double)t * 2.048 / 32768.0;

	return v;
}