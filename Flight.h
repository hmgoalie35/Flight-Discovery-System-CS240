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
		//default constructor
		Flight();
		//value constructor, takes in the departure city, destination city, departure time, arrival time, cost.
		Flight(string, string, Time, Time, float);
		//destructor
		~Flight();
		//prints a flight object.
		friend ostream& operator<<(ostream&, const Flight&);
		//see if flights has a shorter duration
		bool operator<(const Flight&);
		//see if flights has a longer duration
		bool operator>(const Flight&);
		//check if flights have the same duration
		bool operator==(const Flight&);

	private:
		//store the departure, destination city
	    string destination, departure;
	    //store the cost
	    float cost;
	    //store the departure and arrival times
	    Time departure_time, arrival_time;
	    //store the flight duration
	    TimeLength flight_duration;

};

#endif
