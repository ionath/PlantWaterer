/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BcmInitializer.cpp
 * Author: osmc
 * 
 * Created on 21 October 2016, 14:49
 */

#include <bcm2835.h>

#include "BcmInitializer.h"

bool BcmInitializer::m_initialized = false;
int BcmInitializer::m_instanceCount = 0;

BcmInitializer::BcmInitializer() {
	init();
}

BcmInitializer::BcmInitializer(const BcmInitializer& orig) {
	init();
}

BcmInitializer::~BcmInitializer() {
	close();
}

void BcmInitializer::init()
{
	m_instanceCount++;
	if (m_initialized == false)
	{
		if (!bcm2835_init())
		{
			// Error! Not running as root?
			return;
		}
		m_initialized = true;
	}
}

void BcmInitializer::close()
{
	m_instanceCount--;
	if (m_instanceCount <= 0 && m_initialized)
	{
		if (!bcm2835_close())
		{
			// Error closing bcm
		}
		m_initialized = false;
	}
}