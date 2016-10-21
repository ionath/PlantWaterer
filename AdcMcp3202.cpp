/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AdcMcp3202.cpp
 * Author: osmc
 * 
 * Created on 21 October 2016, 13:00
 */

#include <bcm2835.h>

#include "AdcMcp3202.h"

AdcMcp3202::AdcMcp3202() {
	init();
}

AdcMcp3202::AdcMcp3202(const AdcMcp3202& orig) {
}

AdcMcp3202::~AdcMcp3202() {
}

int AdcMcp3202::readSpi()
{
	// Start spi session
	auto result = bcm2835_spi_begin();
	
	// Set the clock speed
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_1024);
	
	// Set the data mode to 0,0. Clock idles in the low state
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	
	// Set chip select to channel 0
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	
	// Set chip select on channel 0 to be active on LOW signal
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
	
	char rxBytes[3];
	// Transfer bytes and read back received data
	bcm2835_spi_transfernb(sendBytes, rxBytes, 3);
	
	// Convert bits to single integer
	int reading = ((int)rxBytes[1] << 8) | ((int)rxBytes[2]);
	
	// Shutdown SPI once finished
	bcm2835_spi_end();
	
	return reading;
}

float AdcMcp3202::convertToFloat(int value)
{
	return (float)value/MAX_VALUE;
}

void AdcMcp3202::init()
{
	// start bit is HIGH to start signify start bit
	uint8_t startBit = 1;
	// Set HIGH for single ended mode
	uint8_t sigDiff = 1;
	// Set LOW for ADC channel 0
	uint8_t oddSign = 0;
	// Set HIGH for MSB first.
	uint8_t msbf = 1;
	
	uint8_t configBits = (sigDiff<<7) | (oddSign<<6) | (msbf<<5);
	
	sendBytes[0] = startBit;
	sendBytes[1] = configBits;
	sendBytes[2] = 0x0;
}