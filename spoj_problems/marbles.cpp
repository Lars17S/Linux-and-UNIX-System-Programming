#include <iostream>
#include <algorithm>
using namespace std;
long long int binomial_coefficient(int n, int k);

int main()
{
	short T;
	int n, k;
	cin >> T;
	for (short i = 0; i < T; ++i) {
		cin >> n >> k;
		if (n == k || k == 1)
			cout << 1 << endl;
		else
			cout << binomial_coefficient(min((k - 1), ((n - 1) - (k - 1))), n - 1) << endl;
	}

	return 0;
}

long long int binomial_coefficient(int n, int k) {
	cout << "Num: " << (k - (n - 1)) << " | Den: " << n << endl;
	if (n == 1)
		return k; // k / 1
	else return binomial_coefficient(n - 1, k) * (k - (n - 1)) / n; //(to avoid floor function)
}