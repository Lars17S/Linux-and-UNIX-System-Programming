#include <iostream>
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long* num = new long long[n];
    for (long long i = 0; i < n; ++i) {
        cin >> num[i];
    }
    long long max = -1;
    long long i = 0;
    if (n == 1) {
        cout << 1 << endl;
    }
    else {
        while (i < n - 1) {
        long long count = 1;
        while (i < n - 1 && num[i] < num[i + 1]) {
            ++count;
            ++i;
        }
        if (max < count) {
            max = count;
        }
        ++i;
        }
        cout << max << endl;
    }
    
    return 0;
}