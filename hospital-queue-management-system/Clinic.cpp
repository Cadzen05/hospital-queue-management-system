#include "Clinic.h"
#include <iostream>

Clinic::Clinic() : name("Unnamed Clinic") {}

Clinic::Clinic(string clinicName) : name(clinicName) {}

string Clinic::getName() const {
    return name;
}

bool Clinic::addPatient(const Patient& p) {
    return queue.enqueue(p);
}

bool Clinic::addCriticalPatient(const Patient& p) {
    return queue.enqueueCritical(p);
}

bool Clinic::removePatient() {
    return queue.dequeue();
}

Patient Clinic::takeOutPatient() {
    if (queue.isEmpty()) {
        cout << "No more patients." << endl;
        return Patient("", "", "");
    }
    Patient next = queue.peek();
    queue.dequeue();
    cout << name << " Patient: " << next.getFirstName() << " " << next.getLastName()
     << " was taken to the operating room." << endl;
    return next;
}

bool Clinic::cancelPatient(const string& ssn, Patient& removed) {
    return queue.removePatientBySSN(ssn, removed);
}


bool Clinic::isFull() const {
    return queue.isFull();
}

void Clinic::listPatients(ostream& os) const {
    queue.listPatients(os);
}
