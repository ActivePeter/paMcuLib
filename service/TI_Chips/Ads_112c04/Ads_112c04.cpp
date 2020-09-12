#include "Ads_112c04.h"
#include "string.h"
/****************************************************
 * logic 层代码
 * ***************************************************/
Ads_112c04 Ads_112c04::instance = Ads_112c04();

Ads_112c04::Ads_112c04() {}
/** 
 * @brief 初始化ads112c04
 * @param A0_A1_   用于选择设备地址，手动接，需要与实际相符
 */
void Ads_112c04::init(AxState A0, AxState A1) {
	I2C_ADDRESS = 64+A0+A1<<2;
	// if (A0 == DGND && A1 == DGND) 
	// else if (A0 == DVDD && A1 == DGND) I2C_ADDRESS = 65;
	// else if (A0 == SDA && A1 == DGND) I2C_ADDRESS = 66;
	// else if (A0 == SCL && A1 == DGND) I2C_ADDRESS = 67;
	// else if (A0 == DGND && A1 == DVDD) I2C_ADDRESS = 68;
	// else if (A0 == DVDD && A1 == DVDD) I2C_ADDRESS = 69;
	// else if (A0 == SDA && A1 == DVDD) I2C_ADDRESS = 70;
	// else if (A0 == SCL && A1 == DVDD) I2C_ADDRESS = 71;
	// else if (A0 == DGND && A1 == SDA) I2C_ADDRESS = 72;
	// else if (A0 == DVDD && A1 == SDA) I2C_ADDRESS = 73;
	// else if (A0 == SDA && A1 == SDA) I2C_ADDRESS = 74;
	// else if (A0 == SCL && A1 == SDA) I2C_ADDRESS = 75;
	// else if (A0 == DGND && A1 == SCL) I2C_ADDRESS = 76;
	// else if (A0 == DVDD && A1 == SCL) I2C_ADDRESS = 77;
	// else if (A0 == SDA && A1 == SCL) I2C_ADDRESS = 78;
	// else if (A0 == SCL && A1 == SCL) I2C_ADDRESS = 79;
}
/** 
 * @brief 配置ads112c04寄存器0
 * @param gain   增益
 */
void Ads_112c04::configRegister0(Gain gain)
{
	
	//configuration register, assuming 16 bit resolution
	unsigned char reg = 0 ;
	reg|=gain<<1;
	pa_IICSettingStruct a;
	pa_IIC_writeLen(I2C_ADDRESS,reg,0,0,a);
	// Wire.beginTransmission(I2C_ADDRESS);
	// Wire.write(reg);
	// Wire.endTransmission();
}


/** 
 * @brief 配置ads112c04寄存器1
 * @param speedOfSample   采样速率
 * @param mode 模式：速度是否翻倍  
 * @param convMode 转换模式  
 */
void Ads_112c04::configRegister1(SpeedOfSample speedOfSample, Mode mode, ConvMode convMode) 
{
	unsigned char reg = 0 ;
	reg|=speedOfSample<<5|mode<<4|convMode<<3;
	pa_IICSettingStruct a;
	
	pa_IIC_writeLen(I2C_ADDRESS,reg,0,0,a);
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