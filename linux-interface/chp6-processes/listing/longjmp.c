/*  Performing a Nonlocal Goto.
    C itself does not support exceptions, but it can be simulated using
    setjmp() and longjmp() functions.*/

#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

/*  jmp_buf stores information to restore a calling environment. The information
    is sufficient to restore execution at the correct block of the program.
    It stores a copy of the program counter register (which points to the currently
    executing machine-language instruction) and the stack pointer register (which
    marks the top of the stack). */
static jmp_buf env;

static void f2(void) {
    longjmp(env, 2);
}

static void f1(int argc) {
    if (argc == 1)
        longjmp(env, 1);
    f2();
}

int main(int argc, char *argv[]) {
    /*  setjmp() establishes a target for a later jump performed by longjmp(). 
        Returns 0 on initial call, nonzero on return via longjmp(). */
    switch (setjmp(env)) {
    case 0:             /* This is the return after the initial setjmp() */
        printf("Calling f1() after initial setjmp()\n");
        f1(argc);       /* Never returns */
        break;

    case 1:
        printf("We jumped back from f1()\n");
        break;

    case 2:
        printf("We jumped back from f2()\n");
        break;
    }

    exit(EXIT_SUCCESS);
}

/*  Usage example: "./longjmp" or "./longjmp x" */