#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int N, p;
	cin >> N >> p;
	long long* part_sum = new long long[N];
	cin >> part_sum[0];
	for (int i = 1; i < N; ++i) {
		cin >> part_sum[i];
		part_sum[i] += part_sum[i - 1];
	}

	int max = -1;
	for (int i = 0; i < N - 1; ++i)
		if (max < (part_sum[i] % p) + ((part_sum[N - 1] - part_sum[i]) % p))
			max = (part_sum[i] % p) + ((part_sum[N - 1] - part_sum[i]) % p);

	cout << max << endl;
	return 0;
}