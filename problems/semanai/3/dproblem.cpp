#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    string str;
    cin >> str;
    if (n == 1) {
        cout << "NO" << endl;
    }
    else {
        int i = 0;
        while (i < (n - 1) && str[i] == str[i + 1]) {
            ++i;
        }
        if (i == n - 1) {
            cout << "NO" << endl;
        } else {
            string res;
            res.push_back(str[i]);
            res.push_back(str[i + 1]);
            cout << "YES" << endl;
            cout << res << endl;
        }
        
    }
    return 0;
}