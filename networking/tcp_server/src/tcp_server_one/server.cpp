#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;

int main() {

    // Create a socket
    // AF_INET is an address family (IPv4)
    // Type: SOCK_STREAM: TCP (reliable, connection oriented)
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1) {
        cerr << "Can't create a socket!";
        return -1;
    }

    // Bind the socket to a IP / port, it means assigns an IP address to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    // The htons() function converts the unsigned short integer hostshort from host 
    // byte order to network byte order.
    hint.sin_port = htons(54003); // IMPORTANT htons
    // inet_pton - convert IPv4 and IPv6 addresses from text to binary form
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
    /* When a socket is created with socket(2), it exists in a name space (ad‐
       dress family) but has no address assigned to it.   bind()  assigns  the
       address  specified  by  addr  to the socket referred to by the file de‐
       scriptor sockfd. */
    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1) {
        cerr << "Can't bind to IP/port";
        return -2;
    } 

    // Mark the socket for listening in
    // The listen function places a socket in a state in which it is listening for an
    // incoming connection.
    if (listen(listening, SOMAXCONN) == -1) {
        cerr << "Can't listen!";
        return -3;
    }
    // Accept a call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    // accept a connection on a socket
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    if (clientSocket == -1) {
        cerr << "Problem with client connecting!";
        return -4;
    }

    // Close the listening socket
    close (listening);
     
    // Sets the first num bytes of the block of memory pointed by ptr to the specified value (interpreted as an unsigned char).
    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0);
    if (result) {
        cout << host << " connected on " << service << endl;
    } else {
        // Numerical to string
        // inet_ntop - convert IPv4 and IPv6 addresses from binary to text form
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        // The ntohs() function converts the unsigned short integer netshort from network byte order to host byte order.
        cout << host << " connected on " << ntohs(client.sin_port) << endl;
    }
    
    // While receiving, display messages, echo messages
    char buf[4896];
    while (true) {
        // Clear the buffer
        memset(buf, 0, 4096);
        // Wait for a message
        // recv, recvfrom, recvmsg - receive a message from a socket
        int bytesRecv = recv(clientSocket, buf, 4096, 0);
        if (bytesRecv == -1) {
            cerr << "There was a connection issue" << endl;
            break;
        }
        else if (bytesRecv == 0) {
            cout << "The client disconnected" << endl;
            break;
        }

        // Display message
        cout << "Received: " << string(buf, 0, bytesRecv) << endl;


        // Resend message
        // The system calls send(), sendto(), and sendmsg() are used to transmit a message to another socket. 
        send(clientSocket, buf, bytesRecv + 1, 0);
    }
    
    // Close socket
    close(clientSocket);
    return 0;
}