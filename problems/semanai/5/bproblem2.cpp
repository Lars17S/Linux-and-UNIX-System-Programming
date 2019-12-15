#include <bits/stdc++.h> 
#include <cmath>
using namespace std; 

bool sumSquare(long long n) 
{ 
    unordered_map<long long, long long> s; 
    for (long long i = 0; i * i <= n; ++i) { 
  
        // store square value in hashmap 
        s[i * i] = 1; 
        if (s.find(n - i * i) != s.end()) { 
            //cout << sqrt(n - i * i) << "^2 + "
             //    << i << "^2" << endl; 
            return true; 
        } 
    } 
    return false; 
} 
bool isPrime(int n) 
{ 
    // Corner case 
    if (n <= 1) 
        return false; 
  
    // Check from 2 to n-1 
    for (int i = 2; i < n; i++) 
        if (n % i == 0) 
            return false; 
  
    return true; 
} 

bool sumSquare2(long long n) 
{ 
    for (long long i = 1; i * i <= n; i++) 
        for (long long j = 1; j * j <= n; j++) 
            if (i * i + j * j == n) { 
                return true; 
            } 
    return false; 
} 
  
// driver Program 
int main() 
{ 
    long long n;
    vector<long long> T_n;
    cin >> n;
    long long k = 1;
    long long T = (k * (k + 1)) / 2;
    while(T <= n) {
        T_n.push_back(T);
        ++k;
        T = (k * (k + 1)) / 2;
    }

    for (long long i = 0; i < T_n.size(); ++i) {
        if (binary_search(T_n.begin(), T_n.end(), n - T_n[i])) {
            cout << "YES" << endl;
            return 0;
        }
    }

    cout << "NO" << endl;
    return 0;
} 