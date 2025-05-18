#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <climits>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Person {
    protected:
        string WayToDie, Name, PhoneNumber;
        double Age;
    public:
        string GetName();
        string GetDie();
        virtual void Input();
        virtual ~Person();
};

string Person::GetName() {
    return Name;
}

string Person::GetDie() {
    return WayToDie;
}

void Person::Input() {
    cin >> Name >> Age >> PhoneNumber;
}

Person::~Person() {}

class Politician : public Person {
    private:
        string Position;
    public:
        string GetPos();
        void Input();
};

string Politician::GetPos() {
    return Position;
}

void Politician::Input() {
    Person::Input();
    cin >> Position;
    WayToDie = "dau tim";
}

class BusinessMen : public Person {
    private:
        double Asset;
    public:
        double GetAsset();
        void Input();
};

double BusinessMen::GetAsset() {
    return Asset;
}

void BusinessMen::Input() {
    Person::Input();
    cin >> Asset;
    if (Asset > 5) {
        WayToDie = "nang";
    } else if (Asset > 3 && Asset <= 5) {
        WayToDie = "binh thuong";
    } else {
        WayToDie = "nhe";
    }
}

class Prisoner : public Person {
    private:
        string Crime;
        double Sentenced;
    public:
        double GetSentenced();
        void Input();
};

double Prisoner::GetSentenced() {
    return Sentenced;
}

void Prisoner::Input() {
    Person::Input();
    cin >> Crime >> Sentenced;
    if (Sentenced > 20) {
        WayToDie = "nang";
    } else if (Sentenced > 10 && Sentenced <= 20) {
        WayToDie = "binh thuong";
    } else {
        WayToDie = "nhe";
    }
}   

class DeathNote {
    private:
        vector<Person*> Persons;
    public:
        void Input();
        pair<string, string> FindLongestPos();
        pair<double, string> TotalAsset();
        pair<double, string> TotalSentenced();
        void Ouput();
        ~DeathNote();
};

void DeathNote::Input() {
    vector<string> UniqueName;
    size_t n, m;
    cin >> n >> m;
    for (size_t i = 0; i < n; i++) {
        int Type; cin >> Type;
        Person* Temp = nullptr;
        if (Type == 1) {
            Temp = new Politician;
        } else if (Type == 2) {
            Temp = new BusinessMen;
        } else {
            Temp = new Prisoner;
        }
        Temp->Input();
        auto it = find(UniqueName.begin(), UniqueName.end(), Temp->GetName());    
        if (it != UniqueName.end()) {
            delete Temp;
            continue;
        } else {
            if (Persons.size() >= m) {
                UniqueName.push_back(Temp->GetName());
                Persons.push_back(Temp);
                UniqueName.erase(UniqueName.begin());
                Persons.erase(Persons.begin());
            } else {
                UniqueName.push_back(Temp->GetName());
                Persons.push_back(Temp);
            }  
        } 
    }
}

pair<string, string> DeathNote::FindLongestPos() {
    string LongestPosition = "", Name = "";
    for (Person* Temp : Persons) {
        if (auto* Poli = dynamic_cast<Politician*>(Temp)) {
            if (Poli->GetPos().size() > LongestPosition.size()) {
                LongestPosition = Poli->GetPos();
                Name = Poli->GetName();
            }
        }
    }
    return {Name, LongestPosition};
}

pair<double, string> DeathNote::TotalAsset() {
    double Total = 0, Max = -1;
    string WayToDie = "";
    for (Person* Temp : Persons) {
        if (auto* BusinessMan = dynamic_cast<BusinessMen*>(Temp)) {
            double AssetValue = BusinessMan->GetAsset();
            Total += AssetValue;
            if (AssetValue > Max) {
                Max = AssetValue;
                WayToDie = Temp->GetDie();
            }
        }
    }
    return {Total, WayToDie};
}

pair<double, string> DeathNote::TotalSentenced() {
    double Total = 0, Max = -1;
    string WayToDie = "";
    for (Person* Temp : Persons) {
        if (auto* Prison = dynamic_cast<Prisoner*>(Temp)) {
            double SentencedValue = Prison->GetSentenced();
            Total += SentencedValue;
            if (SentencedValue > Max) {
                Max = SentencedValue;
                WayToDie = Temp->GetDie();
            }
        }
    }
    return {Total, WayToDie};
}

void DeathNote::Ouput() {
    if (Persons.size() == 0) {
        cout << "Deathnote trong";
        return;
    }
    bool HasPoli = false;
    bool HasBussi = false;
    bool HasPrisoner = false;
    for (Person* p : Persons) {
        if (dynamic_cast<Politician*>(p)) 
            HasPoli = true;
        else if (dynamic_cast<Prisoner*>(p)) 
            HasPrisoner = true;
        else if (dynamic_cast<BusinessMen*>(p)) 
            HasBussi = true;
    }
    if (HasPoli) {
        auto Result = FindLongestPos();
        cout << Result.first << ", Chuc vu: " << Result.second << endl;
    }
    if (HasBussi) {
        auto Result = TotalAsset();
        cout << "Doanh nhan: " << Result.first << " ty dong, Cach thuc chet: " << Result.second << endl;
    }
    if (HasPrisoner) {
        auto Result = TotalSentenced();
        cout << "Tu nhan: " << Result.first << ", Cach thuc chet: " << Result.second << endl;
    }
}


DeathNote::~DeathNote() {
    for (Person* Temp : Persons) {
        delete Temp;
    }
}

int main() {
    DeathNote UIT;
    UIT.Input();
    UIT.Ouput();
}