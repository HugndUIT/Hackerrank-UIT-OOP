#include <cmath>
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

class Item {
    protected:
        string Name, Producer;
        double Price, TrueVal;
    public:
        void SetTrueVal(double);
        double GetTrueVal();
        virtual void EnterInfo();
        virtual ~Item();
};

void Item::SetTrueVal(double NewVal) {
    TrueVal = NewVal;
}

double Item::GetTrueVal() {
    return TrueVal;
}

void Item::EnterInfo() {
    cin >> Name >> Price >> Producer;
    TrueVal = Price;
}

Item::~Item() {}

class Pants : public Item {
    private:
        double Length;
    public:
        virtual void EnterInfo();
};

class Jean : public Pants {
    public:
        void TrueValue();
        void EnterInfo();
};

class Kaki : public Pants {
    public: 
        void TrueValue();
        void EnterInfo();
};

void Pants::EnterInfo() {
    Item::EnterInfo();
    cin >> Length;
}

void Jean::TrueValue() {
    SetTrueVal(GetTrueVal() * 0.8);
}

void Kaki::TrueValue() {
    SetTrueVal(GetTrueVal() * 1.5);
}

void Jean::EnterInfo() {
    Pants::EnterInfo();
    TrueValue();
}

void Kaki::EnterInfo() {
    Pants::EnterInfo();
    TrueValue();
}

class Shirt : public Item {
    private:
        string Color;
    public:
        virtual void EnterInfo();
};

class ShortSleeveShirt : public Shirt {
    private:
        bool WithOrNoCollar;
    public:
        void EnterInfo();
};

class LongSleeveShirt : public Shirt {
    private:
        double SleeveLength;
    public:
        void EnterInfo();
};

void Shirt::EnterInfo() {
    Item::EnterInfo();
    cin >> Color;
}

void ShortSleeveShirt::EnterInfo() {
    Shirt::EnterInfo();
    cin >> WithOrNoCollar;
}

void LongSleeveShirt::EnterInfo() {
    Shirt::EnterInfo();
    cin >> SleeveLength;
}

class Cap : public Item {
    private:
        double Level, Buff;
    public:
        void SetBuff(double);
        double GetBuff();
        virtual void EnterInfo();
};

class Helmet : public Cap {
    public:
        void EnterInfo();
};

class SilverHelmet : public Cap {
    public:
        void EnterInfo();
};

class GoldenHelmet : public Cap {
    public: 
        void EnterInfo();
};

void Cap::SetBuff(double Buff) {
    this->Buff = Buff;
}

double Cap::GetBuff() {
    return Buff;
}

void Cap::EnterInfo() {
    Item::EnterInfo();
    cin >> Level;
}

void Helmet::EnterInfo() {
    Cap::EnterInfo();
    SetTrueVal(0);
    SetBuff(1);
}

void SilverHelmet::EnterInfo() {
    Cap::EnterInfo();
    SetBuff(1.5);
}

void GoldenHelmet::EnterInfo() {
    Cap::EnterInfo();
    SetBuff(3);
}

void EnterInfo(vector<Item*> & ItemsList, long long Quantity) {
    long long Type;
    for (long long i = 0; i < Quantity; i++) {
        cin >> Type;
        Item* TemporaryItem = nullptr;
        if (Type == 1 || Type == 2) {
            if (Type == 1) {
                TemporaryItem = new Jean;
            } else {
                TemporaryItem = new Kaki;
            }
        } else if (Type == 3 || Type == 4) {
            if (Type == 3) {
                TemporaryItem = new ShortSleeveShirt;
            } else {
                TemporaryItem = new LongSleeveShirt;
            }
        } else {
            if (Type == 5) {
                TemporaryItem = new Helmet;
            } else if (Type == 6) {
                TemporaryItem = new SilverHelmet;
            } else {
                TemporaryItem = new GoldenHelmet;
            }
        } 
        TemporaryItem->EnterInfo();
        ItemsList.push_back(TemporaryItem);
    }
}

void DisplayInfo(vector<Item*> & ItemsList) {
    for (Item* Items : ItemsList) {
        delete Items;
    }
    ItemsList.clear();
}

double Buff(const vector<Item*> & ItemsList) {
    double MaxBuff = 1;
    for (auto Items : ItemsList) {
        if (dynamic_cast<Cap*>(Items)) {
            MaxBuff = max(MaxBuff, static_cast<Cap*>(Items)->GetBuff());
        } 
    }
    return MaxBuff;
}

double TotalValue(const vector<Item*> & ItemsList) {
    double Total = 0, Sum = 0;
    for (auto Items : ItemsList) {
        if (dynamic_cast<Cap*>(Items)) {
            Sum += Items->GetTrueVal();
        } else {
            Total += Items->GetTrueVal();
        }
    }
    return Total * Buff(ItemsList) + Sum;
}

int main() {
    long long Quantity;
    vector<Item*> ItemsList;
    cin >> Quantity;
    EnterInfo(ItemsList, Quantity);
    cout << TotalValue(ItemsList);
    DisplayInfo(ItemsList);
}