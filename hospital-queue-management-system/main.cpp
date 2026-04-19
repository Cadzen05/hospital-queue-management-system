//This file contains the 'main' function. Program execution begins and ends there.
// Caden Cunningham
// 5/7/2025

#include <iostream>
#include <iomanip>
#include "Functions.h"
using namespace std;

int main()
{
    ifstream inFile;
    inFile.open("patient.csv");

    if (!inFile.is_open()) {
        cerr << "Error opening file: inFile\n";
        return 0;
    }

    ofstream outFile;
    outFile.open("report.txt");

    if (!outFile.is_open()) {
        cerr << "Error opening file: outFile\n";
        return 0;
    }

    map<std::string, Clinic> clinics = {
        {"HC", Clinic("Heart Clinic")},
        {"PC", Clinic("Pulmonary Clinic")},
        {"PSC", Clinic("Plastic Surgery Clinic")}
    };

    loadPatients(inFile, clinics, outFile);
    displayMenu(clinics, outFile);

    inFile.close();
    outFile.close();

    return 0;
}
 
