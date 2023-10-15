// Lab 6 - 1

#include <iostream>
#include <cstring>

using namespace std;

class DisciplinaryAction {
private:
    char *imeNaStudentot;
    int indeksNaStudentot;
    char *pricina;
    int brojNaKazneniSesii;

    void copy(const DisciplinaryAction &da) {
        this->imeNaStudentot = new char[strlen(da.imeNaStudentot) + 1];
        strcpy(this->imeNaStudentot, da.imeNaStudentot);
        this->indeksNaStudentot = da.indeksNaStudentot;
        this->pricina = new char[strlen(da.imeNaStudentot) + 1];
        strcpy(this->pricina, da.pricina);
        this->brojNaKazneniSesii = da.brojNaKazneniSesii;
    }

    void freeMemory() {
        delete[] imeNaStudentot;
        delete[] pricina;
    }

public:
    DisciplinaryAction() {
        this->imeNaStudentot = new char[0];
        strcpy(this->imeNaStudentot, "");
        this->indeksNaStudentot = 000000;
        this->pricina = new char[0];
        strcpy(this->pricina, "");
        this->brojNaKazneniSesii = 0;
    }

    DisciplinaryAction(char *name, int index, char *reason, int numOfSessions) {
        this->imeNaStudentot = new char[strlen(name) + 1];
        strcpy(this->imeNaStudentot, name);
        this->indeksNaStudentot = index;
        this->pricina = new char[strlen(name) + 1];
        strcpy(this->pricina, reason);
        this->brojNaKazneniSesii = numOfSessions;
    }

    DisciplinaryAction(const DisciplinaryAction &da) {
        copy(da);
    }

    DisciplinaryAction &operator=(const DisciplinaryAction &da) {
        if (this != &da) {
            freeMemory();
            copy(da);
        }
        return *this;
    }

    DisciplinaryAction &operator++() {
        brojNaKazneniSesii++;
        return *this;
    }

    bool operator>=(const DisciplinaryAction &da) const {
        return brojNaKazneniSesii >= da.brojNaKazneniSesii;
    }

    void setIndex(int index) {
        this->indeksNaStudentot = index;
    }

    int getIndex() const {
        return indeksNaStudentot;
    }

    friend ostream &operator<<(ostream &out, const DisciplinaryAction &da) {
        out << "Student: " << da.imeNaStudentot << endl;
        out << "Student's index: " << da.indeksNaStudentot << endl;
        out << "Reason: " << da.pricina << endl;
        out << "Sessions: " << da.brojNaKazneniSesii << endl;
        return out;
    }

    ~DisciplinaryAction() {
        freeMemory();
    }
};

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for (int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;
        int sessions;

        cin >> name >> index >> reason >> sessions;

        arr[i] = DisciplinaryAction(name, index, reason, sessions);
    }

    cout << "-- Testing operator = & operator <<  --\n";
    cout << arr[0];

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    cout << arr[0];

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    cout << merka;

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        cout << arr[i];


    cout << "\nTesting operator ++ and <<" << endl;
    for (int i = 0; i < n; i++)
        cout << (++arr[i]);


    cout << "\nTesting operator >=" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << i << " " << ((arr[i] >= arr[j]) ? ">= " : "< ") << j << endl;
            }
        }
    }

    return 0;
}