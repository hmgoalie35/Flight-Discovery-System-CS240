#ifndef TIME_H
#define TIME_H

#include <string>
#include <iostream>
#include <stdlib.h>
using namespace std;

#include "timeLength.h"

class Time {

	public:
		Time();
		Time(string t);
		Time(int newHours,int newMins,bool newAM);
		bool operator== (Time t2);
		bool operator> (Time t2);
		bool operator< (Time t2);
		TimeLength operator- (Time t2);
		TimeLength operator+ (Time t2);
		Time operator+ (TimeLength t);
		Time operator- (TimeLength t);
		friend ostream& operator<<(ostream &out, const Time &t);
	private:
		int militaryHours;
		int hours;
		int mins;
		bool AM;
		int daysPast;



};

#endif