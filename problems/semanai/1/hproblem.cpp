#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        long long x, y;
        cin >> x >> y;
        if (abs(x - y) != 1)
            cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}