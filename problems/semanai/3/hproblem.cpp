#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long* num_worm = new long long[n];
    for (long long i = 0; i < n; ++i) {
        cin >> num_worm[i];
    }
    long long j_worm;
    cin >> j_worm;
    long long* label = new long long[j_worm];
    for (long long i = 0; i < j_worm; ++i) {
        cin >> label[i];
    }
    vector<long long> range;
    long long l = 0;
    long long r = l + num_worm[0];
    range.push_back(l); 
    for (long long i = 1; i < n; ++i) {
        l = r + 1;
        r = r + num_worm[i];
        //cout << "l: " << l << " r: " << r << endl;
        range.push_back(l);
    }
    for (auto pair : range) {
        //cout << pair << endl;
    }

    for (long long i = 0; i < j_worm; ++i) {
        std::vector<long long>::iterator low1 = upper_bound(range.begin(), range.end(), label[i]);
        cout << low1 - range.begin() << endl;
    }

    return 0;
}