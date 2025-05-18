#include <cmath>
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

class Room {
    protected:
        string Name;
        long long Floor, RoomNumber, Capacity;
    public:
        string GetName();
        long long GetFloor();
        long long GetRoomNumber();
        long long GetCapacity();
        virtual void EnterInfo();
        virtual ~Room();
};

Room::~Room() {}

void Room::EnterInfo() {
    cin >> Name >> Floor >> RoomNumber >> Capacity;
}

long long Room::GetFloor() {
    return Floor;
}

long long Room::GetRoomNumber() {
    return RoomNumber;
}

long long Room::GetCapacity() {
    return Capacity;
}
string Room::GetName() {
    return Name;
}

class Theory : public Room {
    private:
        bool HasAirCondition;
    public:
        void EnterInfo();
};

void Theory::EnterInfo() {
    Room::EnterInfo();
    cin >> HasAirCondition;
}

class Practice : public Room {
    private:
        long long NumberOfComputer;
    public:
        void EnterInfo(); 
};

void Practice::EnterInfo() {
    Room::EnterInfo();
    cin >> NumberOfComputer;
}

class LectureHall : public Room {
    private:
        long long NumberOfProjector;
    public:
        void EnterInfo();
};

void LectureHall::EnterInfo() {
    Room::EnterInfo();
    cin >> NumberOfProjector;
}

long long TotalCapacity(const vector<Room*> & RoomList) {
    long long Sum = 0;
    for (size_t i = 0; i < RoomList.size(); i++) {
        Sum += RoomList[i]->GetCapacity();
    }
    return Sum;
}

vector<Room*> FindTightestRoom(const vector<Room*> & RoomList, long long Parameter) {
    vector<Room*> Result;
    long long BestFit = LLONG_MAX;

    for (auto Rooms : RoomList) {
        long long Diff = Rooms->GetCapacity() - Parameter;
        if (Diff >= 0) {
            if (Diff < BestFit) {
                BestFit = Diff;
                Result.clear();
                Result.push_back(Rooms);
            } else if (Diff == BestFit) {
                Result.push_back(Rooms);
            }
        }
    }

    sort(Result.begin(), Result.end(), [](Room* x, Room* y) {
        return x->GetFloor() < y->GetFloor(); 
    });

    return Result;
}; 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long NumberOfRooms, Parameter;
    vector<Room*> RoomList, Temporary;
    cin >> NumberOfRooms;
    for (long long i = 0; i < NumberOfRooms; i++) {
        int Type;
        cin >> Type;
        Room* Temporary = nullptr;
        if (Type == 1) {
            Temporary = new Theory;    
        } else if (Type == 2) {
            Temporary = new Practice;
        } else if (Type == 3) {
            Temporary = new LectureHall;
        }
        Temporary->EnterInfo();
        RoomList.push_back(Temporary);
    }
    cin >> Parameter;

    cout << TotalCapacity(RoomList) << endl;
    
    Temporary = FindTightestRoom(RoomList, Parameter);

    if (Temporary.size() == 0) {
        cout << "NULL";
    } else {
        cout << Temporary.front()->GetName();
    }

    for (Room* x : RoomList) {
        delete x;
    }
}