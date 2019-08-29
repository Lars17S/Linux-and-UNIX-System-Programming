#include <iostream>
using namespace std;

int main()
{
	short n, sum1 = 0, sum2 = 0;
	short x = -1, y = -1;
	bool state = true; //1 OK, 0 CORRUPT
	cin >> n;
	while (n > 0) {
		bool** A = new bool* [n];
		for (int i = 0; i < n; i++) A[i] = new bool[n];

		for (short i = 0; i < n; ++i)
			for (short j = 0; j < n; ++j)
				cin >> A[i][j];
		short i, j;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				sum1 += A[i][j];
				sum2 += A[j][i];
			}
			if (sum1 % 2 != 0) {
				if (x == -1)
					x = i;
				else state = false;
			}
			if (sum2 % 2 != 0) {
				if (y == -1)
					y = i;
				else state = false;
			}
			sum1 = 0;
			sum2 = 0;
		}

		if (x == -1 && y == -1)
			cout << "OK" << endl;
		else if (state == false || x != -1 && y == -1 || x == -1 && y != -1)
			cout << "Corrupt" << endl;
		else if (x != -1 && y != -1)
			cout << "Change bit (" << x + 1 << "," << y + 1 << ")" << endl;

		x = -1;
		y = -1;
		state = true;
		delete[] A;
		cin >> n;
	}

	return 0;
}
