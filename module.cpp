#include "Module.h"
using namespace std;
#include <iostream>

Module::Module() {
// Prompt the user for the module name
    cout << "Enter the module name: ";
    getline(cin, moduleName);

// Prompt the user for the lecturer's name
    cout << "Enter the lecturer's name: ";
    getline(cin, lecturerName);
}

string Module::getModuleName() const {
    return moduleName;
}

string Module::getLecturerName() const {
    return lecturerName;
}

void Module::setModuleName() { 
    string newModuleName;

    // Prompt the user for the new module name
    cout << "Enter the new module name: ";
    getline(cin, newModuleName);

    // Set the module's name to the new value
    moduleName = newModuleName;
    cout << "Module name updated to: " << moduleName << endl;
} 
void Module::setLecturerName() { 
    string newLecturerName;

    // Prompt the user for the new lecturer's name
    cout << "Enter the new lecturer's name: ";
    getline(cin, newLecturerName);

    // Set the module's lecturer name to the new value
    lecturerName = newLecturerName;
    cout << "Lecturer name updated to: " << lecturerName << endl;
}