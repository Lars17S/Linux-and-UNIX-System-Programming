/*  Listing 13-1: Using O_DIRECT to bypass the buffer cache */

#define _GNU_SOURCE
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include "../../useful-functions/error_handler.h"
#include "../../useful-functions/error_handler.c"

int main(int argc, char *argv[]) {
    int fd;
    ssize_t numRead;
    size_t length, alignment;
    off_t offset;
    void *buf;

    if (argc < 3) 
        invalidCmdLineArg();
    
    length = atoi(argv[2]);
    offset = (argc > 3) ? atoi(argv[3]) : 0;
    alignment = (argc > 4) ? atoi(argv[4]) : 4096;

    /*  O_RDONLY    
        Linux allows an application to bypass the buffer cache
        when performing disk I/O, thus transferring data directly from user space to a file
        or disk device. This is sometimes termed direct I/O or raw I/O.
    */
    fd = open(argv[1], O_RDONLY | O_DIRECT);
    if (fd == -1) 
        errExit("open");
    
    /*  memalign() allocates a block of memory aligned on an address that
        is a multiple of its first argument. The following expression
        ensures that 'buf' is aligned on a non-power-of-two multiple of
        'alignment'. We do this to ensure that if, for example, we ask
        for a 256-byte aligned buffer, then we don't accidentally get
        a buffer that is also aligned on a 512-byte boundary.
        The '(char *)' cast is needed to allow pointer arithmetic (which
        is not possible on the 'void *' returned by memalign()). 
    
        Whereas malloc gives you a chunk of memory that could have any
        alignment (the only requirement is that it must be aligned for
        the largest primitive type that the implementation supports),
        posix_memalign gives you a chunk of memory that is guaranteed
        to have the requested alignment.

        So the result of e.g. posix_memalign(&p, 32, 128) will be a 128-byte
        chunk of memory whose start address is guaranteed to be a multiple of 32.

        (I still do not understand why alignment must be a multiple of 2)
    */

    buf = (char *) memalign(alignment * 2, length + alignment) + alignment;
    if (buf == NULL)
        errExit("memalign");
    
    if (lseek(fd, offset, SEEK_SET) == -1)
        errExit("lseek");
    
    numRead = read(fd, buf, length);
    if (numRead == -1)
        errExit("read");
    printf("Read %ld bytes\n", (long) numRead);
    
    exit(EXIT_SUCCESS);
}