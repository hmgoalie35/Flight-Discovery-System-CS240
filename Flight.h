#ifndef Flight_H
#define Flight_H

#include <iostream>
#include <string>
#include "Date.h"
#include "time.h"
#include "timeLength.h"

using namespace std;

class Flight{
	
	public:
	    Flight(string, string, Time, Time, float);
	   // ~Flight();
	    friend ostream& operator<<(ostream&,  Flight&);
	    bool operator<(const Flight&);
	    bool operator>(const Flight&);
	    bool operator==(const Flight&);

	private:
	    string destination, departure;
	    float cost;
	    Time departure_time, arrival_time;
	    TimeLength flight_duration;

};

#endif
