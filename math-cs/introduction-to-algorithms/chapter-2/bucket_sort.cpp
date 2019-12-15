#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
double* bucketSort(double* arr, int& n);

const int size = 10;

int main() {
    int n;
    cin >> n;
    double* arr = new double[n];
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    double* arr_sort = bucketSort(arr, n);
    for (int i = 0; i < n; ++i) 
        cout << arr_sort[i] << " ";
    return 0;
}

double* bucketSort(double* arr, int& n) {
    vector<vector<double>> B(10);
    for (int i = 0; i < n; ++i)
        B[floor(n * arr[i])].push_back(arr[i]);
    for (int i = 0; i < 10; ++i) {
        // Insertion sort
        if (B[i].size() <= 1) 
            continue;
        for (int j = 1; j < B[i].size(); ++j) {
            double key = B[i][j];
            int k = j - 1;
            while (k >= 0 && key < B[i][k]) {
                B[i][k + 1] = B[i][k];
                --k;
            }
            B[i][k + 1] = key;
        }
    }
    // Concatonate list
    double* B_sort = new double[n];
    for (int i = 0; i < n;)
        for (auto it_i : B) 
            for (auto it_j : it_i) {
                B_sort[i] = it_j;
                ++i;
            }
    return B_sort;
}