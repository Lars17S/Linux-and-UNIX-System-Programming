#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int length;
        cin >> length;
        string str;
        cin >> str;
        if (length == 2) {
            if (str[0] < str[1]) {
                cout << "YES" << endl;
                cout << 2 << endl;
                cout << str[0] << " " << str[1] << endl;
            }
            else cout << "NO" << endl;
        }
        else {
            cout << "YES" << endl;
            cout << 2 << endl;
            cout << str[0] << " "  << str.substr(1, str.length() - 1) << endl;
        }
    }

    return 0;
}