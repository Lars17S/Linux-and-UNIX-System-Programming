/*  8.2 Implement getpwnam() using setpwent(), getpwent(), and
    endpwent(). */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <string.h>

/*  passwd is the structure that defines each element in the /etc/passwd file
    in linux operating systems */
struct passwd *getpwnamT(const char *name) {
    /*  getpwent() function returns records from the password file one by one 
        endpwent() close the password file */
    static struct passwd *pwd;
    do {
        pwd = getpwent();
    } while (pwd != NULL && strcmp(name, pwd->pw_name) != 0);
    endpwent();
    return pwd;
}

/*  printf() format
    (1) A minus(-) sign tells left alignment.
    (2) A number after % specifies the minimum field width to be printed if the characters
        are less than the size of width the remaining space is filled with space and if it
        is greater than it printed as it is without truncation. */
int main(int argc, char *argv[]) {
    struct passwd *pwdTest;
    if ( (pwdTest = getpwnamT(argv[1]))!= NULL)
        printf("%-8s %ld\n", pwdTest->pw_name, (long) pwdTest->pw_uid);
    else printf("%s Not found\n", argv[1]);

    exit(EXIT_SUCCESS);
}