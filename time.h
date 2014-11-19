#ifndef TIME_H
#define TIME_H

#include <string>
#include <iostream>
using namespace std;

#include "timeLength.h"

class Time {

	public:
		Time(string t);
		bool operator== (Time t2);
		bool operator> (Time t2);
		bool operator< (Time t2);
		TimeLength operator- (Time t2);
		TimeLength operator+ (Time t2);

		friend ostream& operator<<(ostream &out, const Time &t);
	private:
		bool AM;
		int militaryHours;
		int hours;
		int mins;




};

#endif