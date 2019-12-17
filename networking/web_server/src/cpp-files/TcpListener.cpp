#include "TcpListener.h"

/* Windows Sockets API (WSA), later shortened to Winsock, is a technical 
specification that defines how Windows network software should access 
network services, especially TCP/IP. */

int TcpListener::init() {
	// Initialize winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0) {
		return wsOk;
	}

	// Create a socket
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET) {
		/* The WSAGetLastError function returns the error status for the last Windows 
		Sockets operation that failed. */
		return WSAGetLastError();
	}

	// Bind the ip address and port to a socket
	sockaddr_in sock_addr;
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_port = htons(m_port);
	inet_pton(AF_INET, m_ipAddress, &sock_addr.sin_addr);
	if (bind(m_socket, (sockaddr*)&sock_addr, sizeof(sock_addr)) == SOCKET_ERROR)
		return WSAGetLastError();

	// Tell winsock the socket is for listening
	if (listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
		return WSAGetLastError();

	// Create the master file descriptor set and zero it
	FD_ZERO(&m_master);
	FD_SET(m_socket, &m_master);

	// Return zero means that the process closed succesfully
	return 0;
}

int TcpListener::run() {
	bool running = true;
	while (running) {
		fd_set copy = m_master;
		// NOTE: What is select?
		/* The select() function indicates which of the specified file descriptors is ready 
		for reading, ready for writing, or has an error condition pending. If the specified 
		condition is false for all of the specified file descriptors, select() blocks, up to 
		the specified timeout interval, until the specified condition is true for at least one 
		of the specified file descriptors or until a signal arrives that needs to be delivered. */
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		/* The select function blocks the calling process until there is activity on any
		of the specified sets of file descriptors, or until the timeout period has expired. */
		// Read https://www.gnu.org/software/libc/manual/html_node/Waiting-for-I_002fO.html
		// Loop through all the current connections / potential connections
		for (int i = 0; i < socketCount; i++) {
			SOCKET sock = copy.fd_array[i];
			// Check if it is an inbound communication
			if (sock == m_socket) {
				// Accept a new connection
				int client = accept(m_socket, nullptr, nullptr);

				// Add the new connection to the list of connected clients
				FD_SET(client, &m_master);
				onClientConnected(client);
			}
			else {
				char buf[4096];
				// ZeroMemory fills a block of memory with zeros.
				ZeroMemory(buf, 4096);

				// Receive message. bytesIn is a file descriptor
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0) {
					// Drop the client
					onClientDisconnected(sock);
					closesocket(sock);
					FD_CLR(sock, &m_master);
				}
				else {
					onMessageReceived(sock, buf, bytesIn);
				}
			}
		}
	}

	// Remove the m_socket socket from the master file descriptor set and 
	// close it to prevent anyone else trying to connect
	FD_CLR(m_socket, &m_master);
	closesocket(m_socket);
	
	while (m_master.fd_count > 0) {
		SOCKET sock = m_master.fd_array[0];

		// Remove it from the master file list and close the socket
		FD_CLR(m_socket, &m_master);
		closesocket(m_socket);
	}

	// Cleanup winsock
	WSACleanup();
	return 0;
}

int TcpListener::sendToClient(int clientSocket, const char* msg, int length) {
	return send(clientSocket, msg, length, 0);
}

void TcpListener::sendErrorString(int& sendingClient) {
	int sock_errorId = WSAGetLastError();
	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, sock_errorId,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR)&messageBuffer, 0, NULL);
	std::string message(messageBuffer, size);
	LocalFree(messageBuffer);
	int e = sendToClient(sendingClient, message.c_str(), message.size() + 1);
}

void TcpListener::broadcastToClients(int sendingClient, const char* msg, int length) {
	bool error_sendMsg = false;
	for (int i = 0; i < m_master.fd_count; i++) {
		SOCKET outSock = m_master.fd_array[i];
		if (outSock != m_socket && outSock != sendingClient)
			if (sendToClient(outSock, msg, length) == SOCKET_ERROR)
				error_sendMsg = true;
	}
	if (error_sendMsg)
		sendErrorString(sendingClient);
}