//  Listing 10-1: Retrieving and converting calendar times

#include <locale.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define SECONDS_IN_TROPICAL_YEAR (365.2419 * 24 * 60 * 60)

int main(int argc, char *argv[]) {
    time_t t;
    struct tm *gmp, *locp;
    struct tm gm, loc;
    struct timeval tv;

    /*  time() function receives an argument. The value returned by the function
        is in two directions, first to the argument variable and the return itself.
        That's why argument can be NULL, since anyway the returned value will be
        captured by the variable t */
    t = time(NULL);
    printf("Seconds since the Epoch (1 Jan 1970): %ld", (long) t);
    printf(" (about %6.3f years)\n", t / SECONDS_IN_TROPICAL_YEAR);

    if (gettimeofday(&tv, NULL) == -1) {
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /*  var member tv_sec: Seconds since 00:00:00, 1 Jan 1970 UTC
        var member tv_usec: Additional microseconds determined by the CPU */
    printf("    gettimeofday() returned %ld secs, %ld microsecs\n",
                (long) tv.tv_sec, (long) tv.tv_usec);

    gmp = gmtime(&t);
    if (gmp == NULL) {
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    gm = *gmp;      /*  Save local copy, since *gmp may be modified
                        by asctime() or gmtime() */
    printf("Broken down by gmtime():\n");
    printf("    year=%d mon=%d mday=%d hour=%d min=%d sec=%d ", gm.tm_year,
                gm.tm_mon, gm.tm_mday, gm.tm_hour, gm.tm_min, gm.tm_sec);
    printf("wday=%d yday=%d isdst=%d\n", gm.tm_wday, gm.tm_yday, gm.tm_isdst);

    locp = localtime(&t);
    if (locp == NULL) {
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    loc = *locp;
    printf("Broken down by localtime():\n");
    printf(" year=%d mon=%d mday=%d hour=%d min=%d sec=%d ",
                loc.tm_year, loc.tm_mon, loc.tm_mday,
                loc.tm_hour, loc.tm_min, loc.tm_sec);
    printf("wday=%d yday=%d isdst=%d\n\n",
                loc.tm_wday, loc.tm_yday, loc.tm_isdst);

    printf("asctime() formats the gmtime() value as:    %s", asctime(&gm));
    printf("ctime() formats the time as:                %s", ctime(&t));

    /*  returns to the time_t type */
    printf("mktime() of gmtime() value:     %ld sec\n", (long) mktime(&gm));
    printf("mktime() of localtime() value: %ld secs\n", (long) mktime(&loc));

    exit(EXIT_SUCCESS);
}