#include "pa_ILI9341.h"
#ifdef DISPLAY_USE_ILI9341

pa_ILI9341 pa_ILI9341::instance = pa_ILI9341();

pa_ILI9341::pa_ILI9341()
{
}

void pa_ILI9341::reset()
{
	this->setRST(0);
	// HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_RESET);
	pa_delayMs(200);
	// pa_delayMs(200);
	this->setCS(0);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	pa_delayMs(200);
	// pa_delayMs(200);
	this->setRST(1);
	// HAL_GPIO_WritePin(LCD_RST_PORT, LCD_RST_PIN, GPIO_PIN_SET);
}

void pa_ILI9341::enable()
{
	this->setRST(1);
}

void pa_ILI9341::init(Rotation Rotation)
{
	enable();
	reset();

	//SOFTWARE RESET
	this->writeCommand(0x01);
	pa_delayMs(1000);

	writeCommand(0xEF);
	writeData(0x03);
	writeData(0x80);
	writeData(0x02);

	//POWER CONTROL A
	this->writeCommand(0xCB);
	this->writeData(0x39);
	this->writeData(0x2C);
	this->writeData(0x00);
	this->writeData(0x34);
	this->writeData(0x02);

	//POWER CONTROL B
	this->writeCommand(0xCF);
	this->writeData(0x00);
	this->writeData(0xC1);
	this->writeData(0x30);

	//DRIVER TIMING CONTROL A
	this->writeCommand(0xE8);
	this->writeData(0x85);
	this->writeData(0x00);
	this->writeData(0x78);

	//DRIVER TIMING CONTROL B
	this->writeCommand(0xEA);
	this->writeData(0x00);
	this->writeData(0x00);

	//POWER ON SEQUENCE CONTROL   ok
	this->writeCommand(0xED);
	this->writeData(0x64);
	this->writeData(0x03);
	this->writeData(0x12);
	this->writeData(0x81);

	//PUMP RATIO CONTROL
	this->writeCommand(0xF7);
	this->writeData(0x20);

	//POWER CONTROL,VRH[5:0]
	this->writeCommand(0xC0); //
	this->writeData(0x23);

	//POWER CONTROL,SAP[2:0];BT[3:0]
	this->writeCommand(0xC1); //
	this->writeData(0x10);

	//VCM CONTROL
	this->writeCommand(0xC5); //
	this->writeData(0x3E);
	this->writeData(0x28);

	//VCM CONTROL 2
	this->writeCommand(0xC7); //
	this->writeData(0x86);

	//MEMORY ACCESS CONTROL
	this->writeCommand(0x36);
	this->writeData(0x48);

	//PIXEL FORMAT
	this->writeCommand(0x3A);
	this->writeData(0x55);

	//FRAME RATIO CONTROL, STANDARD RGB COLOR
	this->writeCommand(0xB1);
	this->writeData(0x00);
	this->writeData(0x18);

	//DISPLAY FUNCTION CONTROL
	this->writeCommand(0xB6);
	this->writeData(0x08);
	this->writeData(0x82);
	this->writeData(0x27);

	//3GAMMA FUNCTION DISABLE
	this->writeCommand(0xF2);
	this->writeData(0x00);

	//GAMMA CURVE SELECTED
	this->writeCommand(0x26);
	this->writeData(0x01);

	//POSITIVE GAMMA CORRECTION
	this->writeCommand(0xE0);
	this->writeData(0x0F);
	this->writeData(0x31);
	this->writeData(0x2B);
	this->writeData(0x0C);
	this->writeData(0x0E);
	this->writeData(0x08);
	this->writeData(0x4E);
	this->writeData(0xF1);
	this->writeData(0x37);
	this->writeData(0x07);
	this->writeData(0x10);
	this->writeData(0x03);
	this->writeData(0x0E);
	this->writeData(0x09);
	this->writeData(0x00);

	//NEGATIVE GAMMA CORRECTION
	this->writeCommand(0xE1);
	this->writeData(0x00);
	this->writeData(0x0E);
	this->writeData(0x14);
	this->writeData(0x03);
	this->writeData(0x11);
	this->writeData(0x07);
	this->writeData(0x31);
	this->writeData(0xC1);
	this->writeData(0x48);
	this->writeData(0x08);
	this->writeData(0x0F);
	this->writeData(0x0C);
	this->writeData(0x31);
	this->writeData(0x36);
	this->writeData(0x0F);

	//EXIT SLEEP
	this->writeCommand(0x11);
	pa_delayMs(120);

	//TURN ON DISPLAY
	this->writeCommand(0x29);

	//STARTING ROTATION
	setRotation(Rotation);
}

