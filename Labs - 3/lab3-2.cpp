// Lab 3 - 2

#include <iostream>
#include <cstring>

using namespace std;

class Employee {
    char ime[20];
    char ID[20];
    float plata;
public:
    Employee() {}

    Employee(char ime[20], char ID[20], float plata) {
        strcpy(this->ime, ime);
        strcpy(this->ID, ID);
        this->plata = plata;
    }

    Employee(const Employee &e) {
        strcpy(this->ime, e.ime);
        strcpy(this->ID, e.ID);
        this->plata = e.plata;
    }

    ~Employee() {}

    char *getId() {
        return ID;
    }

};

class Department {
    int ID;
    char ime[20];
    Employee vraboteni[3];
public:
    Department() {}

    Department(int ID, char ime[20], Employee vraboteni[3]) {
        this->ID = ID;
        strcpy(this->ime, ime);
        for (int i = 0; i < 3; i++) {
            this->vraboteni[i] = vraboteni[i];
        }
    }

    Department(const Department &d) {
        this->ID = d.ID;
        strcpy(this->ime, d.ime);
        for (int i = 0; i < 3; i++) {
            this->vraboteni[i] = d.vraboteni[i];
        }
    }

    ~Department() {}


    int getId() {
        return ID;
    }

    bool hasDuplicateID() {
        for (int i = 0; i < 3; i++) {
            if (strcmp(vraboteni[i].getId(), vraboteni[i + 1].getId()) == 0) {
                return true;
            }
        }
    }

};

int main() {
    char ID[14], ime[20], name[50];
    int broj, n, numEmployees, id1;
    float salary;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> ID >> ime >> salary;
        Employee p1(ime, ID, salary);
        cin >> ID >> ime >> salary;
        Employee p2(ime, ID, salary);
        cin >> ID >> ime >> salary;
        Employee p3(ime, ID, salary);
        cin >> id1 >> name;
        Employee p[3];
        p[0] = p1;
        p[1] = p2;
        p[2] = p3;
        Department d(id1, name, p);
        cout << "Department " << d.getId() << ":" << endl;
        if (d.hasDuplicateID() == true)
            cout << "Postojat vraboteni so ist ID" << endl;
        else
            cout << "Ne postojat vraboteni so ist ID" << endl;
    }
    return 0;
}