#pragma once

#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")

// NOTE: A class is abstract if it has at least one pure virtual function.
class TcpListener {

public:
	TcpListener(const char* ipAddress, int port) :
		m_ipAddress(ipAddress), m_port(port) { }

	// Initialize the listener (it is a process, returns a state process)
	int init();

	// Run the listener (it is a process, returns a state process)
	int run();

protected:
	 
	// NOTE: What is virtual function?
	/* A virtual function a member function which is declared within a base 
	class and is re-defined(Overriden) by a derived class */
	
	// Handler for client connections
	virtual void onClientConnected(int clientSocket) = 0;

	// Handler for client disconnections
	virtual void onClientDisconnected(int clientSocket) = 0;

	// Handler for when a message is received from the client
	virtual void onMessageReceived(int clientSocket, const char* msg, int length) = 0;

	// Send a message to a client
	int sendToClient(int clientSocket, const char* msg, int length);

	// Broadcast a message from a client
	void broadcastToClients(int sendingClient, const char* msg, int length);

	// Handler to send error message to client
	void sendErrorString(int& sendingClient);

private:

	const char* m_ipAddress;	// IP Adress server will run on
	int m_port;					// Port # for the web service
	int m_socket;				// Internal FD for the listening socket
	// NOTE: What is a file descriptor?
	/* A file descriptor is a positive integer assigned to identify each file
	opened by a process in Linux operating system. It comes from the convention
	that everything in Linux is a file. It is a low level kernel variable for Linux
	operating system. So this idea comes from UNIX and related computer OS. */
	fd_set m_master;			// Master file descriptor set

};