/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NetworkSession.cpp
 * Author: osmc
 * 
 * Created on 22 October 2016, 21:37
 */

#include "NetworkSession.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <cassert>

NetworkSession::NetworkSession()
{
}

NetworkSession::NetworkSession(int socketFD)
{
	m_clientSocketFD = socketFD;
}

NetworkSession::NetworkSession(NetworkSession&& orig)
{
	*this = orig;
}

NetworkSession::~NetworkSession() 
{
	closeConnection();
}

NetworkSession& NetworkSession::operator=(NetworkSession&& orig)
{
	m_clientSocketFD = orig.m_clientSocketFD;
}

NetworkSession::NetworkSession(const NetworkSession& orig)
{
	assert(0);
}

NetworkSession& NetworkSession::operator=(const NetworkSession& orig)
{
	assert(0);
}

bool NetworkSession::isValidSocket()
{
	return m_clientSocketFD != INVALID_SOCKET;
}

std::string NetworkSession::readFromConnection()
{
	const size_t BUFFER_SIZE = 256;
	char buffer[BUFFER_SIZE];
	bzero(buffer,BUFFER_SIZE);
	int n = read(m_clientSocketFD, buffer, BUFFER_SIZE-1);
	if (n == 0)
	{
		// Connection closed
		connectionClosedByClient();
	}
	if (n < 0)
	{
		error("ERROR reading from socket");
	}
	
	return std::string(buffer);
}

void NetworkSession::writeToConnection(const std::string& data)
{
	int n = write(m_clientSocketFD, data.c_str(), data.length());
	if (n == 0)
	{
		// Connection closed
		connectionClosedByClient();
	}
	if (n < 0)
	{
		error("ERROR writing to socket");
	}
}

void NetworkSession::closeConnection()
{
	if (isValidSocket())
	{
		close(m_clientSocketFD);
		m_clientSocketFD = INVALID_SOCKET;
	}
}

void NetworkSession::error(const char *msg)
{
	
}
void NetworkSession::connectionClosedByClient()
{
	
}
