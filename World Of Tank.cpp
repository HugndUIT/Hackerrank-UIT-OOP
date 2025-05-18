#include <map>
#include <set>
#include <cmath>
#include <vector>
#include <climits>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;

class Turret {
    protected:
        double Size, NumAmmos;
    public:
        Turret();
        Turret(double, double);
        double GetNumAmmos();
        void SetNumAmmos(double);
        virtual double DamageDealt(double);
        void EnterInfo();
        virtual ~Turret();
};

void Turret::EnterInfo() {
    cin >> NumAmmos;
}

void Turret::SetNumAmmos(double Ammos) {
    NumAmmos = Ammos;
}

double Turret::GetNumAmmos() {
    return NumAmmos;
}

double Turret::DamageDealt(double) {
    return -1;
}

Turret::Turret() {}

Turret::~Turret() {}

Turret::Turret(double S, double N = 0) : Size(S), NumAmmos(N) {}

class ML20S : public Turret {
    public:
        ML20S();
        double DamageDealt(double);
};

ML20S::ML20S() : Turret(152) {}

double ML20S::DamageDealt(double NumCrews) {
    return NumCrews / 4.0 * Size * NumAmmos;
}

class F34 : public Turret {
    public:
        F34();
        double DamageDealt(double);
};

F34::F34() : Turret(76.2) {}

double F34::DamageDealt(double) {
    return 3 * Size * NumAmmos;
} 

class D25T : public Turret {
    public:
        D25T();
        double DamageDealt(double);
};

D25T::D25T() : Turret(122) {}

double D25T::DamageDealt(double) {
    return 3 * Size * NumAmmos;
} 

class M65L : public Turret {
    public:
        M65L();
        double DamageDealt(double);
};

M65L::M65L() : Turret(130) {}

double M65L::DamageDealt(double NumCrews) {
    return NumCrews / 4.0 * Size * NumAmmos;
}

class Engine {
    protected:
        double HorsePower, GasAvailable;
    public:
        Engine();
        Engine(double, double);
        double GetGas();
        void SetGas(double);
        virtual double CalculateFuel(double, double);
        void EnterInfo();
        virtual ~Engine();
};

void Engine::EnterInfo() {
    cin >> GasAvailable;
}

void Engine::SetGas(double Gas) {
    GasAvailable = Gas;
}

double Engine::GetGas() {
    return GasAvailable;
} 

double Engine::CalculateFuel(double, double) {
    return -1;
}

Engine::Engine() {}

Engine::~Engine() {}

Engine::Engine(double H, double G = 0) : HorsePower(H), GasAvailable(G) {}

class V2 : public Engine {
    public:
        V2();
        double CalculateFuel(double, double); 
};

V2::V2() : Engine(500) {}

double V2::CalculateFuel(double Weight, double Distance) {
    double Consume = 450.0 / Weight;
    return (Consume / 100.0) *  Distance;
} 

class V2K : public Engine {
    public:
        V2K();
        double CalculateFuel(double, double); 
};

V2K::V2K() : Engine(600) {}

double V2K::CalculateFuel(double Weight, double Distance) {
    double Consume = 450.0 / Weight;
    return (Consume / 100.0) *  Distance;
} 

class DG8M : public Engine {
    public:
        DG8M();
        double CalculateFuel(double, double); 
};

DG8M::DG8M() : Engine(1000) {}

double DG8M::CalculateFuel(double Weight, double Distance) {
    double Consume = 400.0 / Weight;
    return (Consume / 100.0) *  Distance;
} 

class Tank {
    protected:
        string Name;
        Turret* Cannon;
        Engine* Motive;
        double Weight, NumCrews;
    public:
        Tank();
        Tank(string, Turret*, Engine*, double, double); 
        double GetCrews();
        double GetWeight();
        string GetName();
        virtual double Performance(double);
        virtual double DamageDealt(int);
        void EnterInfo();
        virtual ~Tank();
};

string Tank::GetName() {
    return Name;
}

double Tank::GetWeight() {
    return Weight;
}

double Tank::GetCrews() {
    return NumCrews;
}

double Tank::Performance(double) {
    return -1;
}

double Tank::DamageDealt(int) {
    return -1;
}

