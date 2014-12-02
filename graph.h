#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <iostream>
#include "time.h"

using namespace std;

class Graph {
	
	public:
		Graph ();										//constructor
		~Graph ();										//destructor
		void add_flight (string cityInfo[], int size);	//add flight info to graph. check if city already exists

		/*=checks if user input matches info in graph. returns true or false=*/
		bool set_depart_city (string user_choice);
		bool set_destination (string user_choice);
		bool set_depart_date (string user_choice);
		bool set_depart_time (string user_choice);
		bool set_return_date (string user_choice);
		bool set_return_time (string user_choice);
		/*======================================*/

		void print_flight_sched ();						//displays entire Daily Flight schedule
		void j_itin ();									//Just Get Me There
		void f_itin ();									//Fewest Hops
		void c_itin ();									//Cheapest
		void s_itin ();									//Shortest Trip

	private:

		/*====values from file=====*/		
		string departure_city;
		string destination_city; 
		float cost; 
		/*=========================*/

		/*====user given values====*/
		string user_depart_city;
		string user_destination_city;
		string user_depart_date;
		string user_depart_time;
		string user_return_date;
		string user_return_time;
		/*=========================*/
};

#endif

