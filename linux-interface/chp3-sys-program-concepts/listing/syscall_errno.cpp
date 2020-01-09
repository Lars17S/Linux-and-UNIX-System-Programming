#include <iostream>
#include <cmath>
#include <string.h>
#include <cerrno>
using namespace std;

/* Almost every system call and library function returns some type of status. 
Linux kernel reports of a system call. This status value should always be checked */

int main(int argc, char* argv[]) {
    double not_a_number = log(-1.0);
    /* The errno defines the integer variable, which is set by system calls
    and some library functions in the event of an error to indicate what went
    wrong */
    if (errno == EDOM)
        cout << "log(-1) failed: " << strerror(errno) << endl;
    return 0;
}