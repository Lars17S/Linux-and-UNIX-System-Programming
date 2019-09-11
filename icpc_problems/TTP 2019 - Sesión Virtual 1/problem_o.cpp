#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;
void print_map(map<tuple<int, int, int>, vector<int>>& frequency_set);

int main()
{
	int n, k, num, remainder, num_add, new_indice;
	map<int, int> key_occurrence;
	map<tuple<int, int, int>, vector<int>> frequency_set;
	vector<int> last_set;
	tuple<int, int, int> last_key, new_key;
	vector<int> solution;
	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		cin >> num;
		key_occurrence[num]++;
	}

	for (map<int, int>::iterator it = key_occurrence.begin(); it != key_occurrence.end(); ++it)
		frequency_set[make_tuple(it->second, 1, it->second)].push_back(it->first);

	//print_map(frequency_set);
	remainder = k;
	while (remainder != 0) {
		last_key = frequency_set.rbegin()->first;
		last_set = frequency_set[last_key];
		num_add = min(static_cast<int>(last_set.size()), remainder);
		solution.insert(solution.end(), last_set.begin(), last_set.begin() + num_add);
		new_indice = get<1>(last_key) + 1;
		new_key = make_tuple(int(floor(get<2>(last_key) / new_indice)), new_indice, get<2>(last_key));
		if (get<0>(new_key) != 0) { // Re-insert the node key of map with a new key
			auto node = frequency_set.extract(last_key);
			node.key() = new_key;
			frequency_set.insert(move(node));
		}
		else frequency_set.erase(last_key); // If frequency is equal to zero, then deletes the last key node
		//print_map(frequency_set);
		remainder = remainder - num_add;
	}

	if (solution.size() == 0)
		cout << 0 << endl;
	for (vector<int>::iterator it = solution.begin(); it != solution.end(); ++it)
		cout << *it << " ";

	return 0;
}

void print_map(map<tuple<int, int, int>, vector<int>>& frequency_set) {
	for (map<tuple<int, int, int>, vector<int>>::iterator it_i = frequency_set.begin(); it_i != frequency_set.end(); ++it_i) {
		tuple<int, int, int> key = it_i->first;
		cout << "| FREQUENCY: " << get<0>(key) << " | INDICE: " << get<1>(key) << " | GROUP KEY: " << get<2>(key) << " | Elements: ";
		for (vector<int>::iterator it_j = it_i->second.begin(); it_j != it_i->second.end(); ++it_j)
			cout << *it_j << " ";
		cout << endl;
	}
	cout << endl;
}