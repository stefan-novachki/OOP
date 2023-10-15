// Lab 5 - 2

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

class DeliveryPerson {
private:
    char dostavuvacID[6];
    char *dostavuvacIme;
    int dostavuvacLokacija;
    int brIzvrseniDostavi;

    void copyConstructor(const DeliveryPerson &dp) {
        strcpy(this->dostavuvacID, dp.dostavuvacID);
        this->dostavuvacLokacija = dp.dostavuvacLokacija;
        this->brIzvrseniDostavi = dp.brIzvrseniDostavi;
        this->dostavuvacIme = new char[strlen(dp.dostavuvacIme) + 1];
        strcpy(this->dostavuvacIme, dp.dostavuvacIme);
    }

public:
    DeliveryPerson() {
        strcpy(this->dostavuvacID, "");
        this->dostavuvacLokacija = 0;
        this->brIzvrseniDostavi = 0;
        this->dostavuvacIme = new char[0];
        strcpy(this->dostavuvacIme, "");
    }

    DeliveryPerson(char *dostavuvacID, char *dostavuvacIme, int dostavuvacLokacija, int brIzvrseniDostavi = 0) {
        strcpy(this->dostavuvacID, dostavuvacID);
        this->dostavuvacLokacija = dostavuvacLokacija;
        this->brIzvrseniDostavi = brIzvrseniDostavi;
        this->dostavuvacIme = new char[strlen(dostavuvacIme) + 1];
        strcpy(this->dostavuvacIme, dostavuvacIme);
    }

    DeliveryPerson(const DeliveryPerson &dp) {
        copyConstructor(dp);
    }

    DeliveryPerson &operator=(const DeliveryPerson &dp) {
        if (this != &dp) {
            delete[] dostavuvacIme;
            copyConstructor(dp);
        }
        return *this;
    }

    void print() {
        cout << "ID: " << dostavuvacID;
        cout << " Name: " << dostavuvacIme;
        cout << " Current location: " << dostavuvacLokacija;
        cout << " # of deliveries: " << brIzvrseniDostavi;
        cout << endl;
    }

    const char *getDostavuvacID() const {
        return dostavuvacID;
    }

    void setDostavuvacLokacija(int dostavuvacLokacija) {
        this->dostavuvacLokacija = dostavuvacLokacija;
    }

    int getDostavuvacLokacija() {
        return dostavuvacLokacija;
    }

    int getBrIzvrseniDostavi() {
        return brIzvrseniDostavi;
    }

    bool operator==(const DeliveryPerson &dp) {
        return strcmp(this->dostavuvacID, dp.dostavuvacID) == 0;
    }

    void zgolemiProdazbi() {
        brIzvrseniDostavi++;
    }

    ~DeliveryPerson() {
        delete[] dostavuvacIme;
    }
};

class DeliveryApp {
private:
    char appIme[20];
    DeliveryPerson *dostavuvaci;
    int brNaDostavuvaci;

    void copyConstructor(const DeliveryApp &da) {
        strcpy(this->appIme, da.appIme);
        this->brNaDostavuvaci = da.brNaDostavuvaci;
        this->dostavuvaci = new DeliveryPerson[da.brNaDostavuvaci];
        for (int i = 0; i < da.brNaDostavuvaci; i++) {
            this->dostavuvaci[i] = da.dostavuvaci[i];
        }
    }

public:
    DeliveryApp() {
        strcpy(this->appIme, "");
        this->brNaDostavuvaci = 0;
        this->dostavuvaci = new DeliveryPerson[brNaDostavuvaci];
    }

    DeliveryApp(const char *appIme) {
        strcpy(this->appIme, appIme);
        this->brNaDostavuvaci = 0;
        this->dostavuvaci = new DeliveryPerson[brNaDostavuvaci];
    }

    DeliveryApp(const DeliveryApp &da) {
        copyConstructor(da);
    }

    DeliveryApp &operator=(const DeliveryApp &da) {
        if (this != &da) {
            delete[] dostavuvaci;
            copyConstructor(da);
        }
        return *this;
    }

