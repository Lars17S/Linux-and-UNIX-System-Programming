/*  Modify Figure 1.9 as follows: First, change the port number assigned to the 
    sin_port member from 13 to 9999. Next, change the single call to write into 
    a loop that calls write for each byte of the result string. Compile this modified 
    server and start it running in the background. Next, modify the client from the 
    previous exercise (which prints the counter before terminating), changing the 
    port number assigned to the sin_port member from 13 to 9999. Start this 
    client, specifying the IP address of the host on which the modified server is 
    running as the command-line argument. What value is printed as the client's 
    counter? If possible, also try to run the client and server on different hosts. */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAXLINE 4096
#define LISTENQ 1024

void errorHandler() {
    printf("The error message is: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
}

int Socket(int family, int type, int protocol) {
    int n;

    if ( (n = socket(family, type, protocol)) < 0)
        errorHandler();
    return n;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t addrlen) {
    int n;

    if ( (n = accept(sockfd, addr, &addrlen)) == -1) 
        errorHandler();
    return n;
}

int main(int argc, char *argv[]) {
    int         listenfd, connfd;
    struct      sockaddr_in servaddr, cliaddr;
    char        buff[MAXLINE];
    socklen_t   clilen;
    /*  The time_t datatype is a data type in the ISO C library defined
    for storing system time values. */
    time_t      ticks;

    if (argc != 2) {
        printf("Invalid command line arguments\n");
        return 0;
    }

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    int port = atoi(argv[1]);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if (inet_pton(AF_INET, "0.0.0.0", &servaddr.sin_addr) <= 0)
        errorHandler();

    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
        errorHandler();

    if (listen(listenfd, LISTENQ) == -1)
        errorHandler();

    clilen = sizeof(cliaddr);
    while(1) {
        connfd = Accept(listenfd, (struct sockaddr*)&cliaddr, clilen);
        ticks = time(NULL);
        /*  The snprintf() function formats and stores a series of characters and values in the array buffer.
            %.24s specifies that a maximum of 24 characters be printed.
            The ctime() function returns the string representing the localtime based on the argument timer. */
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        for (int i = 0; i < strlen(buff); i++) {
            char *ch = &buff[i];
            if (write(connfd, ch, sizeof(char)) == -1)
                errorHandler();
        }
            

        if (close(connfd) == -1)
            errorHandler();
    }
}

/*  Answer:
    OUTPUT Test 1:
    Thu
    String length received: 3
    Jan 16 01:24:17 2020

    String length received: 23
    Number of times n > 0: 2

    OUTPUT Test 2:
    Thu Jan 16 01:24:44 2020

    String length received: 26
    Number of times n > 0: 1

    OUTPUT Test 3:
    T
    String length received: 1
    hu Jan 16 01:24
    String length received: 15
    :
    String length received: 1
    59 20
    String length received: 5
    20

    String length received: 4
    Number of times n > 0: 5

    Possible answer: It appears that it is not possible to send just 1 byte char. 
    counter variable is not constant, the reason may lead in the TCP Protocol
    behaviour. Since it is a complex protocol that divides data into packets and
    then deliver them as segments, it is possible that congestion control algorithm
    decides the minimum size of segments to be delivered and then sends them. 
    
    More information: 
    https://en.wikipedia.org/wiki/TCP_congestion_control
    Computer Networking: A Top-down Approach. pags. 269 - 282 
    
    Usage example: ./5-exercise 12001 */