#include "graph.h"
/*
FIX: time constraints
	 same city being inputted

*/
//constructor
Graph::Graph() { }

//destructor
Graph::~Graph() {

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
	//add_city(destination_city);
	Flight f = Flight(departure_city, destination_city, departure_time, arrival_time, cost);
	cityList[city_pos(departure_city)].flightList.push_back(f);
}		

//checks if city is in the list of cities
void Graph::add_city(string cityName) {
	bool in = false;
	for (size_t i = 0; i < cityList.size(); i++) {
		if (cityName == cityList[i].name) in = true;
	}
	if(!in) {
		City city = City();
		city.name = cityName;
		cityList.push_back(city);
	}
}

int Graph::city_pos(string cityName) {
	size_t i;
	for (i = 0; i < cityList.size(); i++) {
		if (cityName == cityList[i].name) break;
	}
	return i;
}

//checks city inputs do not contain numbers or spaces
bool checkSyntax (string input) {
	for (size_t i = 0; i < input.size(); i++) {
		if (input.at(i) == ' ' || isdigit(input.at(i))) {
			cout << "Enter inputs without numbers or spaces. ";
			return false;
		}
	}
	return true;
}

bool checkTime (string input) {
	if (input.size() != 7 || input.at(2) != ':' || (input.at(5) != 'a' && input.at(5) != 'p') || input.at(6) != 'm') {
		cout << "Enter time in correct format. ";
		return false;
	}
	for (size_t i = 0; i < input.size() - 2; i++) {
		if (input.at(i) == ' ' || isalpha(input.at(i))) {
			cout << "Enter time without spaces ending in 'am' or 'pm'. ";
			return false;
		}
	}
	int hour = stoi(input.substr(0,2)); 
	int minute = stoi(input.substr(3,2)); 
	if (!(hour >= 1 && hour <= 12) || !(minute >= 0 && minute <= 60)) {
		cout << "Enter acceptalble time. ";
		return false;
	}
	return true;
}

bool checkDate (string input) {
	if (input.size() != 10 || (input.at(2) != '/' || input.at(5) != '/')) {
		cout << "Enter input in correct format. ";
		return false;
	}
	for (size_t i = 0; i < input.size(); i++) {
		if (input.at(i) == ' ' || isalpha(input.at(i))) {
			cout << "Enter inputs without letters or spaces. ";
			return false;
		}
	}
	int day = stoi(input.substr(0,2)); 
	int month = stoi(input.substr(3,2)); 
	int year = stoi(input.substr(6,input.size()));
	if (!(day >= 1 && day <= 31) || !(month >= 1 && month <= 12) || !(year >= 1950 && year <= 2014)) {
		cout << "Enter correct date. ";
		return false;
	}
	return true;
}
	
//checks if city user wants to depart from exists and then sets variable
bool Graph::set_depart_city (string user_choice) {
	if (!(checkSyntax(user_choice))) return false;
	//check if city has flights
	user_depart_city = user_choice;
	return true;
}

//checks if city user wants to travel to exists and then sets variable
bool Graph::set_destination (string user_choice) {
	if (!(checkSyntax(user_choice))) return false;
	//check that destination != departure city
	user_destination_city = user_choice;
	return true;
}

//checks if departure date is possible, checks syntax, then sets variable
bool Graph::set_depart_date (string user_choice) {
	if (!(checkDate(user_choice))) return false;
	int day = stoi(user_choice.substr(0,2)); 
	int month = stoi(user_choice.substr(3,2)); 
	int year = stoi(user_choice.substr(6,user_choice.size()));
	Date d(day, month, year);
	user_depart_date = d;
	return true;
}

//checks if departure time is possible, checks syntax, then sets variable
bool Graph::set_depart_time (string user_choice) {
	if (!(checkTime(user_choice))) return false;
	Time t(user_choice);
	user_depart_time = t;
	return true;
}

//checks if return date is possible, checks syntax, then sets variable
bool Graph::set_return_date (string user_choice) {
	if (!(checkDate(user_choice))) return false;
	int day = stoi(user_choice.substr(0,2)); 
	int month = stoi(user_choice.substr(3,2)); 
	int year = stoi(user_choice.substr(6,user_choice.size()));
	Date d(day, month, year);
	if (d < user_depart_date) {
		cout << "Return date is before depart date. ";
		return false;
	}
	user_return_date = d;
	return true;
}

//checks if return time is possible, checks syntax, then sets variable
bool Graph::set_return_time (string user_choice) {
	if (!(checkTime(user_choice))) return false;
	Time t(user_choice);
	if (t < user_depart_time && user_depart_date == user_return_date) {
		cout << "Return time is before depart time on the same day. ";
		return false;
	}
	user_return_time = t;
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
