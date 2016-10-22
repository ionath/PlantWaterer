/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NetworkListener.h
 * Author: osmc
 *
 * Created on 22 October 2016, 21:37
 */

#ifndef NETWORKLISTENER_H
#define NETWORKLISTENER_H

#include "NetworkSession.h"

class NetworkListener {
public:
	NetworkListener();
	NetworkListener(const NetworkListener& orig);
	virtual ~NetworkListener();
	
	void SetupSocket(int portNo);
	NetworkSession ListenForConnection();
	
	void CloseSocket();
	
private:
	// File descriptor for server socket
	int m_listenSocketFD;

private:
	void error(const char *msg);
};

#endif /* NETWORKLISTENER_H */

