#define _DEFAULT_SOURCE
#define _XOPEN_SOURCE
#include <unistd.h>
#include <pwd.h>
#include <shadow.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *username, *password, *encrypted, *p;
    struct passwd *pwd;
    struct spwd *spwd;
    bool authOk;
    size_t len;
    long lnmax;

    /*  Get the value of the variable NAME in the enviroment list */
    lnmax = sysconf(_SC_LOGIN_NAME_MAX);
    if (lnmax == -1) 
        lnmax = 256;

    username = malloc(lnmax);
    if (username == NULL) {
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("Username: ");
    /*  Its purpose is to clear (or flush) the output buffer and move
        the buffered data to console or disk */
    fflush(stdout);
    /*  It reads a line from the specified stream and stores it into
        the string pointed to by str. */
    if (fgets(username, lnmax, stdin) == NULL)
        exit(EXIT_FAILURE);

    len = strlen(username);
    if (username[len - 1] == '\n')
        username[len - 1] == '\0';
    
    pwd = getpwnam(username);
    if (pwd == NULL) {
        printf("Could not get password record\n");
        exit(EXIT_FAILURE);
    }
        
    spwd = getspnam(username);
    if (spwd == NULL && errno == EACCES) {
        printf("no permission to read shadow passwod file\n");
        exit(EXIT_FAILURE);
    }

    if (spwd != NULL)       /* If there is a shadow password record */
        pwd->pw_passwd = spwd->sp_pwdp; /* Use the shadow password */

    password = getpass("Password: ");

    /* Encrypt password and erase cleartext version immediately */

    encrypted = crypt(password, pwd->pw_passwd);
    for (p = password; *p != '\0';)
        *p++ = '\0';

    if (encrypted == NULL) {
        printf("Error using crypt() function\n");
        exit(EXIT_FAILURE);
    }

    authOk = strcmp(encrypted, pwd->pw_passwd) == 0;
    if (!authOk) {
        printf("Incorrect password\n");
        exit(EXIT_FAILURE);
    }

    printf("Succesfully authenticated: UID=%ld\n", (long) pwd->pw_uid);

    exit(EXIT_SUCCESS);
}