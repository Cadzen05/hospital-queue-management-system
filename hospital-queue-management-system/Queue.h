#pragma once
#include <string>
#include <iomanip>
#include "Patient.h"

using namespace std;

class Queue {
    private:
        struct Node {
            Patient data;
            Node* next;
            Node(const Patient& p) : data(p), next(nullptr) {}
        };
    
        Node* criticalFront;
        Node* criticalRear;
        Node* regularFront;
        Node* regularRear;
        int size;
        const int MAX_SIZE = 10;
    
    public:
        Queue();
        ~Queue();
        Node* getCriticalFront() const { return criticalFront; }
        Node* getRegularFront() const { return regularFront; }
        bool enqueue(const Patient& p);
        bool enqueueCritical(const Patient& p);
        bool dequeue();
        bool isFull() const;
        bool isEmpty() const;
        int getSize() const;
        Patient peek() const;
        bool removePatientBySSN(const string& ssn, Patient& removed);
        void listPatients(ostream& os) const;
    };

