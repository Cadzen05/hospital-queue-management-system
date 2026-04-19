#include "Queue.h"
#include <iostream>

using namespace std;

Queue::Queue() : criticalFront(nullptr), criticalRear(nullptr),
                 regularFront(nullptr), regularRear(nullptr), size(0) {}

Queue::~Queue() {
    // Free up all dynamically allocated nodes before destruction.
    while (!isEmpty()) {
        dequeue();
    }
}

bool Queue::isFull() const {
    return size >= MAX_SIZE;
}

bool Queue::isEmpty() const {
    return size == 0;
}

int Queue::getSize() const {
    return size;
}

bool Queue::enqueue(const Patient& p) {
    if (isFull()) return false;

    Node* newNode = new Node(p);

    // Regular patients are added to the regular queue.
    if (!regularRear) {
        regularFront = regularRear = newNode;
    } else {
        regularRear->next = newNode;
        regularRear = newNode;
    }

    size++;
    return true;
}

bool Queue::enqueueCritical(const Patient& p) {
    if (isFull()) return false;

    Node* newNode = new Node(p);

    // Critical patients are stored separately so they are first served.
    if (!criticalRear) {
        criticalFront = criticalRear = newNode;
    } else {
        criticalRear->next = newNode;
        criticalRear = newNode;
    }

    size++;
    return true;
}

bool Queue::dequeue() {
    Node* temp = nullptr;

    // Always remove a critical patient before a regular patient.
    if (criticalFront) {
        temp = criticalFront;
        criticalFront = criticalFront->next;
        if (!criticalFront) criticalRear = nullptr;
    } else if (regularFront) {
        temp = regularFront;
        regularFront = regularFront->next;
        if (!regularFront) regularRear = nullptr;
    } else {
        return false;
    }

    delete temp;
    size--;
    return true;
}

Patient Queue::peek() const {
    // Return the next patient to be served without removing.
    if (criticalFront) return criticalFront->data;
    if (regularFront) return regularFront->data;
    return Patient("", "", "");
}

bool Queue::removePatientBySSN(const string& ssn, Patient& removed) {
    Node* prev = nullptr;
    Node* curr = criticalFront;

    // Check critical patient queue first.
    while (curr) {
        if (curr->data.getSSN() == ssn) {
            removed = curr->data;

            if (prev) prev->next = curr->next;
            else criticalFront = curr->next;

            if (curr == criticalRear) criticalRear = prev;

            delete curr;
            size--;
            return true;
        }

        prev = curr;
        curr = curr->next;
    }

    // If not found, search the regular queue.
    prev = nullptr;
    curr = regularFront;

    while (curr) {
        if (curr->data.getSSN() == ssn) {
            removed = curr->data;

            if (prev) prev->next = curr->next;
            else regularFront = curr->next;

            if (curr == regularRear) regularRear = prev;

            delete curr;
            size--;
            return true;
        }

        prev = curr;
        curr = curr->next;
    }

    return false;
}

void Queue::listPatients(ostream& os) const {
    Node* curr = criticalFront;

    // Display critical patients first.
    while (curr) {
        os << left << setw(15) << curr->data.getFirstName()
           << setw(20) << curr->data.getLastName()
           << setw(10) << curr->data.getSSN()
           << setw(10) << "C" << '\n';
        curr = curr->next;
    }

    // Display regular patients after critical patients.
    curr = regularFront;
    while (curr) {
        os << left << setw(15) << curr->data.getFirstName()
           << setw(20) << curr->data.getLastName()
           << setw(10) << curr->data.getSSN()
           << setw(10) << "R" << '\n';
        curr = curr->next;
    }
}