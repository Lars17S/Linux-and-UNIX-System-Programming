#include <iostream>
using namespace std;
int recursive_mod_exp(int& b, int n, int& m);

int main()
{
	int b, n, m;
	cout << "b: ";
	cin >> b;
	cout << "n: ";
	cin >> n;
	cout << "m: ";
	cin >> m;
	if (b <= 0 || m < 2 || n < 0)
		return -1;
	cout << b << "^" << n << " mod " << m << " = " << recursive_mod_exp(b, n, m) << endl;
	return 0;
}

int recursive_mod_exp(int& b, int n, int& m) {
	if (n == 0) // Base case b^0 mod m = 1
		return 1;
	else if (n % 2 == 0)
		return (recursive_mod_exp(b, n / 2, m) * recursive_mod_exp(b, n / 2, m)) % m;
	else if (n % 2 != 0)
		return (((recursive_mod_exp(b, n / 2, m) * recursive_mod_exp(b, n / 2, m)) % m) * b % m) % m;
}