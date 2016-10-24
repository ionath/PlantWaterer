/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MonitorConnections.h
 * Author: osmc
 *
 * Created on 24 October 2016, 19:09
 */

#ifndef MONITORCONNECTIONS_H
#define MONITORCONNECTIONS_H

#include <thread>

#include "NetworkListener.h"

class AdcMcp3202;
class WaterPump;

class MonitorConnections {
public:
	MonitorConnections();
	MonitorConnections(const MonitorConnections& orig);
	MonitorConnections(AdcMcp3202* adcSpi, WaterPump* waterPump, int portNo)
		: m_adcSpi(adcSpi)
		, m_waterPump(waterPump)
	{
		networkListener.SetupSocket(portNo);
	}
	virtual ~MonitorConnections();
	
	void monitorConnections();
	
	void asyncMonitorConnections();
	
private:

	AdcMcp3202* m_adcSpi;
	WaterPump* m_waterPump;
	
	NetworkListener networkListener;
	
	std::thread m_thread;
	
private:
	
	static void staticMonitorConnections(MonitorConnections* self);
};

#endif /* MONITORCONNECTIONS_H */

