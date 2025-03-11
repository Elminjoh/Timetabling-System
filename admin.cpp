
#include "admin.h"
#include <algorithm>
using namespace std;
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <cctype>


string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

// Function to parse the INI file
map<string, map<string, string>> parseIniFile(const string& iniFilePath) {
    ifstream inFile(iniFilePath);
    map<string, map<string, string>> iniData;
    string currentSection;
    string line;

    while (getline(inFile, line)) {
        line = trim(line);

        // Ignore empty lines and comments
        if (line.empty() || line[0] == ';' || line[0] == '#') continue;

        // Section header (e.g., [FileSettings])
        if (line[0] == '[' && line.back() == ']') {
            currentSection = line.substr(1, line.size() - 2);
        }
        // Key-value pair (e.g., filePath=Timetable.txt)
        else {
            size_t equalPos = line.find('=');
            if (equalPos != string::npos) {
                string key = trim(line.substr(0, equalPos));
                string value = trim(line.substr(equalPos + 1));
                iniData[currentSection][key] = value;
            }
        }
    }

    return iniData;

}

void writeIniFile(const string& iniFilePath, const map<string, map<string, string>>& iniData) {
    ofstream outFile(iniFilePath);
    for (const auto& section : iniData) {
        outFile << "[" << section.first << "]" << endl;
        for (const auto& kv : section.second) {
            outFile << kv.first << "=" << kv.second << endl;
        }
        outFile << endl;
    }
}

void admin::AddModule() {
    const string iniFilePath = "SInfo.ini";  // Path to your INI file
    map<string, map<string, string>> iniData = parseIniFile(iniFilePath);

    // Prompt for the student ID to search for
    string studentID;
    cout << "Enter Student ID: ";
    cin.ignore();  // Clear newline character left in the buffer
    cin >> studentID;
    cin.ignore();  // Clear newline character left in the buffer

    // Check if the student ID section exists in the INI file
    if (iniData.find(studentID) != iniData.end()) {
        cout << "Student ID: " << studentID << endl;

        // Retrieve and display modules
        string modules = iniData[studentID]["modules"];
        cout << "Modules: " << modules << endl;

        // Retrieve and display group
        string group = iniData[studentID]["groups"];
        cout << "Group: " << group << endl;

        // Prompt for the new module to add
        string newModule;
        cout << "Enter the new module to add:";
        //cin.ignore();  // Clear newline character left in the buffer
        getline(cin,newModule);  // Correctly handles user input for the new module

        // Add the new module to the modules line
        if (!modules.empty()) {
            modules += ", " + newModule;
        } else {
            modules = newModule;
        }
        iniData[studentID]["modules"] = modules;

        // Write the updated INI data back to the file without cutting out the first line
        writeIniFile(iniFilePath, iniData);

        cout << "Module added successfully!" << endl;
    } else {
        cout << "Error: Student ID not found in INI file." << endl;
    }
}

void admin::EditModule() {

    const string iniFilePath = "SInfo.ini";  // Path to your INI file
    map<string, map<string, string>> iniData = parseIniFile(iniFilePath);

    // Prompt for the student ID to search for
    string studentID;
    cout << "Enter Student ID: ";
    cin >> studentID;
    cin.ignore();  // Clear newline character left in the buffer

    // Check if the student ID section exists in the INI file
    if (iniData.find(studentID) != iniData.end()) {
        // Retrieve and display current modules
        string modules = iniData[studentID]["modules"];
        cout << "Current Modules: " << modules << endl;

        // Prompt the user for the old module name
        string oldModuleName, newModuleName, newLecturerName;
        cout << "Enter the old module name: ";
        getline(cin, oldModuleName);

        // Check if the old module exists in the modules list
        size_t pos = modules.find(oldModuleName);
        if (pos != string::npos) {
            // Prompt the user for the new module name
            cout << "Enter the new module name: ";
            getline(cin, newModuleName);

            // Prompt the user for the new lecturer name
            cout << "Enter the new lecturer name: ";
            getline(cin, newLecturerName);

            // Replace the old module with the new one in the module list
            modules.replace(pos, oldModuleName.length(), newModuleName);
            iniData[studentID]["modules"] = modules;  // Update the modules in INI data

            // Update the lecturer name
            iniData[studentID]["lecturer"] = newLecturerName;  // Update the lecturer in INI data

            // Write the updated INI data back to the file
            writeIniFile(iniFilePath, iniData);

            cout << "Module and lecturer updated successfully!" << endl;
        } else {
            cout << "Error: Module not found!" << endl;
        }
    } else {
        cout << "Error: Student ID not found in INI file." << endl;
    }
    
}

