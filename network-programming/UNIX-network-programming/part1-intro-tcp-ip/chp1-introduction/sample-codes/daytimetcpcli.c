#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

#define MAXLINE 4096

int main(int argc, char *argv[]) {
    int     sockfd;
    ssize_t n;
    char    recvline[MAXLINE + 1];
    /*  Structure for handling internet addresses  */
    struct  sockaddr_in servaddr;

    if (argc != 2) {
        printf("Invalid command line arguments\n");
        exit(EXIT_FAILURE);
    }

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error while creating socket");
        exit(EXIT_FAILURE);
    }

    /*  The bzero() function erases the data in the n bytes of the memory
        starting at the location pointed to by s, by writing zeros (bytes
        containing '\0') to that area. */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12001);
    /*  inet_pton - convert IPv4 and IPv6 addresses from text to binary form. */
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        perror("inet_pton error");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Connection error");
        exit(EXIT_FAILURE);
    }


    while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = 0;    /*  null terminate */
        /*  int fputs(const char *str, FILE *stream) writes a string to the specified
            stream up to but not including the null character. */
        if (fputs(recvline, stdout) == EOF)
            perror("fputs error");
    }
    if (n < 0)
        perror("read error");
        
    exit(EXIT_SUCCESS);
}

/*  Usage example: ./daytimetcpcli 0.0.0.0 */