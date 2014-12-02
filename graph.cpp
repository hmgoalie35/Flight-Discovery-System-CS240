#include "graph.h"

//constructor
Graph::Graph () { }

//destructor
Graph::~Graph () {
	for (int i = 0; i < cityList.size(); i++ ){
		for (int j = 0; j < cityList[i].flightList.size(); j++ ){
			delete &(cityList[i].flightList[j]);
		}
		delete &cityList[i];
	}
}

//adds flight info to graph. checks if city already exists
void Graph::add_flight (string cityInfo[], int size) {
	departure_city = cityInfo[0];
	destination_city = cityInfo[1];
	Time departure_time(cityInfo[2]);
	Time arrival_time(cityInfo[3]);
	string costHolder = (cityInfo[4]).substr(1, (cityInfo[4]).size() - 2); 
	cost = stof(costHolder); 
	add_city(departure_city);
	add_city(destination_city);
	Flight * f = new Flight(departure_city, destination_city, departure_time, arrival_time, cost);
	cityList[city_pos(departure_city)].flightList.push_back(*f);
}		

//checks if city is in the list of cities
void Graph::add_city(string cityName){
	bool in = false;
	for (int i = 0; i < cityList.size(); i++){
		if (cityName == cityList[i].name) in = true;
	}
	if(!in){
		City * city = new City();
		city->name = cityName;
		cityList.push_back(*city);
	}
}
int Graph::city_pos(string cityName){
	int i;
	for (i = 0; i < cityList.size(); i++){
		if (cityName == cityList[i].name) break;
	}
	return i;
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
