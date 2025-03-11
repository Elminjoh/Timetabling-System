#ifndef USER_H 
#define USER_H 
#include <string> 
using namespace std;

class User { 
    public: 
        User( string username, string password, bool isAdmin); 
        string getUsername() const; 
        bool checkPassword(string password) const; 
        bool isAdmin() const; 
        bool isStudent() const;
    private:
        string username; 
        string password; 
        bool admin; 
        bool student;
}; 
#endif