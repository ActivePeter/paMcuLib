#include "Ads_112c04.h"
#include "string.h"
/****************************************************
 * logic 层代码
 * ***************************************************/
Ads_112c04 Ads_112c04::instance = Ads_112c04();

Ads_112c04::Ads_112c04() {}

void Ads_112c04::init(unsigned char A0, unsigned char A1) {
	if (A0 == DGND && A1 == DGND) I2C_ADDRESS = 64;
	else if (A0 == DVDD && A1 == DGND) I2C_ADDRESS = 65;
	else if (A0 == SDA && A1 == DGND) I2C_ADDRESS = 66;
	else if (A0 == SCL && A1 == DGND) I2C_ADDRESS = 67;
	else if (A0 == DGND && A1 == DVDD) I2C_ADDRESS = 68;
	else if (A0 == DVDD && A1 == DVDD) I2C_ADDRESS = 69;
	else if (A0 == SDA && A1 == DVDD) I2C_ADDRESS = 70;
	else if (A0 == SCL && A1 == DVDD) I2C_ADDRESS = 71;
	else if (A0 == DGND && A1 == SDA) I2C_ADDRESS = 72;
	else if (A0 == DVDD && A1 == SDA) I2C_ADDRESS = 73;
	else if (A0 == SDA && A1 == SDA) I2C_ADDRESS = 74;
	else if (A0 == SCL && A1 == SDA) I2C_ADDRESS = 75;
	else if (A0 == DGND && A1 == SCL) I2C_ADDRESS = 76;
	else if (A0 == DVDD && A1 == SCL) I2C_ADDRESS = 77;
	else if (A0 == SDA && A1 == SCL) I2C_ADDRESS = 78;
	else if (A0 == SCL && A1 == SCL) I2C_ADDRESS = 79;
}

void Ads_112c04::configRegister0(unsigned char channel, unsigned char gain, unsigned char mode)
{
	unsigned char INP1 = 0, INP0 = 0;


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

double Ads_112c04::readADC()
{
	unsigned char a;
	pa_IICSettingStruct b;
	pa_IIC_writeLen(I2C_ADDRESS,0x80,0,&a,b);
	pa_IIC_readLen(I2C_ADDRESS,0x80,0,&a,b);
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

void Ads_112c04::reset() 
{
	unsigned char a;
	pa_IICSettingStruct b;
	pa_IIC_writeLen(I2C_ADDRESS,0x06,0,&a,b);
}