/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MonitorConnections.cpp
 * Author: osmc
 * 
 * Created on 24 October 2016, 19:09
 */

#include "MonitorConnections.h"

#include "ToString.h"
#include "AdcMcp3202.h"
#include "WaterPump.h"

MonitorConnections::MonitorConnections() {
}

MonitorConnections::MonitorConnections(const MonitorConnections& orig) {
}

MonitorConnections::~MonitorConnections() {
}

void MonitorConnections::monitorConnections()
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

void MonitorConnections::asyncMonitorConnections()
{
	// Warning! maybe destroying a previous thread
	m_thread = std::thread(staticMonitorConnections, this);
}

void MonitorConnections::staticMonitorConnections(MonitorConnections* self)
{
	if (self)
	{
		self->monitorConnections();
	}
}