#ifndef admin_h
#define admin_h
#include <iostream>
#include <string>
#include <vector>
#include "module.h"
#include "group.h"
#include "room.h"
#include "timetable.h"
#include "student.h"
#include "session.h"
#include "lecturer.h"
using namespace std;

class admin{
    // private members //
    private:
        vector<Module> modules;
        vector<StudentGroup> groups;
        vector<Room> rooms;
        vector<Session> sessions;
        vector<Lecturer> lecturers;
        
        

    // public members //
    public:

        void AddModule();
        void EditModule();
        void DeleteModule();

        void Sessions();

        void AddGroups();
        void DeleteGroups();
        void EditGroups();
        
        void AddRooms();
        void DeleteRooms();
        
        void addLecturer(); 
        void deleteLecturer(); 
        
        void CreateTimetable();
        void UpdateTimetable();
        
        bool Admin_login();
        void Admin_menu();
};
#endif