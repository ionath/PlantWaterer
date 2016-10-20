/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   WaterPump.h
 * Author: osmc
 *
 * Created on 20 October 2016, 15:05
 */

#ifndef WATERPUMP_H
#define WATERPUMP_H

class WaterPump {
public:
	WaterPump();
	WaterPump(const WaterPump& orig);
	virtual ~WaterPump();
	
	void initGPIO();
	
	void turnOn();
	void turnOff();
	
private:

};

#endif /* WATERPUMP_H */