    void assignDelivery(int restoranLokacija, int klientLokacija) {
        int minDosIdx = -1;
        int minDistanca = 10;
        int dostaviBrojac = 0;

        for (int i = 0; i < brNaDostavuvaci; i++) {
            int momentalnaLokacija = dostavuvaci[i].getDostavuvacLokacija();
            int distanca = abs(momentalnaLokacija - restoranLokacija);
            if (distanca <= minDistanca) {
                if (distanca == minDistanca) {
                    if (dostavuvaci[i].getBrIzvrseniDostavi() < dostavuvaci[minDosIdx].getBrIzvrseniDostavi()) {
                        minDosIdx = i;
                        dostaviBrojac = dostavuvaci[i].getBrIzvrseniDostavi();
                    } else if (dostavuvaci[i].getBrIzvrseniDostavi() == dostavuvaci[minDosIdx].getBrIzvrseniDostavi()) {
                        if (momentalnaLokacija < dostavuvaci[minDosIdx].getBrIzvrseniDostavi()) {
                            minDosIdx = i;
                            dostaviBrojac = dostavuvaci[i].getBrIzvrseniDostavi();
                        }
                    }
                } else {
                    minDosIdx = i;
                    minDistanca = distanca;
                    dostaviBrojac = dostavuvaci[i].getBrIzvrseniDostavi();
                }
            }
        }
        dostavuvaci[minDosIdx].setDostavuvacLokacija(klientLokacija);
        dostavuvaci[minDosIdx].zgolemiProdazbi();
    }

    void addDeliveryPerson(const DeliveryPerson &novDostavuvac) {
        for (int i = 0; i < brNaDostavuvaci; i++) {
            if (strcmp(dostavuvaci[i].getDostavuvacID(), novDostavuvac.getDostavuvacID()) == 0) {
                return;
            }
        }
        DeliveryPerson *tmp = new DeliveryPerson[brNaDostavuvaci + 1];
        for (int i = 0; i < brNaDostavuvaci; i++) {
            tmp[i] = dostavuvaci[i];
        }
        tmp[brNaDostavuvaci++] = novDostavuvac;
        delete[] dostavuvaci;
        dostavuvaci = tmp;
    }

    void print() {
        cout << appIme;
        cout << endl;
        (brNaDostavuvaci == 0) ? (cout << "EMPTY" << endl) : cout << "";
        for (int i = 0; i < brNaDostavuvaci; i++) {
            dostavuvaci[i].print();
        }
    }

    ~DeliveryApp() {
        delete[] dostavuvaci;
    }
};

int main() {

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "CONSTRUCTOR DeliveryPerson" << endl;
        DeliveryPerson person("12345", "Stefan", 5);
        person.print();
        cout << "CONSTRUCTOR DeliveryPerson OK" << endl;
    } else if (testCase == 2) {
        cout << "COPY-CONSTRUCTOR DeliveryPerson" << endl;
        DeliveryPerson person = DeliveryPerson("12345", "Stefan", 5);
        person.print();
        cout << "COPY-CONSTRUCTOR DeliveryPerson OK" << endl;
    } else if (testCase == 3) {
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = DeliveryPerson" << endl;
        DeliveryPerson person;
        DeliveryPerson person2("12345", "Stefan", 5);
        person = person2;
        person.print();
        cout << "DEFAULT CONSTRUCTOR AND OPERATOR = DeliveryPerson OK" << endl;
    } else if (testCase == 4) {
        cout << "CONSTRUCTOR DeliveryApp" << endl;
        char appName[50];
        cin >> appName;
        DeliveryApp app(appName);
        app.print();
        cout << "CONSTRUCTOR DeliveryApp OK" << endl;
    } else if (testCase == 5) {
        cout << "DeliveryApp addDeliveryPerson test" << endl;
        char appName[50];
        cin >> appName;
        DeliveryApp app(appName);
        int n;
        cin >> n;
        char ID[6];
        char name[20];
        int location;
        for (int i = 0; i < n; i++) {
            cin >> ID >> name >> location;
            app.addDeliveryPerson(DeliveryPerson(ID, name, location));
        }
        app.print();
    } else if (testCase == 6) {
        cout << "DeliveryApp addDeliveryPerson test" << endl;
        char appName[50];
        cin >> appName;
        DeliveryApp app(appName);
        int n;
        cin >> n;
        char ID[6];
        char name[20];
        int location;
        for (int i = 0; i < n; i++) {
            cin >> ID >> name >> location;
            app.addDeliveryPerson(DeliveryPerson(ID, name, location));
        }
        cin >> n; //read assign deliveries
        for (int i = 0; i < n; i++) {
            int restaurantArea, customerArea;
            cin >> restaurantArea >> customerArea;
            app.assignDelivery(restaurantArea, customerArea);
        }
        app.print();
    }
    return 0;
}