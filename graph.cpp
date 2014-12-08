#include "graph.h"

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
	string costHolder = (cityInfo[4]).substr(1, (cityInfo[4]).size() - 1); 
	cost = stof(costHolder); 
	add_city(departure_city);
	add_city(destination_city);
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

//finds position of city within citylist vector
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

//checks that time is valid and correct format
bool checkTime (string input) {
	int hour, minute;
	if (input.size() != 7 && input.size() != 6) {
		cout << "Enter time in correct format. ";
		return false;
	}
	if (input.size() == 7) {
		if (input.at(2) != ':' || (input.at(5) != 'a' && input.at(5) != 'p') || input.at(6) != 'm') {
			cout << "Enter time in correct format. ";
			return false;
		} else {
			hour = stoi(input.substr(0,2)); 
			minute = stoi(input.substr(3,2)); 
		}
	}
	if (input.size() == 6) {
		if (input.at(1) != ':' || (input.at(4) != 'a' && input.at(4) != 'p') || input.at(5) != 'm') {
			cout << "Enter time in correct format. ";
			return false;
		} else {
			hour = stoi(input.substr(0,1)); 
			minute = stoi(input.substr(2,1)); 
		}
	}
	for (size_t i = 0; i < input.size() - 2; i++) {
		if (input.at(i) == ' ' || isalpha(input.at(i))) {
			cout << "Enter time without spaces ending in 'am' or 'pm'. ";
			return false;
		}
	}
	if (!(hour >= 1 && hour <= 12) || !(minute >= 0 && minute <= 60)) {
		cout << "Enter acceptalble time. ";
		return false;
	}
	return true;
}

//checks date is correct format and is valid
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
	for (size_t i = 0; i < cityList.size(); i++) {
		if (user_choice == cityList[i].name) {
			user_depart_city = user_choice;
			return true;
		}
	}
	cout << "City is not listed in flight schedule. ";
	return false;
}

//checks if city user wants to travel to exists, is not depart city,	 then sets variable
bool Graph::set_destination (string user_choice) {
	if (!(checkSyntax(user_choice))) return false;
	for (size_t i = 0; i < cityList.size(); i++) {
		if (user_choice == cityList[i].name && user_choice != user_depart_city) {
			user_destination_city = user_choice;
			return true;
		}
	}
	cout << "City is not listed in flight schedule or city is same as departure city. ";
	return false;
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
	vector<City>::iterator it;
	for(it = cityList.begin(); it != cityList.end(); it++){
		for(vector<Flight>::iterator i = it->flightList.begin(); i != it->flightList.end(); i++){
			cout << *i << endl;
		}
	}
	//depthFirstSearch(0);
}


// void Graph::depthFirstSearch(int start){
//   vector<bool> unvisited(cityList.size(), true);
//   depthFirstSearchAux(start, unvisited);
// }

// void Graph::depthFirstSearchAux(int start, vector<bool> & unvisited)
// {
//   // Add statements here to process myAdjacencyLists[start].data
//   cout << cityList[start].name << endl;

//   unvisited[start] = false;
//   // Traverse its adjacency list, performing depth-first 
//   // searches from each unvisited vertex in it.
//   for (vector<Flight>::iterator it = cityList[start].flightList.begin(); it != cityList[start].flightList.end(); it++)
//     // check if current vertex has been visited
//     if (unvisited[*it])
//       // start DFS from new node
//       depthFirstSearchAux(*it, unvisited); 
//   }

void Graph::j_itin () {
	vector<Flight> path;
	bool visited[cityList.size()];
	Flight base;
	for (int i = 0; i < cityList.size(); i++){
		visited[i] = false;
	}
	j_recursive(city_pos(user_depart_city), city_pos(user_depart_city), city_pos(user_destination_city), false, user_depart_time, visited, path, base);
	//cout << "The possible flight paths available to travel to " << user_destination_city << " from " << user_depart_city << " and then back again between " << user_depart_time << " and " << user_return_time << " on " << user_depart_date << " are: " << endl;
	int size = 10000;
	int shortest;
	int i;
	for (i = 0; i < j_flightPaths.size(); i++){
		if (j_flightPaths[i].size() < size){
			size = j_flightPaths[i].size();
			shortest = i;
		}	 	
		
	}
	float totalCost = 0;
	TimeLength totalDuration = j_flightPaths[shortest][j_flightPaths[shortest].size() - 1].get_flight_arrival_time() - j_flightPaths[shortest][0].get_flight_departure_time();
	cout << "\n Trip Itinerary: \n";
	for (int j = 0; j < j_flightPaths[shortest].size(); j++){
		totalCost += j_flightPaths[shortest][j].get_cost();
		cout << j_flightPaths[shortest][j];
		if (j != j_flightPaths[shortest].size() - 1){
			cout  << "           |" << endl << "           |" << endl << "           v";
		}
		cout << "\n";
	}
	if (j_flightPaths.size() > 0){
		cout << "Total trip cost: $" << totalCost << endl;
		cout << "Total trip duration: " << totalDuration << endl;
	}
	if (j_flightPaths.size() < 1){
		cout << "No possible paths." << endl;
	}
}			

void Graph::j_recursive(int start, int current, int destination, bool destinationReached, Time currentTime, bool visited[], vector <Flight> path, Flight currentFlight){
	//visited[current] = true;
	if (current != start){
		path.push_back(currentFlight);
	}
	if (destination == current){
		destinationReached = true;
		for (int i = 0; i < cityList.size(); i++){
			visited[i] = false;
		}
	}
	if (current == start && destinationReached){
		path.push_back(currentFlight);
		j_flightPaths.push_back(path);
		return;
	}
	for (int i = 0; i < cityList[current].flightList.size(); i++){
		bool isVisited = visited[city_pos(cityList[current].flightList[i].get_destination_city())];
		Time flightTime = cityList[current].flightList[i].get_flight_departure_time();
		Time arrivalTime =  cityList[current].flightList[i].get_flight_arrival_time();
		if (!isVisited && ((flightTime > currentTime) || flightTime == currentTime) && arrivalTime < user_return_time){
			j_recursive(start, city_pos(cityList[current].flightList[i].get_destination_city()), destination, destinationReached, cityList[current].flightList[i].get_flight_arrival_time(), visited, path, cityList[current].flightList[i]);
		}
	}
	return;
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
