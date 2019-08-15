#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
int point_counter(int& L, int& v, int& l, int& r);

int main()
{
	short t;
	int L, v, l, r;
	vector<int> result;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		cin >> L >> v >> l >> r;
		result.push_back(point_counter(L, v, l, r));
	}
		
	for (int i : result)
		cout << i << endl;

	return 0;
}

int point_counter(int& L, int& v, int& l, int& r) {
	int p = floor(L / v); // Total p points divided by v
	int dl = ceil(double(l) / double(v)) * v; // Next immediate integer divisor larger or equal to l
	int dr = floor(r / v) * v; // Previous immediate integer divisor smaller or equal to r
	int pe = ceil(double((dr - dl) + 1) / double(v)); // Total of points excluded
	return p - pe;
}