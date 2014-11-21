#include "time.h"

Time::Time(string t){
	string h = t.substr(0,2); //create hour string
	string m = t.substr(3,2); //create minutes string
	string testAM = t.substr(5,2); //creates AM/PM string
	AM = (testAM == "AM") ? true : false;
	hours = atoi(h.c_str());
	mins = atoi(m.c_str());
	militaryHours = (AM) ? hours : hours + 12;
}
bool Time::operator== (Time t2){
	return (militaryHours == t2.militaryHours && mins == t2.mins);
}

bool Time::operator> (Time t2){
	bool ret = true;
	if (militaryHours == t2.militaryHours){
		if (mins < t2.mins) ret = false;
	} else if (militaryHours < t2.militaryHours) ret = false;
	return ret;
}

bool Time::operator< (Time t2){
	bool ret = true;
	if (militaryHours == t2.militaryHours){
		if (mins > t2.mins) ret = false;
	} else if (militaryHours > t2.militaryHours) ret = false;
	return ret;
	return ret;
}
TimeLength Time::operator- (Time t2){
	int newHours;
	int newMins;
	if (*this > t2){
		newHours = militaryHours - t2.militaryHours;
		if (mins > t2.mins || mins == t2.mins){
			newMins = mins - t2.mins;
		}
		else {
			int tempMins = mins - t2.mins;
			newMins = 60 + tempMins;
			newHours -=1;
		}
	} else if (*this == t2){
		newHours = 0;
		newMins = 0;
	} else {
		newHours = t2.militaryHours - militaryHours;
		if (t2.mins > mins || t2.mins == mins){
			newMins = t2.mins - mins;
		}
		else {
			int tempMins = t2.mins - mins;
			newMins = 60 + tempMins;
			newHours -=1;
		}
	}
	TimeLength length(newHours,newMins);
	return length;
}

TimeLength Time::operator+ (Time t2){
	int newHours = militaryHours + t2.militaryHours;
	int newMins = mins + t2.mins;
	if (newMins >= 60){
		newHours += 1;
		newMins -= 60;
	}

	TimeLength length(newHours,newMins);
	return length;
}

ostream& operator<<(ostream &out, const Time &t){
	out << t.hours << ":" << t.mins;
	if (t.AM){
		out << "AM";
	} else {
		out << "PM";
	}
	
	return out;
}
