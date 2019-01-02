#ifndef _H_TIME_H_
#define _H_TIME_H_

#pragma once
#include <string>
#include <math.h>

#include "../misc/basic_str_parser.h"

using namespace std;

struct Time {

	// STRING FORMAT:
	// HH:MM:SS

	// DO NOT ALTER FROM THE VARS ITSELF
	int _hr = 0;
	int _min = 0;
	int _sec = 0;
	int _ms = 0;

	Time operator+(const Time& other_time) {
		Time time = *this;
		time.add(other_time.get());
		return time;
	}
	Time operator-(const Time& other_time) {
		Time time = *this;
		time.remove(other_time.get());
		return time;
	}

	std::string get() const {
		string hrs = to_string(_hr);
		string mins = to_string(_min);
		string secs = to_string(_sec);

		if (hrs.size() <= 1) hrs = "0" + hrs;
		if (mins.size() <= 1) mins = "0" + mins;
		if (secs.size() <= 1) secs = "0" + secs;

		return string((hrs)+":" + (mins)+":" + (secs));
	}

	void set(int hr, int min, int seconds, int ms) {
		_ms = 0;
		_sec = 0;
		_hr = 0;

		addMilliSeconds(ms);
		addSeconds(seconds);
		addMins(min);
		addHours(hr);
	}
	// format: HH:MM:SS,
	// THERE IS NO MS
	void set(std::string str) {
		auto data = split(str, ":");
		addSeconds(atoi(data[data.size() - 1].c_str()));
		addMins(atoi(data[data.size() - 2].c_str()));
		addHours(atoi(data[data.size() - 3].c_str()));
	}

	void add(int hr, int min, int seconds, int ms) {
		addMilliSeconds(ms);
		addSeconds(seconds);
		addMins(min);
		addHours(hr);
	}
	void add(std::string str) {
		auto data = split(str, ":");
		addSeconds(atoi(data[data.size() - 1].c_str()));
		addMins(atoi(data[data.size() - 2].c_str()));
		addHours(atoi(data[data.size() - 3].c_str()));
	}

	void remove(int hr, int min, int seconds) {
		removeSeconds(seconds);
		removeMins(min);
		removeHours(hr);
	}
	void remove(std::string str) {
		auto data = split(str, ":");
		removeSeconds(atoi(data[data.size() - 1].c_str()));
		removeMins(atoi(data[data.size() - 2].c_str()));
		removeHours(atoi(data[data.size() - 3].c_str()));
	}

	void addMilliSeconds(int ms) {
		int givenSeconds = ms / 1000;
		int givenMS = ms - ((ms / 1000) * 1000);

		int finalMS;

		int carry = 0;
		if ((_ms + givenMS) >= 1000)
			carry = (_ms + givenMS) / 1000;

		finalMS = (_ms + givenMS) - (((_ms + givenMS) / 1000)*1000);
		addSeconds(givenSeconds+carry);

		_ms = finalMS;
	}

	void addSeconds(int secs) {
		int givenMinutes = secs / 60;
		int givenSeconds = secs - ((secs / 60) * 60);

		int finalMin, finalSec;

		int carry = 0;
		if ((_sec + givenSeconds) >= 60) {
			carry = (_sec + givenSeconds) / 60;
		}

		finalSec = (_sec + givenSeconds) - (((_sec + givenSeconds) / 60)*60);
		addMins(givenMinutes + carry);

		_sec = finalSec;
	}
	void removeSeconds(int secs) {
		int givenMinutes = secs / 60;
		int givenSeconds = secs - ((secs / 60) * 60);

		int finalMin, finalSec;

		// carry
		if (_sec < givenSeconds) {
			_sec += 60;
			_min--;
		}

		finalSec = _sec - givenSeconds;
		finalMin = _min - givenMinutes;

		_sec = finalSec;
		_min = finalMin;
	}

