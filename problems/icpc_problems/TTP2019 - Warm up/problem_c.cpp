#include <iostream>
#include <unordered_map>
#include <cmath>
using namespace std;

int main()
{
	int n, m, left, right, pos;
	char s;
    unordered_map<int, int> id;
	left = 0; 
	right = 0;
	cin >> n; // Set number of instructions
	cin >> s; // First input
	cin >> m;
	id[m] = 0;
	for (int i = 0; i < (n - 1); ++i) {
		cin >> s;
		cin >> m;
		switch (s) {
		case 'L':
			--left;
			id[m] = left;
			break;
		case 'R':
			++right;
			id[m] = right;
			break;
		case '?':
            pos = id.at(m);
			cout << min(abs(left - pos), abs(right - pos)) << endl;
			break;
		}
	}

	return 0;
}
