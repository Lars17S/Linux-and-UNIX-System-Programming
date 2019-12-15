#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long* num = new long long[n];
    multiset<long long> neg;
    multiset<long long> pos;
    multiset<long long> zero;
    long long sum_neg = 0;
    long long sum_zero = 0;
    long long sum_pos = 0;
    for (long long i = 0; i < n; ++i) {
        cin >> num[i];
        if (num[i] < 0) {
            neg.insert(num[i]);
        }
        else if (num[i] == 0) {
            zero.insert(num[i]);
        }
        else {
            pos.insert(num[i]);
        }
    }
    if (neg.size() % 2 == 0) {
        for (auto v : neg) {
            cout << "v neg: " << v << endl;
            sum_neg += abs(-1 - v);
            cout << sum_neg << endl;
        }
    }
    else {
        if (zero.size() >= 1) { // Expend 1 zero
            for (auto v : neg) {
                sum_neg += abs(-1 - v);
            }
        } else {
            for (auto it = neg.begin(); it != prev(neg.end(), 1); ++it) {
                cout << "*it: " << *it << endl;
                sum_neg += abs(-1 - *it);
            }
            sum_neg += abs(1 - *(prev(neg.end(), 1)));
        }
    }
    sum_zero = zero.size();
    for (auto v : pos) {
        sum_pos += abs(1 - v);
    }
    cout << "sum_neg: " << sum_neg << endl;
    cout << "sum_zero: " << sum_zero << endl;
    cout << "sum_pos: " << sum_pos << endl;
    cout << "total: " << sum_neg + sum_zero + sum_pos << endl;
    cout << sum_neg + sum_zero + sum_pos << endl;
    return 0;
}