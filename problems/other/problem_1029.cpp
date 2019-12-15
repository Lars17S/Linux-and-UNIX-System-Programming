#include <iostream>
#include <string>
#include <math.h>
using namespace std;
pair<int, int> search_max_substring(string A);
string replace_substring(string A, int i, int j, int k);

int main() {
    int n, k;
    string A;
    cin >> n >> k >> A;
    pair<int, int> index = search_max_substring(A);
    //cout << "max_substring: " << A.substr(index.second) << endl;
    string fin_string = replace_substring(A, index.first, A.length(), k);
    cout << fin_string << endl;
    return 0;
}

pair<int, int> search_max_substring(string A) {
    int j = A.find(A[0], 1);
    while (j < A.length()) {
        int i = 0;
        int j_init = j;
        while (j < A.length() && A[i] == A[j]) {
            ++i;
            ++j;
        }
        if (j == A.length())
            return make_pair(i, j_init);
        j = A.find(A[0], j_init + 1);
    }
    return make_pair(0, A.length());
}

string replace_substring(string A, int i, int j, int k) {
    string res = A;
    int r = j - i;
    for (int t = 1; t < k; ++t) {
        res.replace(r, res.length() - r, A);
        r += j - i;
    }
    return res;
}