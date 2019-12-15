#include <iostream>
#include <vector>
using namespace std;

int main()
{
	short n, j = 0, min = 0, int_count = 0;
	char a;
	vector<int> index_num;
	cin >> n;
	char* A = new char[n];
	for (short i = 0; i < n; ++i) {
		cin >> a;
		A[i] = a;
	}
	for (short i = 1; i < n - 1; ++i)
		if (A[i] == '0' && A[i - 1] == '1' && A[i + 1] == '1')
			index_num.push_back(i); //Save index of case (1 0 1)

	while (j < index_num.size()) {
		while ((j < index_num.size() - 1) && (index_num[j] + 2 == index_num[j + 1])) {
			++int_count;
			++j;
		}
		++int_count;
		min += int_count - (int_count / 2);
		int_count = 0;
		++j;
	}

	cout << min << endl;

	return 0;
}