void admin::DeleteModule() {
    const string iniFilePath = "SInfo.ini";  // Path to your INI file
    map<string, map<string, string>> iniData = parseIniFile(iniFilePath);

    // Prompt for the student ID to search for
    string studentID;
    cout << "Enter Student ID: ";
    cin >> studentID;
    cin.ignore();  // Clear newline character left in the buffer

    // Check if the student ID section exists in the INI file
    if (iniData.find(studentID) != iniData.end()) {
        // Retrieve and display current modules
        string modules = iniData[studentID]["modules"];
        cout << "Current Modules: " << modules << endl;

        // Prompt the user for the module name to delete
        string moduleName;
        cout << "Enter the module name to delete: ";
        getline(cin, moduleName);

        // Split the modules into a list (assumes modules are separated by commas)
        vector<string> moduleList;
        stringstream ss(modules);
        string item;
        while (getline(ss, item, ',')) {
            moduleList.push_back(item);
        }

        // Find and remove the module
        auto it = remove_if(moduleList.begin(), moduleList.end(),
            [&moduleName](const string& module) {
                return module == moduleName;
            });

        if (it != moduleList.end()) {
            // Erase the removed module
            moduleList.erase(it, moduleList.end());

            // Rebuild the module string
            string updatedModules;
            for (size_t i = 0; i < moduleList.size(); ++i) {
                updatedModules += moduleList[i];
                if (i < moduleList.size() - 1) {
                    updatedModules += ",";  // Add commas between modules
                }
            }

            // Update the modules in the INI data
            iniData[studentID]["modules"] = updatedModules;

            // Write the updated INI data back to the file
            writeIniFile(iniFilePath, iniData);

            cout << "Module " << moduleName << " deleted." << endl;
        } else {
            cout << "Module " << moduleName << " not found." << endl;
        }
    } else {
        cout << "Error: Student ID not found in INI file." << endl;
    }
}

void admin::AddGroups() { 

    const string iniFilePath = "SInfo.ini";  // Path to your INI file
    map<string, map<string, string>> iniData = parseIniFile(iniFilePath);

    // Prompt for the student ID to search for
    string studentID;
    cout << "Enter Student ID: ";
    cin >> studentID;
    cin.ignore();  // Clear newline character left in the buffer

    // Check if the student ID section exists in the INI file
    if (iniData.find(studentID) != iniData.end()) {
        // Prompt for the group name to add
        string groupName;
        cout << "Enter the group name: ";
        getline(cin, groupName);

        // Retrieve the current groups and add the new group
        string groups = iniData[studentID]["groups"];
        if (!groups.empty()) {
            groups += "," + groupName;  // Add a comma before adding the new group
        } else {
            groups = groupName;  // If no groups exist, just set the group name
        }

        // Update the "groups" key with the new group
        iniData[studentID]["groups"] = groups;

        // Write the updated INI data back to the file
        writeIniFile(iniFilePath, iniData);

        cout << "Group " << groupName << " added successfully!" << endl;
    } else {
        cout << "Error: Student ID not found in INI file." << endl;
    }

}


