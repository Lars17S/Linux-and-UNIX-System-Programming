#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <sstream>

/* The ‘#pragma’ directive is the method specified by the C standard
for providing additional information to the compiler.
In order to use sockets, it is necessary to link the winsock libary
file with a pragma: #pragma comment(lib, "Ws2_32.lib"). */
#pragma comment (lib, "ws2_32.lib")

using namespace std;

int main(int argc, char* argv[]) {
	// Initialize winsock
	// WSADATA structure contains information about the Windows Sockets implementation.
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int portno;

	if (argc < 2) {
		cerr << "Port not provided!" << endl;
		system("pause");
		return -1;
	}

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0) {
		cerr << "Can't initialize winsock" << endl;
		system("pause");
		return -1;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		cerr << "Can't create a socket" << endl;
		system("pause");
		return -1;
	}

	// Bind the ip address and port to a socket
	portno = atoi(argv[1]);
	sockaddr_in sock_struct;
	sock_struct.sin_family = AF_INET;
	sock_struct.sin_port = htons(portno);
	// Convert IPv4 and IPv6 addresses from text to binary form
	inet_pton(AF_INET, "0.0.0.0", &sock_struct.sin_addr);

	bind(listening, (sockaddr*)&sock_struct, sizeof(sock_struct));

	// Set the socket to listening
	// SOMAXCONN defines the maximum number of listening connections
	// allowed by the OS
	listen(listening, SOMAXCONN);

	// Create the master file descriptor set and zero it
	// fd_set is used to represent file descriptor set
	fd_set master;
	// Add our first socket that we're interested in interacting with; 
	// the listening socket!
	FD_ZERO(&master);
	FD_SET(listening, &master);

	bool running = true;
	while (running) {
		// Make a copy of the master file descriptor set, this is SUPER important because
		// the call to select() is _DESTRUCTIVE_. The copy only contains the sockets that
		// are accepting inbound connection requests OR messages. 
		fd_set copy = master;
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		/* The select function blocks the calling process until there is activity on any
		of the specified sets of file descriptors, or until the timeout period has expired. */
		// Read https://www.gnu.org/software/libc/manual/html_node/Waiting-for-I_002fO.html
		// Loop through all the current connections / potential connections
		for (int i = 0; i < socketCount; i++) {
			SOCKET sock = copy.fd_array[i];
			// Check if it is an inbound communication
			if (sock == listening) {
				// Accept a new connection
				SOCKET client = accept(listening, nullptr, nullptr);

				// Add the new connection to the list of connected clients
				FD_SET(client, &master);

				// Send a welcome message to the connected client
				string welcomeMsg = "Welcome to Chat Server!\r\n";
				send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
			}
			else {
				char buf[4096];
				// ZeroMemory fills a block of memory with zeros.
				ZeroMemory(buf, 4096);

				// Receive message
				// bytesIn is a file descriptor
				// NOTE: Everything in Linux is a file
				// The recv(), recvfrom(), and recvmsg() calls are used to receive
				// messages from a socket.
				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0) {
					// Drop the client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else {
					// Check to see if it is a command. \quit kills the server
					if (buf[0] == '\\') {
						string cmd = string(buf, bytesIn);
						if (cmd.compare("\\quit") == 0) {
							running = false;
							break;
						}
					}

					// Unknown command
					continue;
				}

				// Send message to other clients
				for (int i = 0; i < master.fd_count; i++) {
					SOCKET outSock = master.fd_array[i];
					if (outSock != listening && outSock != sock) {
						ostringstream ss;
						ss << "SOCKET#" << sock << ": " << buf << "\r\n";
						string strOut = ss.str();
						send(outSock, strOut.c_str(), strOut.size() + 1, 0);
					}
				}
			}
		}
	}

	// Remove the listening socket from the master file descriptor set and 
	// close it to prevent anyone else trying to connect
	FD_CLR(listening, &master);
	closesocket(listening);

	string msg = "Server is shutting down. Goodbye\r\n";
	while (master.fd_count > 0) {
		// Get the socket number
		SOCKET sock = master.fd_array[0];
		send(sock, msg.c_str(), msg.size() + 1, 0);

		// Remove it from the master file list and close the socket
		FD_CLR(sock, &master);
		closesocket(sock);
	}

	// Cleanup winsock
	WSACleanup();
	system("pause");
}

// source: https://bitbucket.org/sloankelly/youtube-source-repository/src/39d0e0460016338163d43d9bc01d4a45b1826619/cpp/networking/MultipleClientsBarebonesServer/MultipleClientsBarebonesServer/main.cpp?at=master