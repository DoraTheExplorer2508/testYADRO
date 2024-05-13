#pragma once
#ifndef _TIME_H_
#define _TIME_H_

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <regex>
using namespace std;

struct TimeUtil {

	uint16_t hour;
	uint16_t min;

public:

	TimeUtil() {
		hour = 0;
		min = 0;
	};

	TimeUtil(uint16_t h, uint16_t m) {
		hour = h;
		min = m;
	}

	void setTimeUtil(uint16_t h, uint16_t m) {
		hour = h;
		min = m;
	}

	friend ostream& operator<<(ostream& os, const TimeUtil& t)
	{
		string hour = "";
		string min = "";

		if (t.hour <= 9) hour = "0" + to_string(t.hour);
		else hour = to_string(t.hour);

		if (t.min <= 9) min = "0" + to_string(t.min);
		else min = to_string(t.min);

		return os << hour << ":" << min << " ";
	}
	bool operator<(const TimeUtil& t)
	{
		if (hour < t.hour) return true;
		else if (hour == t.hour && min < t.min) return true;
		else return false;

	}
	bool operator>(const TimeUtil& t)
	{
		if (hour > t.hour) return true;
		else if (hour == t.hour && min > t.min) return true;
		else return false;

	}
	TimeUtil operator-(const TimeUtil& t)
	{
		if (min < t.min) {
			return TimeUtil(hour - t.hour - 1, min + 60 - t.min);
		}
		else {
			return TimeUtil(hour - t.hour, min - t.min);
		}
	}

	TimeUtil operator+(const TimeUtil& t)
	{
		if ((min + t.min) >= 60) {
			return TimeUtil(hour + t.hour + 1, min + t.min - 60);
		}
		else {
			return TimeUtil(hour + t.hour, min + t.min);
		}
	}

	string toString() {
		string h = "";
		string m = "";

		if (hour <= 9) h = "0" + to_string(hour);
		else h = to_string(hour);

		if (min <= 9) m = "0" + to_string(min);
		else m = to_string(min);

		return  h + ":" + m;
	}

};
#endif