void admin::DeleteGroups() {
    
    const string iniFilePath = "SInfo.ini";  // Path to your INI file
    map<string, map<string, string>> iniData = parseIniFile(iniFilePath);

    // Prompt for the student ID to search for
    string studentID;
    cout << "Enter Student ID: ";
    cin >> studentID;
    cin.ignore();  // Clear newline character left in the buffer

    // Check if the student ID section exists in the INI file
    if (iniData.find(studentID) != iniData.end()) {
        // Retrieve the current groups for the student
        string groups = iniData[studentID]["groups"];
        cout << "Current Groups: " << groups << endl;

        // Prompt the user for the group name to delete
        string groupName;
        cout << "Enter the group name to delete: ";
        getline(cin, groupName);

        // Split the groups into a list (assumes groups are separated by commas)
        vector<string> groupList;
        stringstream ss(groups);
        string item;
        while (getline(ss, item, ',')) {
            groupList.push_back(item);
        }

        // Find and remove the group
        auto it = remove_if(groupList.begin(), groupList.end(),
            [&groupName](const string& group) {
                return group == groupName;
            });

        if (it != groupList.end()) {
            // Erase the removed group
            groupList.erase(it, groupList.end());

            // Rebuild the group string
            string updatedGroups;
            for (size_t i = 0; i < groupList.size(); ++i) {
                updatedGroups += groupList[i];
                if (i < groupList.size() - 1) {
                    updatedGroups += ",";  // Add commas between groups
                }
            }

            // Update the "groups" key with the new groups
            iniData[studentID]["groups"] = updatedGroups;

            // Write the updated INI data back to the file
            writeIniFile(iniFilePath, iniData);

            cout << "Group " << groupName << " deleted successfully!" << endl;
        } else {
            cout << "Group " << groupName << " not found." << endl;
        }
    } else {
        cout << "Error: Student ID not found in INI file." << endl;
    }
}

void admin::EditGroups() {
   
   const string iniFilePath = "SInfo.ini";  // Path to your INI file
    map<string, map<string, string>> iniData = parseIniFile(iniFilePath);

    // Prompt for the student ID to search for
    string studentID;
    cout << "Enter Student ID: ";
    cin >> studentID;
    cin.ignore();  // Clear newline character left in the buffer

    // Check if the student ID section exists in the INI file
    if (iniData.find(studentID) != iniData.end()) {
        // Retrieve the current groups for the student
        string groups = iniData[studentID]["groups"];
        cout << "Current Groups: " << groups << endl;

        // Prompt the user for the old and new group names
        string oldGroupName, newGroupName;
        cout << "Enter the old group name: ";
        getline(cin, oldGroupName);
        cout << "Enter the new group name: ";
        getline(cin, newGroupName);

        // Split the groups into a list (assumes groups are separated by commas)
        vector<string> groupList;
        stringstream ss(groups);
        string item;
        while (getline(ss, item, ',')) {
            groupList.push_back(item);
        }

        // Find and update the group
        bool groupFound = false;
        for (auto& group : groupList) {
            if (group == oldGroupName) {
                group = newGroupName;  // Update the group name
                groupFound = true;
                break;
            }
        }

        if (groupFound) {
            // Rebuild the group string
            string updatedGroups;
            for (size_t i = 0; i < groupList.size(); ++i) {
                updatedGroups += groupList[i];
                if (i < groupList.size() - 1) {
                    updatedGroups += ",";  // Add commas between groups
                }
            }

            // Update the "groups" key with the new groups
            iniData[studentID]["groups"] = updatedGroups;

            // Write the updated INI data back to the file
            writeIniFile(iniFilePath, iniData);

            cout << "Group name updated successfully!" << endl;
        } else {
            cout << "Group " << oldGroupName << " not found." << endl;
        }
    } else {
        cout << "Error: Student ID not found in INI file." << endl;
    }
    
}

