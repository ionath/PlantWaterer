/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BcmInitializer.h
 * Author: osmc
 *
 * Created on 21 October 2016, 14:49
 */

#ifndef BCMINITIALIZER_H
#define BCMINITIALIZER_H

class BcmInitializer {
public:
	BcmInitializer();
	BcmInitializer(const BcmInitializer& orig);
	virtual ~BcmInitializer();
private:

	void init();
	void close();
	
	static bool m_initialized;
	static int m_instanceCount;
};

#endif /* BCMINITIALIZER_H */

