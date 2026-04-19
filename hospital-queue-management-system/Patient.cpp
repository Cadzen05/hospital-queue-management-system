#include "Patient.h"
#include <iostream>

Patient::Patient(string fn, string ln, string s) : firstName(fn), lastName(ln), ssn(s) {}

string Patient::getFirstName() const { return firstName; }
string Patient::getLastName() const { return lastName; }
string Patient::getSSN() const { return ssn; }

void Patient::setFirstName(const string& fn) { firstName = fn; }
void Patient::setLastName(const string& ln) { lastName = ln; }
void Patient::setSSN(const string& s) { ssn = s; }

ostream& operator<<(ostream& os, const Patient& p) {
    os << p.firstName << " " << p.lastName << " (" << p.ssn << ")";
    return os;
}