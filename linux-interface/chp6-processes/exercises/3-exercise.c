/*  6-3. Implement setenv() and unsetenv() using getenv(), putenv(), and, where necessary,
    code that directly modifies environ. Your version of unsetenv() should check to see
    whether there are multiple definitions of an environment variable, and remove
    them all (which is what the glibc version of unsetenv() does). */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern char **environ;
static char eq = '=';

int Setenv(const char *name, const char *value, int overwrite) {
    /*  After putenv() call, string is part of the enviroment. One of the
        elements of environ will be set to POINT TO THE SAME LOCATION AS STRING.  
        Therefore, string should not be an automatic variable (i.e. character array
        allocated on the stack), since this memory area may be overwritten. */
    int res = 0;
    char *str;
    
    str = (char*) malloc(strlen(name) + strlen(value) + 2); // +2 for null-character and '='
    strcpy(str, name);
    strcat(str, &eq);
    strcat(str, value);

    /*  The setenv() function doesn’t change the environment if the variable identified
        by name already exists and overwrite has the value 0. */
    if (getenv(name) == NULL || overwrite != 0)
        res = putenv(str);
    
    return res;
}

int Unsetenv(const char *name) {
    char *str;
    int res = 0;

    while (getenv(name) != NULL && res == 0) {
        strcpy(str, name);
        res = putenv(str);
    }

    return res;
}

int main(int argc, char *argv[]) {
    char **ep;
    static char *var = "LOL=1";
    static char *var2 = "DELL=3";
    int res = 0;
    
    putenv(var);
    putenv(var2);

    if (argc < 3) {
        printf("Invalid command line arguments\n");
        return 0;
    }

    printf("Before operation:\n");
    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);

    if (argc == 5 && (strcmp(argv[1], "set") == 0)) {
        res = Setenv(argv[2], argv[3], atoi(argv[4]));
    }
    else if (argc == 3 && (strcmp(argv[1], "unset") == 0)) {
        res = Unsetenv(argv[2]);
    } else return 0;

    if (res != 0)
        exit(EXIT_FAILURE);  

    printf("After operation:\n");
    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);

    exit(EXIT_SUCCESS);
}

/*  Usage examples:
    (1) ./3-exercise unset LOL
    (2) ./3-exercise set DELL OK 1
    (3) ./3-exercise set GIS 1317 0
    */