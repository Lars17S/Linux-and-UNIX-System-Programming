#include <iostream>
using namespace std;

int main() {
	short n, r, res, Ll, Lr, p, q, i, j;
	short heat = 0;
	bool left_p = true, right_p = true;
	cin >> n;
	cin >> r;
	char* arr = new char[n];
	for (short k = 0; k < n; ++k) {
		cin >> arr[k];
	}

	Ll = -1;
	Lr = n;
	res = 0;
	while (Ll + 1 < Lr && (left_p || right_p) && heat < n) {
		p = Ll + r;
		q = Lr - r;
		i = p;
		j = q;
	
		if (left_p == true) {
			while (arr[i] != '1' && i > 0 && i > p - 2 * (r - 1))
				--i;
			if (arr[i] == '1') {
				Ll = i + r - 1;
				heat = (Ll + 1) + (n - Lr);
				++res;
			}
			else left_p = false; // Pointer 1 death
		}

		if (heat >= n)
			break;

		if (right_p == true) {
			while (arr[j] != '1' && j < (n - 1) && j < q + 2 * (r - 1))
				++j;
			if (arr[j] == '1') {
				Lr = j - r + 1;
				heat = (Ll + 1) + (n - Lr);
				++res;
			}
			else right_p = false; // Pointer 2 death
		}
	}

	if (left_p == false && right_p == false)
		cout << -1 << endl;
	else
		cout << res << endl;
	return 0;
}