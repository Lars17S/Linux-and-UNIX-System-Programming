#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

char *sock_ntop(const struct sockaddr *sa, socklen_t salen) {
    char        portstr[8];
    static char str[128];

    switch (sa->sa_family)
    {
    case AF_INET:;
        struct sockaddr_in *sin = (struct sockaddr_in *) sa;
        if (inet_pton(AF_INET, &sin->sin_addr, sizeof(str)) == NULL)
            return NULL;
        if (ntohs(sin->sin_port != 0)) {
            snprintf(portstr, sizeof(portstr), ":%d",
                    ntohs(sin->sin_port));
            strcat(str, portstr);
        }
        return (str);
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[]) {
    exit(EXIT_SUCCESS);
}