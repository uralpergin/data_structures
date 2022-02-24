#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname) {
    Passenger pass = Passenger(firstname,lastname);
    if(searchPassenger(passengers.getRoot(),pass) == NULL){
        passengers.insert(pass);
    }
    else ;
    /* TODO */
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname) {
    Passenger pass = Passenger(firstname,lastname);
    if(passengers.getRoot() == NULL) return NULL;
    else return searchPassenger(passengers.getRoot(),pass);
    /* TODO */
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity) {
    Flight fli = Flight(flightCode,departureTime,arrivalTime,departureCity,arrivalCity,economyCapacity, businessCapacity);
    if(searchCode(flights.getRoot(),fli) == true) ;
    else flights.insert(fli);
    /* TODO */
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity) {
    std::vector<Flight *> fligh;
    if(flights.getRoot() == NULL) return fligh;
    else{
        searchFlight(flights.getRoot(),fligh,departureCity,arrivalCity);
        return fligh;
    }
    /* TODO */
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    Passenger *pass = searchPassenger(firstname,lastname);
    Flight *fli = searchForFlight(flights.getRoot(),flightCode);
    if(pass != NULL && fli != NULL){
        Ticket tick = Ticket(pass,fli,ticketType);
        (*fli).addTicket(tick);
    }
    else ;
    /* TODO */
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType) {
    Passenger *pass = searchPassenger(firstname,lastname);
    Flight *fli = searchForFlight(flights.getRoot(),flightCode);
    if(pass != NULL && fli != NULL){
        Ticket tick = Ticket(pass,fli,ticketType);
        if(!freeTicketRequests.isFull()) freeTicketRequests.enqueue(tick);
        else;
    }
    else;
    /* TODO */
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode) {
    Flight *fli = searchForFlight(flights.getRoot(),flightCode);
    int size = freeTicketRequests.size();
    if(fli != NULL){
        for(int i = 0; i < size;i++){
            if(freeTicketRequests.peek().getFlight()->getFlightCode() == flightCode){
                if((*fli).addTicket(freeTicketRequests.peek()) == true) freeTicketRequests.dequeue();
                else freeTicketRequests.enqueue(freeTicketRequests.dequeue());
            }
            else freeTicketRequests.enqueue(freeTicketRequests.dequeue()); 
        }
        (*fli).setCompleted(true);
    }
    else;
    /* TODO */
}

void AirlineReservationSystem::print() const {
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}
