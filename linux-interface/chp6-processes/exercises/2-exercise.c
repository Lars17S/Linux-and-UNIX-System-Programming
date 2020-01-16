/*  6-2. Write a program to see what happens if we try to longjmp() into a function that has
    already returned. */

#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

static jmp_buf env;

int func() {
    setjmp(env);
    return 1;
}

int main(int argc, char *argv[]) {
    int x = func();
    longjmp(env, 1);
    printf("x value: %d\n", x);
    exit(EXIT_SUCCESS);
}

/*  Answer: What longjmp() tries to do is to unwind (access) the stack back
    to a frame that no longer exists. That is why a segmentation fault 
    (code dumped) happen. */