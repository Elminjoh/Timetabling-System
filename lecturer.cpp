#include "lecturer.h"
using namespace std;
#include <iostream>

Lecturer::Lecturer() {
    // Prompt the user for the lecturer's name
    cout << "Enter the lecturer's name: ";
    getline(cin, name);

    // Prompt the user for the lecturer's email
    cout << "Enter the lecturer's email: ";
    getline(cin, email);
}

// Getter methods
string Lecturer::getName() const {
    return name;
}

string Lecturer::getEmail() const {
    return email;
}

vector<string> Lecturer::getAssignedModules() const {
    return assignedModules;
}

// Setter methods
void Lecturer::setName() {
     string newName;

    // Prompt the user for the new name
    cout << "Enter the lecturer's new name: ";
    getline(cin, newName);

    // Set the lecturer's name to the new value
    name = newName;
    cout << "Lecturer's name updated to: " << name << endl;
}

void Lecturer::setEmail() {
     string newEmail;

    // Prompt the user for the new email
    cout << "Enter the lecturer's new email: ";
    getline(cin, newEmail);

    // Set the lecturer's email to the new value
    email = newEmail;
    cout << "Lecturer's email updated to: " << email << endl;
}

// Additional methods
void Lecturer::assignLecturerToModule() {
    string moduleName;

    // Prompt the user for the module name
    cout << "Enter the module name to assign the lecturer to: ";
    getline(cin, moduleName);

    // Assign the lecturer to the module
    assignedModules.push_back(moduleName);
    cout << "Lecturer assigned to module: " << moduleName << endl;
}

string Lecturer::getLecturerDetails() const {
    string details = "Name: " + name + "\nEmail: " + email + "\nAssigned Modules:\n";
    for (const auto& module : assignedModules) {
        details += " - " + module + "\n";
    }
    return details;
}