void Tank::EnterInfo() {
    cin >> Weight >> NumCrews;
    Cannon->EnterInfo();
    Motive->EnterInfo();
}

Tank::Tank() {}

Tank::~Tank() {}

Tank::Tank(string N, Turret* C, Engine* M, double W = 0, double R = 0) {
    Name = N;
    Cannon = C;
    Motive = M;
    Weight = W;
    NumCrews = R;
}

class SU152 : public Tank {
    public:
        SU152();
        double Performance(double);
        double DamageDealt(int);
};

SU152::SU152() : Tank("SU152", new ML20S, new V2K) {}

double SU152::Performance(double NumAmmos) {
    double Temp = Cannon->GetNumAmmos();
    return (Temp - NumAmmos) / Temp * 100;
}

double SU152::DamageDealt(int Ammos) {
    Cannon->SetNumAmmos(Cannon->GetNumAmmos() - Ammos);
    return Cannon->DamageDealt(NumCrews);
}

class KV2 : public Tank {
    public:
        KV2();
        double Performance(double);
        double DamageDealt(int);
};

KV2::KV2() : Tank("KV2", new F34, new V2) {}

double KV2::Performance(double NumAmmos) {
    double Temp = Cannon->GetNumAmmos();
    return (Temp - NumAmmos) / Temp * 100;
}

double KV2::DamageDealt(int Ammos) {
    Cannon->SetNumAmmos(Cannon->GetNumAmmos() - Ammos);
    return Cannon->DamageDealt(0);
}

class IS : public Tank {
    public:
        IS();
        double Performance(double);
        double DamageDealt(int);
};

IS::IS() : Tank("IS", new D25T, new V2K) {}

double IS::Performance(double Distance) {
    return ((Motive->GetGas() - Motive->CalculateFuel(Weight, Distance)) / Motive->GetGas()) * 100;
}

double IS::DamageDealt(int Ammos) {
    Cannon->SetNumAmmos(Cannon->GetNumAmmos() - Ammos);
    return Cannon->DamageDealt(0);
}

class Object279 : public Tank {
    public:
        Object279();
        double Performance(double);
        double DamageDealt(int);
};

Object279::Object279() : Tank("Object279", new M65L, new DG8M) {}

double Object279::Performance(double) {
    return (NumCrews / 4) * 100;
}

double Object279::DamageDealt(int Ammos) {
    Cannon->SetNumAmmos(Cannon->GetNumAmmos() - Ammos);
    return Cannon->DamageDealt(NumCrews);
}

void DisplayInfo(const vector<Tank*> & Tanks, double Distance, int Ammos) {
    for (const auto & Vehicle : Tanks) {
        string Name = Vehicle->GetName();
        double Weight = Vehicle->GetWeight();
        int Crews = Vehicle->GetCrews();
        double Performance;
        double Damage;
        if (dynamic_cast<SU152*>(Vehicle) || dynamic_cast<KV2*>(Vehicle)) {
            Performance = Vehicle->Performance(Ammos);
            Damage = Vehicle->DamageDealt(Ammos);
        } else if (dynamic_cast<IS*>(Vehicle)) {
            Performance = Vehicle->Performance(Distance);
            Damage = Vehicle->DamageDealt(Ammos);
        } else {
            Performance = Vehicle->Performance(0);
            Damage = Vehicle->DamageDealt(Ammos);
        }
        cout << Name << ", weight: " << Weight << ", number of crews: " << Crews << ", damage: " << Damage << ", performance: " << Performance << "%\n";
    }
}

void EnterInfo(vector<Tank*> & Tanks, int Quantity) {
    for (int i = 0; i < Quantity; i++) {
        int Type; cin >> Type;
        Tank* Temporary = nullptr;
        if (Type == 1) {
            Temporary = new SU152;
        } else if (Type == 2) {
            Temporary = new KV2;
        } else if (Type == 3) {
            Temporary = new IS;
        } else {
            Temporary = new Object279;
        }
        Temporary->EnterInfo();
        Tanks.push_back(Temporary);
    }
}

int main() {
    int Quantity, NumAmmos;
    double Distance;
    cin >> Quantity;
    vector<Tank*> Tanks;
    EnterInfo(Tanks, Quantity);
    cin >> Distance >> NumAmmos;
    DisplayInfo(Tanks, Distance, NumAmmos);
}