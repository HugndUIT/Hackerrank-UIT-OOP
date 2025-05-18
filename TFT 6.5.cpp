#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

class Champion {
    protected:
        string Name, Toc;
        double Price;
        string He;
        double ATK, DEF, Damage;
    public:
        Champion();
        Champion(string, string, double, string, double, double, double);
        string GetName();
        string GetToc();
        string GetHe();
        double GetATK();
        double GetDEF();
        double GetPrice();
        double GetDamage();
        void SetDamage(double);
        void SetATK(double);
        void SetDEF(double);
        virtual double DamageDealt();
        virtual void EnterInfo();
        virtual ~Champion();
};

Champion::Champion() {}

Champion::Champion(string name, string toc, double price, string he = "", double atk = 0, double def = 0, double damage = 0): 
          Name(name), Toc(toc), Price(price), He(he), ATK(atk), DEF(def), Damage(damage) {}

Champion::~Champion() {}

string Champion::GetName() {
    return this->Name;
}

string Champion::GetToc() {
    return this->Toc;
}

string Champion::GetHe() {
    return this->He;                                                           
}

double Champion::GetDamage() {
    return this->Damage;
}

void Champion::SetDamage(double Damage) {
    this->Damage = Damage;
}

void Champion::SetATK(double ATK) {
    this->ATK = ATK;
}

void Champion::SetDEF(double DEF) {
    this->DEF = DEF;
}

double Champion::GetATK() {
    return this->ATK;
}

double Champion::GetDEF() {
    return this->DEF;
}

double Champion::GetPrice() {
    return this->Price;
}

void Champion::EnterInfo() {
    cin >> ATK >> DEF;
}

double Champion::DamageDealt() {
    return 0;
}

class Jarvan : public Champion {
    private:
        double JarvanSkill;
    public:
        Jarvan();
        void EnterInfo();
        double DamageDealt();
};

Jarvan::Jarvan() : Champion("Jarvan", "CongNghe", 1, "DauSi") {}

void Jarvan::EnterInfo() {
    Champion::EnterInfo();
}

double Jarvan::DamageDealt() {
    return DEF * 2;
}

class Reksai : public Champion {
    private:    
        double ReksaiSkill;
    public:
        Reksai();
        void EnterInfo();
        double DamageDealt();
};

Reksai::Reksai() : Champion("Reksai", "TienCong", 2, "DauSi") {}

void Reksai::EnterInfo() {
    Champion::EnterInfo();
}

double Reksai::DamageDealt() {
    return ATK;
} 

class Sivir : public Champion {
    private:
        double SivirSkill;
    public:
        Sivir();
        void EnterInfo();
        double DamageDealt();
};

Sivir::Sivir() : Champion("Sivir", "CongNghe", 4) {}

void Sivir::EnterInfo() {
    Champion::EnterInfo();
}

double Sivir::DamageDealt() {
    return ATK * 2;
}

class Illaoi : public Champion {
    private:
        double IllaoiSkill;
    public:
        Illaoi();
        void EnterInfo();
        double DamageDealt();
};

Illaoi::Illaoi() : Champion("Illaoi", "TienCong", 1, "DauSi") {}

void Illaoi::EnterInfo() {
    Champion::EnterInfo();
}

double Illaoi::DamageDealt() {
    return (ATK + DEF)/2.0;
}

void BuffTocHe(vector<Champion*> & Champions) {
    set<string> TenSet;
    map<string, int> TocMap;
    map<string, int> HeMap;
    for (auto Tuong : Champions) {
        auto it = TenSet.find(Tuong->GetName());
        if (it != TenSet.end()) {
            continue; 
        } else {
            TenSet.insert(Tuong->GetName());
            TocMap[Tuong->GetToc()]++;
            HeMap[Tuong->GetHe()]++;
        }
    }
    for (auto & Tuong : Champions) {
        if (Tuong->GetHe() == "DauSi") {
            if (HeMap[Tuong->GetHe()] == 2) {
                Tuong->SetDEF(Tuong->GetDEF() + 15);
            } else if (HeMap[Tuong->GetHe()] == 3) {
                Tuong->SetDEF(Tuong->GetDEF() + 30);
            }
        } if (Tuong->GetToc() == "TienCong") {
            if (TocMap[Tuong->GetToc()] == 2) {
                Tuong->SetATK(Tuong->GetATK() + 30);
            }
        } if (Tuong->GetToc() == "CongNghe") {
            if (TocMap[Tuong->GetToc()] == 2) {
                Tuong->SetATK(Tuong->GetATK() + 15);
                Tuong->SetDEF(Tuong->GetDEF() + 15);
            }
        }
    }
}

void DamageDealt(vector<Champion*> & Champions, int Turn) {
    BuffTocHe(Champions);
    int Temp = 1;
    while (Temp != Turn + 1) {
        for (auto & Tuong : Champions) {
            if (dynamic_cast<Reksai*>(Tuong)) {
                if (Temp % 4 == 0) {
                    Tuong->SetDamage(Tuong->GetDamage() + Tuong->DamageDealt() * 2);
                } else {
                    Tuong->SetDamage(Tuong->GetDamage() + Tuong->DamageDealt());
                }
            } else {
                Tuong->SetDamage(Tuong->GetDamage() + Tuong->DamageDealt());
            }
        }
        Temp++;
    }
}

void EnterInfo(vector<Champion*> & Champions, int Quantity) {
    for (int i = 0; i < Quantity; i++) {
        int Type; cin >> Type;
        Champion* Temporary = nullptr;
        if (Type == 1) {
            Temporary = new Jarvan;
        } else if (Type == 2) {
            Temporary = new Reksai;
        } else if (Type == 3) {
            Temporary = new Sivir;
        } else {
            Temporary = new Illaoi;
        } 
        Temporary->EnterInfo();
        Champions.push_back(Temporary);
    }
}

void DisplayInfo(const vector<Champion*> & Champions) {
    int TotalMoney = 0;
    for (auto Tuong : Champions) {
        TotalMoney += Tuong->GetPrice();
        cout << Tuong->GetName() << " - sat thuong gay ra: " << Tuong->GetDamage() << endl; 
    }
    cout << "Tong gia tri: " << TotalMoney;
}

int main() {
    int Quantity, Turn;
    vector<Champion*> Champions;
    cin >> Quantity >> Turn;
    EnterInfo(Champions, Quantity);
    DamageDealt(Champions, Turn);
    DisplayInfo(Champions);
    for (auto Tuong : Champions) {
        delete Tuong;
    }
}