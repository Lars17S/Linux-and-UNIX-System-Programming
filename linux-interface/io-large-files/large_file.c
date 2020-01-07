/*  If you define this macro an additional set of functions is made available
    which enables 32 bit systems to use files of sizes beyond the usual limit
    of 2GB. */
#define _LARGEFILE64_SOURCE
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;
    /*  File offset 64-bit */
    off64_t off;
    if (argc != 3)
        return 0;
    
    fd = open64(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Error opening file: ");
        exit(EXIT_FAILURE);
    }

    /*  This function converts a C-type string, passed as an argument 
        to function call, to a long long integer. */
    off = atoll(argv[2]);
    if (lseek64(fd, off, SEEK_SET) == -1) {
        perror("Error using offset: ");
        exit(EXIT_FAILURE);
    }

    if (write(fd, "test", 4) == -1)
        perror("Error writing into file: ");
    exit(EXIT_SUCCESS);
}