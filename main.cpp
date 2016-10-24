/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: osmc
 *
 * Created on 20 October 2016, 15:04
 */

#include <cstdlib>
#include <iostream>

#include "WaterPump.h"
#include "AdcMcp3202.h"
#include "BcmInitializer.h"
#include "NetworkListener.h"
#include "MonitorConnections.h"

/*
 * 
 */
int main(int argc, char** argv)
{
	// Enable bcm for the life of main function
	BcmInitializer bcm;
	
	AdcMcp3202 adcSpi;
	
	WaterPump waterPump;
	waterPump.initGPIO();
	
	// Run monitorConnections in a different thread
	MonitorConnections monitorConnections(&adcSpi, &waterPump, 27015);
	monitorConnections.asyncMonitorConnections();
	
	while (1)
	{
		std::cout << "r\tTake reading " << "\r\n"
				<< "1\tTurn Pump On " << "\r\n" 
				<< "2\tTurn Pump Off" << "\r\n" 
				<< "x\tExit" << "\r\n";
		char input = 0;
		std::cin.get(input);
		if (input == 'r')
		{
			float result = adcSpi.convertToFloat(adcSpi.readSpi());
			
			std::cout << "Reading: " << result << "\r\n";
		}
		else if (input == '1')
		{
			waterPump.turnOn();
		}
		else if (input == '2')
		{
			waterPump.turnOff();
		}
		else if (input == 'x')
		{
			break;
		}
	}
	
	return 0;
}

