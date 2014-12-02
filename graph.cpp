#include "graph.h"
#include "Date.h"
#include "time.h"

//constructor
Graph::Graph () { 

}

//destructor
Graph::~Graph () { }

//adds flight info to graph. checks if city already exists
void Graph::add_flight (string cityInfo[], int size) {
	for (int i = 0; i < size; i++) {
		cout << cityInfo[i]; 
	}
	cout << endl;
	departure_city = cityInfo[0];
	destination_city = cityInfo[1];
	departure_time = cityInfo[2];
	arrival_time = cityInfo[3]; 
	//cost = stof((cityInfo[4]).c_str());
	//check if depart city exists
	//check if destination city exists
	//if not, create new city node.
	//create new time object. give time and cost to city node
	//if they exist, give time and cost to existing city node 
}		

//checks if city user wants to depart from exists and then sets variable
bool Graph::set_depart_city (string user_choice) {
	user_depart_city = user_choice;
	return true;
}

//checks if city user wants to travel to exists and then sets variable
bool Graph::set_destination (string user_choice) {
	user_destination_city = user_choice;
	return true;
}

//checks if departure date is possible, checks syntax, then sets variable
bool Graph::set_depart_date (string user_choice) {
	user_depart_date = user_choice;
	return true;
}

//checks if departure time is possible, checks syntax, then sets variable
bool Graph::set_depart_time (string user_choice) {
	user_depart_time = user_choice;
	return true;
}

//checks if return date is possible, checks syntax, then sets variable
bool Graph::set_return_date (string user_choice) {
	user_return_date = user_choice;
	return true;
}

//checks if return time is possible, checks syntax, then sets variable
bool Graph::set_return_time (string user_choice) {
	user_return_time = user_choice;
	return true;
}

//print entire flight schedule
void Graph::print_flight_sched () {

}

void Graph::j_itin () {
	cout << "J function call not yet implemented." << endl;
}			

void Graph::f_itin () {
	cout << "F function call not yet implemented." << endl;
}							

void Graph::c_itin () {
	cout << "C function call not yet implemented." << endl;
} 					

void Graph::s_itin () {
	cout << "S function call not yet implemented." << endl;
}						