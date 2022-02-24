#include "Passenger.h"

Passenger::Passenger(std::string firstname, std::string lastname) {
    this->firstname = firstname;
    this->lastname = lastname;
}

const std::string &Passenger::getFirstname() const {
    return firstname;
}

const std::string &Passenger::getLastname() const {
    return lastname;
}

bool Passenger::operator<(const Passenger &rhs) const {
    if((*this).lastname != rhs.lastname){
        int i = 1;
        int j = 0;
        int thisize = lastname.size();
        int rhsize = rhs.lastname.size();
        while(i){
            if(j == thisize && j < rhsize){
                i = 0;
                return true;
            }
            else if(j < thisize && j == rhsize){
                i = 0;
                return false;
            }
            else if(this->lastname[j] < rhs.lastname[j]){
                i = 0;
                return true;
            }
            else if(this->lastname[j] > rhs.lastname[j]){
                i = 0;
                return false;
            }
            else{
                i =1;
                j++;
            }
        }
    }
    else{
        int i = 1;
        int j = 0;
        int thisize = firstname.size();
        int rhsize = rhs.firstname.size(); 
        while(i){
            if(j == thisize && j < rhsize){
                i = 0;
                return true;
            }
            else if(j < thisize && j == rhsize){
                i = 0;
                return false;
            }
            else if(this->firstname[j] < rhs.firstname[j]){
                i = 0;
                return true;
            }
            else if(this->firstname[j] > rhs.firstname[j]){
                i = 0;
                return false;
            }
            else{
                i =1;
                j++;
            }
        }
    }
    /* TODO */
}

bool Passenger::operator>(const Passenger &rhs) const {
    return rhs < *this;
}

bool Passenger::operator==(const Passenger &rhs) const {
    return firstname == rhs.firstname && lastname == rhs.lastname;
}

bool Passenger::operator!=(const Passenger &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Passenger &passenger) {
    os << "Passenger(firstname: " << passenger.firstname;
    os << ", lastname: " << passenger.lastname << ")";
    return os;
}
