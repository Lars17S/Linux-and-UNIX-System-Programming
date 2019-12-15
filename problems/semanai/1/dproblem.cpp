#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    int broken_stick[n];
    for (int i = 0; i < n; ++i)
        cin >> broken_stick[i];
    vector<int> spaces;
    for (int i = 0; i < n - 1; ++i)
        spaces.push_back(broken_stick[i + 1] - broken_stick[i] - 1);
    sort(spaces.begin(), spaces.end(), greater<int>());
    int broken_stickLength = broken_stick[n-1] - broken_stick[0] + 1;
    for (int i = 0; i < k - 1; ++i)
        broken_stickLength -= spaces[i];
    cout << broken_stickLength << endl;
    return 0;
}