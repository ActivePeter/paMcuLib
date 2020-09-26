#include "pa_CommonLib/src/pa_Defines.h"

#include "../Ads_112c04.h"

#ifdef TM4C123G
uint32_t Ads_112c04_getPinOrPortByAdd(GpioPortOrPin pop, char add)
{
	switch (add)
	{
	case 64:
		switch (pop)
		{
		case GpioPortOrPin::GpioPortOrPin_Pin:
			return GPIO_PIN_7;
		case GpioPortOrPin::GpioPortOrPin_Port:
			return GPIO_PORTC_BASE;
		}
	}
	return 0;
}
void Ads_112c04::initHardware()
{
	uint32_t port = Ads_112c04_getPinOrPortByAdd(GpioPortOrPin_Port, this->I2C_ADDRESS);
	uint32_t pin = Ads_112c04_getPinOrPortByAdd(GpioPortOrPin_Pin, this->I2C_ADDRESS);
	uint32_t sysctl = getSyscylOfGpioPort(port);
	SysCtlPeripheralEnable(sysctl);
	while (!SysCtlPeripheralReady(sysctl))
		; //等待时钟开启
	GPIOPinTypeGPIOInput(port, pin);
	SysCtlPeripheralEnable(sysctl);
	while (!SysCtlPeripheralReady(sysctl))
		; //等待时钟开启
	GPIOPinTypeGPIOInput(port, pin);
}

char Ads_112c04::getDrdyState()
{
	uint32_t port = Ads_112c04_getPinOrPortByAdd(GpioPortOrPin_Port, this->I2C_ADDRESS);
	uint32_t pin = Ads_112c04_getPinOrPortByAdd(GpioPortOrPin_Pin, this->I2C_ADDRESS);
	return GPIOPinRead(port,pin)>0;
}
#endif