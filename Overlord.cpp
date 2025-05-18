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

class Member {
    protected:
        string Name;
        double HP, ATK, DEF;
    public:
        double GetHP();
        double GetATK();
        double GetDEF();
        void SetHP(double);
        void SetATK(double);
        void SetDEF(double);
        string GetName(); 
        virtual void Buff(int);
        virtual void Input();
        virtual ~Member();
};

double Member::GetHP() {
    return HP;
}

double Member::GetATK() {
    return ATK;
}

double Member::GetDEF() {
    return DEF;
}

void Member::SetHP(double HP) {
    this->HP = HP;
}

void Member::SetATK(double ATK) {
    this->ATK = ATK;
}

void Member::SetDEF(double DEF) {
    this->DEF = DEF;
}

string Member::GetName() {
    return Name;
}

void Member::Buff(int) {}

void Member::Input() {
    cin >> Name >> HP >> ATK >> DEF;
}

Member::~Member() {}

class Humanity : public Member {
    private:
        string Job;
    public:
        void Input();
        virtual void Buff(int);
        virtual ~Humanity();
};

void Humanity::Input() {
    Member::Input();
    cin >> Job;
}

void Humanity::Buff(int) {}

Humanity::~Humanity() {}

class Human : public Humanity {
    public:
        void Buff(int);
};

void Human::Buff(int) {}

class Elf : public Humanity {
    public:
        void Buff(int);
};

void Elf::Buff(int) {
    SetDEF(GetDEF() + 0.5 * GetDEF());
}

class SemiHuman : public Member {
    private:
        string Racial;
    public:
        void Input();
        virtual void Buff(int);
        virtual ~SemiHuman();
};

void SemiHuman::Buff(int) {}

void SemiHuman::Input() {
    Member::Input();
    cin >> Racial;
}

SemiHuman::~SemiHuman() {}

class Orc : public SemiHuman {
    public:
        void Buff(int);
};

void Orc::Buff(int) {
    SetHP(GetHP() + 0.5 * GetHP());
}

class Golbin : public SemiHuman {
    public:
        void Buff(int);
};

void Golbin::Buff(int) {
    SetATK(GetATK() + 0.1 * GetATK());
}

class MissHapen : public Member {
    public:
        void Input();
        virtual void Buff(int);
        virtual ~MissHapen();
};

void MissHapen::Input() {
    Member::Input();
}

void MissHapen::Buff(int) {}

MissHapen::~MissHapen() {}

class Vampire : public MissHapen {
    public:
        void Buff(int);
};

void Vampire::Buff(int Humans) {
    for (int i = 0; i < Humans; i++) {
        SetHP(GetHP() + 0.1 * GetHP());
    }
}

class Devil : public MissHapen {
    public:
        void Buff(int);
};

void Devil::Buff(int Devils) {
    for (int i = 0; i < Devils; i++) {
        SetATK(GetATK() + 0.1 * GetATK());
        SetDEF(GetDEF() + 0.1 * GetDEF());
    }
}

class Boss : public Member {};

class Guild {
    private:
        vector<Member*> Members;
        Boss* Tycoon;
    public:
        void PlayerTurn();
        void BossTurn();
        bool Combat();
        void EnterInfo();
        void DisplayInfo();
        ~Guild();
};

void Guild::PlayerTurn() {
    for (auto Player : Members) {
        if (Tycoon->GetDEF() > Player->GetATK()) {
            continue;
        } else {
            Tycoon->SetHP(Tycoon->GetHP() - (Player->GetATK() -  Tycoon->GetDEF()));
        }
    }
}

void Guild::BossTurn() {
    if (Members.empty()) {
        return;
    }
    sort(Members.begin(), Members.end(), [](Member* x, Member* y){
        return x->GetHP() < y->GetHP(); 
    });
    if (Members[0]->GetDEF() <= Tycoon->GetATK()) {
        Members[0]->SetHP(Members[0]->GetHP() - (Tycoon->GetATK() - Members[0]->GetDEF()));
    } 
    if (Members[0]->GetHP() <= 0) {
        delete Members[0];
        Members.erase(Members.begin());
    }
}

bool Guild::Combat() {
    int Turn = 1;
    while (Members.size() != 0 && Tycoon->GetHP() > 0 && Turn != 100) {
        PlayerTurn();
        if (Tycoon->GetHP() <= 0) {
            break;
        }
        BossTurn();
        Turn++;
    }
    if (Turn >= 100 || Tycoon->GetHP() > 0) {
        return false;
    } 
    return true;
}  

void Guild::EnterInfo() {
    int Quantity; cin >> Quantity;
    int Humans = 0, Devils = 0;
    for (int i = 0; i < Quantity; i++) {
        int Type; cin >> Type;
        Member* Temp = nullptr;
        if (Type == 1) {
            Temp = new Human;
            Humans++;
        } else if (Type == 2) {
            Temp = new Elf;
            Humans++;
        } else if (Type == 3) {
            Temp = new Orc;
        } else if (Type == 4) {
            Temp = new Golbin;
        } else if (Type == 5) {
            Temp = new Vampire;
        } else {
            Temp = new Devil;
            Devils++;
        }
        Temp->Input();
        Members.push_back(Temp);
    }
    for (Member* Player : Members) {
        if (dynamic_cast<Vampire*>(Player)) {
            Player->Buff(Humans);
        } else if (dynamic_cast<Devil*>(Player)) {
            Player->Buff(Devils);
        } else {
            Player->Buff(0);
        }
    }
    Tycoon = new Boss;
    Tycoon->Input();
}

void Guild::DisplayInfo() {
    if (Combat()) {
        sort(Members.begin(), Members.end(), [](Member* x, Member* y){
            return x->GetHP() < y->GetHP(); 
        });
        for (auto Player : Members) {
            cout << Player->GetName() << " " << Player->GetHP() << endl;
        }
    } else {
        cout << Tycoon->GetName() << " " << Tycoon->GetHP() << endl;
    }
}

Guild::~Guild() {
    if (Members.size() != 0) {
        for (auto Player : Members) {
            delete Player;
        }
    }
}

int main() {
    Guild UIT;
    UIT.EnterInfo();
    UIT.DisplayInfo();
}