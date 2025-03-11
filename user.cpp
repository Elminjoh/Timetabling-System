#include "User.h" 
using namespace std;

User::User(string uname, string pwd, bool isAdmin) : username(uname), password(pwd), admin(isAdmin) {} 
string User::getUsername() const { 
    return username; 
} 
bool User::checkPassword(string pwd) const { 
    return password == pwd; 
} 
bool User::isAdmin() const {
    return admin; 
}
bool User::isStudent() const {
    return student; 
}