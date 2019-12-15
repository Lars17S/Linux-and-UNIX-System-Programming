#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

using namespace std;

void dostuff(int);
void error (const char *msg) {
    cerr << msg << endl;
}

int main(int argc, char* argv[]) {
    // file descriptors (?)
    // they store values returned by socket system and the accept system
    // portno: port number on which the server accepts connections
    int sockfd, newsockfd, portno, pid;
    // an unsigned opaque integral type of length of at least 32-bits.
    // stores the size of the address of the client
    socklen_t clilen;
    char buffer[256];
    // A sockaddr_in is a structure containing an internet address
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2) {
        cerr << "ERROR, no port provided!" << endl;
        return -1;
    }
    // AF_INET refers to the domain address, usually Internet convention (IP Address family)
    // SOCK_STREAM is the type of socket. Stream socket
    // TCP almost always uses SOCK_STREAM  
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        cerr << "ERROR opening socket" << endl;
    // Sets all values in a buffer to zero
    bzero((char*)&serv_addr, sizeof(serv_addr));
    // Convert string to int
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    // s_addr is the IP address of the host. INADDR_ANY is the address of the machine
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    // binds a socket to an address and port. 
    // three arguments: socket file descriptor, structure sockaddr
    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "ERROR on binding" << endl;
    }
    // two arguments: socket file descriptor and the maximum number in the queue of connections
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    // TODO: the new socket created for the connection of the client and server
    // the second argument is a reference pointer to the address of the client
    // on the other end of the connection
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) 
        cerr << "ERROR: connection not accepted" << endl;
    bzero(buffer, 256);
    // reads from the socket
    n = read(newsockfd, buffer, 255);
    if (n < 0) 
        cerr << "ERROR: reading from socket" << endl;
    printf("Here is the message: %s\n", buffer);
    n = write(newsockfd, "I got your message", 18);
    if (n < 0)
        cerr << "ERROR writing to socket" << endl;
    close(newsockfd);
    close(sockfd);
    return 0;
}

// http://www.linuxhowtos.org/C_C++/socket.htm