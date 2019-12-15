#include <sys/stat.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    const int dir_err = mkdir("foo", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (dir_err == -1) {
        cout << "Error creating directory" << endl;
        return -1;
    }
    return 0;
}