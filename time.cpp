#include "time.h"

Time::Time(string t) : daysPast(0){
	int i = 0;
	while (t[i] != ':'){
		i++;
	}
	string h = t.substr(0,i); //create hour string
	string m = t.substr(i+1,2); //create minutes string
	string testAM = t.substr(i+3,2); //creates AM/PM string
	AM = (testAM == "am") ? true : false;
	hours = atoi(h.c_str());
	mins = atoi(m.c_str());
	militaryHours = (AM) ? hours : hours + 12;
}
Time::Time(int newHours,int newMins,bool newAM) : militaryHours(newHours), mins(newMins), AM(newAM) {
	hours = militaryHours;
	if (!AM) hours -=12;
	if (militaryHours >= 24){
		hours -=12;
		militaryHours -=24;
		daysPast +=1;
	}
	if (militaryHours < 12) AM = true;

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

Time Time::operator+ (TimeLength t){
	int newHours = militaryHours + t.hours;
	int newMins = mins + t.mins;
	bool newAM = true;
	if (newMins >= 60){
		newHours += 1;
		newMins -= 60;
	}
	if (newHours > 11) newAM = false;
	Time newTime(newHours,newMins,newAM);
	return newTime;
}


ostream& operator<<(ostream &out, const Time &t){
	if (t.hours == 0) {
		out << 12;
	} else {
		out << t.hours;
	}
	out << ":";
	if (t.mins < 10){
		out << "0";
	}
	out << t.mins;
	if (t.AM){
		out << "AM";
	} else {
		out << "PM";
	}
	
	return out;
}
