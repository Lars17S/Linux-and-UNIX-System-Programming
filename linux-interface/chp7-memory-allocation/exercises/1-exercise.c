/*  7-1. Modify the program in Listing 7-1 (free_and_sbrk.c) to print out the current value of
    the program break after each execution of malloc(). Run the program specifying a
    small allocation block size. This will demonstrate that malloc() doesn’t employ sbrk()
    to adjust the program break on each call, but instead periodically allocates larger
    chunks of memory from which it passes back small pieces to the caller. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ALLOCS 1000000

int main(int argc, char *argv[]) {
    char *ptr[MAX_ALLOCS];
    int freeStep, freeMin, freeMax, blockSize, numAllocs, j;

    printf("\n");

    if (argc < 3) {
        printf("Invalid command-line arguments");
        exit(EXIT_FAILURE);
    }

    numAllocs = atoi(argv[1]);
    if (numAllocs > MAX_ALLOCS) {
        printf("num-allocs > %d\n", MAX_ALLOCS);
        exit(EXIT_FAILURE);
    }

    blockSize = atoi(argv[2]);

    freeStep = (argc > 3) ? atoi(argv[3]) : 1;
    freeMin = (argc > 4) ? atoi(argv[4]) : 1;
    freeMax = (argc > 5) ? atoi(argv[5]) : 1;

    if (freeMax > numAllocs) {
        printf("free-max > num-allocs\n");
        exit(EXIT_FAILURE);
    }

    printf("Initial program break:          %10p\n", sbrk(0));
    
    printf("Allocating %d * %d bytes\n", numAllocs, blockSize);

    for (j = 0; j < numAllocs; j++) {
        ptr[j] = malloc(blockSize);
        if (ptr[j] == NULL) {
            perror("Error allocating memory");
            exit(EXIT_FAILURE);
        }
        printf("Current break for ptr[%d]:      %10p\n", j + 1, sbrk(0));
    }

    printf("Program break is now:           %10p\n", sbrk(0));
    
    printf("Freeing blocks from %d to %d in steps of %d\n",
                freeMin, freeMax, freeStep);
    for (j = freeMin - 1; j < freeMax; j += freeStep) {
        free(ptr[j]);
    }

    printf("After free(), program break is: %10p\n", sbrk(0));

    exit(EXIT_SUCCESS);
}

/*  OUTPUT:
    (1) ./1-exercise 10 100000
        Initial program break:          0x55ee7f8cb000
        Allocating 10 * 100000 bytes
        Current break for ptr[1]:      0x55ee7f8cb000
        Current break for ptr[2]:      0x55ee7f8fc000
        Current break for ptr[3]:      0x55ee7f8fc000
        Current break for ptr[4]:      0x55ee7f92d000
        Current break for ptr[5]:      0x55ee7f92d000
        Current break for ptr[6]:      0x55ee7f95d000
        Current break for ptr[7]:      0x55ee7f95d000
        Current break for ptr[8]:      0x55ee7f98e000
        Current break for ptr[9]:      0x55ee7f98e000
        Current break for ptr[10]:      0x55ee7f9bf000
        Program break is now:           0x55ee7f9bf000
        Freeing blocks from 1 to 1 in steps of 1
        After free(), program break is: 0x55ee7f9bf000


    (2) ./1-exercise 10 100
        Initial program break:          0x55f340568000
        Allocating 10 * 100 bytes
        Current break for ptr[1]:      0x55f340568000
        Current break for ptr[2]:      0x55f340568000
        Current break for ptr[3]:      0x55f340568000
        Current break for ptr[4]:      0x55f340568000
        Current break for ptr[5]:      0x55f340568000
        Current break for ptr[6]:      0x55f340568000
        Current break for ptr[7]:      0x55f340568000
        Current break for ptr[8]:      0x55f340568000
        Current break for ptr[9]:      0x55f340568000
        Current break for ptr[10]:      0x55f340568000
        Program break is now:           0x55f340568000
        Freeing blocks from 1 to 1 in steps of 1
        After free(), program break is: 0x55f340568000

    This program shows the behaviour of malloc() function.
    First, malloc() scans the list of memory blocks free in order to find
    one whose size is larger than or equal to its requirements. We can think
    this memory blocks as chunks of memory. 

    If the block is exactly the right size, then it is returned to the caller.
    If it is larger, then it is split, so that a block of the correct size is returned
    to the caller and a smaller free block is left on the free list. This same
    initial block is filled with small fragments until it reaches the block
    size limit (which normally is defined by the Linux kernel). Thus sbrk()
    returns the same memory reference when malloc() is used to allocates small
    fragments; malloc() will not increase heap memory until the last memory block
    cannot allocates the requested spaces or there is no more free space in the 
    free list memory.

    More information:
    The Linux Programming Interface. pags 144 - 146. */