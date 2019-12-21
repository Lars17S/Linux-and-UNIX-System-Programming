#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "WebServer.h"


//	Handler for when a message is received from the client
void WebServer::onMessageReceived(int clientSocket, const char* msg, int length) {
	// GET /index.html HTTP/1.1

	//	Parse out the document requested
	//	Open the document in the local file system
	//	Write the document back to the client
	std::ifstream f(".\\wwwroot\\index.html");
	std::string content;
	if (f.good()) {
		std::string str((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
		content = str;
	}
	else
		content = "<h1>404 Not Found</h1>";
	f.close();

	std::ostringstream oss;
	// Server response when a TCP connection is successful 
	// Response format
	oss << "HTTP/1.1 200 OK\r\n";
	oss << "Cache-Control: no-cache, private\r\n";
	oss << "Content-Type: text/html\r\n";
	oss << "Content-Length: " << content.size() << "\r\n";
	oss << "\r\n";
	oss << content;

	std::string output = oss.str();
	int size = output.size() + 1;

	sendToClient(clientSocket, output.c_str(), size);
}


//	Handler for client connections
void WebServer::onClientConnected(int clientSocket) {
	 
}

//	Handler for client disconnections
void WebServer::onClientDisconnected(int clientSocket) {

}