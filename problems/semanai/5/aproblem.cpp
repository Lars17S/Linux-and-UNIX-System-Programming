#include <iostream>
#include <string> 
#include <sstream> 
#include <algorithm>
using namespace std;

int main() {
    int l, r;
    cin >> l >> r;
    bool possible = true;
    for (int i = l; i <= r; ++i) {
        string str = to_string(i);
        
        for (int j = 0; j < str.length(); ++j) {
            size_t n = std::count(str.begin(), str.end(), str[j]);
            //cout << n << endl;
            if (n == 1) {
                possible = true;
            } else {
                possible = false;
                break;
            }
        }
        if (possible == true) {
            cout << str << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}