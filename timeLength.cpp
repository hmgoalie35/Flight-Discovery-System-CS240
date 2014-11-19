#include "timeLength.h"

TimeLength::TimeLength(int hours, int mins): hours(hours), mins(mins)
{}

ostream& operator<<(ostream &out, const TimeLength &t){
	out << t.hours << ":" << t.mins;
}