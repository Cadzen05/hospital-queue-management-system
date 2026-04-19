#pragma once
#include <iostream>
#include <string>

using namespace std;

// Stores patient information used throughout the queue system.
class Patient {
private:
    string firstName;
    string lastName;
    string ssn;

public:
    Patient(string fn = "", string ln = "", string s = "");
    
    string getFirstName() const;
    string getLastName() const;
    string getSSN() const;

    void setFirstName(const string&);
    void setLastName(const string&);
    void setSSN(const string&);

    friend ostream& operator<<(ostream& os, const Patient& p);
};
