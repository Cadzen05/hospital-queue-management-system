#include <iostream>
#include <iomanip>
#include "Functions.h"
using namespace std;

int main()
{
    // Opens the input file containing the patient records.
    ifstream inFile;
    inFile.open("sample_patients.csv");
    if (!inFile.is_open()) {
        cerr << "Error opening file: sample_patients.csv\n";
        return 1;
    }

    // Opens the output file to log actions and errors.
    ofstream outFile;
    outFile.open("report.txt");

    if (!outFile.is_open()) {
        cerr << "Error opening file: report.txt\n";
        return 1;
    }

    // Creates the hospital clinics used throughout the program.
    map<std::string, Clinic> clinics = {
        {"HC", Clinic("Heart Clinic")},
        {"PC", Clinic("Pulmonary Clinic")},
        {"PSC", Clinic("Plastic Surgery Clinic")}
    };

    // Load patient data initially, and display interactive user menu.
    loadPatients(inFile, clinics, outFile);
    displayMenu(clinics, outFile);

    inFile.close();
    outFile.close();

    return 0;
}
 
