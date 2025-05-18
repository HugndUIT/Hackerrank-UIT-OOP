#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <climits>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;

class Friend {
    protected:
        string Kind;
        double Time;
        int Age;
        string Name;
    public:
        Friend();
        double GetTime();
        void SetTime(double);
        string GetKind();
        virtual void EnterInfo();
        virtual void DisplayInfo();
        Friend(string, double, int, string);
        virtual ~Friend();
};

Friend::Friend() {}

Friend::~Friend() {}

Friend::Friend(string K, double T = 0, int A = 0, string N = "") :Kind(K), Time(T), Age(A), Name(N) {}

double Friend::GetTime() {
    return Time;
}

string Friend::GetKind() {
    return Kind;
}

void Friend::EnterInfo() {
    cin >> Name >> Age;
}

void Friend::DisplayInfo() {
    cout << "Ten: " << Name << ", tuoi: " << Age;
}

void Friend::SetTime(double Time) {
    this->Time = Time;
}

class BestFriend : public Friend {
    private:    
        string PhoneNumber;
    public:
        BestFriend();
        void EnterInfo();
        void DisplayInfo();
};

BestFriend::BestFriend() : Friend("BestFriend") {}

void BestFriend::EnterInfo() {
    Friend::EnterInfo();
    cin >> PhoneNumber;
    Friend::SetTime(5);
}

void BestFriend::DisplayInfo() {
    Friend::DisplayInfo();
    cout << ", so dien thoai: " << PhoneNumber << endl;
}

class BoyFriend : public Friend {
    private:
        double Income;
    public:
        BoyFriend();
        void EnterInfo();
        void DisplayInfo();
};

BoyFriend::BoyFriend() : Friend("BoyFriend") {}

void BoyFriend::EnterInfo() {
    Friend::EnterInfo();
    cin >> Income;
    Friend::SetTime(5 * Income / 10000000.0);
}

void BoyFriend::DisplayInfo() {
    Friend::DisplayInfo();
    cout << ", thu nhap: " << fixed << setprecision(0) << Income << "d\n";
}

class OtherFriend : public Friend {
    private:
        double Attractiveness;
    public:
        OtherFriend();
        void EnterInfo();
        void DisplayInfo();
};

OtherFriend::OtherFriend() : Friend("OtherFriend") {}

void OtherFriend::EnterInfo() {
    Friend::EnterInfo();
    cin >> Attractiveness;
    Friend::SetTime(Attractiveness * 20);
}

void OtherFriend::DisplayInfo() {
    Friend::DisplayInfo();
    if (Attractiveness >= 0.7) {
        cout << ", do thu hut: cao\n";
    } else if (Attractiveness < 0.7 && Attractiveness >= 0.4) {
        cout << ", do thu hut: trung binh\n";
    } else {
        cout << ", do thu hut: thap\n";
    }
}

vector<Friend*> FindBestFriend(const vector<Friend*> & Friends) {
    double MaxTime = -1;
    vector<Friend*> Pals;
    for (const auto & Pal : Friends) {
        if (Pal->GetTime() > MaxTime) {
            MaxTime = max(MaxTime, Pal->GetTime());
        } 
    }
    for (const auto & Pal : Friends) {
        if (Pal->GetTime() == MaxTime) {
            Pals.push_back(Pal);
        }
    }
    return Pals;
}

map<string, double> CalculateTime(const vector<Friend*> & Friends) {
    map<string, double> MapFriend;
    for (const auto & Pal : Friends) {
        if (dynamic_cast<OtherFriend*>(Pal)) {
            Pal->SetTime(Pal->GetTime() / Friends.size());
            MapFriend[Pal->GetKind()] += Pal->GetTime();
        } else {
            MapFriend[Pal->GetKind()] += Pal->GetTime();
        }
    }
    return MapFriend;
}

void EnterInfo(vector<Friend*> & Friends, int Quantity) {
    for (int i = 0; i < Quantity; i++) {
        int Type; cin >> Type;
        Friend* Temporary = nullptr;
        if (Type == 1) {
            Temporary = new BestFriend;
        } else if (Type == 2) {
            Temporary = new BoyFriend;
        } else {
            Temporary = new OtherFriend;
        } 
        Temporary->EnterInfo();
        Friends.push_back(Temporary);
    }
}

void DeleteMemory(vector<Friend*> & Friends) {
    for (Friend* Pal : Friends) {
        delete Pal;
    }
}

void DisplayInfo(const vector<Friend*> & Friends) {
    map<string, double> MapFriend = CalculateTime(Friends);
    cout << "Thong ke:\n";
    for (const auto & Pair : MapFriend) {
        if (Pair.first == "BestFriend") {
            cout << "-Thoi gian cho ban than: " << Pair.second << " h\n";
        } else if (Pair.first == "BoyFriend") {
            cout << "-Thoi gian cho ban trai: " << Pair.second << " h\n";
        } else if (Pair.first == "OtherFriend") {
            cout << "-Thoi gian cho ban trai khac: " << Pair.second << " h\n";
        }
    }
    cout << "Nguoi ban quan trong nhat:\n";
    vector<Friend*> Temp = FindBestFriend(Friends);
    for (const auto & Pal : Temp) {
        Pal->DisplayInfo();
    }
}

int main() {
    int Quantity;
    cin >> Quantity;
    vector<Friend*> Friends;
    EnterInfo(Friends, Quantity);
    DisplayInfo(Friends);
    DeleteMemory(Friends);
}