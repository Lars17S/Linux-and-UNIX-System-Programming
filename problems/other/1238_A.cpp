#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i) {
        long long num1, num2;
        cin >> num1 >> num2;
        //cout << "num1: " << num1 << " num2: " << num2 << endl;
        if (num1 - num2 != 1)
            cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}