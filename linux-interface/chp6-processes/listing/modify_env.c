/*  Access to nonstandard GNU/Linux extension functions. */
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>

/*  Pointer to enviroment list */
extern char **environ;

int main(int argc, char *argv[]) {
    int j;
    char **ep;
    

    clearenv();             /* Erase entire environment */

    for (j = 1; j < argc; j++) {
        /*  Adds a new variable or modifies the value.
            String must be of the form "NAME=VALUE" */
        if (putenv(argv[j]) != 0) {
            perror("Error using putenv() function");
            exit(EXIT_FAILURE);
        }
    }

    /*  Alternative to putenv() for adding a variable. 
        The setenv() function doesn’t change the environment if the variable
        identified by name already exists and overwrite has the value 0. If
        overwrite is nonzero, the environment is always changed.*/
    if (setenv("GREET", "Hello World", 0) == -1) {
        perror("Error using setenv() function");
        exit(EXIT_FAILURE);
    }

    /*  Removes the variable identified by name. */
    unsetenv("BYE");

    for (ep = environ; *ep != NULL; ep++) 
        puts(*ep);

    exit(EXIT_SUCCESS);
}

/*  Usage example: ./modify_env "GREET=Guten Tag" SHELL=/bin/bash BYE=Ciao */