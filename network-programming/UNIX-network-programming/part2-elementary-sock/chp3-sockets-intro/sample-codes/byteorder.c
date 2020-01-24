#include <stdio.h>
#include <stdlib.h>

/*  DEFINITION: Endianness
    Endianess refers to the order of bytes. 
    Big-endian: The most significant byte is the first and
    the last byte is the least significant. 
    Little-endian: Opposite to big-endian.

    Example: 10001101 (left to right is big-endian)

    Big-endianness is the dominant the networking protocols (IP, TCP, UDP). 
    Little-endianness is the dominant ordering for processor architectures. */ 

int main(int argc, char *argv[]) {
    /*  union is a user defined data type. In union, all members
        share the same memory location. */
    union byteorder
    {
        short       a;
        char        c[sizeof(short)];
    } un;

    un.a = 0x0102;
    if (sizeof(short) == 2) {
        if (un.c[0] == 1 && un.c[1] == 2)
            printf("big-endian\n");
        else if (un.c[0] == 2 && un.c[1] == 1)
            printf("little-endian\n");
        else
            printf("unknown\n");
    }
    else 
        printf("sizeof(short) = %ld\n", sizeof(short));
    
    exit(0);
}