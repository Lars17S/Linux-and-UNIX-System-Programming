#include "MultiClientChat.h"
#include <string>

void MultiClientChat::onClientConnected(int clientSocket) {
	std::string msg = "Welcome to the chat server!\r\n";
	sendToClient(clientSocket, msg.c_str(), msg.size() + 1);
}

void MultiClientChat::onClientDisconnected(int clientSocket) {

}

// TODO: Fix the error of the "CLIENT" message sent twice
void MultiClientChat::onMessageReceived(int clientSocket, const char* msg, int length) {
	broadcastToClients(clientSocket, msg, length);
}