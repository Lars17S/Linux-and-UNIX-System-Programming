#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> nums;
    vector<pair<int, int>> range;
    for (int i = 0; i < n; ++i) {
        long long input;
        cin >> input;
        nums.push_back(input);
    }
    string str;
    cin >> str;
    int i = 0;
    int j = 0;
    while (i < n) {
        j = i;
        while (str[i] == str[j]) {
            ++j;
        }
        //cout << "i: " << i << " j: " << j - 1<< endl;
        range.push_back(make_pair(i, j - 1));
        i = j;
        
    }
    for (auto pair : range) {
        auto it_left = next(nums.begin(), pair.first);
        auto it_right = next(nums.begin(), pair.second);
        sort(it_left, next(it_right, 1));
        
    }
    long long sum = 0;
    for (auto pair : range) {
        
        int i = pair.first;
        int j = pair.second;
        int count = 0;
        //cout << "i: " << i << " j: " << j << endl;
        while (j >= i && count < k) {
            //cout << "a[j]: " << nums[j] << endl;
            sum = sum + nums[j];
            ++count;
            --j;
        }
    }
    
    cout << sum << endl;
    return 0;
}