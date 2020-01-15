/*  Optimization levels in C compiler.
    Turning on optimization makes the compiler attempt to improve the performance
    and/or code size at the expense of compilation time and possibly the ability
    to debug the program. */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf env;

static void doJump(int nvar, int rvar, int vvar) {
    printf("Inside doJump(): nvar=%d rvar=%d vvar=%d\n", nvar, rvar, vvar);
    longjmp(env, 1);
}

int main(int argc, char *argv[]) {
    int nvar;
    /*  NOTE: register keyword
        It's a hint to the compiler that the variable will be heavily used and that
        you recommend it be kept in a processor register if possible. */
    register int rvar;
    /*  NOTE: volatile keyword
        Objects declared as volatile are omitted from optimization because their values
        can be changed by code outside the scope of current code at any time. */
    volatile int vvar;

    nvar = 111;
    rvar = 222;
    vvar = 333;

    if (setjmp(env) == 0) {
        nvar = 777;
        rvar = 888;
        vvar = 999;
        doJump(nvar, rvar, vvar);
    }
    else 
        printf("After longjmp(): nvar=%d rvar=%d vvar=%d\n", nvar, rvar, vvar);

    exit(EXIT_SUCCESS);
}

/*  When we compile with optimization, we get the unexpected results:
    Inside doJump(): nvar=777 rvar=888 vvar=999
    After longjmp(): nvar=111 rvar=222 vvar=999
    
    Optimizing compilers may rearrange the order of instructions in a program
    and store certain variables in CPU registers (register keyword in C). A
    compiler optimizer is unable to take setjmp() and longjmp() because they are
    established and executed at run time. This means that optimized variables
    may end up with incorrect values as a consequence of a longjmp() functions.

    The reason why vvar has the expected value is because it was defined using
    the volatile keyword. 
    
    Usage example: 
    (1) Compiled without optimization
    gcc -o setjmp_vars setjmp_vars.c
    ./setjmp_vars

    (2) Compiled with optimization
    gcc -O1 -o setjmp_vars setjmp_vars.c
    ./setjmp_vars */