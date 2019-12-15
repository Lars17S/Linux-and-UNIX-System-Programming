#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> positive;
    vector<int> negative;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        if (x > 0)
            positive.push_back(x);
        else if (x < 0)
            negative.push_back(x);
    }
    if (positive.size() >= ceil((double)n / 2))
        cout << 1 << endl;
    else if (negative.size() >= ceil((double)n / 2))
        cout << -1 << endl;
    else cout << 0 << endl;
    return 0;
}