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

//checks if city is in the list of cities. if not, creates city
void Graph::add_city(string cityName) {
	bool in = false;
	for (size_t i = 0; i < cityList.size(); i++) {
		if (cityName == cityList[i].name) in = true;
	}
	if(!in) {
		City city = City();
		city.name = cityName;
		city.distance = 0;

		cityList.push_back(city);
	}
}

//finds position of city within cityList vector
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

//checks if city user wants to travel to exists, and is not depart city. then sets variable
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

/*
No matter the objective, you should print all the legs of the trip, in order, along with the total monetary cost, trip time
(arrival time minus departure time), and number of hops for the best possible itinerary, according to the customer's
specified Trip Constraints and Objectives. 

The itinerary also includes return trip information---a list of flights starting at the destination city on the return date,
 and arriving back at the original departure city.
*/
void Graph::j_itin () {
	cout << "J function call not yet implemented." << endl;
}			

//get there in fewest hops w/ breadth first search
void Graph::f_itin () {
	cout << "Fewest Hops Itinerary chosen." << endl;
	vector<Flight> depart_journey(breadthFirst(user_depart_city, user_destination_city, user_depart_time));			//shortest hops to destination


	reset_breadth_first();																							//reset city struct variables
	reset_all_visited();																							//reset flight visited value		
	//vector<Flight> return_journey(breadthFirst(user_destination_city, user_depart_city, user_return_time));		//shortest hops on return trip
}							

/*
Since cityList is a struct comprised of a string city name and a vector of flight objects, linking flight destinations to 
cities on the cityList was done through a deque of strings. The initial departure city is first added to the struct and its 
corresponding city struct in CityList is marked as visited. Then it is taken off the deque and we iterate through its flight vector. Each flight
destination name within this vector is added to the deque. All flight objects with this destination name are marked visited in their flight 
object variables. The first element of the deque is then popped. It will be the name of a city that we have gotten from a flight object.
Its corresponding element in cityList will be set to visited. This cityList element then has its flight vector iterated through. 
This process is repeated for each successive name in the deqeue until the final destination is reached. 
This algorithm ensures that the function does not quit prematurely, as it must print out multiple flight paths if they exist. As a result, the while loop
cannot exit when the final destination is met. Rather, it must check that all the members in the deque that have the same distance from
the parent node have had their flight objects iterated through.

Function returns a vector of flights that can be taken to reach the destination city. It also includes the number of days that
the trip will span, which will need to be added to the sum of the total flight time.
*/
vector<Flight> Graph::breadthFirst (const string &departCity, const string &retCity, Time &departTime) {
	int distance = 0;
	int retCityPos = city_pos(retCity);																		//get position of retCity in cityList
	deque<string> cityDeque;																				//create queue of cities to visit
	vector<Flight> legs;																					//create vector of possible flights to take
	cityDeque.push_back(departCity);																		//put start city in queue
	//Time nextDepart = departTime;																			//get departTime of each flight
	while ( !cityDeque.empty() ) {																			//while deque is not empty
		string vertex = cityDeque.front();																	//get first city name from queue
		cityDeque.pop_front();																				//remove it from queue
		cityList[city_pos(vertex)].visited = true;															//mark city in cityList visited
		if ( cityList[city_pos(vertex)].distance > distance ) distance++;									//increment distance if necessary
		if ((cityList[retCityPos]).visited && distance == cityList[retCityPos].distance) break;				//final city has been visited. Breaking here ensures city could be visited by multiple different flight paths in same number of hops
		for (size_t i = 0; i < cityList[city_pos(vertex)].flightList.size(); i++ ) {						//iterate through all flights leaving from this city
			Flight f(cityList[city_pos(vertex)].flightList[i]);												//create Flight object for each element
			if ( !f.was_visited() ) {																		//for each distinct flight:
				//if ( f.get_flight_departure() < nextDepart ) add day to flight time;						//if depart time for next flight is before current flight's depart time, the next flight must be taken the following day
				if ( f.get_destination_city() != departCity) {												//this ensures flights with initial city's name (departCity) is not visited and departCity is not added to final vector.
					cityDeque.push_back( f.get_destination_city() );										//push name of destination onto deque				
					if (f.get_destination_city() != retCity) set_all_visited( f.get_destination_city() );	//mark all flights with the same destination as visited to avoid repeats. Ex: Boston has two flights to Philly - we only need to look at the first flight and ignore the second. Ignores return city because different flight paths can get to destination in same amount of hops, so it must be revisited
					cityList[city_pos(f.get_destination_city())].distance = (distance + 1);					//increment the distance of the corresponding element within cityList
					departTime = f.get_flight_departure();													//reset flight departure time
					legs.push_back(f);																		//push flight onto itinerary vector
				} else set_all_visited( f.get_destination_city() );
			}
		}	
	}
	if (!(cityList[retCityPos]).visited && cityDeque.empty()) cout << "Shortest path could not be found." << endl;
	return legs;
}

void Graph::c_itin () {
	cout << "C function call not yet implemented." << endl;
} 					

void Graph::s_itin () {
	cout << "Shortets Trip itinerary chosen." << endl;
}

/*
Once a city name has appeared in the flightList within a certain city struct, all flights with this name are marked as visited.
This is done for the shortest hop itinerary, since time and date are not relevant for the search, and we do not want to visit
the same cities multiple times.
*/
void Graph::set_all_visited(string city) {
	for (size_t j = 0; j < cityList.size(); j++) {
		for (size_t i = 0; i < cityList[j].flightList.size(); i++) {
			if (cityList[j].flightList[i].get_destination_city() == city) {
				cityList[j].flightList[i].set_visited(true);
			}
		}
	}
}		

void Graph::reset_all_visited() {
	for (size_t j = 0; j < cityList.size(); j++) {
		for (size_t i = 0; i < cityList[j].flightList.size(); i++) {
			cityList[j].flightList[i].set_visited(false);
			cityList[j].flightList[i].clear_distance();
		}
	}
}	

//resets all City values after breadth first search
void Graph::reset_breadth_first() {								
	for (size_t i = 0; i < cityList.size(); i++) {
		cityList[i].distance= 0;
		cityList[i].visited = false; 
	}
}				
