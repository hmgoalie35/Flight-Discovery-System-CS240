#ifndef TIME_LENGTH_H
#define TIME_LENGTH_H

#include <iostream>
#include <string>
using namespace std;


class TimeLength {
	public:
		TimeLength();
		TimeLength(int hours, int mins);
		int hours;
		int mins;
		bool operator== (TimeLength t2);
		bool operator> (TimeLength t2);
		bool operator< (TimeLength t2);
		TimeLength operator- (TimeLength t2);
		TimeLength operator+ (TimeLength t2);

		friend ostream& operator<<(ostream &out, const TimeLength &t);

	private:
};

#endif