void pa_ILI9341::flush(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t Colour)
{
	if (x1 < 0)
		x1 = 0;
	if (y1 < 0)
		y1 = 0;
	if (x2 > this->LCD_WIDTH)
		x2 = LCD_WIDTH;
	if (y2 > this->LCD_HEIGHT)
		y2 = LCD_HEIGHT;
	setAddress(x1, y1, x2, y2);
	burst(Colour, (x2 - x1 + 1) * (y2 - y1 + 1));
}

void pa_ILI9341::burst(uint16_t Colour, uint32_t Size)
{
	//SENDS COLOUR
	uint32_t Buffer_Size = 0;
	if ((Size * 2) < BURST_MAX_SIZE)
	{
		Buffer_Size = Size;
	}
	else
	{
		Buffer_Size = BURST_MAX_SIZE;
	}

	setDC(1);
	setCS(0);
	// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);

	unsigned char chifted = Colour >> 8;
	;
	//=new unsigned char[Buffer_Size];
	for (uint32_t j = 0; j < Buffer_Size; j += 2)
	{
		pa_ILI9341_burst_buffer[j] = chifted;
		pa_ILI9341_burst_buffer[j + 1] = Colour;
	}

	uint32_t Sending_Size = Size * 2;
	uint32_t Sending_in_Block = Sending_Size / Buffer_Size;
	uint32_t Remainder_from_block = Sending_Size % Buffer_Size;

	if (Sending_in_Block != 0)
	{
		for (uint32_t j = 0; j < (Sending_in_Block); j++)
		{
			pa_spiTransmit(pa_ILI9341_burst_buffer, Buffer_Size);
			// HAL_SPI_Transmit(HSPI_INSTANCE, (unsigned char *)burst_buffer, Buffer_Size, 10);
		}
	}

	pa_spiTransmit(pa_ILI9341_burst_buffer, Remainder_from_block);
	//REMAINDER!
	// HAL_SPI_Transmit(HSPI_INSTANCE, (unsigned char *)burst_buffer, Remainder_from_block, 10);

	setCS(1);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void pa_ILI9341::writeCommand(uint8_t Command)
{
	this->setCS(0);
	this->setDC(0);
	pa_spiTransmit(&Command, 1);
	this->setCS(1);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET);
	// ILI9341_SPI_Send(Command);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void pa_ILI9341::writeData(uint8_t Command)
{
	this->setDC(1);
	this->setCS(0);
	pa_spiTransmit(&Command, 1);
	this->setCS(1);
	// HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET);
	// ILI9341_SPI_Send(Data);
	// HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET);
}

void pa_ILI9341::setAddress(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2)
{
	if (X1 < 0)
		X1 = 0;
	if (Y1 < 0)
		Y1 = 0;
	if (X2 > this->LCD_WIDTH)
		X2 = LCD_WIDTH;
	if (Y2 > this->LCD_HEIGHT)
		Y2 = LCD_HEIGHT;

	this->writeCommand(0x2A);
	this->writeData(X1 >> 8);
	this->writeData(X1);
	this->writeData(X2 >> 8);
	this->writeData(X2);

	this->writeCommand(0x2B);
	this->writeData(Y1 >> 8);
	this->writeData(Y1);
	this->writeData(Y2 >> 8);
	this->writeData(Y2);

	this->writeCommand(0x2C);
}

void pa_ILI9341::setRotation(Rotation Rotation)
{
	// uint8_t screen_rotation = Rotation;

	this->writeCommand(0x36);
	pa_delayMs(1);

	switch (Rotation)
	{
	case Rotation_VERTICAL_1:
		this->writeData(0x40 | 0x08);
		LCD_WIDTH = 240;
		LCD_HEIGHT = 320;
		break;
	case Rotation_HORIZONTAL_1:
		this->writeData(0x20 | 0x08);
		LCD_WIDTH = 320;
		LCD_HEIGHT = 240;
		break;
	case Rotation_VERTICAL_2:
		this->writeData(0x80 | 0x08);
		LCD_WIDTH = 240;
		LCD_HEIGHT = 320;
		break;
	case Rotation_HORIZONTAL_2:
		this->writeData(0x40 | 0x80 | 0x20 | 0x08);
		LCD_WIDTH = 320;
		LCD_HEIGHT = 240;
		break;
	default:
		//EXIT IF SCREEN ROTATION NOT VALID!
		break;
	}
}

#endif
