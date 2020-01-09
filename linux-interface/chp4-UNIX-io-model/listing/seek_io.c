#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include "../../useful-functions/get_num.h"
#include "../../useful-functions/get_num.c"

extern int errno;
void errorHandler();

int main(int argc, char *argv[]) {
    int fd, ap;

    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        printf("%s file {r<length> | R<length> | w<string> | s<offset>}...\n", argv[0]);
        return 0;
    }
        
    fd = open(argv[1], O_RDWR | O_CREAT, 
                S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH); /*  rw-rw-rw */

    if (fd == -1) 
        errorHandler();

    for (ap = 2; ap < argc; ap++) {
        switch (argv[ap][0]) {
            case 'r':   /*  Display bytes at current offset, as text */
            case 'R': ;  /*  Display bytes at current offset, in hex */
                char *buf;
                ssize_t numRead;
                size_t len;
                len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
                /*  The malloc() function allocates size bytes and returns a pointer to 
                    the allocated memory. */
                buf = malloc(len);
                if (buf == NULL)
                    errorHandler();
                
                numRead = read(fd, buf, len);
                if (numRead == -1) 
                    errorHandler();
                
                if (numRead == 0)
                    printf("%s: end-of-file\n", argv[ap]);
                else {
                    printf("%s: ", argv[ap]);
                    for (int j = 0; j < numRead; j++) {
                        if (argv[ap][0] == 'r') {
                            /*  The isprint() function checks whether a character is a printable 
                            character or not. */
                            printf("%c", isprint((unsigned char) buf[j]) ? buf[j] : '?');
                        }
                        else {
                            /*  %02x means print at least 2 digits */
                            printf("%02x ", (unsigned int) buf[j]);
                        }
                    }
                    printf("\n");
                }

                free(buf);
                break;
            case 'w': ;  /*  Write string at current offset */
                ssize_t numWritten;
                numWritten = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
                if (numWritten == -1)
                    errorHandler();
                printf("%s: wrote %ld bytes\n", argv[ap], (long) numWritten);
                break;
            case 's': ;   /*  Change file offset */
                off_t offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
                if (lseek(fd, offset, SEEK_SET) == -1)
                    errorHandler();
                printf("%s: seek succeded\n", argv[ap]);
                break;
            default:
                printf("Argument must start with [rRws]: %s\n", argv[ap]);
        }
    }
    exit(EXIT_SUCCESS);
}


void errorHandler() {
    fprintf(stderr, "ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
}

/*  Use example: ./seek_io tfile s0 w"Hello there" r5 
    Seek to offset 0, writes "Hello there" into tfile, read 5 bytes from offset */
