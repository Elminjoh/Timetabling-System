#ifndef LECTURER_H
#define LECTURER_H

#include <string>
#include <vector>

using namespace std;

class Lecturer {
public:
    Lecturer();
    
    // Getter methods
    string getName() const;
    string getEmail() const;
    vector<string> getAssignedModules() const;

    // Setter methods
    void setName();
    void setEmail();

    // Additional methods
    void assignLecturerToModule();
    string getLecturerDetails() const;

private:
    string name;
    string email;
    vector<string> assignedModules;
};

#endif
