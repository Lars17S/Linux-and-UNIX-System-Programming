#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

/*  read "n" bytes from a descriptor */
ssize_t readn(int fd, void *vptr, size_t n) {
    size_t nleft;
    ssize_t nread;
    char *ptr;

    ptr = (char*) vptr;
    nleft = n;
    while (nleft > 0) {
        if ( (nread = read(fd, ptr, nleft)) < 0) {
            /*  EINTR 4 Interrupted system call */
            if (errno == EINTR) 
                nread = 0;
            else
                return -1;
        } else if (nread == 0) 
            break;  /*  EOF */
        
        nleft -= nread;
        /*  moves the pointer to the next character
            passed nread length */
        ptr += nread;
    }
    return (n - nleft);
}

/*  write "n" bytes to a descriptor */
ssize_t writen(int fd, const void *vptr, size_t n) {
    size_t nleft;
    ssize_t nwritten;
    const char *ptr;

    ptr = vptr;
    nleft = n;
    while (nleft > 0) {
        if (nwritten = write (fd, ptr, nleft) <= 0) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;   /*  and call write() again */
            else
                return -1;
        }

        nleft -= nwritten;
        ptr += nwritten;
    }

    return n;
}


int main(int argc, char *argv[]) {

    exit(EXIT_SUCCESS);
}