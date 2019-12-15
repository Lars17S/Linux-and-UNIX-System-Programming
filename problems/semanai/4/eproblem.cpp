#include <iostream>
#include <tuple>
#include <algorithm>
using namespace std;
tuple<int, int, int> find_max(int* num, int low, int high);

int main() {
    int n;
    cin >> n;
    int* num = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> num[i];
    }
    tuple<int, int, int> res = find_max(num, 0, n - 1);
    cout << "l: " << get<0>(res) << " r: " << get<1>(res) << " sum: " << get<2>(res) << endl;
    return 0;
}

tuple<int, int, int> find_max(int* num, int low, int high) {
    int left = 0;
    int right = 0;
    int sum = num[low];
    int temp_sum = 0;
    int temp_left = 0;
    for (int i = 0; i < high; ++i) {
        temp_sum = max(num[i], temp_sum + num[i]);
        if (temp_sum > sum) {
            sum = temp_sum;
            right = i;
            left = temp_left;
        } 
        if (temp_sum == num[i]) {
            temp_left = i;
        }
    }
    return make_tuple(left, right, sum);
}