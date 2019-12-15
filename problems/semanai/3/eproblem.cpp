#include <iostream>
#include <cmath>
using namespace std;

int main() {
    long long T, F;
    cin >> T >> F;
    long long n = (-3 + sqrt(9 + 8 * F + 8 * T)) / 2;
    long long c = T - n;
    cout << c << endl;


    return 0;
}