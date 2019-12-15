#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> arr;
    for (long long i = 0; i < n; ++i) {
        long long input;
        cin >> input;
        arr.push_back(abs(input));
    }
        
    sort(arr.begin(), arr.end());

    long long ans = 0;
    for(long long i = 0; i < n; i++){
        long long pos = upper_bound(arr.begin(), arr.end(), arr[i] * 2) - arr.begin();
        --pos;
        ans += abs(i - pos);
    }

    cout << ans << endl;
    return 0;
}