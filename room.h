#ifndef room_h
#define room_h
#include <string>
using namespace std;
class Room {
public:
    Room();
    string getRoomName() const;
    void setRoomName();
private:
    string roomName;
};

#endif