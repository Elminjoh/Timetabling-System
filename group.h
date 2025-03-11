#ifndef group_h
#define group_h
#include <string>
#include <vector>
using namespace std;

class StudentGroup {
public:
    StudentGroup();
    void addStudent();
    string getGroupName() const;
    vector<string> getStudents() const;

    void setGroupName(); 
private:
    string groupName;
    vector<string> students;
};

#endif
