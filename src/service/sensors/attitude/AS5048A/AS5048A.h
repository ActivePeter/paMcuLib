#ifndef __AS5048A_H__
#define __AS5048A_H__

#include "pa_CommonLib/src/drv/pa_CommonDrv/pa_CommonDrv.h"

class AS5048A
{

	bool errorFlag;
	uint8_t dout;
	uint8_t din;
	uint8_t clk;
	uint16_t position;
	uint16_t transaction(uint16_t data);

public:
	/**
	 *	Constructor
	 */
	AS5048A();

	/**
	 * Initialiser
	 * Sets up the SPI interface
	 */
	void init(uint8_t id);

	/**
	 * Closes the SPI connection
	 */
	void close();

	/*
	 * Read a register from the sensor
	 * Takes the address of the register as a 16 bit uint16_t
	 * Returns the value of the register
	 */
	uint16_t read(uint16_t registerAddress);

	/*
	 * Write to a register
	 * Takes the 16-bit  address of the target register and the 16 bit uint16_t of data
	 * to be written to that register
	 * Returns the value of the register after the write has been performed. This
	 * is read back from the sensor to ensure a sucessful write.
	 */
	// uint16_t write(uint16_t registerAddress, uint16_t data);

	/**
	 * Get the rotation of the sensor relative to the zero position.
	 *
	 * @return {int} between -2^13 and 2^13
	 */
	int getRotation();

	/**
	 * Returns the raw angle directly from the sensor
	 */
	uint16_t getRawRotation();

	/**
	 * returns the value of the state register
	 * @return 16 bit uint16_t containing flags
	 */
	uint16_t getState();

	/**
	 * Print the diagnostic register of the sensor
	 */
	void printState();

	/**
	 * Returns the value used for Automatic Gain Control (Part of diagnostic
	 * register)
	 */
	uint8_t getGain();

	/*
	 * Get and clear the error register by reading it
	 */
	uint16_t getErrors();

	/*
	 * Set the zero position
	 */
	void setZeroPosition(uint16_t arg_position);

	/*
	 * Returns the current zero position
	 */
	uint16_t getZeroPosition();

	/*
	 * Check if an error has been encountered.
	 */
	bool error();
	//硬件层////////////////////////////////////////////////////////////////////////////////////
	void Hardware_init();

	void setCS(char state);

private:
	uint8_t spiCalcEvenParity(uint16_t);
	uint8_t id;
};

#endif // __AS5048A_H__