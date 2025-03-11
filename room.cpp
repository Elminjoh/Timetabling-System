#include "room.h"
using namespace std;
#include <iostream>

Room::Room() {
    // Prompt the user for the room name
    cout << "Enter the room name: ";
    getline(cin, roomName);
}

string Room::getRoomName() const {
    return roomName;
}

void Room::setRoomName() { 
    string newRoomName;

    // Prompt the user for the new room name
    cout << "Enter the new room name: ";
    getline(cin, newRoomName);

    // Set the room's name to the new value
    roomName = newRoomName;
    cout << "Room name updated to: " << roomName << endl;
}