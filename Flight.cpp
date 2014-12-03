#include "Flight.h"

//default constructor
Flight::Flight(){

}

//value constructor, takes in the departure city, destination city, departure time, arrival time, cost and sets the members accordingly.
Flight::Flight(string the_departure, string the_destination, Time the_departure_time, Time the_arrival_time, float the_cost) {
    destination = the_destination;
    departure = the_departure;
    cost = the_cost;
    departure_time = the_departure_time;
    arrival_time = the_arrival_time;
    flight_duration = arrival_time - departure_time;
}
//Prints out a Flight object. Formatted as Departure, Destination, Departure Time, Arrival Time, Cost, Flight Duration.
ostream& operator<< (ostream& out, const Flight& flight) {
    out << "Departure: " << flight.departure << "\nDestination: " << flight.destination << "\nDeparture Time: " << flight.departure_time << "\nArrival Time: " << flight.arrival_time << "\nCost: $" << flight.cost << "\nTrip Time: " << flight.flight_duration  << endl;
    return out;
}

//checks to see if one flight has a shorter duration than the other
bool Flight::operator<(const Flight& flight) {
    return (flight_duration < flight.flight_duration);
}

//checks to see if one flight has a longer duration than the other
bool Flight::operator>(const Flight& flight) {
    return (flight_duration > flight.flight_duration);

}

//checks to see if both flights have the same duration
bool Flight::operator==(const Flight& flight) {
    return (flight_duration == flight.flight_duration);
}

//destructor
Flight::~Flight() {

}
