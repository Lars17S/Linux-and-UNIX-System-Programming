#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    int n;
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        set<char> a;
    set<char> b;
        string str1;
        string str2;
        cin >> str1 >> str2;
        vector<char> s(100000);
        for (int j = 0; j < str1.length(); ++j) {
            //cout << "str1: " << str1[j] << endl;
            a.insert(str1[j]);
        }
        for (int j = 0; j < str2.length(); ++j) {
            //cout << "str2: " << str2[j] << endl;
            b.insert(str2[j]);
        }

        auto it = std::set_intersection (a.begin(), a.end(), b.begin(), b.end(), s.begin());
                                               // 10 20 0  0  0  0  0  0  0  0
        s.resize(it-s.begin());                      // 10 20
        if (s.size() != 0) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
    return 0;
}

