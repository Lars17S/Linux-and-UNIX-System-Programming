#pragma once
#include "TcpListener.h"

class MultiClientChat : public TcpListener {
public:
	MultiClientChat(const char* ipAddress, int port) :
		TcpListener(ipAddress, port) { }

protected:
	void onClientConnected(int clientSocket);
	void onClientDisconnected(int clientSocket);
	void onMessageReceived(int clientSocket, const char* msg, int length);
};