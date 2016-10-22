/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NetworkSession.h
 * Author: osmc
 *
 * Created on 22 October 2016, 21:37
 */

#ifndef NETWORKSESSION_H
#define NETWORKSESSION_H

#include <string>

const int INVALID_SOCKET = -1;

class NetworkSession
{
public:
	NetworkSession();
	NetworkSession(int socketFD);
	NetworkSession(NetworkSession&& orig);
	virtual ~NetworkSession();
	
	NetworkSession& operator=(NetworkSession&& orig);
	
	// Do not allow copying. socket FD should only be stored in one place
private:
	NetworkSession(const NetworkSession& orig);
	NetworkSession& operator=(const NetworkSession& orig);
	
	
public:
	
	bool isValidSocket();
	
	std::string readFromConnection();
	void writeToConnection(const std::string& data);
	
	void closeConnection();
	
private:
	int m_clientSocketFD = INVALID_SOCKET;
	
private:
	void error(const char *msg);
	void connectionClosedByClient();
};

#endif /* NETWORKSESSION_H */

