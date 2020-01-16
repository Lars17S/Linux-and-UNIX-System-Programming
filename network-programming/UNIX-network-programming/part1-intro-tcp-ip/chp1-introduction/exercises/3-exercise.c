/*  1.3 Modify the first argument to socket in Figure 1.5 to be 9999. Compile and run 
    the program. What happens? Find the errno value corresponding to the error 
    that is printed. How can you find more information on this error? */

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

    if ( (sockfd = socket(9999, SOCK_STREAM, 0)) < 0) {
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

    while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF)
            perror("fputs error");
    }
    if (n < 0)
        perror("read error");
         
    exit(EXIT_SUCCESS);
}

/*  Answer: The number passed in the first argument does not correspond to any valid
    address family defined in Linux.
    You can find more information about the error using the errno value. */