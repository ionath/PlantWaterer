/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AdcMcp3202.h
 * Author: osmc
 *
 * Created on 21 October 2016, 13:00
 */

#ifndef ADCMCP3202_H
#define ADCMCP3202_H

class AdcMcp3202 {
public:
	static const int MAX_VALUE = 0xfff;
	
public:
	AdcMcp3202();
	AdcMcp3202(const AdcMcp3202& orig);
	virtual ~AdcMcp3202();
	
	int readSpi();
	float convertToFloat(int value);
	
private:
	char sendBytes[3];
	
	void init();
};

#endif /* ADCMCP3202_H */

