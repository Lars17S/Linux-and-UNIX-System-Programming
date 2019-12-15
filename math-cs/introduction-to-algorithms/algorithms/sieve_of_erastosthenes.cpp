#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
vector<int> sieve_of_erastosthenes(int& p);

int main()
{
	int n;
	cin >> n;
	for (int j : sieve_of_erastosthenes(n))
		cout << j << endl;
}

// Sieve of Erastosthenes (Algorithm)
// Theorem: If n is a compound number, then there exist at least a prime divisor equal or less than sqrt(n)
vector<int> sieve_of_erastosthenes(int& n) {
	bool* list_number = new bool[n];
	vector<int> prime_nums;
	for (int i = 1; i < n; ++i) {
		list_number[i] = true;
	}

	for (int i = 2; i <= sqrt(n); ++i) {
		if (list_number[i])
			for (int j = i * i; j <= n; j += i)
				list_number[j] = false;
	}

	for (int i = 2; i <= n; ++i) {
		if (list_number[i])
			prime_nums.push_back(i);
	}
	
	return prime_nums;
}
