#include <sys/times.h>
#include <time.h>
#include <unistd.h>

#include "../../useful-functions/error_handler.h"
#include "../../useful-functions/error_handler.c"

/*  This macro expands to an expression representing the number of clock
    ticks per second. Clock ticks are units of time of a constant but
    system-specific length, as those returned by function clock.
    CLK_TCK is an obsolete alias of this macro. */


/*  Display 'msg' and process time */
static void displayProcessTimes(const char *msg) {
    struct tms t;
    clock_t clockTime;
    static long clockTicks = 0;

    if (msg != NULL)
        printf("%s\n", msg);
    
    /*  Fetch clock ticks on first call */
    if (clockTicks == 0) {
        /*  POSIX allows an application to test at compile or run time whether
            certain options are supported, or what the value is of certain
            configurable constants or limits.
            
            _SC_CLK_TCK is the number of clock ticks per second, usually kernel
            is configured for 100 clocks per second (or 100Hz clock). */
        clockTicks = sysconf(_SC_CLK_TCK);
        if (clockTicks == -1) 
            errExit("sysconf");
    }

    /*  The C library function clock_t clock(void) returns the number of clock
        ticks elapsed since the program was launched. To get the number of seconds
        used by the CPU, you will need to divide by CLOCKS_PER_SEC. */
    clockTime = clock();
    if (clockTime == -1) 
        errExit("clock");

    printf("    clock() returns: %ld clocks-per-sec (%.2f secs)\n",
                (long) clockTime, (double) clockTime / CLOCKS_PER_SEC);
    
    /*  On success, times() returns the elapsed (real) time in clock ticks since
        some arbitrary point in the past. 
        On Linux, we can specify buf as NULL; in this case, times() simply returns
        a function result. However, this is not portable. */
    if (times(&t) == -1)
        errExit("times");
    printf("    times() yields: user CPU=%.2f; system CPU: %.2f\n",
            (double) t.tms_utime / clockTicks,
            (double) t.tms_stime / clockTicks);
}

int main(int argc, char *argv[]) {
    int numCalls, j;
    printf("CLOCKS_PER_SEC=%ld sysconf(_SC_CLK_TCK)=%ld\n\n",
                (long) CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK));
    
    displayProcessTimes("At program start:\n");
    
    numCalls = (argc > 1) ? atoi(argv[1]) : 100000;
    for (j = 0; j < numCalls; j++)
        (void) getppid();
    
    displayProcessTimes("\nAfter getppid() loop:\n");
    
    exit(EXIT_SUCCESS);
}