void admin::Sessions() {
    const string iniFilePath = "Timetable.ini";  // Path to your Timetable INI file
    map<string, map<string, string>> iniData = parseIniFile(iniFilePath);

    // Prompt for the module name to add/edit session details
    string moduleName;
    cout << "Enter the module name: ";
    cin.ignore();  // Clear newline character left in the buffer
    getline(cin, moduleName);

    // Trim the module name to remove extra spaces
    moduleName = trim(moduleName);

    // Check if the module section exists in the INI file
    if (iniData.find(moduleName) != iniData.end()) {
        // Prompt for session type (Lecture, Lab, etc.)
        string sessionType;
        cout << "Enter the session type (e.g., Lecture, Lab, Tutorial): ";
        getline(cin, sessionType);

        // Prompt for the day of the session
        string day;
        cout << "Enter the day of the session (e.g., Monday, Tuesday): ";
        getline(cin, day);

        // Prompt for the session time
        string sessionTime;
        cout << "Enter the session time (format HH:MM:SS-HH:MM:SS): ";
        getline(cin, sessionTime);

        // Update the INI data for the module with the new session details
        iniData[moduleName]["Session"] = sessionType;
        iniData[moduleName]["Day"] = day;
        iniData[moduleName]["Time"] = sessionTime;

        // Write the updated INI data back to the Timetable.ini file
        writeIniFile(iniFilePath, iniData);

        cout << "Session details added/updated successfully for module \"" << moduleName << "\"!" << endl;
    } else {
        cout << "Error: Module \"" << moduleName << "\" not found in Timetable.ini file." << endl;

        // Debugging: List all available modules
        cout << "Available modules in Timetable.ini:" << endl;
        for (const auto& section : iniData) {
            cout << section.first << endl;
        }
    }
}

void admin::AddRooms() {
    const string iniFilePath = "Timetable.ini";  // Path to your Timetable INI file
    map<string, map<string, string>> iniData = parseIniFile(iniFilePath);

    // Prompt for the module name to search for
    string moduleName;
    cout << "Enter the module name: ";
    cin.ignore();  // Clear newline character left in the buffer
    getline(cin, moduleName);

    // Trim the module name to remove extra spaces
    moduleName = trim(moduleName);

    // Check if the module section exists in the INI file
    if (iniData.find(moduleName) != iniData.end()) {
        // Prompt the user for the room name
        string roomName;
        cout << "Enter the room name: ";
        getline(cin, roomName);

        // Retrieve and update the room information
        iniData[moduleName]["Room"] = roomName;

        // Write the updated INI data back to the Timetable.ini file
        writeIniFile(iniFilePath, iniData);

        cout << "Room " << roomName << " added successfully for module " << moduleName << "!" << endl;
    } else {
        cout << "Error: Module " << moduleName << " not found in Timetable.ini file." << endl;

        // Debugging: List all available modules
        cout << "Available modules in Timetable.ini:" << endl;
        for (const auto& section : iniData) {
            cout << section.first << endl;
        }
    }
}

void admin::DeleteRooms() {
    const string iniFilePath = "Timetable.ini";  // Path to your Timetable INI file
    map<string, map<string, string>> iniData = parseIniFile(iniFilePath);

    // Prompt for the module name to search for
    string moduleName;
    cout << "Enter the module name: ";
    cin.ignore();  // Clear newline character left in the buffer
    getline(cin, moduleName);

    // Check if the module section exists in the INI file
    if (iniData.find(moduleName) != iniData.end()) {
        // Retrieve the current room information
        string currentRoom = iniData[moduleName]["Room"];

        // Prompt the user for the room name to delete
        string roomName;
        cout << "Enter the room name to delete: ";
        getline(cin, roomName);

        // Check if the room matches the one in the INI file
        if (currentRoom == roomName) {
            // Clear the room field
            iniData[moduleName]["Room"] = "";

            // Write the updated INI data back to the Timetable.ini file
            writeIniFile(iniFilePath, iniData);

            cout << "Room " << roomName << " deleted from module " << moduleName << "." << endl;
        } else {
            cout << "Room " << roomName << " does not match the room in the Timetable for module " << moduleName << "." << endl;
        }
    } else {
        cout << "Error: Module " << moduleName << " not found in Timetable.ini file." << endl;
    }
}

