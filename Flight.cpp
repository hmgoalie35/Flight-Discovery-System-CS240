#include "Flight.h"

Flight::Flight(string the_departure, string the_destination, Time the_departure_time, Time the_arrival_time, float the_cost) {
    destination = the_destination;
    departure = the_departure;
    cost = the_cost;
    departure_time = the_departure_time;
    arrival_time = the_arrival_time;
}

ostream& operator<< (ostream& out, Flight& flight) {
    out << "Departure: " << flight.departure << "\nDestination: " << flight.destination << "\nDeparture Time: " << flight.departure_time << "\nArrival Time: " << flight.arrival_time << "\nCost: $" << flight.cost << "\nTrip Time: " << (flight.arrival_time - flight.departure_time)  << endl;
    return out;
}

bool Flight::operator< (const Flight& flight) {
    return (departure_time < flight.departure_time) && (arrival_time < flight.arrival_time);
}

bool Flight::operator> (const Flight& flight ) {
    return (departure_time > flight.departure_time) && (arrival_time > flight.arrival_time);

}

bool Flight::operator== (const Flight& flight) {
    return (destination == flight.destination && departure == flight.departure && cost == flight.cost && departure_time == flight.departure_time && arrival_time == flight.arrival_time);
}

// Flight::~Flight() {

// }
