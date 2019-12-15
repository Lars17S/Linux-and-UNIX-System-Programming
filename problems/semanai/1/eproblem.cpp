#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long x, y;
    cin >> x >> y;
    if (x == 1 && y == 1)
        cout << "White" << endl;
    else if (x == n && y == n)
        cout << "Black" << endl;
    else {
        long long dist_white = max(x, y) - 1;
        long long dist_black = max(n - y, n - x);
        if (dist_white <= dist_black) 
            cout << "White" << endl;
        else cout << "Black" << endl;
    }
    return 0;
}