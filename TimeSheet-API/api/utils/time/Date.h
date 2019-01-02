#ifndef _H_DATE_H_
#define _H_DATE_H_

#pragma once
#include "../../defines.h"

#include <string>
#include <vector>
#include <map>

struct Date {
	int _year = 1;
	int _month = 1;
	int _day = 1;

	string get() {
		string str;
		str.append(to_string(_day));
		str.append("/");
		str.append(to_string(_month));
		str.append("/");
		str.append(to_string(_year));
		return str;
	}

	void set(string str) {
		auto data = split(str, "/");
		_year = atoi(data[data.size() - 1].c_str());
		_month = atoi(data[data.size() - 2].c_str());
		_day = atoi(data[data.size() - 3].c_str());
	}
	
	void set(int day, int month, int year) {
		_day = day;
		_month = month;
		_year = year;
	}

	bool operator==(const Date& date) {
		if (_year == date._year &&
			_month == date._month &&
			_day == date._day)
			return true;
		return false;
	}

};
#endif // !_H_DATE_H_
