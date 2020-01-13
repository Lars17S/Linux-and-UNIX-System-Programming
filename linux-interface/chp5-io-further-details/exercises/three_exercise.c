#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd;
    ssize_t numBytes, numWritten;
    ssize_t total = 0;
    char ch = 's';

    switch(argc) {
        case 3:
        fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
        break;
        
        case 4:
        fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        break;
        
        default:
        printf("Invalid command-line arguments");
        exit(EXIT_FAILURE);
    }

    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    sscanf(argv[2], "%zu", &numBytes);
    printf("Number of bytes: %zu\n", numBytes);
    for (long long i = 0; i < (long) numBytes; ++i) {
        if (argc == 4)
            lseek(fd, 0, SEEK_END);
        numWritten = write(fd, &ch, 1);
        if (numWritten == -1) {
            perror("Error writing into file");
            exit(EXIT_FAILURE);
        }
        ++total;
    }
    printf("File %s | Num. Bytes: %ld, Wrote: %ld\n", argv[1], (long) numBytes, (long) total);
    close(fd);
    exit(EXIT_SUCCESS);
}

/*  When the O_APPEND flag is ignored the character could not be written at the end of the file. 
    This happen because two instances of the program are running and the offset of one of them
    could actually be behind the other offset. This causes that a character is actually written
    in a position where currently exists a character. 

    This problem is related with the concept of atomicity (race condition) and can be solved
    using the O_APPEND. */