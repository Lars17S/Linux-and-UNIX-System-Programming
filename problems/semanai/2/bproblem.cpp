#include <iostream>
using namespace std;

int main() {
    int andrew, dmitry, michal;
    cin >> andrew >> dmitry >> michal;
    int green, purple, black;
    cin >> green >> purple >> black;
    int rest = 0;
    if (green >= andrew) {
        int rest_green;
        rest_green = green - andrew;
        if (rest_green + purple >= dmitry) {
            int rest_gp = (rest_green + purple) - dmitry;
            if (rest_gp + black >= michal) {
                cout << "YES" << endl;
            }
            else {
                cout << "NO" << endl;
            }
        }
        else {
            cout << "NO" << endl;
        }
    }
    else {
        cout << "NO" << endl;
    }
    return 0;
}