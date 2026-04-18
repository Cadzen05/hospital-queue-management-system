# hospital-queue-management-system
C++ hospital queue management system with priority handling for critical patients, file I/O, and object-oriented design

## **Features**

- Manages patients across Heart, Pulmonary, and Plastic Surgery clinics
- Prioritizes critical patients over regular patients
- Loads patient data from a CSV file
- Cancels patients by SSN
- Generates a report log of actions and errors
- Uses object-oriented design with custom queue logic

## **Getting Started**

### **Prerequisites**

Before running the program, make sure you have:
- A C++ compiler such as **g++** or **Visual Studio**
- All project source files in the same folder
- A valid `patient.csv` input file

### **Installation**

1. Clone or download this repository.
2. Place all `.cpp`, `.h`, and `patient.csv` files in the same directory.
3. Compile the program.

Using g++:

```bash
g++ main.cpp Clinic.cpp Functions.cpp Patient.cpp Queue.cpp -o hospital
```

### **Usage**

Run the program:

./hospital

After starting, the program:

- Loads patient data from patient.csv
- Lets you choose a clinic department
- Allows you to add patients, add critical patients, remove patients for operation, cancel patients, and list the current queue
- Writes activity and error messages to report.txt

### **Input Format**

The patient.csv file should use this format:

ClinicCode,FirstName,LastName,SSN
HC,Bernie,Sanders,2
PC,Yosemite,Sam,1
PSC,Bugs,Bunny,3


Clinic codes:

- HC = Heart Clinic
- PC = Pulmonary Clinic
- PSC = Plastic Surgery Clinic

## **Contact**

For questions, feedback, or collaboration, feel free to reach out:

- GitHub: Cadzen05 (https://github.com/Cadzen05)
- Email: cadzen05@gmail.com
- LinkedIn: Caden Cunningham (www.linkedin.com/in/caden-cunningham-78a382404)

## **Acknowledgements**

This project was inspired by the idea of designing a hospital patient queue management, and was developed to strengthen my understanding of C++, object-oriented programming, file I/O, and custom data structures.
