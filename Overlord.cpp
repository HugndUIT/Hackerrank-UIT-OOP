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

class Teacher {
    protected:
        string Name;
        double Exp;
    public:
        virtual void EnterInfo();
        virtual double CalculateWage();
        virtual ~Teacher();
};

Teacher::~Teacher() {}

void Teacher::EnterInfo() {
    cin >> Name >> Exp;
}

double Teacher::CalculateWage() {
    return -1;
}

class GVCN : public Teacher {
    private:
        string ClassName;
    public:
        void EnterInfo();
        double CalculateWage();
};

void GVCN::EnterInfo() {
    Teacher::EnterInfo();
    cin >> ClassName;
}

double GVCN::CalculateWage() {
    return Exp * 2000000 + 1000000;
}

class GVBM : public Teacher {
    private:
        string SubjectName;
    public:
        void EnterInfo();
        double CalculateWage();
};

void GVBM::EnterInfo() {
    Teacher::EnterInfo();
    cin >> SubjectName;
}

double GVBM::CalculateWage() {
    return Exp * 2000000;
}

class Student {
    protected:
        string Name, ClassName;
        double Math, Physic, Chemistry;
    public:
        string GetClassName();
        double GetDTB();
        virtual double ReStudyMoney();
        virtual void EnterInfo();
        virtual ~Student();
};

Student::~Student() {}

string Student::GetClassName() {
    return ClassName;
}

double Student::GetDTB() {
    return (Math + Physic + Chemistry) / 3.0;
}

double Student::ReStudyMoney() {
    return -1;
}

void Student::EnterInfo() {
    cin >> Name >> ClassName >> Math >> Physic >> Chemistry;
}

class HSBT : public Student {
    public:
        double ReStudyMoney();
};

double HSBT::ReStudyMoney() {
    double Total = 0;
    double Subjects[] = {Math, Physic, Chemistry};
    for (double Subject : Subjects) {
        if (Subject < 5) {
            Total += 1000000;
        }
    }
    return Total;
}

class HSNVK : public Student {
    public:
        double ReStudyMoney();
};

double HSNVK::ReStudyMoney() {
    return 0;
}

class Class {
    private:
        vector<Teacher*> GV;
        vector<Student*> HS;
        vector<string> ClassOrder;
    public:
        double ReStudyPrice();
        double TeacherSalary();
        unordered_map<string, int> ReStudyStudent();
        unordered_map<string, int> NextGradeStudent();
        void EnterInfo();
        void DisplayInfo();
};

double Class::TeacherSalary() {
    double Total = 0;
    for (Teacher* GiaoVien : GV) {
        Total += GiaoVien->CalculateWage();
    }
    return Total;
}

double Class::ReStudyPrice() {
    double Total = 0;
    for (Student* HocSinh : HS) {
        if (HocSinh->GetDTB() <= 5.0) {
            Total += HocSinh->ReStudyMoney();
        }
    }
    return Total;
}

unordered_map<string, int> Class::ReStudyStudent() {
    unordered_map<string, int> MapClass;
    ClassOrder.clear(); 
    for (Student* HocSinh : HS) {
        string className = HocSinh->GetClassName();
        if (MapClass.count(className) == 0) {
            ClassOrder.push_back(className);
        }

        if (HocSinh->GetDTB() <= 5.0) {
            MapClass[className]++;
        } else {
            MapClass[className]; 
        }
    }
    return MapClass;
}

unordered_map<string, int> Class::NextGradeStudent() {
    unordered_map<string, int> MapClass;
    for (Student* HocSinh : HS) {
        if (HocSinh->GetDTB() > 5.0) {
            MapClass[HocSinh->GetClassName()]++;
        } else {
            MapClass[HocSinh->GetClassName()];
        }
    }
    return MapClass;
}

void Class::EnterInfo() {
    int NumOfTeacher, NumOfStudent;
    cin >> NumOfTeacher;
    for (int i = 0; i < NumOfTeacher; i++) {
        int Type; cin >> Type;
        Teacher* Temp = nullptr;
        if (Type == 1) {
            Temp = new GVCN;
        } else {
            Temp = new GVBM;
        }
        Temp->EnterInfo();
        GV.push_back(Temp);
    }
    cin >> NumOfStudent;
    for (int i = 0; i < NumOfStudent; i++) {
        int Type; cin >> Type;
        Student* Temp = nullptr;
        if (Type == 1) {
            Temp = new HSBT;
        } else {
            Temp = new HSNVK;
        }
        Temp->EnterInfo();
        HS.push_back(Temp);
    }
}

void Class::DisplayInfo() {
    unordered_map<string, int> MapClassOne = ReStudyStudent();
    unordered_map<string, int> MapClassTwo = NextGradeStudent();
    for (const auto & className : ClassOrder) {
        cout << "Lop: " << className << ", so hoc sinh len lop: " << MapClassTwo[className] << ", so hoc sinh dup: " << MapClassOne[className] << endl;
    }
    if (ReStudyPrice() >= TeacherSalary()) {
        cout << "Du " << fixed << setprecision(0) << ReStudyPrice() - TeacherSalary() <<"d";
    } else {
        cout << "Khong du chi tra luong";
    }
}

int main() {
    Class UIT;
    UIT.EnterInfo();
    UIT.DisplayInfo();
}