void admin::CreateTimetable() {
    const string sInfoFilePath = "SInfo.ini";  // Path to SInfo.ini
    const string timetableFilePath = "Timetable.ini";  // Path to Timetable.ini

    // Parse both INI files
    map<string, map<string, string>> sInfoData = parseIniFile(sInfoFilePath);
    map<string, map<string, string>> timetableData = parseIniFile(timetableFilePath);

    // Prompt for the student ID
    string studentID;
    cout << "Enter Student ID: ";
    cin >> studentID;
    cin.ignore();  // Clear newline character

    // Check if the student ID exists in the SInfo.ini file
    if (sInfoData.find(studentID) != sInfoData.end()) {
        // Retrieve student-specific data
        string modules = sInfoData[studentID]["modules"];
        string group = sInfoData[studentID]["groups"];

        // Split the modules by comma
        vector<string> moduleList;
        stringstream ss(modules);
        string module;
        while (getline(ss, module, ',')) {
            moduleList.push_back(trim(module));
        }

        // Open file for saving the timetable at the specified path
        string timetableFileName = "studentTimetable.txt";  // Fixed filename
        ofstream outFile(timetableFileName);  // Open file for writing

        if (!outFile.is_open()) {
            cout << "Error opening file for writing." << endl;
            return;
        }

        // Write the timetable header to the file
        outFile << "Timetable for Student ID: " << studentID << endl;
        outFile << "Group: " << group << endl;
        outFile << "---------------------------------------------------------------" << endl;
        outFile << left << setw(25) << "Module"
                << setw(15) << "Day"
                << setw(20) << "Time"
                << setw(20) << "Room"
                << setw(20) << "Lecturer"
                << "Session" << endl;
        outFile << "---------------------------------------------------------------" << endl;

        // Loop through each module and fetch its details from the Timetable.ini file
        for (const auto& moduleName : moduleList) {
            // Check if the module exists in Timetable.ini
            if (timetableData.find(moduleName) != timetableData.end()) {
                // Fetch and write the module details to the file
                string day = timetableData[moduleName]["Day"];
                string time = timetableData[moduleName]["Time"];
                string room = timetableData[moduleName]["Room"];
                string lecturer = timetableData[moduleName]["Lecturer"];
                string session = timetableData[moduleName]["Session"]; // Include session

                // Write formatted timetable row to the file
                outFile << left << setw(25) << moduleName
                        << setw(15) << day
                        << setw(20) << time
                        << setw(20) << room
                        << setw(20) << lecturer
                        << session << endl;
            } else {
                // Handle the case where timetable data for the module is not available
                outFile << left << setw(25) << moduleName 
                        << "No timetable data available." << endl;
            }
        }
        
        outFile << "---------------------------------------------------------------" << endl;

        // Notify user and close file
        cout << "Timetable saved to " << timetableFileName << endl;
        outFile.close();
    } else {
        cout << "Error: Student ID " << studentID << " not found in SInfo.ini file." << endl;
    }
}
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

