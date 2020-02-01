/*  12-1. Write a program that lists the process ID and command name for all processes
    being run by the user named in the program’s command-line argument. (You may
    find the userIdFromName() function from Listing 8-1, on page 159, useful.) This can
    be done by inspecting the Name: and Uid: lines of all of the /proc/PID/status files on
    the system. Walking through all of the /proc/PID directories on the system requires the
    use of readdir(3), which is described in Section 18.8. Make sure your program
    correctly handles the possibility that a /proc/PID directory disappears between the
    time that the program determines that the directo 
*/
#define _GNU_SOURCE
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "../../useful-functions/ugid_functions.h"
#include "../../useful-functions/ugid_functions.c"

int main(int argc, char *argv[]) {
    struct dirent *entry;
    struct stat filestat;
    int userId;
    DIR *dfd;

    if (argc != 2) {
        printf("Invalid command-line argument\n");
        exit(EXIT_FAILURE);
    }

    if ( (userId = (int) userIdFromName(argv[1])) == -1) {
        printf("Invalid user name\n");
        exit(EXIT_FAILURE);
    }

    if ( (dfd = opendir("/proc/")) == NULL) {
        printf("Can't open /proc/ \n");
        exit(EXIT_FAILURE);
    }

    while ( (entry = readdir(dfd)) != NULL) {
        stat(entry->d_name, &filestat);
        if (S_ISDIR(filestat.st_mode)) {
            FILE *fd;
            ssize_t read;
            size_t len = 0;
            char *line = NULL;
            char *str = (char*) malloc(256 * sizeof(char));
            
            strcat(str, "/proc/");
            strcat(str, entry->d_name);
            strcat(str, "/status");
            if ( (fd = fopen(str, "r")) == NULL) {
                free(str);
                continue;
            }

            if (( (read = getline(&line, &len, fd)) != -1))
                printf("%s", line);
            
            fclose(fd);
            free(str);
            if (line)
                free(line);
        }
    }

    exit(EXIT_SUCCESS);
}