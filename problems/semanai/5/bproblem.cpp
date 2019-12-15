#include <iostream>
#include <cmath>
#include <unordered_map>
using namespace std;


bool sumSquare(long long n) 
{ 
    unordered_map<long long, long long> s; 
    for (long long i = 0; i * i <= n; ++i) { 
  
        // store square value in hashmap 
        s[i * i] = 1; 
        if (s.find(n - i * i) != s.end()) { 
            //cout << sqrt(n - i * i) << "^2 + "
                 //<< i << "^2" << endl; 
            return true; 
        } 
    } 
    return false; 
} 

int main() {
    long long n;
    cin >> n;
    long long num = 8 * n + 2;
    //cout << num << endl;
    if (n == 1) {
        cout << "NO" << endl;
    }else {
    if (sumSquare(num)) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    }
    return 0;
}