	void addMins(int mins) {
		int givenHours = mins / 60;
		int givenMins = mins - ((mins / 60) * 60);

		int finalMins = 0, finalHrs = 0;

		int carry = 0;
		if (_min + givenMins >= 60) {
			carry = (_min + givenMins) / 60;
		}

		finalMins = (_min + givenMins) - (((_min + givenMins) / 60)*60);
		addHours(finalHrs + carry);

		_min = finalMins;
	}
	void removeMins(int mins) {
		int givenHours = mins / 60;
		int givenMins = mins - ((mins / 60) * 60);

		int finalHours, finalMins;

		// carry
		if (_min < givenMins) {
			_min += 60;
			_hr--;
		}

		finalMins = _min - givenMins;
		finalHours = _hr - givenHours;

		_min = finalMins;
		_hr = finalHours;
	}

	void addHours(int hrs) {
		_hr += hrs;
	}
	void removeHours(int hrs) {
		_hr -= hrs;
	}

	Time operator/(int n) {
		Time time = *this;
		time.divide(n);
		return time;
	}

	void divide(int n) {
		
		if (!_sec) _sec = _sec / n;
		if (!_min) {
			float mins = _min / n;
			string min = to_string(mins);
			auto min_data = split(min, ".");

			_min = atoi(min_data[0].c_str());
			addSeconds(atoi(min_data[1].c_str()));
		}
		
		if (!_hr) {
			float hrs = _hr / n;
			string hr = to_string(hrs);
			auto hr_data = split(hr, ".");

			_hr = atoi(hr_data[0].c_str());
			addMins(atoi(hr_data[1].c_str()));
		}
	}

	void reset() {
		_hr = 0;
		_min = 0;
		_sec = 0;
	}

};

struct Time_PAM {
	int _hour = 0;
	int _min = 0;
	bool _isAM = true;

	std::string get() {
		string hr = to_string(_hour);
		string mins = to_string(_min);

		if (hr.size() <= 1)
			hr = "0" + hr;
		if (mins.size() <= 1)
			mins = "0" + mins;

		string str = hr + ":" + mins + " ";
		str.append((_isAM) ? "AM" : "PM");
		return str;
	}

	void set(int hours, int mins, bool am) {
		_hour = hours;
		_min = mins;
		_isAM = am;
	}

	void set(std::string str) {
		if (str == "")
			return;

		auto data = split(str, ":");
		auto last_split = split(data[data.size() - 1], " ");

		_isAM = (last_split[last_split.size() - 1] == "AM") ? true : false;

		_hour = atoi(data[0].c_str());
		_min = atoi(data[1].c_str());
	}

	void add(int hours, int mins) {
		addMins(mins);
		addHours(hours);
	}

	void addMins(int mins) {
		Time time1 = convertTo24HrFormat();
		Time time2;
		time2.addMins(mins);

		time1 = time1 + time2;

		*this = convertFrom24HrFormat(time1);
	}
	void addHours(int hours) {
		Time time1 = convertTo24HrFormat();
		Time time2;
		time2.addHours(hours);

		time1 = time1 + time2;

		*this = convertFrom24HrFormat(time1);
	}

	Time_PAM operator-(Time_PAM &other) {
		Time other_24hr = other.convertTo24HrFormat();
		Time this_24hr = this->convertTo24HrFormat();
		Time _final = this_24hr - other_24hr;
		return convertFrom24HrFormat(_final);
	}

	Time convertTo24HrFormat() {
		Time time;
		if (_isAM)
			time.addHours(_hour);
		else time.addHours(_hour + 12);

		time.addMins(_min);
		time.addSeconds(00);

		return time;
	}
	Time_PAM convertFrom24HrFormat(Time given) {
		Time_PAM time;

		if (given._hr > 12) {
			time._isAM = false;
			time._hour = given._hr - 12;
		}
		else {
			time._isAM = true;
			time._hour = given._hr;
		}

		if (_hour == 24) {
			time._isAM = true;
			time._hour = 0;
		}

		if (_hour == 12) {
			time._isAM = false;
			time._hour = 12;
		}

		time._min = given._min;
		return time;
	}

};
#endif // !_H_TIME_H_
