#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

void doProcess(int);

int main(int argc, char* argv[]) {
    int sock, new_sock, portno, pid;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;

    if (argc < 2) {
        cerr << "Error: port not provided!" << endl;
        return -1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        cerr << "Error opening socket" << endl;
        return -1;
    }
    // Sets all the values to zero, it works to initialize all the variable to zero
    bzero((char*)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    inet_pton(AF_INET, "0.0.0.0", &serv_addr.sin_addr);
    if (bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Error binding socket" << endl;
        return -1;
    }

    listen(sock, 5);
    clilen = sizeof(cli_addr);
    while (1) {
        new_sock = accept(sock, (sockaddr*)&cli_addr, &clilen);
        if (new_sock < 0)
            cerr << "Error accepting connection" << endl;
        /* Fork system call is used for creating a new process, which is 
        called child process, which runs concurrently with the process 
        that makes the fork() call (parent process). */
        pid = fork();
        if (pid < 0) 
            cerr << "Error on fork" << endl;
        else if (pid == 0) {
            close(sock);
            doProcess(new_sock);
            exit(0);   
        }
        else close(new_sock);
    }
    
    close (sock);

    return 0;
}

/******** DOSTUFF() *********************
 There is a separate instance of this function 
 for each connection.  It handles all communication
 once a connnection has been established.
 *****************************************/

void doProcess(int new_sock) {
    int n;
    char buffer[256];

    bzero(buffer, 256);
    n = read(new_sock, buffer, 255);
    if (n < 0)
        cerr << "Error reading from socket" << endl;
    printf("CLIENT: %s\n", buffer);
    n = write(new_sock, "Received", 8);
    if (n < 0) 
        cerr << "Error writing to socket" << endl;
}