void admin::UpdateTimetable() {
    string studentID;
    cout << "Enter Student ID to update the timetable: ";
    cin >> studentID;
    cin.ignore();  // Clear newline character from the buffer

    // Open the studentTimetable.txt file for reading
    string timetableFileName = "studentTimetable.txt";
    ifstream inFile(timetableFileName);
    if (!inFile.is_open()) {
        cout << "Error: Could not open file " << timetableFileName << endl;
        return;
    }

    vector<string> lines;
    string line;

    // Read the file content into a vector of strings (lines)
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    // Find the student timetable based on their ID
    size_t studentStartLine = string::npos;
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].find("Timetable for Student ID: " + studentID) != string::npos) {
            studentStartLine = i;
            break;
        }
    }

    if (studentStartLine == string::npos) {
        cout << "Error: Student ID not found in timetable." << endl;
        return;
    }

    // Print the current timetable and allow the user to choose a module to update
    cout << "Current Timetable for Student ID: " << studentID << endl;
    for (size_t i = studentStartLine + 3; i < lines.size(); ++i) {  // Skip header lines
        if (lines[i].find("---------------------------------------------------------------") != string::npos)
            break;
        cout << lines[i] << endl;
    }

    string moduleToUpdate;
    cout << "Enter the module name you want to update: ";
    getline(cin, moduleToUpdate);

    // Find the module and update its details
    bool moduleFound = false;
    for (size_t i = studentStartLine + 3; i < lines.size(); ++i) {
        if (lines[i].find(moduleToUpdate) != string::npos) {
            moduleFound = true;
            cout << "Module found: " << lines[i] << endl;

            // Prompt for updates
            string newDay, newTime, newRoom, newLecturer, newSession;
            cout << "Enter the new day (leave blank to keep current): ";
            getline(cin, newDay);
            cout << "Enter the new time (leave blank to keep current): ";
            getline(cin, newTime);
            cout << "Enter the new room (leave blank to keep current): ";
            getline(cin, newRoom);
            cout << "Enter the new lecturer (leave blank to keep current): ";
            getline(cin, newLecturer);
            cout << "Enter the new session type (leave blank to keep current): ";
            getline(cin, newSession);

            // Update the line with new values
            stringstream updatedLine;
            updatedLine << left << setw(25) << moduleToUpdate
                        << setw(15) << (newDay.empty() ? "Current Day" : newDay)
                        << setw(20) << (newTime.empty() ? "Current Time" : newTime)
                        << setw(20) << (newRoom.empty() ? "Current Room" : newRoom)
                        << setw(20) << (newLecturer.empty() ? "Current Lecturer" : newLecturer)
                        << (newSession.empty() ? "Current Session" : newSession);

            lines[i] = updatedLine.str();
            break;
        }
    }

    if (!moduleFound) {
        cout << "Module not found!" << endl;
        return;
    }

    // Write the updated lines back to the file
    ofstream outFile(timetableFileName);
    if (!outFile.is_open()) {
        cout << "Error: Could not open file " << timetableFileName << endl;
        return;
    }

    for (const auto& updatedLine : lines) {
        outFile << updatedLine << endl;
    }
    outFile.close();

    cout << "Timetable updated successfully!" << endl;
}

void admin::addLecturer() {
    const string iniFilePath = "Timetable.ini";  // Path to your Timetable INI file
    map<string, map<string, string>> iniData = parseIniFile(iniFilePath);

    // Prompt for the module name to associate the lecturer with
    string moduleName;
    cout << "Enter the module name: ";
    cin.ignore();  // Clear newline character left in the buffer    
    getline(cin, moduleName);

    // Trim the module name to remove extra spaces
    moduleName = trim(moduleName);

    // Check if the module section exists in the INI file
    if (iniData.find(moduleName) != iniData.end()) {
        // Prompt the user for the lecturer's name
        string name;
        cout << "Enter the lecturer's name: ";
        getline(cin, name);

        // Add or update the lecturer's name in the module section
        iniData[moduleName]["Lecturer"] = name;

        // Write the updated INI data back to the Timetable.ini file
        writeIniFile(iniFilePath, iniData);

        cout << "Lecturer " << name << " added successfully for module \"" << moduleName << "\"!" << endl;
    } else {
        cout << "Error: Module \"" << moduleName << "\" not found in Timetable.ini file." << endl;

        // Debugging: List all available modules
        cout << "Available modules in Timetable.ini:" << endl;
        for (const auto& section : iniData) {
            cout << section.first << endl;
        }
    }
}

