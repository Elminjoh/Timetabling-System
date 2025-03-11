#include "group.h"
using namespace std;
#include <iostream>

StudentGroup::StudentGroup() {
    // Prompt the user for the group name
    cout << "Enter the group name: ";
    getline(cin, groupName);
}

void StudentGroup::addStudent() {
    string studentName;

    // Prompt the user for the student's name
    cout << "Enter the student's name: ";
    getline(cin, studentName);

    // Add the student to the list
    students.push_back(studentName);
    cout << "Student " << studentName << " added successfully!" << endl;
}

string StudentGroup::getGroupName() const {
    return groupName;
}

vector<string> StudentGroup::getStudents() const {
    return students;
}
void StudentGroup::setGroupName() { 
   string newGroupName;

    // Prompt the user for the new group name
    cout << "Enter the new group name: ";
    getline(cin, newGroupName);

    // Set the group name to the new value
    groupName = newGroupName;
    cout << "Group name updated to: " << groupName << endl; 
} 