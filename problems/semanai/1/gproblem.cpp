#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    multimap<int, int> nums;
    for (int i = 0; i < n; ++i) {
        int input;
        cin >> input;
        nums.insert(make_pair(input, i + 1));
    }
    vector<pair<int, int>> nums_set; // value, index
    int i = 0;
    multimap<int, int>::iterator it = nums.begin();
    if (nums.size != 1) {
        while (nums_set.size() != k && it != prev(nums.end(), 1)) {
        if (it->first != (next(it, 1)->first))
            nums_set.push_back(make_pair(it->second, it->first));
        ++it;
    }
    else {

    }
    
    if (nums_set.size() == k) {
        cout << "YES" << endl;
        for (auto v : nums_set) {
        cout << v.first << " ";
        }
    }
    else {
        if (prev(nums.end(), 1)->first != (*prev(nums_set.end(), 1)).second)
            nums_set.push_back(make_pair(prev(nums.end(), 1)->second, prev(nums.end(), 1)->first));
        if (nums_set.size() == k) {
            cout << "YES" << endl;
            for (auto v : nums_set) {
                cout << v.first << " ";
            }
        }
        else cout << "NO" << endl;
    }
    
    
    
    return 0;
}