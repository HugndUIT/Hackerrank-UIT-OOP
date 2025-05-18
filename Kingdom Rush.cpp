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

// Lop Tru

class Tower {
    public:
        virtual void Input();
        virtual ~Tower();
};

void Tower::Input() {}

Tower::~Tower() {}

// Lop Ban Ten

class Archer : public Tower {
    private:
        double PhysicDame;
    public:
        void Input();
        double getPhysicDame();
        void setPhysicDame(double);
};

double Archer::getPhysicDame() {
    return PhysicDame;
}

void Archer::setPhysicDame(double physicDame) {
    PhysicDame = physicDame;
}

void Archer::Input() {
    cin >> PhysicDame;
}

// Lop Phep Thuat

class Arcane : public Tower {
    private:
        double MagicDame;
    public:
        void Input();
        double getMagicDame();
        void setMagicDame(double);
};

double Arcane::getMagicDame() {
    return MagicDame;
}

void Arcane::setMagicDame(double magicDame) {
    MagicDame = magicDame;
}

void Arcane::Input() {
    cin >> MagicDame;
}

// Lop Linh

class Barrack : public Tower {
    private:
        double Quantity, Time;
    public:
        void Input();
        double getQuantity();
        void setQuantity(double);
        double getTime();
        void setTime(double);
};

double Barrack::getQuantity() {
    return Quantity;
}

double Barrack::getTime() {
    return Time;
}

void Barrack::setQuantity(double quantity) {
    Quantity = quantity;
}

void Barrack::setTime(double time) {
    Time = time;
}

void Barrack::Input() {
    cin >> Quantity >>  Time;
}

// Lop Quai Vat

class Monster {
    private:
        double HP, PhysicAmor, MagicAmor;
        double OriginHP;
    public:
        void Input();
        double getHP();
        double getOriginHP();
        double getPhysicAmor();
        double getMagicAmor();
        void setHP(double hp);
        void setPhysicAmor(double physicAmor);
        void setMagicAmor(double magicAmor);
};

double Monster::getHP() {
    return HP;
}

double Monster::getOriginHP() {
    return OriginHP;
}

double Monster::getPhysicAmor() {
    return PhysicAmor;
}

double Monster::getMagicAmor() {
    return MagicAmor;
}

void Monster::setHP(double hp) {
    HP = hp;
}

void Monster::setPhysicAmor(double physicAmor) {
    PhysicAmor = physicAmor;
}

void Monster::setMagicAmor(double magicAmor) {
    MagicAmor = magicAmor;
}

void Monster::Input() {
    cin >> HP >> PhysicAmor >> MagicAmor;
    OriginHP = HP;
}

// Lop KingDom Rush

class KingdomRush {
    private:
        vector<Tower*> Towers;
        vector<Monster> Monsters;
    public:
        void Input();
        double Time();
        double Linh();
        int Combat();
        void Output();
};

void KingdomRush::Input() {
    int NumberTower, NumberMonster;
    cin >> NumberTower;
    for (int i = 0; i < NumberTower; i++) {
        int Type; cin >> Type;
        Tower* Turret = nullptr;
        if (Type == 1) {
            Turret = new Archer;
        } else if (Type == 2) {
            Turret = new Arcane;
        } else {
            Turret = new Barrack;
        }
        Turret->Input();
        Towers.push_back(Turret);
    }
    cin >> NumberMonster;
    for (int i = 0; i < NumberMonster; i++) {
        Monster Temp;
        Temp.Input();
        Monsters.push_back(Temp);
    }
}

double KingdomRush::Time() {
    double TotalTime = 0;
    for (Tower* Turret : Towers) {
        if (dynamic_cast<Barrack*>(Turret)) {
            TotalTime += static_cast<Barrack*>(Turret)->getTime();
        }
    }
    return TotalTime;
}

double KingdomRush::Linh() {
    double TotalLinh = 0;
    for (Tower* Turret : Towers) {
        if (dynamic_cast<Barrack*>(Turret)) {
            TotalLinh += static_cast<Barrack*>(Turret)->getQuantity();
        }
    }
    return TotalLinh;
}

int KingdomRush::Combat() {
    if (Monsters.size() > Linh()) {
        return 1;
    } 
    double TotalTime = Time() + 1;
    while (Monsters.size() > 0 && TotalTime > 0) {
        int MinIndex = 0;
        for (size_t i = 1; i < Monsters.size(); ++i) {
            if (Monsters[i].getHP() < Monsters[MinIndex].getHP()) {
                MinIndex = i;
            }
        }
        for (Tower* Turret : Towers) {
            double HP = Monsters[MinIndex].getOriginHP() * 0.1;
            if (auto* archer = dynamic_cast<Archer*>(Turret)) {
                if (archer->getPhysicDame() >= Monsters[MinIndex].getPhysicAmor()) {
                    Monsters[MinIndex].setHP(Monsters[MinIndex].getHP() - (archer->getPhysicDame() + HP));
                }
            } else if (auto* arcane = dynamic_cast<Arcane*>(Turret)) {
                if (arcane->getMagicDame() >= Monsters[MinIndex].getMagicAmor()) {
                    Monsters[MinIndex].setHP(Monsters[MinIndex].getHP() - (arcane->getMagicDame() - Monsters[MinIndex].getMagicAmor()));
                }
            }
        }
        if (Monsters[MinIndex].getHP() <= 0) {
            Monsters.erase(Monsters.begin() + MinIndex);
        }
        TotalTime--;
    }
    if (Monsters.empty()) 
        return 0;
    return 2;
}

void KingdomRush::Output() {
    for (Monster Temp : Monsters) {
        cout << Temp.getHP() << endl;
    }
}

int main() {
    KingdomRush UITCoder;
    UITCoder.Input();
    int Result = UITCoder.Combat();
    if (Result == 0) {
        cout << "SUCCESS";
    } else if (Result == 1) {
        cout << "FAILED";
    } else { 
        UITCoder.Output(); 
    }
}