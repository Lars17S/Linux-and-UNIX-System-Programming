#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int main() {
    short N, A;
    cin >> N;
    cin >> A;
    int limit_x2 = -INT32_MAX; 
    int limit_y2 = INT32_MAX;
    int limit_x1 = INT32_MAX;
    int limit_y1 = -INT32_MAX;
    for (short i = 0; i < A; ++i) {
        short x, y;
        cin >> x >> y;
        if (limit_x2 < x)
            limit_x2 = x;
        if (limit_x1 > x)
            limit_x1 = x;
        if (limit_y2 > y) 
            limit_y2 = y;
        if (limit_y1 < y)
            limit_y1 = y;
    }
    if (limit_x2 < 0)
        limit_x2 = 0;
    if (limit_x1 > 0)
        limit_x1 = 0;
    if (limit_y2 > 0) 
        limit_y2 = 0;
    if (limit_y1 < 0)
        limit_y1 = 0;
    cout << "limit_x1: " << limit_x1 << endl;
    cout << "limit_y1: " << limit_y1 << endl;
    cout << "limit_x2: " << limit_x2 << endl;
    cout << "limit_y2: " << limit_y2 << endl;
    short diff_x = abs(limit_x1 - limit_x2);
    short diff_y = abs(limit_y1 - limit_y2);
    vector<string> box;
    cout << "diff_x: " << diff_x << endl;
    cout << "diff_y: " << diff_y << endl;
    for (short i = 0; i < diff_x; ++i) {
        box.push_back("");
        for (short j = 0; j < diff_y; ++j) {
            box[i] += "o";
        }
        cout << box[i] << endl;
    }
    short x1 = limit_x1;
    short y1 = limit_y1;
    box[-x1][-y1] = 'x';
    for (short i = 0; i < diff_x; ++i) {
        cout << box[i] << endl;
    }
    return 0;
}