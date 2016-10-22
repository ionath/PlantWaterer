/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NetworkListener.cpp
 * Author: osmc
 * 
 * Created on 22 October 2016, 21:37
 */

#include "NetworkListener.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

NetworkListener::NetworkListener() {
}

NetworkListener::NetworkListener(const NetworkListener& orig) {
}

NetworkListener::~NetworkListener() {
}

void NetworkListener::SetupSocket(int portNo)
{
	struct sockaddr_in serverAddr;
	
	m_listenSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	if (m_listenSocketFD < 0)
	{
	   error("ERROR opening socket");
	}

	bzero((char *) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(portNo);
	if (bind(m_listenSocketFD, (struct sockaddr *) &serverAddr,
			 sizeof(serverAddr)) < 0) 
	{
		error("ERROR on binding");
	}
}

NetworkSession NetworkListener::ListenForConnection()
{
	struct sockaddr_in clientAddr;
	
	listen(m_listenSocketFD, 5);
	socklen_t clientLen = sizeof(clientAddr);
	int clientSocketFD = accept(m_listenSocketFD, 
				(struct sockaddr *) &clientAddr, 
				&clientLen);
	if (clientSocketFD < 0)
	{
		error("ERROR on accept");
	}
	
	return NetworkSession(clientSocketFD);
}

void NetworkListener::CloseSocket()
{
	close(m_listenSocketFD);
}

void NetworkListener::error(const char *msg)
{
	
}
