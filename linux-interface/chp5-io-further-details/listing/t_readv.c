#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
/*  The <sys/uio.h> header shall define the iovec structure. */
#include <sys/uio.h>
#include <fcntl.h>

#define STR_SIZE 100

int main(int argc, char *argv[]) {
    int fd;
    /*  The set of buffers to be transferred is defined by the array iov.
        iov is a structure with iov_base (start address of buffer) and iov_len. */
    struct iovec iov[2];
    /*  First and second buffer */
    int x;
    char str[STR_SIZE];
    ssize_t numRead, totRequired;

    if (argc != 2) 
        return 0;
    
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    totRequired = 0;

    iov[0].iov_base = &x;
    iov[0].iov_len = sizeof(x);
    totRequired += iov[0].iov_len;

    iov[1].iov_base = str;
    iov[1].iov_len = STR_SIZE;
    totRequired += iov[1].iov_len;

    /*  Instead of accepting a single buffer of data to be read or written,
        these functions transfer multiple buffers of data in a single system call.
        This process is related with atomicity concept: It means that the kernel
        ensures that a process is done in a single pperation. */
    numRead = readv(fd, iov, 2);
    if (numRead == -1) {
        perror("Error using readv");
        exit(EXIT_FAILURE);
    }

    if (numRead < totRequired) 
        printf("Read fewer bytes than requested\n");

    printf("Total bytes requested: %ld; bytes read: %ld\n", (long) totRequired, (long) numRead);
    exit(EXIT_SUCCESS);
}