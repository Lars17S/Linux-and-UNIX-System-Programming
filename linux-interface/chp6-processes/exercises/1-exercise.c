/*  6-1. Compile the program in Listing 6-1 (mem_segments.c), and list its size
    using ls –l. Although the program contains an array (mbuf) that is around
    10 MB in size, the executable file is much smaller than this. Why is this? */

/*  Code snippet (mem_segments.c) */
int main(int argc, char *argv[]) {
    static char mbuf[10240000];
    return 0;
}

/*  Answer: The answer is that when a program is stored in disk, it is not necessary to
    allocate space for the unintialized variable. The executable only saves the
    information about the location and size required. The space is allocated
    durint the running time. */