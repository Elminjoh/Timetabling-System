#ifndef session_h
#define session_h
#include <string>
using namespace std;

class Session {
public:
    Session();
    string getTypeName() const;
    
private:
    string typeName;
};

#endif


