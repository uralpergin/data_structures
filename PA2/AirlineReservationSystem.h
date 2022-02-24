#ifndef AIRLINERESERVATIONSYSTEM_H
#define AIRLINERESERVATIONSYSTEM_H

#include "BST.h"
#include "Queue.h"
#include "Passenger.h"
#include "Flight.h"
#include "Ticket.h"

class AirlineReservationSystem {
public: // DO NOT CHANGE THIS PART.
    AirlineReservationSystem() {}

    void addPassenger(const std::string &firstname, const std::string &lastname);

    Passenger *searchPassenger(const std::string &firstname, const std::string &lastname);

    void addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity);

    std::vector<Flight *> searchFlight(const std::string &departureCity, const std::string &arrivalCity);

    void issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType);

    void saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType);

    void executeTheFlight(const std::string &flightCode);

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    Passenger *searchPassenger(BSTNode<Passenger> *p,Passenger pass){
        if(p == NULL) return NULL;
        else{
            if(p -> data  == pass) return &(p->data);
            else if(p -> data > pass) return searchPassenger(p -> left, pass);
            else return searchPassenger(p -> right, pass);
        }
    }

    bool searchCode(BSTNode<Flight> *p,Flight fli){
        if(p == NULL) return false;
        else{
            if(p -> data == fli) return true;
            else if(p -> data > fli) return searchCode(p -> left, fli);
            else return searchCode(p -> right, fli);
        }
    }

    void searchFlight(BSTNode<Flight> *p,std::vector<Flight *> &f,const std::string &departureCity, const std::string &arrivalCity){
        if(p == NULL) ;
        else{
            if((p -> data).getDepartureCity() == departureCity && (p -> data).getArrivalCity() == arrivalCity) f.push_back(&(p -> data));
            searchFlight(p->left,f,departureCity,arrivalCity);
            searchFlight(p->right,f,departureCity,arrivalCity);
        }
    }

    Flight *searchForFlight(BSTNode<Flight> *p,const std::string flightcode){
        if(p == NULL) return NULL;
        else{
            if((p->data).getFlightCode() == flightcode) return &(p->data);
            else if((p->data).getFlightCode() > flightcode) return searchForFlight(p->left,flightcode);
            else return searchForFlight(p->right,flightcode);
        }
    }

   

private: // DO NOT CHANGE THIS PART.
    BST<Passenger> passengers;
    BST<Flight> flights;

    Queue<Ticket> freeTicketRequests;
};

#endif //AIRLINERESERVATIONSYSTEM_H
