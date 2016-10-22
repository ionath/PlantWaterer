/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WaterPump.cpp
 * Author: osmc
 * 
 * Created on 20 October 2016, 15:05
 */

#include "WaterPump.h"

#include <bcm2835.h>

#define PIN_PUMP_PLUS RPI_BPLUS_GPIO_J8_08
#define PIN_PUMP_MINUS RPI_BPLUS_GPIO_J8_07

WaterPump::WaterPump() {
}

WaterPump::WaterPump(const WaterPump& orig) {
}

WaterPump::~WaterPump() {
}

void WaterPump::initGPIO()
{
    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN_PUMP_PLUS, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(PIN_PUMP_MINUS, BCM2835_GPIO_FSEL_OUTP);
	
	// Set pump to off
	bcm2835_gpio_write(PIN_PUMP_PLUS, LOW);
	bcm2835_gpio_write(PIN_PUMP_MINUS, LOW);
}

void WaterPump::turnOn()
{
	// Set pump to on
	bcm2835_gpio_write(PIN_PUMP_PLUS, HIGH);
}

void WaterPump::turnOff()
{
	// Set pump to off
	bcm2835_gpio_write(PIN_PUMP_PLUS, LOW);
}

