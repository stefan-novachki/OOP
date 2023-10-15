// Lab 9 - 1

#include <iostream>
#include <cstring>

using namespace std;

class Employee {
protected:
    char ime[100];
    int godini;
public:
    Employee(char *ime = "", int godini = 0) {
        strcpy(this->ime, ime);
        this->godini = godini;
    }

    virtual void displayInfo() = 0;
};

class Payable {
protected:
    double plata;
public:
    Payable(double plata = 0.0) {
        this->plata = plata;
    }

    virtual double calculateSalary() = 0;

};

class Developer : virtual public Employee, virtual public Payable {
protected:
    char programskiJazik[100];
public:
    Developer(char *ime = "", int godini = 0, double plata = 0.0, char *programskiJazik = "") :
            Employee(ime, godini), Payable(plata) {
        strcpy(this->programskiJazik, programskiJazik);
    }

    double calculateSalary() {
        return plata - (plata * 0.10);
    }

    void displayInfo() {
        cout << "-- Developer Information --" << endl;
        cout << "Name: " << ime << endl;
        cout << "Age: " << godini << endl;
        cout << "Salary: $" << calculateSalary() << endl;
        cout << "Programming Language: " << programskiJazik << endl;
    }

};

class Manager : virtual public Employee, virtual public Payable {
protected:
    int brojNaOddeli;
public:
    Manager(char *ime = "", int godini = 0, double plata = 0.0, int brojNaOddeli = 0) :
            Employee(ime, godini), Payable(plata) {
        this->brojNaOddeli = brojNaOddeli;
    }

    double calculateSalary() {
        int bonus = brojNaOddeli * (plata * 0.05);
        return plata + bonus;
    }

    void displayInfo() {
        cout << "-- Manager Information --" << endl;
        cout << "Name: " << ime << endl;
        cout << "Age: " << godini << endl;
        cout << "Salary: $" << calculateSalary() << endl;
        cout << "Number of Departments: " << brojNaOddeli << endl;
    }

};

double biggestSalary(Payable *payable[], int n) {
    Payable *maxSalaryEmployee = payable[0];

    for (int i = 1; i < n; i++) {
        if (payable[i]->calculateSalary() > maxSalaryEmployee->calculateSalary()) {
            maxSalaryEmployee = payable[i];
        }
    }

    return maxSalaryEmployee->calculateSalary();
}

int main() {
    Payable *payable[5];
    Developer developers[5];
    Manager managers[5];
    int j = 0, k = 0;
    for (int i = 0; i < 5; i++) {
        char name[50];
        int age;
        double salary;
        cin >> name >> age >> salary;
        if (i % 2 == 0) {
            char programmingLanguage[50];
            cin >> programmingLanguage;
            developers[j] = Developer(name, age, salary, programmingLanguage);
            developers[j].displayInfo();
            payable[i] = &developers[j];
            j++;
        } else {
            int numberOfDepartments;
            cin >> numberOfDepartments;
            managers[k] = Manager(name, age, salary, numberOfDepartments);
            managers[k].displayInfo();
            payable[i] = &managers[k];
            k++;
        }
    }
    cout << endl << "Biggest Salary: " << biggestSalary(payable, 5);
    return 0;
}

