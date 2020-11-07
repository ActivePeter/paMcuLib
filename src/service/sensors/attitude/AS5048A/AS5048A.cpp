#include <AS5048A.h>

//#define AS5048A_DEBUG

const int AS5048A_CLEAR_ERROR_FLAG = 0x0001;
const int AS5048A_PROGRAMMING_CONTROL = 0x0003;
const int AS5048A_OTP_REGISTER_ZERO_POS_HIGH = 0x0016;
const int AS5048A_OTP_REGISTER_ZERO_POS_LOW = 0x0017;
const int AS5048A_DIAG_AGC = 0x3FFD;
const int AS5048A_MAGNITUDE = 0x3FFE;
const int AS5048A_ANGLE = 0x3FFF;

/**
 * Constructor
 */
AS5048A::AS5048A(uint8_t arg_cs)
{
	_cs = arg_cs;
	errorFlag = false;
	position = 0;
}

/**
 * Initialiser
 * Sets up the SPI interface
 */
void AS5048A::init()
{
	// 1MHz clock (AMS should be able to accept up to 10MHz)
	settings = SPISettings(1000000, MSBFIRST, SPI_MODE1);

	//setup pins
	pinMode(_cs, OUTPUT);

	//SPI has an internal SPI-device counter, it is possible to call "begin()" from different devices
	SPI.begin();
}

/**
 * Closes the SPI connection
 * SPI has an internal SPI-device counter, for each init()-call the close() function must be called exactly 1 time
 */
void AS5048A::close()
{
	SPI.end();
}

/**
 * Utility function used to calculate even parity of uint16_t
 */
uint8_t AS5048A::spiCalcEvenParity(uint16_t value)
{
	uint8_t cnt = 0;
	uint8_t i;

	for (i = 0; i < 16; i++)
	{
		if (value & 0x1)
		{
			cnt++;
		}
		value >>= 1;
	}
	return cnt & 0x1;
}

/**
 * Get the rotation of the sensor relative to the zero position.
 *
 * @return {int} between -2^13 and 2^13
 */
int AS5048A::getRotation()
{
	uint16_t data;
	int rotation;

	data = AS5048A::getRawRotation();
	rotation = (int)data - (int)position;
	if (rotation > 8191)
		rotation = -((0x3FFF) - rotation); //more than -180
	//if(rotation < -0x1FFF) rotation = rotation+0x3FFF;

	return rotation;
}

/**
 * Returns the raw angle directly from the sensor
 */
uint16_t AS5048A::getRawRotation()
{
	return AS5048A::read(AS5048A_ANGLE);
}

/**
 * returns the value of the state register
 * @return 16 bit uint16_t containing flags
 */
uint16_t AS5048A::getState()
{
	return AS5048A::read(AS5048A_DIAG_AGC);
}

/**
 * Print the diagnostic register of the sensor
 */
void AS5048A::printState()
{
	uint16_t data;

	data = AS5048A::getState();
	if (AS5048A::error())
	{
		Serial.print("Error bit was set!");
	}
	Serial.println(data, BIN);
}

/**
 * Returns the value used for Automatic Gain Control (Part of diagnostic
 * register)
 */
uint8_t AS5048A::getGain()
{
	uint16_t data = AS5048A::getState();
	return (uint8_t)data & 0xFF;
}

/*
 * Get and clear the error register by reading it
 */
uint16_t AS5048A::getErrors()
{
	return AS5048A::read(AS5048A_CLEAR_ERROR_FLAG);
}

/*
 * Set the zero position
 */
void AS5048A::setZeroPosition(uint16_t arg_position)
{
	position = arg_position % 0x3FFF;
}

/*
 * Returns the current zero position
 */
uint16_t AS5048A::getZeroPosition()
{
	return position;
}

/*
 * Check if an error has been encountered.
 */
bool AS5048A::error()
{
	return errorFlag;
}

/*
 * Read a register from the sensor
 * Takes the address of the register as a 16 bit uint16_t
 * Returns the value of the register
 */
