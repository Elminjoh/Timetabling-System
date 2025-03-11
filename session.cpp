#include "session.h"
using namespace std;
#include <iostream>
Session::Session() {
     // Prompt the user for the session type name
    cout << "Enter the session type name: ";
    getline(cin, typeName);
}


string Session::getTypeName() const {
    return typeName;
}