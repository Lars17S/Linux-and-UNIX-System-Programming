#include <iostream>
using namespace std;

int main() {
	short t;
	long long a, b, k;
	cin >> t;
	for (short i = 0; i < t; ++i) {
		cin >> a >> b >> k;
		if (k % 2 == 0)
			cout << (k / 2) * (a - b) << endl;
		else
			cout << (((k - 1) / 2) * (a - b)) + a << endl;
	}

	return 0;
}