/*  UNIX I/O model is universal (open(), read(), write(), close()). This program is used to 
    perform I/O on all types of files. It copies byte by byte each file. */

/*  <sys/stat.h> is the header in the C POSIX library for the C programming language 
    that contains constructs that facilitate getting information about files attributes. */
#include <sys/stat.h>
/*  fcntl.h is the header in the C POSIX library for the C programming language that 
    contains constructs that refer to file control */
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
//  Library created for utilities
//  #include "tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024 /* Allow "cc -D" to ovveride function */
#endif

int main(int argc, char *argv[]) {
    int inputFd, outputFd, openFlags;
    /*  mode_t consists of a load of bit-packed booleans. It refers to the permissions for RWX.
        They are written in octal, so you need to interpreted them in binary in order to use. */
    mode_t filePerms;
    /*  size_t is used to represent the size of objects (bytes) in memory.
        ssize_t is the same, but it is signed integral type. */
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc != 3 || strcmp(argv[1], "-- help") == 0) 
        usageErr("%s old-file new-file\n", argv[0]);

    //  Open input and output files
    /*  open(pathname, flags, mode*): In this case, flag is the permission read only. */
    inputFd = open(argv[1], O_RDONLY);

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH; /* permissions: rw(owner)-rw(user)-rw(other) */
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1)
        errExit("opening file %s", argv[2]);

    /*  Transfer data until we encounter end of input or an error */

    /* read and wirte system calls returns the number of bytes read/written */
    while ((numRead == read(inputFd, buf, BUF_SIZE)) > 0) 
        if (write(outputFd, buf, numRead) != numRead)
            fatal("Could not write whole buffer");
    if (numRead == -1) 
        errExit("read");
    
    if (close(inputFd) == -1)
        errExit("close input");
    if (close(outputFd) == -1) 
        errExit("close output");
    
    exit(EXIT_SUCCESS);
}

// The Linux Programming Interface, pag 71