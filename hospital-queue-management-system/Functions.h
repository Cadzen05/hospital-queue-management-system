#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cctype>
#include "Clinic.h"
#include "Patient.h"

using namespace std;

void loadPatients(ifstream& inFile, map<string, Clinic>& clinics, ofstream& outFile);
void displayMenu(map<string, Clinic>& clinics, ofstream& outFile);
void clinicMenu(Clinic& clinic, ofstream& outFile);
void addPatient(Clinic& clinic, ofstream& outFile);
void addCriticalPatient(Clinic& clinic, ofstream& outFile);
void operationOnPatient(Clinic& clinic, ofstream& outFile);
void cancelPatient(Clinic& clinic, ofstream& outFile);
void listPatients(Clinic& clinic, ofstream& outFile);



