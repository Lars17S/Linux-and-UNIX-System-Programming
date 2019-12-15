#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;
unsigned long long int fermat_factorization(unsigned long long int& n);

int main()
{
	unsigned long long int n, A; // X = x^2, Y = y^2
	cin >> n;
	cout << fermat_factorization(n);
}

unsigned long long int fermat_factorization(unsigned long long int& n) {
	if (n % 2 != 1)
		return n;
	unsigned long long int x, Y, a;
	x = ceil(sqrt(n));
	Y = x * x - n;
	while (fmod(sqrt(Y), 1.0) != 0.0) {
		++x;
		Y = x * x - n;
	}
	a = x - sqrt(Y);
	if (a == 1 || n / a == 1)
		return max(a, n / a);
	else return fermat_factorization(a);
}