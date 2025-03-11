#ifndef MODULE_H
#define MODULE_H
#include <string>
using namespace std;

class Module {
public:
    Module();
    string getModuleName() const;
    string getLecturerName() const;

    void setModuleName();
    void setLecturerName();

private:
    string moduleName;
    string lecturerName;
};

#endif  