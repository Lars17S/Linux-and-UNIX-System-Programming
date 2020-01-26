//  Listing 9-1: Display all process user and group IDs
/*  access to traditional functions which were omitted from the
    POSIX standard */
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/fsuid.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
/*  userNameFromID() and groupNameFromId() functions */
#include "../../chp8-users-and-groups/listing/ugid_functions.h"
#include "../../chp8-users-and-groups/listing/ugid_functions.c"

#define SG_SIZE (NGROUPS_MAX + 1)

int main(int argc, char *argv[]) {
    /*  real user id, effective id, saved-set-id, file-system id (linux) */
    uid_t ruid, euid, suid, fsuid;
    gid_t rgid, egid, sgid, fsgid;
    gid_t suppGroups[SG_SIZE];
    int numGroups, j;
    char *p;

    /*  read the user IDs process */
    if (getresuid(&ruid, &euid, &suid) == -1) {
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    /*  read the group IDs process */
    if (getresgid(&rgid, &egid, &sgid) == -1) {
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /*  Attempts to change file-system IDs are always ignored
        for unprivileged processes, but even so, the following
        calls return the current file-system IDs 
        "setfsuid() Always returns the previous file-system user ID" */

    fsuid = setfsuid(0);
    fsgid = setfsgid(0);

    printf("UID: ");
    p = userNameFromId(ruid);
    printf("real=%s (%ld); ", (p == NULL) ? "???" : p, (long) ruid);
    p = userNameFromId(euid);
    printf("eff=%s (%ld); ", (p == NULL) ? "???" : p, (long) euid);
    p = userNameFromId(suid);
    printf("saved=%s (%ld); ", (p == NULL) ? "???" : p, (long) suid);
    p = userNameFromId(fsuid);
    printf("fs=%s (%ld); ", (p == NULL) ? "???" : p, (long) fsuid);
    printf("\n");

    printf("GID: ");
    p = groupNameFromId(rgid);
    printf("real=%s (%ld); ", (p == NULL) ? "???" : p, (long) rgid);
    p = groupNameFromId(egid);
    printf("eff=%s (%ld); ", (p == NULL) ? "???" : p, (long) egid);
    p = groupNameFromId(sgid);
    printf("saved=%s (%ld); ", (p == NULL) ? "???" : p, (long) sgid);
    p = groupNameFromId(fsgid);
    printf("fs=%s (%ld); ", (p == NULL) ? "???" : p, (long) fsgid);
    printf("\n");

    /*  A user on Linux belongs to a primary group, which is specified in the
        /etc/passwd file, and can be assigned to multiple supplementary groups,
        which are specific in the /etc/group file. 
        
        getgroups() returns the supplementary group IDs of the calling
        process in list.*/
    
    numGroups = getgroups(SG_SIZE, suppGroups);
    if (numGroups == -1) {
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("Supplementary groups (%d): ", numGroups);
    for (j = 0; j < numGroups; j++) {
        p = groupNameFromId(suppGroups[j]);
        printf("%s (%ld) ", (p == NULL) ? "???" : p, (long) suppGroups[j]);
    }
    printf("\n");
    
    exit(EXIT_SUCCESS);
}

/*  Try ./idshow and sudo ./idshow to see the difference 
    root processes always have id 0 */