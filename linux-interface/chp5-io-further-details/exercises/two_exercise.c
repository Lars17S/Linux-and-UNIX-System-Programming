#include <stdlib.h>
/*  sys/types.h - data types    */
#include <sys/types.h>
#include <sys/stat.h>
/*  unistd.h - standard symbolic constants and types */
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd;
    ssize_t numWritten;
    if (argc != 3) {
        printf("File name or input text not declared");
        exit(EXIT_FAILURE);
    }

    /*  Because O_CREAT is not declared, it only opens an existing file. */
    fd = open(argv[1], O_RDWR | O_APPEND);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    printf("%s file\n", argv[1]);

    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("Error using lseek");
        exit(EXIT_FAILURE);
    }

    numWritten = write(fd, argv[2], strlen(argv[2]));
    if (numWritten == -1) {
        perror("Error writing in file");
        exit(EXIT_FAILURE);
    }
    printf("%s | total: %ld bytes, wrote: %ld bytes\n", argv[2], (long) strlen(argv[2]), (long) numWritten);

    close(fd);
    exit(EXIT_SUCCESS);
}

/*  The text is written at the end of the file, even if lseek is used. The reason is that
    the file was opened using O_APPEND.
    O_APPEND
    The file is opened in append mode. Before each write(2), the file offset is positioned 
    at the end of the file, as if with lseek(2). 
    Usage example: ./two_exercise sample.txt "Hi there!" */