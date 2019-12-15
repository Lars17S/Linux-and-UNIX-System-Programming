#include <iostream>
using namespace std;

int main() {
    int n, k;   
    cin >> n >> k;
    int* num = new int[n];
    for (int i = 0; i < n; ++i) 
        cin >> num[i];
    int i = -1; 
    int j = n;
    bool left_most = true;
    bool right_most = true;
    while (i < j && (left_most == true || right_most == true)) {
        if (left_most) {
            if (num[i + 1] <= k)
                ++i;
            else left_most = false;
        }

        if (i >= j) break;

        if (right_most) {
            if (num[j - 1] <= k)
                --j;
            else right_most = false;
        }
        //cout << "i: " << i << " | j: " << j << endl;
    }
    int total;
    if (i != j) {
        total = (i + 1) + (n - j);
    } else total = i + n - j;
    
    cout << total << endl;
    return 0;
}