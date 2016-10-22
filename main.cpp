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

#include <thread>
#include <sstream>
#include <string>

#include "WaterPump.h"
#include "AdcMcp3202.h"
#include "BcmInitializer.h"
#include "NetworkListener.h"

template <class T>
std::string ToString(T value)
{
	std::ostringstream ostrm;
	ostrm << value;
	return ostrm.str();
}

class MonitorConnections
{
public:
	MonitorConnections(AdcMcp3202* adcSpi, WaterPump* waterPump, int portNo)
		: m_adcSpi(adcSpi)
		, m_waterPump(waterPump)
	{
		networkListener.SetupSocket(portNo);
	}
		
	void monitorConnections()
	{
		while (1)
		{
			auto networkSession = networkListener.ListenForConnection();
			
			if (networkSession.isValidSocket())
			{
				while (1)
				{
					auto readStr = networkSession.readFromConnection();
					if (readStr == "GET READING")
					{
						auto reading = m_adcSpi->convertToFloat(m_adcSpi->readSpi());
						auto readingStr = std::string("READING ") + ToString(reading);
						networkSession.writeToConnection(readingStr);
					}
					else if (readStr == "PUMP ON")
					{
						m_waterPump->turnOn();
					}
					else if (readStr == "PUMP OFF")
					{
						m_waterPump->turnOff();
					}
				}
			}
		}
	}
	
	void asyncMonitorConnections()
	{
		// Warning! maybe destroying a previous thread
		m_thread = std::thread(staticMonitorConnections, this);
	}
	
private:
	AdcMcp3202* m_adcSpi;
	WaterPump* m_waterPump;
	
	NetworkListener networkListener;
	
	std::thread m_thread;
	
private:
	
	static void staticMonitorConnections(MonitorConnections* self)
	{
		if (self)
		{
			self->monitorConnections();
		}
	}
	
};


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

