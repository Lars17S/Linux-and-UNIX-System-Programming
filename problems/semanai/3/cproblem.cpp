#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

int main() {
    int n;
    cin >> n;
    int* num = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> num[i];
    }
    vector<int> val;
    int i = 0;
    while (i < n) {
        int count = 1;
        while (i < n - 1 && num[i] == num[i + 1]) {
            ++count;
            ++i;
        }
        //cout << "cont: " << count << endl;
        ++i;
        val.push_back(count);
    }
    vector<int> max;
    for (auto it = val.begin(); it != prev(val.end(), 1); ++it) {
        auto ia = it + 1;
        max.push_back(min(*it, *ia));
    }
    for (auto v : max) {

        //cout << v << " ";
    }
    cout << *max_element(max.begin(), max.end()) * 2 << endl; 
    return 0;
}