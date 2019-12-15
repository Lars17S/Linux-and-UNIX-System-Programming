#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, d;
    cin >> n >> d;
    string s;
    cin >> s;
    //cout << "s: " << s << endl;
    int i = 0;
    int num_jump = 0;
    bool possible = true;
    while (i != n - 1) {
        //cout << "i: " << i << endl;
        int jump = min(d, (n - 1) - i);
        //cout << "jump: " << jump << endl;
        int search_i = i + jump;
        //cout << "search_i " << search_i << endl;
        //cout << "s[search_i]: " << s[search_i] << endl;
        while (search_i > i && s[search_i] != '1') {
            //cout << "s: " << s[search_i] << endl;
            --search_i;
        }
        //cout << "search_i " << search_i << endl;
        if (search_i == i) {
            possible = false;
            break;
        }
        ++num_jump;
        i = search_i;
    }
    if (possible) {
        cout << num_jump << endl;
    }
    else {
        cout << -1 << endl;
    }
    return 0;
}