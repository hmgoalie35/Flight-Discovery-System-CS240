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
		bool operator<(const Flight&) const;
		//see if flights has a longer duration
		bool operator>(const Flight&) const;
		//check if flights have the same duration
		bool operator==(const Flight&) const;
		//get flight duration
		TimeLength get_flight_duration();

		//get flight departure time
		Time get_flight_departure();
		//get flight arrival time
		Time get_flight_arrival();
		//get departure city
		string get_departure_city();
		//get destination city
		string get_destination_city();
		
		Time get_flight_departure_time();
		Time get_flight_arrival_time();
		//get distance
		int get_distance();
		//get cost of flight
		float get_cost();
		//check if flight was visited. 
		bool was_visited();
		//reset distance values
		void clear_distance();
		//set distance to new value
		void set_distance(int value);
		//set visited to new value
		void set_visited(bool);
		//add time to flight duration
		void set_time_duration(TimeLength delay);

	private:
		//store the departure, destination city
	    string destination, departure;
	    //store the cost
	    float cost;
	    //store the departure and arrival times
	    Time departure_time, arrival_time;
	    //store the flight duration
	    TimeLength flight_duration;
	    //if we have already checked this flight for shortest path, etc.
	    bool visited;
	    int distance;

};

#endif
