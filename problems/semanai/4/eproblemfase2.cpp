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
    vector<int> max;
    int i = 0;
    if (n == 1) {
        cout << 1 << endl;
    }
    else {
        while (i < n - 1) {
            int j = i;
            int count = 1;
            while (i < n - 1 && num[i] <= num[i + 1]) {
                ++i;
                ++count;
            }
            max.push_back(count);
            ++i;
        }
        cout << *max_element(max.begin(), max.end()) << endl;
    }
    
    return 0;
}