#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
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
    map<int, int> nums_set;
    multimap<int, int>::iterator it = nums.begin();
    while (nums_set.size() != k && it != nums.end()) {
        if (nums_set.count(it->first) == 0) {
            //cout << "it->first: " << it->first << endl;
            nums_set[it->first] = it->second;
        }
            
        ++it;
    }
    if (nums_set.size() == k) {
        cout << "YES" << endl;
        for (auto v : nums_set)
            cout << v.second << " ";
    }
    else cout << "NO" << endl;
    return 0;
}