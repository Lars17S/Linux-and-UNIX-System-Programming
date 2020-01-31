/*  11-1. Try running the program in Listing 11-1 on other UNIX implementations if
    you have access to them. */

#include <unistd.h>
#include <string.h>
#include "../../useful-functions/error_handler.h"
#include "../../useful-functions/error_handler.c"

/*  Print 'msg' plus sysconf() value for 'name' */
static void sysconfPrint(const char *msg, int name) {
    long lim;

    errno = 0;
    lim = sysconf(name);
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
    sysconfPrint("_SG_ARG_MAX           ", _SC_ARG_MAX);
    sysconfPrint("_SC_LOGIN_NAME_MAX    ", _SC_LOGIN_NAME_MAX);
    sysconfPrint("_SC_OPEN_MAX:         ", _SC_OPEN_MAX);
    sysconfPrint("_SC_NGROUPS_MAX:      ", _SC_NGROUPS_MAX);
    sysconfPrint("_SC_PAGESIZE:         ", _SC_PAGESIZE);
    sysconfPrint("_SC_RTSIG_MAX:        ", _SC_RTSIG_MAX);
    exit(EXIT_SUCCESS);
}