#include "graph.h"
#include "timeLength.h"
#include <climits>
#include <queue>
#include <algorithm>
#include <iomanip>
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
	//sort(cityList[city_pos(departure_city)].flightList.begin(), cityList[city_pos(departure_city)].flightList.end());
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
		cout << "Enter acceptable time. ";
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
//The departure date must be different from (and before) the return date.
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
	if ( !(d > user_depart_date) ) {
		cout << "Return date is before or on depart date. ";
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
}

/*
No matter the objective, you should print all the legs of the trip, in order, along with the total monetary cost, trip time
(arrival time minus departure time), and number of hops for the best possible itinerary, according to the customer's
specified Trip Constraints and Objectives. 

The itinerary also includes return trip information---a list of flights starting at the destination city on the return date,
 and arriving back at the original departure city.
*/
 void Graph::j_itin () {
 	vector<Flight> path;
 	Flight base;

 	j_recursive(city_pos(user_depart_city), city_pos(user_depart_city), city_pos(user_destination_city), user_depart_time, path, base);
	//cout << "The possible flight paths available to travel to " << user_destination_city << " from " << user_depart_city << " and then back again between " << user_depart_time << " and " << user_return_time << " on " << user_depart_date << " are: " << endl;
 	size_t sizeThere = 10000;
 	int shortestThere;
 	size_t i;
 	int totalCost;
 	int totalHops;
 	TimeLength totalDuration;
 	if (j_flightPaths.size() > 0){
 		for (i = 0; i < j_flightPaths.size(); i++){
 			if (j_flightPaths[i].size() < sizeThere){
 				sizeThere = j_flightPaths[i].size();
 				shortestThere = i;
 			}	 	

 		}
 		float totalCostThere = 0;
 		TimeLength durationThere = j_flightPaths[shortestThere][j_flightPaths[shortestThere].size() - 1].get_flight_arrival_time() - j_flightPaths[shortestThere][0].get_flight_departure_time();
 		cout << "-------------------TRIP ITINERARY-------------------\n";
 		cout << "-------------------DEPARTING TRIP-------------------\n";
		cout << "-------------------" << user_depart_date <<"-------------------------\n";

 		for (size_t j = 0; j < j_flightPaths[shortestThere].size(); j++){
 			totalCostThere += j_flightPaths[shortestThere][j].get_cost();
 			cout << j_flightPaths[shortestThere][j];
 			if (j != j_flightPaths[shortestThere].size() - 1){
 				cout  << "           |" << endl << "           |" << endl << "           v";
 			}
 			cout << "\n";
 		}
 		cout << "=================================\n";
 		cout << "Total One-Way Cost: $" << totalCostThere << endl;
 		cout << "Total One-Way Hops: " << sizeThere << endl;
 		cout << "Total One-Way Time: " << durationThere << endl;
 		cout << "=================================\n\n";
 		totalCost = totalCostThere;
 		totalHops = sizeThere;
 		totalDuration = durationThere;
 		j_flightPaths.clear();
 		j_recursive(city_pos(user_destination_city), city_pos(user_destination_city), city_pos(user_depart_city), user_return_time, path, base);
 		sizeThere = 10000;
 		if (j_flightPaths.size() > 0){
 			for (i = 0; i < j_flightPaths.size(); i++){
 				if (j_flightPaths[i].size() < sizeThere){
 					sizeThere = j_flightPaths[i].size();
 					shortestThere = i;
 				}	 	

 			}
 			totalCostThere = 0;
 			TimeLength durationThere = j_flightPaths[shortestThere][j_flightPaths[shortestThere].size() - 1].get_flight_arrival_time() - j_flightPaths[shortestThere][0].get_flight_departure_time();
			cout << "-------------------RETURNING TRIP-------------------\n";
			cout << "-------------------" << user_return_date <<"-------------------------\n";

 			for (size_t j = 0; j < j_flightPaths[shortestThere].size(); j++){
 				totalCostThere += j_flightPaths[shortestThere][j].get_cost();
 				cout << j_flightPaths[shortestThere][j];
 				if (j != j_flightPaths[shortestThere].size() - 1){
 					cout  << "           |" << endl << "           |" << endl << "           v";
 				}
 				cout << "\n";
 			}
 			cout << "=================================\n";
 			cout << "Total Return Cost: $" << totalCostThere << endl;
 			cout << "Total Return Hops: " << sizeThere << endl;
 			cout << "Total Return Time: " << durationThere << endl;
 			cout << "=================================\n\n";
 			
 			totalCost += totalCostThere;
 			totalHops += sizeThere;
 			totalDuration = totalDuration + durationThere;
			cout << "-------------------ROUND TRIP-------------------\n";

 			cout << "=================================\n";
 			cout << "Total Round-Trip Cost: $" << totalCost << endl;
 			cout << "Total Round-Trip Hops: " << totalHops << endl;
 			cout << "Total Round-Trip Travel Time: " << totalDuration << endl;
 			cout << "=================================\n\n";
 		} else {
 			cout << "There is no possible returning path in that time." << endl;
 		}
 		
 	} else {
 	
 		cout << "\nNo possible paths.\n\n";
 	}		
 }

 void Graph::j_recursive(int start, int current, int destination, Time currentTime, vector <Flight> path, Flight currentFlight){
 	if (current != start){
 		path.push_back(currentFlight);
 	}
 	if (destination == current) {
 		j_flightPaths.push_back(path);
 		return;
 	}

 	for (size_t i = 0; i < cityList[current].flightList.size(); i++){
 		Time flightTime = cityList[current].flightList[i].get_flight_departure_time();
 		if (((flightTime > currentTime) || flightTime == currentTime)){
 			j_recursive(start, city_pos(cityList[current].flightList[i].get_destination_city()), destination, cityList[current].flightList[i].get_flight_arrival_time(), path, cityList[current].flightList[i]);
 		}
 	}
 	return;
 }