void admin::deleteLecturer() {
    const string iniFilePath = "Timetable.ini";  // Path to your Timetable INI file
    map<string, map<string, string>> iniData = parseIniFile(iniFilePath);

    // Prompt for the module name to associate the lecturer with
    string moduleName;
    cout << "Enter the module name: ";
    cin.ignore();  // Clear newline character left in the buffer
    getline(cin, moduleName);

    // Trim the module name to remove extra spaces
    moduleName = trim(moduleName);

    // Check if the module section exists in the INI file
    if (iniData.find(moduleName) != iniData.end()) {
        // Check if a lecturer exists for this module
        if (iniData[moduleName].find("Lecturer") != iniData[moduleName].end()) {
            // Set the lecturer name to an empty string, keeping "Lecturer=" in place
            iniData[moduleName]["Lecturer"] = "";

            // Write the updated INI data back to the Timetable.ini file
            writeIniFile(iniFilePath, iniData);

            cout << "Lecturer's name deleted successfully from module \"" << moduleName << "\"!" << endl;
        } else {
            cout << "Error: No lecturer found for module \"" << moduleName << "\"." << endl;
        }
    } else {
        cout << "Error: Module \"" << moduleName << "\" not found in Timetable.ini file." << endl;

        // Debugging: List all available modules
        cout << "Available modules in Timetable.ini:" << endl;
        for (const auto& section : iniData) {
            cout << section.first << endl;
        }
    }
}

bool admin::Admin_login() {
    string login;
    string password;
    bool isloggedIn = false; 

    // Prompt the user for login details
    cout << "Enter your login: ";
    cin >> login;
    cout << "Enter your password: ";
    cin.ignore();
    getline(cin, password);

    const string filePath = "ALogin.txt"; // Admin login file
    ifstream inFile(filePath);

    if (!inFile.is_open()) {
        cerr << "Error: Unable to open login file." << endl;
        return false;
    }

    string line;

    // Loop through the file to find the matching login credentials
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split line by comma
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Ensure that the line has both login and password tokens
        if (tokens.size() == 2 && tokens[0] == login && tokens[1] == password) {
            cout << "Login successful!" << endl;
            isloggedIn = true;
            break;
        }
    }

    if (!isloggedIn) {
        cout << "Invalid login credentials!" << endl;
    }

    inFile.close();
    return isloggedIn;
}


void admin::Admin_menu() {
        int choice;
        do {
            cout << "\nAdmin Menu:\n";
            cout << "1. Add Module\n";
            cout << "2. Edit Module\n";
            cout << "3. Delete Module\n";
            cout << "4. Add Student Group\n";
            cout << "5. Edit Student Group\n";
            cout << "6. Delete Student Group\n";
            cout << "7. Define Session Type\n";
            cout << "8. Add Room\n";
            cout << "9. Delete Room\n";
            cout << "10. Add Lecturer\n";
            cout << "11. Delete Lecturer\n";
            cout << "12. Create Timetable\n";
            cout << "13. Update Timetable\n";
            cout << "14. Logout\n";
            cout << "Enter choice: ";
            
        while (!(cin >> choice)) {
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid input. Please enter a number between 1 and 14: ";
        }
            

            string name, moduleName, lecturerName, groupName, sessionType, roomName, oldName, newName, newEmail, oldModuleName, newModuleName, oldRoomName, newRoomName, oldGroupName, newGroupName, newLecturerName;
            string sessionDetails;
            admin admin;

            switch (choice) {
                case 1:
                    admin.AddModule();
                    break;
                case 2:
                    admin.EditModule();
                    break;
                case 3:
                    admin.DeleteModule();
                    break;
                case 4:
                    admin.AddGroups();
                    break;
                case 5:
                    admin.EditGroups();
                    break;
                case 6:
                    admin.DeleteGroups();
                    break;
                case 7:
                    admin.Sessions();
                    break;
                case 8:
                    admin.AddRooms();
                    break;
                case 9:
                    admin.DeleteRooms();
                    break;
                case 10:
                    admin.addLecturer();
                    break;
                case 11:
                    admin.deleteLecturer();
                    break;
                case 12:
                    admin.CreateTimetable();
                    break;
                case 13:
                    admin.UpdateTimetable();
                    break;
                case 14:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice, please try again.\n";
            }
        } while (choice != 14);
    }