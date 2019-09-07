#include <iostream>
#include <vector>
#include <map>
using namespace std;


int main()
{
	map<long long, vector<int>> value_index;
	vector<int> nice_index;
	long long diff_sum, max, sum = 0;
	const long long factor = 2;
	int n, num, count = 0;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> num;
		value_index[num].push_back(i);
		sum += num;
	}

	map<long long, vector<int>>::reverse_iterator it_j;
	it_j = value_index.rbegin();
	max = it_j->first;
	do {
		diff_sum = sum - factor * (it_j->first);
		// Check if sum - 2 * a[i] exists and check if the value it is not the same element A[j]
		if (value_index.count(diff_sum) == 1 && !(it_j->first == diff_sum && value_index.at(diff_sum).size() == 1)) {
			nice_index.insert(nice_index.end(), value_index.at(diff_sum).begin(), value_index.at(diff_sum).end());
			count += value_index.at(diff_sum).size();
		}
		++it_j;
	} while (max >= diff_sum && it_j != value_index.rend());

	cout << count << endl;
	for (vector<int>::iterator it = nice_index.begin(); it != nice_index.end(); ++it)
		cout << *it + 1 << " ";

	return 0;
}