//get there in fewest hops w/ breadth first search
 void Graph::f_itin () {
 	cout << "Fewest Hops Itinerary chosen." << endl;
 	TimeLength set_zero(0,0);
 	roundTripTime = set_zero;
 	roundTripCost = 0;
 	roundTripHops = 0;	
	vector<Flight> depart_journey(breadthFirst(user_depart_city, user_destination_city, user_depart_time));		//shortest hops to destination
	if (depart_journey.size() != 0) {
		cout << endl << "DEPARTURE TRIP ON " << user_depart_date << ":" << endl;		
		print_results(depart_journey);
		cout << endl << "RETURN TRIP ON " << user_return_date << ":" << endl;
		vector<Flight> return_journey(breadthFirst(user_destination_city, user_depart_city, user_return_time));	//shortest hops on return trip
		if (return_journey.size() != 0) print_results(return_journey);
		cout << "=================================" << endl;
		cout << "Total Round-Trip Cost: $" << roundTripCost << endl;
		cout << "Total Round-Trip Hops: " << roundTripHops << endl;
		cout << "Total Round-Trip Time: " << roundTripTime << endl;	
		cout << "=================================" << endl << endl;
	}
}							

//print results from breadth first search
void Graph::print_results(vector<Flight> breadth_results) {
	Time compareFlightTime;
	int totalHops = 0;
	float totalCost = 0.0;
	TimeLength totalTripTime(0,0);
	TimeLength day(24,0);
	TimeLength reset(0,0);
	deque<Flight> path;
	size_t end_index = breadth_results.size() - 1;
	path.push_front( breadth_results[end_index] );
	totalTripTime = breadth_results[end_index].get_flight_duration();
	totalCost += breadth_results[end_index].get_cost();
	for (int j = end_index - 1; j >= 0; j--) {
		string prev = path[0].get_departure_city();
		compareFlightTime = path[0].get_flight_departure();
		if (breadth_results[j].get_destination_city() == prev) {
			path.push_front(breadth_results[j]);
			totalTripTime = totalTripTime + breadth_results[j].get_flight_duration();						
			totalCost += breadth_results[j].get_cost();
		}
	}
	//check for layover times
	for (size_t i = 0; i < path.size() - 1; i++){
		if(path[i].get_flight_arrival() > path[i+1].get_flight_departure() ){
			totalTripTime = totalTripTime - path[i+1].get_flight_duration();
			TimeLength temp = (path[i].get_flight_arrival() - path[i+1].get_flight_departure());
			TimeLength tempDuration = 	path[i+1].get_flight_duration();
			path[i+1].set_time_duration(reset);
			path[i+1].set_time_duration(day - temp + tempDuration);
			totalTripTime = totalTripTime + path[i+1].get_flight_duration();								
		}
	}
	for (size_t i = 0; i < path.size(); i++) {
		cout << path[i];
		if ( i < (path.size() - 1) ) {
			totalHops++;
			cout << "		|" << endl;
			cout << "		|" << endl;
			cout << "		V" << endl;
		} else cout << endl;
	}
	cout << "Total One-Way Cost: $" << totalCost << endl;
	cout << "Total One-Way Hops: " << totalHops << endl;
	cout << "Total One-Way Time: " << totalTripTime << endl << endl;
	roundTripTime = roundTripTime + totalTripTime;
	roundTripCost += totalCost;
	roundTripHops += totalHops;
	//=====RESET FIELDS=====//
	reset_breadth_first();																							//reset city struct variables
	reset_all_visited();																							//reset flight visited value		
	totalTripTime = reset;
	//======================//
}


