#include <iostream>
#include "admin.h"
#include "student.h"
#include "user.h"
#include <limits>
using namespace std;

int main() {
    int userType;
    bool isloggedIn = false;
    char exitChoice;

    cout << "*** TIMETABLE ***" << endl;

    while (true) {
        cout << "Please select user type: " << endl;
        cout << "1. Admin" << endl;
        cout << "2. Student" << endl;
        cout << "Enter your choice (or press 0 to cancel): ";
        
        while (!(cin >> userType)) {
        cin.clear(); // clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "Invalid input. Please enter a number between 0 and 2: ";
    }

        admin adminUser;
        Student studentUser;

        switch (userType) {
            case 1: // admin
                isloggedIn = adminUser.Admin_login();
                if (isloggedIn) {
                    adminUser.Admin_menu();
                  //  return 0; // Exit after successful login and menu
                }
                break;

            case 2: // student
                isloggedIn = studentUser.Student_login();
                if (isloggedIn) {
                    studentUser.student_menu();
                 //   return 0; // Exit after successful login and menu
                }
                break;

            case 0: // exit
                cout << "Exiting the program." << endl;
                return 0;

            default:
                cout << "Invalid user type. Please try again." << endl;
                break;
        }

        if (!isloggedIn) {
            cout << "Login failed. Would you like to try again? (y/n): ";
            cin >> exitChoice;

            if (tolower(exitChoice) != 'y') {
                cout << "Exiting the program." << endl;
                return 0; // Exit the program if the user chooses not to try again
            }
        }
    }

    return 0;
}
