#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    int* num = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> num[i];
    }
    if (n == 1) {
        cout << 0 << endl;
    }
    else {
        vector<int> range;
        int i = 0;
        while (i < n) {
            int p = i;
            int q = i;
            int count = 0;
            if (count < n && i == 0 && num[1] == 2) {
                //cout << "num[i]: " << num[i] << " ";
                ++i;
                q = i;
                ++count;
            }
            while (i >= 1 && i < n - 1 && num[i] == num[i + 1] - 1 && num[i] == num[i - 1] + 1 && count < n) {
                //cout << "num[i]: " << num[i] << " ";
                ++i;
                q = i;
                ++count;
            }
            if (q == n - 1 && count < n - 1 && num[n - 2] == 999) {
                //cout << "num[i]: " << num[i] << endl;
                ++i;
                ++q;
                ++count;
            }
            //cout << "p: " << p << " | q: " << q << endl;
            range.push_back(count);
            ++i;
        }
        for (auto i : range) {
            //cout << i << " ";
        }
        cout << *max_element(range.begin(), range.end()) << endl;
    }
}