uint16_t AS5048A::read(uint16_t registerAddress)
{
	uint16_t command = 0b0100000000000000; // PAR=0 R/W=R
	command = command | registerAddress;

	//Add a parity bit on the the MSB
	command |= ((uint16_t)spiCalcEvenParity(command) << 15);

	//Split the command into two uint8_ts
	uint8_t right_uint8_t = command & 0xFF;
	uint8_t left_uint8_t = (command >> 8) & 0xFF;

#ifdef AS5048A_DEBUG
	Serial.print("Read (0x");
	Serial.print(registerAddress, HEX);
	Serial.print(") with command: 0b");
	Serial.println(command, BIN);
#endif

	//SPI - begin transaction
	SPI.beginTransaction(settings);

	//Send the command
	digitalWrite(_cs, LOW);
	SPI.transfer(left_uint8_t);
	SPI.transfer(right_uint8_t);
	digitalWrite(_cs, HIGH);

	//Now read the response
	digitalWrite(_cs, LOW);
	left_uint8_t = SPI.transfer(0x00);
	right_uint8_t = SPI.transfer(0x00);
	digitalWrite(_cs, HIGH);

	//SPI - end transaction
	SPI.endTransaction();

#ifdef AS5048A_DEBUG
	Serial.print("Read returned: ");
	Serial.print(left_uint8_t, BIN);
	Serial.print(" ");
	Serial.println(right_uint8_t, BIN);
#endif

	//Check if the error bit is set
	if (left_uint8_t & 0x40)
	{
#ifdef AS5048A_DEBUG
		Serial.println("Setting error bit");
#endif
		errorFlag = true;
	}
	else
	{
		errorFlag = false;
	}

	//Return the data, stripping the parity and error bits
	return (((left_uint8_t & 0xFF) << 8) | (right_uint8_t & 0xFF)) & ~0xC000;
}

/*
 * Write to a register
 * Takes the 16-bit  address of the target register and the 16 bit uint16_t of data
 * to be written to that register
 * Returns the value of the register after the write has been performed. This
 * is read back from the sensor to ensure a sucessful write.
 */
uint16_t AS5048A::write(uint16_t registerAddress, uint16_t data)
{

	uint16_t command = 0b0000000000000000; // PAR=0 R/W=W
	command |= registerAddress;

	//Add a parity bit on the the MSB
	command |= ((uint16_t)spiCalcEvenParity(command) << 15);

	//Split the command into two uint8_ts
	uint8_t right_uint8_t = command & 0xFF;
	uint8_t left_uint8_t = (command >> 8) & 0xFF;

#ifdef AS5048A_DEBUG
	Serial.print("Write (0x");
	Serial.print(registerAddress, HEX);
	Serial.print(") with command: 0b");
	Serial.println(command, BIN);
#endif

	//SPI - begin transaction
	SPI.beginTransaction(settings);

	//Start the write command with the target address
	digitalWrite(_cs, LOW);
	SPI.transfer(left_uint8_t);
	SPI.transfer(right_uint8_t);
	digitalWrite(_cs, HIGH);

	uint16_t dataToSend = 0b0000000000000000;
	dataToSend |= data;

	//Craft another packet including the data and parity
	dataToSend |= ((uint16_t)spiCalcEvenParity(dataToSend) << 15);
	right_uint8_t = dataToSend & 0xFF;
	left_uint8_t = (dataToSend >> 8) & 0xFF;

#ifdef AS5048A_DEBUG
	Serial.print("Sending data to write: ");
	Serial.println(dataToSend, BIN);
#endif

	//Now send the data packet
	digitalWrite(_cs, LOW);
	SPI.transfer(left_uint8_t);
	SPI.transfer(right_uint8_t);
	digitalWrite(_cs, HIGH);

	//Send a NOP to get the new data in the register
	digitalWrite(_cs, LOW);
	left_uint8_t = -SPI.transfer(0x00);
	right_uint8_t = SPI.transfer(0x00);
	digitalWrite(_cs, HIGH);

	//SPI - end transaction
	SPI.endTransaction();

	//Return the data, stripping the parity and error bits
	return (((left_uint8_t & 0xFF) << 8) | (right_uint8_t & 0xFF)) & ~0xC000;
}
