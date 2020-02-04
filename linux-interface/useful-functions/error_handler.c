#include "error_handler.h"

void errExit(const char *msg) {
    printf("%s - errno prints: %s\n", msg, strerror(errno));
    exit(EXIT_FAILURE);
}

void invalidCmdLineArg() {
    printf("Invalid command-line argument\n");
    exit(EXIT_FAILURE);
}