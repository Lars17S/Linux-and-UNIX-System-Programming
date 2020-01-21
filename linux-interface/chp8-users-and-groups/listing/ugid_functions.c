/*  Listing 8-1: Functions to convert user and group IDs to and from user
    and group names */

#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include <stdlib.h>

/*  This is an integer data type used to represent user IDs.
    In the GNU C Library, this is an alias for unsigned int */
char* userNameFromId(__uid_t uid) {
    struct passwd *pwd;
    pwd = getpwuid(uid);
    return (pwd == NULL) ? NULL : pwd->pw_name;
}

__uid_t userIdFromName(const char *name) {
    struct passwd *pwd;
    __uid_t u;
    char *endptr;

    if (name == NULL || *name == '\0')
        return -1;
    
    /*  converts the initial part of the string in str to a long int value
        according to the given base. */
    u = strtol(name, &endptr, 10);
    if (*endptr == '\0') 
        return u;
    
    pwd = getpwdnam(name);
    if (pwd == NULL)
        return -1;
    
    return pwd->pw_uid;
}

char* groupNameFromId(__gid_t gid) {
    struct group *grp;
    grp = getgrgid(gid);
    return (grp == NULL) ? NULL : grp->gr_name;
}

/*  This is an integer data type used to represent group IDs.
    In the GNU C Library, this is an alias for unsigned int. */
__gid_t groupIdFromName(const char *name) {
    struct group *grp;
    __gid_t g;
    char *endptr;

    if (name == NULL || *name == '\0')
        return -1;

    g = strtol(name, &endptr, 10);
    if (*endptr == '\0')
        return g;

    grp = getgrnam(name);
    if (grp == NULL)
        return -1;

    return grp->gr_gid;
}