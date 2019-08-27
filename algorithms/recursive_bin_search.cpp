#include <iostream>
#include <algorithm>
using namespace std;
int recursive_bin_search(int A[], int i, int j, int x);

int main()
{
	int n, x, i, j;
	cin >> n;
	int* A = new int[n];
	for (int i = 0; i < n; ++i)
		cin >> A[i];
	sort(&A[0], &A[n - 1]);
	cout << "x value: ";
	cin >> x;
	cout << "left limit i: ";
	cin >> i;
	cout << "right limit j: ";
	cin >> j;
	cout << "position: " << recursive_bin_search(A, i, j, x);

	delete[] A;
	return 0;
}

int recursive_bin_search(int A[], int i, int j, int x) {
	int m = (i + j) / 2;
	if (x == A[m])
		return m;
	else if (x < A[m] && i < m)
		return recursive_bin_search(A, i, m - 1, x);
	else if (x > A[m] && j > m)
		return recursive_bin_search(A, m + 1, j, x);
	else
		return -1;
}