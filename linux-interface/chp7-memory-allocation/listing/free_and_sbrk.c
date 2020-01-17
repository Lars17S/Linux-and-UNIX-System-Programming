/*  Listing 7-1: Demonstrate what happens to the program break when memory is freed */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define MAX_ALLOCS 1000000

int main(int argc, char *argv[]) {
    char *ptr[MAX_ALLOCS];
    int freeStep, freeMin, freeMax, blockSize, numAllocs, j;

    printf("\n");

    if (argc < 3) {
        printf("Invalid command-line arguments\n");
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
    freeMax = (argc > 5) ? atoi(argv[5]) : numAllocs;

    if (freeMax > numAllocs) {
        printf("free-max > num-allocs\n");
        exit(EXIT_FAILURE);
    }

    printf("Initial program break:          %10p\n", sbrk(0));
    printf("Allocating %d*%d bytes\n", numAllocs, blockSize);

    for (j = 0; j < numAllocs; j++) {
        ptr[j] = malloc(blockSize);
        if (ptr[j] == NULL) {
            perror("Error using malloc()");
            exit(EXIT_FAILURE);
        }
    }

    printf("Program break is now:           %10p\n", sbrk(0));

    printf("Freeing blocks from %d to %d in steps of %d\n",
                freeMin, freeMax, freeStep);
    for (j = freeMin - 1; j < freeMax; j += freeStep) 
        free(ptr[j]);

    printf("After free(), program break is: %10p\n", sbrk(0));

    exit(EXIT_SUCCESS);    
}

/*  In general, free() doesn’t lower the program break, but instead adds the block of
    memory to a list of free blocks that are recycled by future calls to malloc(). 

    Usage example:
    (1) ./free_and_sbrk 1000 10240 1 1 999
    (2) ./free_and_sbrk 1000 1024 */