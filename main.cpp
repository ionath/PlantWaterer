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

/*
 * 
 */
int main(int argc, char** argv)
{
	WaterPump waterPump;
	waterPump.initGPIO();
	
	while (1)
	{
		std::cout << "1\tTurn On " << "\r\n" 
				<< "2\tTurn Off" << "\r\n";
		char input = 0;
		std::cin.get(input);
		if (input == '1')
		{
			waterPump.turnOn();
		}
		else if (input == '2')
		{
			waterPump.turnOff();
		}
	}
	
	return 0;
}

