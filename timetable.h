#ifndef timetable_h
#define timetable_h
#include <map>
#include <vector>
#include <string>
using namespace std;

class Timetable {
public:
    void addSession();
    void removeSession(int weekNumber, const string& sessionDetails);
    vector<string> getSessions() const;
    void updateSession();
private:
    map<int, vector<string>> schedule;
};

#endif
