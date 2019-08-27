#include <iostream>
#include <algorithm>
using namespace std;
int recursive_gcd(int& a, int& b);

int main() {
	int a, b;
	cin >> a >> b;
	if (a == b) {
		cout << "gcd: " << a << endl;
		return 0;
	}
	else if (a < b)
		swap(a, b);
	cout << "gcd: " << recursive_gcd(a, b) << endl;
	return 0;
}

int recursive_gcd(int& a, int& b) {
	if (b == 0)
		return a;
	else return recursive_gcd(b, a % b);
}