#pragma once
#include <iostream>
#include <string>
#include "Queue.h"

using namespace std;

// Represents a hospital clinic with its own queue of patients.
class Clinic {
    private:
        string name;
        Queue queue;
    public:
        Clinic();
        Clinic(string clinicName);
        
        string getName() const;
        bool addPatient(const Patient& p);
        bool addCriticalPatient(const Patient& p);
        bool removePatient();
        Patient takeOutPatient();
        bool cancelPatient(const string& ssn, Patient& removed);
        bool isFull() const;
        void listPatients(ostream& os) const;
    };
