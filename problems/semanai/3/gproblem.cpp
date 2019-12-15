#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    cin.clear(); cin.ignore();
    string str;
    getline(cin, str);
    //cout << str << endl;
    vector<int> count;
    int i = 0;
    while (i < n) {
        count.push_back(0);
        auto it = count.rbegin();
        while (i < n && str[i] != ' ') {
            if (isupper(str[i])) {
                //cout << str[i] << endl;
                *it = *it + 1;
            }
            ++i;
        }
        ++i;
        //cout << *it << endl;
    }
    cout << *max_element(count.begin(), count.end()) << endl;
}