#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int i = 0;
    while (i < (n - 1) && arr[i] < arr[i + 1]) {
        ++i;
    }
    while (i < (n - 1) && arr[i] == arr[i + 1]) {
        ++i;
    }
    while (i < (n - 1) && arr[i] > arr[i + 1]) {
        ++i;
    }
    if (i == (n - 1)) 
        cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}