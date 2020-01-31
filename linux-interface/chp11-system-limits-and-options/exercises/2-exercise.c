/*  11-2. Try running the program in Listing 11-2 on other file systems. */

#include <unistd.h>
#include <string.h>
#include "../../useful-functions/error_handler.h"
#include "../../useful-functions/error_handler.c"

/*  Print 'msg' plus fpathconf() value for 'name' */
static void fpathconfPrint(const char *msg, int fd, int name) {
    long lim;

    errno = 0;
    lim = fpathconf(fd, name);
    if (lim != -1)        /* Call succeded, limit determinate */
        printf("%s %ld\n", msg, lim);
    else {
        if (errno == 0)     /* Call succeded, limit indeterminate */
            printf("%s (indeterminate)\n", msg);
        else {              /* Call failed */
            char str[] = "sysconf ";
            strncat(str, msg, strlen(msg));
            errExit(str);
        }
    }
}

int main(int argc, char *argv[]) {
    fpathconfPrint("_PC_NAME_MAX: ", STDIN_FILENO, _PC_NAME_MAX);
    fpathconfPrint("_PC_PATH_MAX: ", STDIN_FILENO, _PC_PATH_MAX);
    fpathconfPrint("_PC_PIPE_BUF: ", STDIN_FILENO, _PC_PIPE_BUF);
    exit(EXIT_SUCCESS);
}

/*  OUTPUT:
    _PC_NAME_MAX:  255
    _PC_PATH_MAX:  4096
    _PC_PIPE_BUF:  4096
*/