#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	string time, a;
	short T, hour;
	cin >> T;
	for (short i = 0; i < T; ++i) {
		cin >> time;
		if (time[time.length() - 1] == '0' && time[time.length() - 2] == '0') {
			a = "";
			if (time.length() >= 5)
				a.push_back(time[time.length() - 5]);
			a.push_back(time[time.length() - 4]);
			istringstream(a) >> hour;
			if (hour <= 12)
				cout << hour + 12 << endl;
			else
				cout << hour % 12 << endl;
		}
		else
			cout << 0 << endl;
	}

	return 0;
}