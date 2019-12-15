#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, c;
    cin >> n >> c;
    int g = 0;
    int k = 1;
    int costo = 0;
    while (g < n - k && k <= n) {
        int llenar = min(c - g, n - k);
        //cout << "llenar: " << llenar << endl;
        costo = costo + llenar * k;
        //cout << "costo: " << costo << endl;
        g = g + llenar;
        //cout << "g: " << g << endl;
        ++k;
        --g;
    }
    cout << costo << endl;
    return 0;
}