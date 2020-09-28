#include "pa_Defines.h"

#ifdef INPUT_USE_TOUCHSCREEN

#include "pa_touchScreen.h"

pa_touchScreen pa_touchScreen::instance = pa_touchScreen();

pa_touchScreen::pa_touchScreen() {}

uint16_t pa_touchScreen::spiRead()
{
	uint8_t buffer[2];
	pa_spiReceive(buffer,2);

	uint16_t data=buffer[0];
	data<<=1;
	data|=buffer[1];
	return data;
}

void pa_touchScreen::spiWrite(uint8_t value)
{
	pa_spiTransmit(&value, 1);
}

uint8_t pa_touchScreen::isPressed()
{
	return !Hardware_ReadIRQ();
}

uint8_t pa_touchScreen::readCoordinates(uint16_t Coordinates[2])
{
	uint32_t avg_x, avg_y = 0;
	uint16_t rawx, rawy = 0;
	uint32_t calculating_x, calculating_y = 0;

	uint32_t samples = config.SampleCount;
	uint32_t counted_samples = 0;
	Hardware_SetCS(0);
	while ((samples > 0) && isPressed())
	{
		spiWrite(CMD_RDY);

		rawy = spiRead();
		avg_y += rawy;
		calculating_y += rawy;

		spiWrite(CMD_RDX);
		rawx = spiRead();
		avg_x += rawx;
		calculating_x += rawx;
		samples--;
		counted_samples++;
	};
	Hardware_SetCS(1);

	if ((counted_samples == config.SampleCount) && isPressed())
	{

		calculating_x /= counted_samples;
		calculating_y /= counted_samples;

		rawx = calculating_x;
		rawy = calculating_y;

		rawx *= -1;
		rawy *= -1;

		//CONVERTING 16bit Value to Screen coordinates
		// 65535/273 = 240!
		// 65535/204 = 320!
		Coordinates[0] = ((240 - (rawx / config.X_TRANSLATION)) - config.X_OFFSET) * config.X_MAGNITUDE;
		Coordinates[1] = ((rawy / config.Y_TRANSLATION) - config.Y_OFFSET) * config.Y_MAGNITUDE;

		return 1;
	}
	else
	{
		Coordinates[0] = 0;
		Coordinates[1] = 0;
		return 0;
	}
}

void pa_touchScreen::init(uint16_t screenWidth, uint16_t screenHeight)
{
	config.X_TRANSLATION = 65535 / screenWidth;
	config.Y_TRANSLATION = 65535 / screenHeight;
	Hardware_Init();
}

#endif