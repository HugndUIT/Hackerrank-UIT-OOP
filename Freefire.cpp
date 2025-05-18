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

// Lop Sung

class Gun {
    protected:
        string Name;
        double MagazineSize, Damage, RateOfFire, NumOfMagazines, WearOut;
    public:
        Gun();
        Gun(string, double, double, double);
        double GetSize();
        double GetDame();
        double GetRate();
        string GetName();
        void SetSize(double);
        void SetDame(double);
        void SetRate(double);
        virtual double TotalDame(double);
        virtual void Input();
        virtual ~Gun(); 
};

Gun::Gun() {}

Gun::Gun(string N, double M, double D, double R) : Name(N), MagazineSize(M), Damage(D), RateOfFire(R) {}

double Gun::GetSize() {
    return MagazineSize;
}

double Gun::GetDame() {
    return Damage;
}

double Gun::GetRate() {
    return RateOfFire;
}

string Gun::GetName() {
    return Name;
}

void Gun::SetSize(double Size) {
    MagazineSize = Size;
}

void Gun::SetDame(double Dame) {
    Damage =  Dame;
}

void Gun::SetRate(double Rate) {
    RateOfFire = Rate;
}

double Gun::TotalDame(double) {
    return -1;
}

void Gun::Input() {
    cin >> NumOfMagazines >> WearOut;
    if (WearOut != 1) {
        Damage *= WearOut;
        RateOfFire /= 2;
    }
}

Gun::~Gun() {}

// Lop Sung Ngan

class Pistol : public Gun {
    public:
        Pistol();  
        Pistol(string, double, double, double);
        void Input();
        double TotalDame(double); 
        virtual ~Pistol();    
};

Pistol::Pistol() {}

Pistol::Pistol(string N, double M, double D, double R) : Gun(N, M, D, R) {}

double Pistol::TotalDame(double Time) {
    double Total = 0;
    double Size = MagazineSize;
    while (Time > 0 && NumOfMagazines != 0) {
        Total += Damage;
        MagazineSize--;
        if (MagazineSize == 0) {
            Time -= 2;
            Time -= 1.0 / RateOfFire;
            NumOfMagazines--;
            MagazineSize = Size;
        } else {
            Time -= 1.0 / RateOfFire;
        }
    }
    return Total;
} 

void Pistol::Input() {
    Gun::Input();
}

Pistol::~Pistol() {}

// Lop G18

class G18 : public Pistol {
    public:
        G18();
};

G18::G18() : Pistol("G18", 12, 2, 1) {}

// Lop M500 

class M500 : public Pistol {
    public:
        M500();
};

M500::M500() : Pistol("M500", 5, 4, 0.5) {}

// Lop Sung Truong

class Rifle : public Gun {
    private:
        double BonusDame;
    public:
        Rifle();
        Rifle(string, double, double, double);
        void Input();
        double TotalDame(double);
        virtual ~Rifle();
};

Rifle::Rifle() {}

Rifle::Rifle(string N, double M, double D, double R) : Gun(N, M, D, R) {}

double Rifle::TotalDame(double Time) {
    double Total = 0;
    double Size = MagazineSize;
    while (Time > 0 && NumOfMagazines != 0) {
        Total += Damage;
        MagazineSize--;
        if (MagazineSize == 0) {
            Time -= 2;
            Time -= 1.0 / RateOfFire;
            NumOfMagazines--;
            MagazineSize = Size;
        } else {
            Time -= 1.0 / RateOfFire;
        }
    }
    return Total;
}

void Rifle::Input() {
    Gun::Input();
    cin >> BonusDame;
    Damage += BonusDame;
}

Rifle::~Rifle() {}

// Lop MP40

class MP40 : public Rifle {
    public:
        MP40();
};

MP40::MP40() : Rifle("MP40", 20, 3, 5) {}

// Lop AK

class AK : public Rifle {
    public:
        AK();
};

AK::AK() : Rifle("AK", 30, 5, 1) {}

// Lop Sung Ban Tia

class Sniper : public Gun {
    public:
        Sniper();
        Sniper(string, double, double, double);
        void Input();
        double TotalDame(double);
        virtual ~Sniper(); 
};

Sniper::Sniper() {}

Sniper::Sniper(string N, double M, double D, double R) : Gun(N, M, D, R) {}

double Sniper::TotalDame(double Time) {
    double Total = 0;
    double Size = MagazineSize;
    while (Time > 0 && NumOfMagazines != 0) {
        Total += Damage;
        MagazineSize--;
        if (MagazineSize == 0) {
            Time -= 2;
            Time -= (1.0 / RateOfFire) + 1;
            NumOfMagazines--;
            MagazineSize = Size;
        } else {
            Time -= (1.0 / RateOfFire) + 1;
        }
    }
    return Total;
}

void Sniper::Input() {
    Gun::Input();
}

Sniper::~Sniper() {}

// Lop SVD 

class SVD : public Sniper {
    public:
        SVD();
};

SVD::SVD() : Sniper("SVD", 10, 5, 0.5) {}

// Lop AWM

class AWM : public Sniper {
    public:
        AWM(); 
};

AWM::AWM() : Sniper("AWM", 5, 10, 0.5) {}

class Game {
    private:
        vector<Gun*> Guns;
        double Time;
    public:
        void Input();
        void Output();
        ~Game();
};

void Game::Input() {
    int Quantity; cin >>  Quantity;
    for (int i = 0; i < Quantity; i++) {
        int Type; cin >> Type;
        Gun* Temp = nullptr;
        if (Type == 1) {
            Temp = new G18;
        } else if (Type == 2) {
            Temp = new M500;
        } else if (Type == 3) {
            Temp = new MP40;
        } else if (Type == 4) {
            Temp = new AK;
        } else if (Type == 5) {
            Temp = new SVD;
        } else {
            Temp = new AWM;
        }
        Temp->Input();
        Guns.push_back(Temp);
    }
    cin >> Time;
}

void Game::Output() {
    for (Gun* Ord : Guns) {
        cout << Ord->GetName() << ": " << Ord->TotalDame(Time) << endl;
    }
}

Game::~Game() {
    if (Guns.size() != 0) {
        for (Gun* Ord : Guns) {
            delete Ord;
        }
        Guns.clear();
    }
}

int main() {
    Game FreeFire;
    FreeFire.Input();
    FreeFire.Output();
}