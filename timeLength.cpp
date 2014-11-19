#include "timeLength.h"

TimeLength::TimeLength(int hours, int mins): hours(hours), mins(mins)
{}
bool TimeLength::operator== (TimeLength t2){
	return (hours == t2.hours && mins == t2.mins);
}
bool TimeLength::operator> (TimeLength t2){
	bool ret = true;
	if (hours == t2.hours){
		if (mins < t2.mins || mins == t2.mins){
		 ret = false;
		}
	} else if (hours < t2.hours) ret = false;
	return ret;
}

bool TimeLength::operator< (TimeLength t2){
	bool ret = true;
	if (hours == t2.hours){
		if (mins > t2.mins || mins == t2.mins){
		 ret = false;
		}
	} else if (hours > t2.hours) ret = false;
	return ret;
}
TimeLength TimeLength::operator- (TimeLength t2){
	int newHours;
	int newMins;
	if (*this > t2){
		newHours = hours - t2.hours;
		newMins = mins - t2.mins;
		if (newMins < 0){
			newMins += 60;
			newHours -= 1;
		}
	} else if (*this == t2){
		newHours = 0;
		newMins = 0;
	} else {
		newHours = t2.hours - hours;
		newMins = t2.mins - mins;
		if (newMins < 0){
			newMins += 60;
			newHours -= 1;
		}
	}
	TimeLength length (newHours,newMins);
	return length;
}

TimeLength TimeLength::operator+ (TimeLength t2){
	int newHours = hours + t2.hours;
	int newMins = mins + t2.mins;
	if (newMins >= 60){
		newMins -= 60;
		newHours += 1;
	}
	TimeLength length (newHours, newMins);
	return length;
}

ostream& operator<<(ostream &out, const TimeLength &t){
	out << t.hours << ":" << t.mins;
}