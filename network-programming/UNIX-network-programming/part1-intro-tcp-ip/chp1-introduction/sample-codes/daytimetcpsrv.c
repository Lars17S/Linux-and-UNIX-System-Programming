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

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12001);
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
        if (write(connfd, buff, strlen(buff)) == -1)
            errorHandler();

        if (close(connfd) == -1)
            errorHandler();
    }
}