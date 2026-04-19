#include "Functions.h"

// Returns true if the string contains only numeric characters.
bool isDigits(string str) {
    return str.find_first_not_of("0123456789") == string::npos;
}

// Load patient records from the CSV file into their assigned clinics.
void loadPatients(ifstream& inFile, map<string, Clinic>& clinics, ofstream& outFile) {
    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string clinicCode, firstName, lastName, ssn;

        getline(ss, clinicCode, ',');
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, ssn, ',');

        // Skip records that reference an unknown clinic code.
        if (clinics.find(clinicCode) == clinics.end()) {
            outFile << "Invalid clinic code: " << clinicCode << " — Line skipped\n";
            continue;
        }

        // Skip records that have non-numeric SSN's.
        if (!isDigits(ssn)) {
            outFile << "Invalid SSN for " << firstName << " " << lastName << " — Line skipped\n";
            continue;
        }

        Patient p(firstName, lastName, ssn);

        // Add the patient if space is available in the clinic queue.
        if (!clinics[clinicCode].addPatient(p)) {
            outFile << "Clinic full: " << clinicCode << " — Could not add " << p << "\n";
        } else {
            outFile << "Added: " << p << " to " << clinicCode << "\n";
        }
    }

    outFile << "\n\n";
}

// Add a regular patient to the selected clinic.
void addPatient(Clinic& clinic, ofstream& outFile) {
    string firstName, lastName, ssn;

    cout << "\nEnter Patient's First Name: ";
    cin >> firstName;
    cout << "Enter Patient's Last Name: ";
    cin >> lastName;
    cout << "Enter Patient's SSN: ";
    cin >> ssn;

    if (ssn.empty()) {
        cout << "Operation canceled: SSN cannot be empty.\n";
        outFile << "Operation canceled: SSN cannot be empty.\n";
        return;
    }

    // Require the SSN to contain only digits.
    if (!isDigits(ssn)) {
        cout << "Invalid SSN. SSN must be numeric.\n";
        outFile << "Invalid SSN for " << firstName << " " << lastName << ": SSN must be numeric.\n";
        return;
    }

    // Stop the user if the clinic queue is full.
    if (clinic.isFull()) {
        cout << "Clinic is full. Cannot add patient.\n";
        outFile << "Clinic is full. Cannot add patient for " << firstName << " " << lastName << ".\n";
        return;
    }

    Patient p(firstName, lastName, ssn);

    if (clinic.addPatient(p)) {
        cout << clinic.getName() << " Patient (Regular):    " << firstName << " " << lastName << " was added to the waiting room\n";
        outFile << clinic.getName() << " Patient (Regular):    " << firstName << " " << lastName << " was added to the waiting room\n";
    }
    else {
        cout << "Failed to add patient.\n";
        outFile << "Failed to add patient: " << firstName << " " << lastName << ".\n";
    }
}

// Add a critical patient so they receive priority in the queue.
void addCriticalPatient(Clinic& clinic, ofstream& outFile) {
    string firstName, lastName, ssn;

    cout << "\nEnter first name: ";
    cin >> firstName;
    cout << "Enter last name: ";
    cin >> lastName;
    cout << "Enter SSN: ";
    cin >> ssn;

    if (ssn.empty()) {
        cout << "Operation canceled: SSN cannot be empty.\n";
        outFile << "Operation canceled: SSN cannot be empty.\n";
        return;
    }

    // Require the SSN to contain only digits.
    if (!isDigits(ssn)) {
        cout << "Invalid SSN. SSN must be numeric.\n";
        outFile << "Invalid SSN for " << firstName << " " << lastName << ": SSN must be numeric.\n";
        return;
    }

    // Stop the user if the clinic queue is full.
    if (clinic.isFull()) {
        cout << "Clinic is full. Cannot add critical patient.\n";
        outFile << "Clinic is full. Cannot add critical patient for " << firstName << " " << lastName << ".\n";
        return;
    }

    Patient p(firstName, lastName, ssn);

    if (clinic.addCriticalPatient(p)) {
        cout << clinic.getName() << " Patient (Critical):    " << firstName << " " << lastName << " was added to the waiting room\n";
        outFile << clinic.getName() << " Patient (Critical):    " << firstName << " " << lastName << " was added to the waiting room\n";
    }
    else {
        cout << "Failed to add critical patient.\n";
        outFile << "Failed to add critical patient: " << firstName << " " << lastName << ".\n";
    }
}

// Remove the next patient for operation.
void operationOnPatient(Clinic& clinic, ofstream& outFile) {
    Patient moved = clinic.takeOutPatient();

    // Only log the action if a real patient was moved.
    if (!moved.getFirstName().empty() && !moved.getLastName().empty()) {
        outFile << clinic.getName() << " Patient: " << moved.getFirstName() << " " << moved.getLastName() << " was taken to the operating room.\n";
    }
}

// Remove a patient from the queue using their SSN.
void cancelPatient(Clinic& clinic, ofstream& outFile) {
    string ssn;
    cout << "\nEnter Patient SSN: ";
    cin >> ssn;

    Patient removed;

    if (clinic.cancelPatient(ssn, removed)) {
        cout << clinic.getName() << " Patient: " << removed.getFirstName() << " " << removed.getLastName() << " was removed from the waiting list.\n";
        outFile << clinic.getName() << " Patient: " << removed.getFirstName() << " " << removed.getLastName() << " was removed from the waiting list.\n";
    } else {
        cout << "ERROR " << clinic.getName() << ": Unable to find patient: " << ssn << " in the waiting room.\n";
        outFile << "ERROR " << clinic.getName() << ": Unable to find patient: " << ssn << " in the waiting room.\n";
    }
}

// Display all patients currently waiting in the specific clinic.
void listPatients(Clinic& clinic, ofstream& outFile) {
    cout << "\nPatient List\n";
    outFile << "\nPatient List\n";

    clinic.listPatients(cout);
    clinic.listPatients(outFile);

    cout << endl;
    outFile << endl;
}

// Show the main clinic selection menu to the user.
void displayMenu(map<string, Clinic>& clinics, ofstream& outFile) {
    int choice;
    do {
        cout << "\n    KC RESEARCH HOSPITAL\n";
        cout << "1. Heart Clinic\n";
        cout << "2. Pulmonary Clinic\n";
        cout << "3. Plastic Surgery\n";
        cout << "4. Quit\n";
        cout << "Please enter the clinic of interest: ";
        cin >> choice;

        switch (choice) {
        case 1:
            clinicMenu(clinics["HC"], outFile);
            break;
        case 2:
            clinicMenu(clinics["PC"], outFile);
            break;
        case 3:
            clinicMenu(clinics["PSC"], outFile);
            break;
        case 4:
            break;
        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 4);
}

// Show the action menu for a specific clinic.
void clinicMenu(Clinic& clinic, ofstream& outFile) {
    int choice;
    
    do {
        cout << "\nWelcome to the " << clinic.getName() << "\n";
        cout << "1. - Add Patient\n";
        cout << "2. - Add Critical Patient\n";
        cout << "3. - Take out Patient for Operation\n";
        cout << "4. - Cancel Patient\n";
        cout << "5. - List Patients in Queue\n";
        cout << "6. - Change Department or exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                addPatient(clinic, outFile);
                break;
            case 2:
                addCriticalPatient(clinic, outFile);
                break;
            case 3:
                operationOnPatient(clinic, outFile);
                break;
            case 4:
                cancelPatient(clinic, outFile);
                break;
            case 5:
                listPatients(clinic, outFile);
                break; 
            case 6:
                cout << "Returning to department menu.\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 6);
}