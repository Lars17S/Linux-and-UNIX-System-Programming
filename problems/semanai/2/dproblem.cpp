#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        double l, r;
        cin >> l >> r;
        l = l - 1;
        long long sum_l, sum_r;
        if ((long long)l % 2 == 0) {
            sum_l = ceil(l / 2);
        } else sum_l = ceil(l / 2) * -1;
        if ((long long)r % 2 == 0) {
            sum_r = ceil(r / 2);
        } else sum_r = ceil(r / 2) * -1;
        cout << sum_r - sum_l << endl;
    }
    return 0;
}