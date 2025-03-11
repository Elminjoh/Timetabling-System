#include "Student.h"
#include "admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

/**
 * Prints the timetable for the given Student ID from the file at the specified path
 *
 * The function will loop through the file to find the timetable for the given Student ID
 * and print the timetable information until the next student or EOF is encountered.
 * If no timetable is found, a message will be printed to the console.
 *
 * @param[in] studentID the Student ID to search for in the timetable file
 * @param[in] filePath the path to the timetable file
 */
void Student::ViewTimetable() {
    const string filePath = "studentTimetable.txt"; // Path to the timetable file
    string studentID;

    // Prompt for the student's ID (if not already stored in the object)
    cout << "Enter your Student ID: ";
    cin >> studentID;
    cin.ignore(); // Ignore newline character after input

    ifstream inFile(filePath);
    if (!inFile) {
        cerr << "Error opening file: " << filePath << endl;
        return;
    }

    string line;
    bool isStudentTimetable = false;
    bool timetableFound = false;

    // Loop through the file to find the timetable for the given Student ID
    while (getline(inFile, line)) {
        if (line.find("Timetable for Student ID: " + studentID) != string::npos) {
            isStudentTimetable = true; // Found the timetable section for this student
            timetableFound = true;
            cout << line << endl; // Print the header line
        }
        // Print the timetable information until the next student or EOF
        else if (isStudentTimetable) {
            if (line.find("Timetable for Student ID:") != string::npos) {
                // Stop printing when a new student's timetable is encountered
                break;
            }
            cout << line << endl; // Print the current student's timetable
        }
    }

    if (!timetableFound) {
        cout << "No timetable found for Student ID: " << studentID << endl;
    }

    inFile.close(); // Close the file
}
bool Student::Student_login() {
    string login;
    string password;
    bool isloggedin = false;

    cout << "Enter your login ID: ";
    cin >> login;
    cout << "Enter your Password: ";
    cin.ignore();
    getline(cin, password);

    const string filePath = "SLogin.txt";
    ifstream inFile(filePath);

    fstream file(filePath, ios::in | ios::out | ios::ate);
    if (file.is_open()) {
        streampos fileSize = file.tellg();
        file.seekg(0); // Move to the beginning of the file

        string line;
        streampos currentPosition;

        while (!file.eof()) {
            currentPosition = file.tellg();

            getline(file, line);
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, ',')) {
                tokens.push_back(token);
            }
            
            if (tokens[0] == login && tokens[1] == password) {
                cout << "Login successful. Welcome, " << login << endl;
                isloggedin = true;
                break;
            }
        }
    }
    return isloggedin;
}

void Student::student_menu() {
    int choice;
    
    do {
        cout << "\nStudent Menu:\n";
        cout << "1. View Timetable\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        

    while (!(cin >> choice)) {
        cin.clear(); // clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number between 0 and 2: ";
    }  

        switch (choice) {
            case 1:
                ViewTimetable(); // Correct call without timetable object
                break;
            case 0:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 0);
}
