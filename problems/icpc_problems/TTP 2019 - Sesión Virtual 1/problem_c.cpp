// problem_c.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>
#include <string>
#include <sstream> 
using namespace std;
tm make_tm(short& year, short& month, short& day);
void string_toint(short& num, string str);

int main()
{
	short N, pos_c, year1, month1, day1, year2, month2, day2;
	tm tm1, tm2;
	time_t time1, time2, difference;
	string date_input;
	double portable_difference;
	cin >> N;
	for (short i = 0; i < N; ++i) {
		cin >> date_input;
		pos_c = (date_input[1] == '/') ? 1 : 2;
		string_toint(year1, date_input.substr(date_input.size() - 4, date_input.size() - 1));
		string_toint(month1, date_input.substr(0, pos_c));
		string_toint(day1, date_input.substr(pos_c + 1, date_input.size() - 6));

		tm1 = make_tm(year1, month1, day1);
		cin >> date_input;
		pos_c = (date_input[1] == '/') ? 1 : 2;
		string_toint(month2, date_input.substr(0, pos_c));
		string_toint(day2, date_input.substr(pos_c + 1, date_input.size() - 1));

		if (month1 == 12 && day1 > 24 && month2 == 1)
			year2 = year1 + 1;
		else if (month1 == 1 && day1 < 7 && month2 == 12)
			year2 = year1 - 1;
		else
			year2 = year1;

		tm2 = make_tm(year2, month2, day2);
		time1 = mktime(&tm1);
		time2 = mktime(&tm2);

		portable_difference = difftime(time1, time2) / (60 * 60 * 24);

		if (portable_difference == 0)
			cout << i + 1 << " SAME DAY" << endl;
		else if (abs(portable_difference) > 7)
			cout << i + 1 << " OUT OF RANGE" << endl;
		else if (portable_difference > 0) {
			cout << i + 1 << " " << month2 << "/" << day2 << "/" << year2 << " IS " << portable_difference << " ";
			if (portable_difference == 1)
				cout << "DAY PRIOR";
			else
				cout << "DAYS PRIOR";
			cout << endl;
		}
		else if (portable_difference < 0) {
			cout << i + 1 << " " << month2 << "/" << day2 << "/" << year2 << " IS " << abs(portable_difference) << " ";
			if (portable_difference == -1)
				cout << "DAY AFTER";
			else
				cout << "DAYS AFTER";
			cout << endl;
		}
	}

	return 0;
}


tm make_tm(short& year, short& month, short& day)
{
	std::tm tm = { 0 };
	tm.tm_year = year - 1900; // years count from 1900
	tm.tm_mon = month - 1;    // months count from January=0
	tm.tm_mday = day;         // days count from 1
	return tm;
}

void string_toint(short& num, string str) {
	stringstream convert(str);
	convert >> num;
	convert.str("");
	convert.clear();
}