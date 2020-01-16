/*  1.3 Modify Figure 1.5 by placing a counter in the while loop, counting the number 
    of times read returns a value greater than 0. Print the value of the counter 
    before terminating. Compile and run your new client. */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAXLINE 4096

int main(int argc, char *argv[]) {
    int     sockfd;
    ssize_t n;
    char    recvline[MAXLINE + 1];
    struct  sockaddr_in servaddr;

    if (argc != 3) {
        printf("Invalid command line arguments\n");
        exit(EXIT_FAILURE);
    }

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Value of errno: %d | Error message: %s\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[2]);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        perror("inet_pton error");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection error");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    n = read(sockfd, recvline, MAXLINE);
    while (n > 0) {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF)
            perror("fputs error");
        printf("\nString length received: %d\n", (int) strlen(recvline));
        ++count;
        n = read(sockfd, recvline, MAXLINE);
    }
    if (n < 0)
        perror("read error");

    printf("Number of times n > 0: %d\n", count);   
    exit(EXIT_SUCCESS);
}

/*  Answer: The number passed in the first argument does not correspond to any valid
    address family defined in Linux.
    You can find more information about the error using the errno value. */