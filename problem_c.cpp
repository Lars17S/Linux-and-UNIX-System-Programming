#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int convert_val(int& value);

const int SIZE = 200000;
int arr[SIZE];

int main()
{
	int n, m, l, r;
	int pos;
	char s;
	l = 0; 
	r = 0;
	cin >> n; // Set number of instructions
	cin >> s; // First input
	cin >> m;
	arr[convert_val(l)] = m;
	for (int i = 0; i < (n - 1); ++i) {
		cin >> s;
		cin >> m;
		switch (s) {
		case 'L':
			--l;
			arr[convert_val(l)] = m;
			break;
		case 'R':
			++r;
			arr[convert_val(r)] = m;
			break;
		case '?':
			pos = find(&arr[convert_val(l)], &arr[convert_val(r)], m) - arr;
			cout << min(abs(l - (pos - 100000)), abs(r - (pos - 100000))) << endl;
			break;
		}
	}

	return 0;
}

int convert_val(int& value) {
	return value + 100000;
}
