#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    int n;
    double k;
    cin >> n >> k;
    int min = 999999999;
    int index;
    for (int i = 0; i < n; ++i) {
        // k + r = a + bn
        double a, b, r;
        cin >> a >> b;
        if (k < a)
            r = a - k;
        else if (k == a) {
            r = 0;
        }
        else {
            r = b * (double)ceil((k - a) / b) - (k - a);
        }
        if (min > r) {
            min = r;
            index = i + 1;
        }
        //cout << "r: " << r << endl;
    }
    cout << index << endl;
    return 0;
}