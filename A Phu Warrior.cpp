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

class Weapon {
    protected:  
        double Damage, Turn;
    public:
        double GetDame();
        double GetTurn();
        void SetDame(double);
        void SetTurn(double);
        virtual void Input();
        virtual double DamePerTurn();
        virtual ~Weapon();
};

double Weapon::GetDame() {
    return Damage;
}

double Weapon::GetTurn() {
    return Turn;
}

void Weapon::SetDame(double Dame) {
    this->Damage = Dame;
}

void Weapon::SetTurn(double Turn) {
    this->Turn = Turn;
}

void Weapon::Input() {
    cin >> Damage >> Turn;
}

double Weapon::DamePerTurn() {
    return -1;
}

Weapon::~Weapon() {}

class Knife : public Weapon {
    private:
        double Length;
    public:
        void Input(); 
        double DamePerTurn();
};

void Knife::Input() {
    Weapon::Input();
    cin >> Length;
}

double Knife::DamePerTurn() {
    return Damage * Length;
}

class Bow : public Weapon {
    private:
        double Arrows;
    public:
        void Input();
        double DamePerTurn();
};

void Bow::Input() {
    Weapon::Input();
    cin >> Arrows;
}

double Bow::DamePerTurn() {
    return Damage * Arrows / 2.0;
}

class WildBeast {
    protected:
        double HP, Damage;
    public:
        double GetHP();
        void SetHP(double);
        virtual void Input();
        virtual double DamePerTurn();
        virtual ~WildBeast();
};  

double WildBeast::GetHP() {
    return HP;
}

void WildBeast::SetHP(double HP) {
    this->HP = HP;
}

void WildBeast::Input() {
    cin >> HP >> Damage;
}

double WildBeast::DamePerTurn() {
    return -1;
}

WildBeast::~WildBeast() {}

class Bull : public WildBeast {
    private:
        double Hits;
    public:
        double GetHits();
        void SetHits(double);
        void Input();
        double DamePerTurn();
};

double Bull::GetHits() {
    return Hits;
}

void Bull::SetHits(double Hits) {
    this->Hits = Hits;
}

void Bull::Input() {
    WildBeast::Input();
    cin >> Hits;
}

double Bull::DamePerTurn() {
    return Damage;
}

class Tiger : public WildBeast {
    public:
        void Input();
        double DamePerTurn();
};

void Tiger::Input() {
    WildBeast::Input();
}

double Tiger::DamePerTurn() {
    return Damage * 1.5;
}

class APhu {
    private:
        double HP;
        vector<Weapon*> Weapons;
        vector<WildBeast*> WildBeasts;
    public:
        void Input();
        void BeastTakeDamage(double);
        bool IsWin();
        void Output();
        ~APhu();
};

void APhu::Input() {
    cin >> HP;
    int Quantity; 
    cin >> Quantity;
    for (int i = 0; i < Quantity; i++) {
        int Type; cin >> Type;
        Weapon* VuKhi = nullptr;
        if (Type == 1) {
            VuKhi = new Knife;
        } else {
            VuKhi = new Bow;
        }
        VuKhi->Input();
        Weapons.push_back(VuKhi);
    }
    cin >> Quantity;
    for (int i = 0; i < Quantity; i++) {
        int Type; cin >> Type;
        WildBeast* ThuDu = nullptr;
        if (Type == 1) {
            ThuDu = new Bull;
        } else {
            ThuDu = new Tiger;
        }
        ThuDu->Input();
        WildBeasts.push_back(ThuDu);
    }
}

void APhu::BeastTakeDamage(double damage) {
    if (WildBeasts.empty()) 
        return;
    if (auto* bull = dynamic_cast<Bull*>(WildBeasts[0])) {
        bull->SetHP(bull->GetHP() - damage);
        bull->SetHits(bull->GetHits() - 1);
        if (bull->GetHP() <= 0 || bull->GetHits() <= 0) {
            WildBeasts.erase(WildBeasts.begin());
        } else {
            HP -= WildBeasts[0]->DamePerTurn();
        }
    } else {
        WildBeasts[0]->SetHP(WildBeasts[0]->GetHP() - damage);
        if (WildBeasts[0]->GetHP() <= 0) {
            WildBeasts.erase(WildBeasts.begin());
        } else {
            HP -= WildBeasts[0]->DamePerTurn();
        }
    }
}


bool APhu::IsWin() {
    for (size_t i = 0; i < Weapons.size(); i++) {
        while (Weapons[i]->GetTurn() > 0) {
            BeastTakeDamage(Weapons[i]->DamePerTurn());
            if (dynamic_cast<Knife*>(Weapons[i])) {
                Weapons[i]->SetTurn(Weapons[i]->GetTurn() - 1);
            } else {
                Weapons[i]->SetTurn(Weapons[i]->GetTurn() - 2);
            }
            if (Weapons[i]->GetTurn() <= 0) {
                Weapons.erase(Weapons.begin() + i);
            }
            if (WildBeasts.size() == 0) {
                return true;
            }
            if (HP <= 0) {
                return false;
            }   
        }
        if (Weapons.size() != 0) {
            Weapons.erase(Weapons.begin() + i);
            --i;
        }
    }  
    if (WildBeasts.size() != 0) {
        double Dame = HP * 0.1;
        while (HP > 0) {
            BeastTakeDamage(Dame);
            HP -= Dame;
            if (WildBeasts.size() == 0) {
                return true;
            } 
        }
        return false;
    }
    return true;
}

void APhu::Output() {
    if (IsWin()) {
        cout << "A Phu chien thang, hp con lai: " << HP << ", so vu khi con lai: " << Weapons.size();
    } else {
        cout << "A Phu that bai, so thu du con lai: " << WildBeasts.size();
    }
}

APhu::~APhu() {
    for (Weapon* VuKhi : Weapons) {
        delete VuKhi;
    }
    Weapons.clear();
    for (WildBeast* ThuDu : WildBeasts) {
        delete ThuDu;
    }
    WildBeasts.clear();
}

int main() {
    APhu UIT;
    UIT.Input();
    UIT.Output();
}