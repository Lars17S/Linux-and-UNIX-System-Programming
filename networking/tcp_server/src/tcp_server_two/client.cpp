#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

int main(int argc, char* argv[]) {
    int sockfd, portno, n;
    sockaddr_in serv_addr;
    /* The hostent structure is used by functions to store information about a given host, 
    such as host name, IPv4 address, and so forth. */
    hostent *server;
    char buffer[256];
    if (argc < 3) {
        fprintf(stderr, "usage %s hostname port", argv[0]);
        return -1;
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cerr << "Error opening socket" << endl;
    }
    /* Takes such a name as an argument and returns a pointer to a hostent 
    containing information about that host. */
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr, "Error, no such host");
        return -1;
    }

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    // bcopy - copy byte sequence
    // #define h_addr  h_addr_list[0]  /* address, for backward compatiblity */
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    // convert values between host and network byte order
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Error connecting" << endl;
    }
    /* The client needs to know the port number of the server, but it does not need to know its 
    own port number. This is typically assigned by the system when connect is called. */
    printf("Please enter the message: ");
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) {
        cerr << "Error writing to socket" << endl;
    }
    bzero(buffer, 256);
    n = read(sockfd, buffer, 255);
    if (n < 0) {
        cerr << "Error reading from socket" << endl;
    }
    printf("%s", buffer);
    return 0;
}