/*
Since cityList is a struct comprised of a string city name and a vector of flight objects, linking flight destinations to 
cities on the cityList was done through a deque of strings. The initial departure city is first added to the struct and its 
corresponding city struct in CityList is marked as visited. Then it is taken off the deque and we iterate through its flight vector. Each flight
destination name within this vector is added to the deque. All flight objects with this destination name are marked visited in their flight 
object variables. The first element of the deque is then popped. It will be the name of a city that we have gotten from a flight object.
Its corresponding element in cityList will be set to visited. This cityList element then has its flight vector iterated through. 
This process is repeated for each successive name in the deqeue until the queue is empty. 
This algorithm ensures that the function does not quit prematurely, as it must print out multiple flight paths if they exist. As a result, the while loop
cannot exit until deque is empty. Once the destination city is reached much, bool onePath = true. Now, only
flights that arrive in the correct destination city are added to the vector. This saves space and results in the deqeue not adding unnecessary new elements.
Function returns a vector of flights that can be taken to reach the destination city.
*/
vector<Flight> Graph::breadthFirst (const string &departCity, const string &retCity, Time &departTime) {
	bool destination_reached = false;
	int retCityPos = city_pos(retCity);																					//get position of retCity in cityList
	deque<string> cityDeque;																							//create queue of cities to visit
	vector<Flight> legs;																								//create vector of possible flights to take
	cityDeque.push_back(departCity);																					//put start city in queue
	while ( !cityDeque.empty() && !destination_reached) {																//while deque is not empty and destination has not been reached
		string vertex = cityDeque.front();																				//get first city name from queue
		cityDeque.pop_front();																							//remove it from queue
		cityList[city_pos(vertex)].visited = true;																		//mark city in cityList visited
		for (size_t i = 0; i < cityList[city_pos(vertex)].flightList.size(); i++ ) {									//iterate through all flights leaving from this city
			Flight f(cityList[city_pos(vertex)].flightList[i]);															//create Flight object for each element
			if ( !f.was_visited() ) {																					//if flight is distinct:
				if (f.get_departure_city() == departCity && f.get_flight_departure() < departTime ){}					//if first flight leaves before the user wants to start trip (departure and return), skip this flight
					else {
					if ( f.get_destination_city() == departCity) set_all_visited( f.get_destination_city() );			//this ensures flights with initial city's name (departCity) is not visited and departCity is not added to final vector.			
					else {
						if ( !(destination_reached) ) {
							cityDeque.push_back( f.get_destination_city() );											//push name of destination onto deque				
							set_all_visited( f.get_destination_city() );												//mark all flights with the same destination as visited to avoid repeats. Ex: Boston has two flights to Philly - we only need to look at the first flight and ignore the second. Ignores return city because different flight paths can get to destination in same amount of hops, so it must be revisited
							legs.push_back(f);																			//push flight onto itinerary vector
						}
					}
		 			if ( f.get_destination_city() == retCity) destination_reached = true;								//final city has been visited once.
		 		}
		 	}
		 }	
		}
		if (!(cityList[retCityPos]).visited && cityDeque.empty()) {
			cout << "Shortest path could not be found. Check flight listings and flight times." << endl << endl;
			vector<Flight> fail(0);
			return fail;
		} 
		return legs;
	}	
	void Graph::c_itin () {
		cout << "C function call not yet implemented." << endl;
	} 					

	void Graph::s_itin () {
		roundTripCost = 0;
		roundTripHops = 0;
		roundTripTime = TimeLength(0,0);
		cout << "-------------------DEPARTING TRIP-------------------\n";
		shortest_travel_time(user_depart_city, user_destination_city, "departing");
		float tempRoundTripCost = roundTripCost;
		int tempRoundTripHops = roundTripHops;
		TimeLength tempRoundTripTime = roundTripTime;

		if(roundTripCost != 0 && roundTripHops != 0 && !(roundTripTime == TimeLength(0,0))){
			cout << "-------------------RETURNING TRIP-------------------\n";
			shortest_travel_time(user_destination_city, user_depart_city, "returning");
			if(roundTripCost > tempRoundTripCost && roundTripHops > tempRoundTripHops &&  roundTripTime > tempRoundTripTime){
				cout << "-------------------ROUND TRIP-------------------\n";
				cout << "The cost for round trip is: " << "$" << roundTripCost << endl;
				cout << "The total number of hops for the round trip is: " << roundTripHops << endl;
				cout << "The total trip time for the round trip is: " << roundTripTime << endl << endl;
			}
		}else{
			cout << "-------------------RETURNING TRIP-------------------\n";
			cout << "There is no flight within the given constraints from " << user_destination_city << " to " << user_depart_city << endl;
		}

	}

	void Graph::shortest_travel_time(string departure, string arrival, string mode){
		int source_index = city_pos(departure);
		vector<TimeLength> d;
		for(unsigned i = 0; i < cityList.size(); i++){
			d.push_back(TimeLength(1000000,0));
		}
		d[source_index] = TimeLength(0, 0);
		vector<Flight> shortest_path_list(cityList.size()), Q;
		for(unsigned i = 0; i < cityList.size(); i++){
			for(unsigned j = 0; j < cityList[i].flightList.size(); j++){
				Q.push_back(cityList[i].flightList[j]);
			}
		}
		Time previous_departure;
		if(mode == "departing"){
			previous_departure = user_depart_time;
		}else if(mode == "returning"){
			previous_departure = user_return_time;
		}
		while(!Q.empty()){
			Flight f = Q.front();
			Q.erase(Q.begin());
			int city_index = city_pos(f.get_destination_city());
			for(unsigned i = 0; i < cityList[city_index].flightList.size(); i++){
				if(d[city_pos(cityList[city_index].flightList[i].get_departure_city())] > (d[city_pos(f.get_departure_city())]) + (f.get_flight_duration())){
					if(mode == "departing"){
						if(f.get_flight_departure() > previous_departure || f.get_flight_departure() > user_depart_time){
							d[city_pos(cityList[city_index].flightList[i].get_departure_city())] = (d[city_pos(f.get_departure_city())]) + (f.get_flight_duration());
							shortest_path_list[city_pos(cityList[city_index].flightList[i].get_departure_city())] = f;
							previous_departure = f.get_flight_departure();
						}
					}else if(mode == "returning"){
						if(f.get_flight_departure() > previous_departure || f.get_flight_departure() > user_return_time){
							d[city_pos(cityList[city_index].flightList[i].get_departure_city())] = (d[city_pos(f.get_departure_city())]) + (f.get_flight_duration());
							shortest_path_list[city_pos(cityList[city_index].flightList[i].get_departure_city())] = f;
							previous_departure = f.get_flight_departure();
						}
					}
				}
			}
		}
		vector<Flight> final_list;
		string current_city = arrival;
		while(current_city != departure){
			if(shortest_path_list[city_pos(current_city)].get_departure_city() != ""){
				final_list.push_back(shortest_path_list[city_pos(current_city)]);
				current_city = shortest_path_list[city_pos(current_city)].get_departure_city();
			}else{
				break;
			}
		}
		if(d[city_pos(arrival)] == TimeLength(1000000,0)){
			cout << "There is no flight within the given constraints from " << departure << " to " << arrival << endl;
		}else{
			cout << "The shortest " << mode << " trip is via the following flight(s): \n\n";
			float cost = 0;
			TimeLength the_time(0,0);
			for(int i = final_list.size() - 1; i >= 0; i--){
				if(i == 0){
					cost += final_list[i].get_cost();
					the_time = the_time + final_list[i].get_flight_duration();
					cout << final_list[i] << endl;
				}else{
					cost += final_list[i].get_cost();
					the_time = the_time + final_list[i].get_flight_duration();
					cout << final_list[i]  << "           |" << endl << "           |" << endl << "           v\n";
				}
			}

			cout << "The cost for the trip is: " << "$" << cost << endl;
			cout << "The number of hops for the trip is: " << final_list.size() << endl;
			cout << "The trip time is: " << the_time << endl;
			roundTripCost += cost;
			roundTripTime = roundTripTime + the_time;
			roundTripHops += final_list.size();
		}	
	}

/*
Once a city name has appeared in the flightList within a certain city struct, all flights with this name are marked as visited.
This is done for the fewest hop itinerary, since time and date are not relevant for the search, and we do not want to visit
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
