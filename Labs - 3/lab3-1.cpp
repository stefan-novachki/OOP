// Lab 3 - 1

#include <iostream>
#include <cstring>

using namespace std;

class MobilePhone {
    char model[100];
    int broj;
    int godina;
public:
    MobilePhone() {}

    MobilePhone(char model[100], int broj, int godina) {
        strcpy(this->model, model);
        this->broj = broj;
        this->godina = godina;
    }

    MobilePhone(const MobilePhone &mp) {
        strcpy(this->model, mp.model);
        this->broj = mp.broj;
        this->godina = mp.godina;
    }

    ~MobilePhone() {}

    void print() {
        cout << model << " " << broj << " release year: " << godina << endl;
    }

};

class Owner {
    char ime[100];
    char prezime[100];
    MobilePhone mobilen;
public:
    Owner() {}

    Owner(char ime[100], char prezime[100], MobilePhone mobilen) {
        strcpy(this->ime, ime);
        strcpy(this->prezime, prezime);
        this->mobilen = mobilen;
    }

    Owner(const Owner &o) {
        strcpy(this->ime, o.ime);
        strcpy(this->prezime, o.prezime);
        this->mobilen = o.mobilen;
    }

    ~Owner() {}

    void print() {
        cout << ime << " " << prezime << " has a mobile phone: " << endl;
        mobilen.print();
    }

};

int main() {
    char model[20];
    int modelNumber;
    int year;
    char name[20];
    char surname[20];

    int testCase;

    cin >> testCase;

    cin >> model;
    cin >> modelNumber;
    cin >> year;
    cin >> name;
    cin >> surname;

    if (testCase == 1) {
        MobilePhone mobilePhone(model, modelNumber, year);

        Owner owner(name, surname, mobilePhone);
        owner.print();
    }
    if (testCase == 2) {
        MobilePhone mobilePhone(MobilePhone(model, modelNumber, year));

        Owner owner(name, surname, mobilePhone);
        owner.print();
    }

}