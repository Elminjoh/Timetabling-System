#include "Timetable.h"
#include <algorithm>
using namespace std;
#include <iostream>

void Timetable::addSession() {
     int weekNumber;
    string sessionDetails;

    // Prompt the user for the week number
    cout << "Enter the week number: ";
    cin >> weekNumber;
    cin.ignore();  // to ignore any leftover newline from cin

    // Prompt the user for the session details
    cout << "Enter the session details: ";
    getline(cin, sessionDetails);

    // Add the session details to the timetable for the given week number
    schedule[weekNumber].push_back(sessionDetails);
    cout << "Session added for Week " << weekNumber << ": " << sessionDetails << endl;
}

vector<string> Timetable::getSessions() const {
   int weekNumber;

    // Prompt the user for the week number
    cout << "Enter the week number: ";
    cin >> weekNumber;

    // Check if the week exists in the schedule
    if (schedule.find(weekNumber) != schedule.end()) {
        return schedule.at(weekNumber);
    }

    cout << "No sessions found for Week " << weekNumber << endl;
    return {};
}
void Timetable::updateSession() { 
     int weekNumber;
    string oldSessionDetails, newSessionDetails;

    // Prompt the user for the week number
    cout << "Enter the week number: ";
    cin >> weekNumber;
    cin.ignore(); // Ignore leftover newline

    // Prompt the user for the old session details
    cout << "Enter the session details to update: ";
    getline(cin, oldSessionDetails);

    // Prompt the user for the new session details
    cout << "Enter the new session details: ";
    getline(cin, newSessionDetails);

    // Update the session if it exists
    if (schedule.find(weekNumber) != schedule.end()) { 
        for (auto& session : schedule[weekNumber]) { 
            if (session == oldSessionDetails) { 
                session = newSessionDetails; 
                cout << "Session updated successfully." << endl;
                return; 
            } 
        }
        cout << "Session not found for Week " << weekNumber << endl;
    } else {
        cout << "No sessions found for Week " << weekNumber << endl;
    } 
}

void Timetable::removeSession(int weekNumber, const string& sessionDetails) { 
   if (schedule.find(weekNumber) != schedule.end()) { 
        auto& sessions = schedule[weekNumber]; 
        auto it = remove(sessions.begin(), sessions.end(), sessionDetails);
        
        if (it != sessions.end()) {
            sessions.erase(it, sessions.end());
            cout << "Session '" << sessionDetails << "' removed from Week " << weekNumber << endl;
        } else {
            cout << "Session '" << sessionDetails << "' not found in Week " << weekNumber << endl;
        }
    } else {
        cout << "No sessions found for Week " << weekNumber << endl;
    } 
}