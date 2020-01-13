#include <stdio.h>
#include <stdlib.h>

/*  NOTE: extern keyword  
    - The extern keyword extends the visibility of the C variables and C functions.
    - When extern is used with a variable, it’s only declared, not defined. */
/*  The environment list can be accessed using the global variable char **environ. */
extern char **environ;

int main(int argc, char *argv[]) {
    char **ep;

    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);

    exit(EXIT_SUCCESS);
}