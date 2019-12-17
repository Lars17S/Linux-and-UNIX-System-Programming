#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    short p;
    cin >> p;
    for (short i = 0; i < p; ++i) {
        int n;
        cin >> n;
        unordered_map<int, int> val;
        for (int j = 0; j < n; ++j) {
            int num;
            cin >> num;
            if (val.count(num) == 0)
                val[num] = 1;
            else val[num]++;
        }

        // Find the minimum frequency 
        int s = val.begin()->second;
        for (pair<int, int> v : val) {
            //cout << "key: " << v.first << " freq: " << v.second << endl;
            if (v.second < s)
                s = v.second;
        }
        
        // Loop through s + 1 to 2
        s = s + 1;
        int min_sum = INT32_MAX;
        for (int j = s; j > 1; j--) {
            int total_j = 0;
            //cout << "s: " << j << endl;
            for (pair<int, int> v : val) {
                bool possible = false;
                int s1 = j;
                int max_i = v.second / s1;
                // Check the solution for every linear combination t(s) + m(s - 1) = freq_i
                for (int t = max_i; t >= 0; t--) {
                    int k = v.second - s1 * t;
                    if (k % (s1 - 1) == 0) {
                        possible = true;
                        int m = k / (s1 - 1);
                        //cout << s1 << "(" << t << ") + " << s1 - 1 << "(" << m << ") = " << v.second << endl;
                        total_j += m + t;
                        break;
                    }
                }
                if (!possible) {
                    total_j = INT32_MAX;
                    break;
                }   
            }
            if (total_j < min_sum)
                min_sum = total_j;
        }
        cout << min_sum << endl;
    }
    return 0;
}
