#include <iostream>
#include <string>
#include <deque>
using namespace std;

int main()
{
	short n, c;
	string a, b, res_s;
	deque<char> res;
	cin >> n;
	for (short i = 0; i < n; ++i) {
		cin >> a;
		cin >> b;
		std::size_t pos = a.find('1');
		if (pos == string::npos)
			a = "0";
		else
			a = a.substr(pos);
		pos = b.find('1');
		if (pos == string::npos)
			b = "0";
		else
			b = b.substr(pos);
		if (a.length() > b.length())
			b = string(a.length() - b.length(), '0') + b;
		else if (a.length() < b.length())
			a = string(b.length() - a.length(), '0') + a;

		c = 0;
		for (short j = a.length(); j > 0; --j) {
			res.push_front('0' + (((a[j - 1] - '0') + (b[j - 1] - '0') + c) % 2));
			c = (((a[j - 1] - '0') + (b[j - 1]) - '0') + c) / 2;
		}
		if (c != 0)
			res.push_front('0' + c);
		for (deque<char>::iterator it = res.begin(); it != res.end(); ++it)
			res_s.push_back(*it);
		cout << (i + 1) << ' ' << res_s << endl;
		res_s = "";
		res.clear();
	}

	return 0;
}