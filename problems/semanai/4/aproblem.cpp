#include <iostream>
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long bill100 = 0;
    long long bill20 = 0;
    long long bill10 = 0;
    long long bill5 = 0;
    long long bill1 = 0;
    bill100 = n / 100;
    //cout << bill100 << endl;
    n = n % 100;
    bill20 = n / 20;
    //cout << bill20 << endl;
    n = n % 20;
    bill10 = n / 10;
    //cout << bill10 << endl;
    n = n % 10;
    bill5 = n / 5;
    //cout << bill5 << endl;
    n = n % 5;
    bill1 = n / 1;
    //cout << bill1 << endl;
    cout << bill100 + bill20 + bill10 + bill5 + bill1 << endl;
    return 0;
}