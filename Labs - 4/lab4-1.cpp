// Lab 4 - 1

#include <iostream>
#include <cstring>

using namespace std;

int dolzina(const char *str) {
    int len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

class DisciplinaryAction {
    char *name;
    int index;
    char *reason;

    void oslobodiMemory() {
        delete[] name;
        delete[] reason;
    }

    void copyTemplejt(const DisciplinaryAction &da) {
        this->name = new char[dolzina(da.name) + 1];
        std::strcpy(this->name, da.name);
        this->index = da.index;
        this->reason = new char[dolzina(da.reason) + 1];
        std::strcpy(this->reason, da.reason);
    }

public:
    DisciplinaryAction() {
        this->name = new char[0];
        this->index = 0;
        this->reason = new char[0];
    }

    DisciplinaryAction(char *name, int index, char *reason) {
        this->name = new char[dolzina(name) + 1];
        std::strcpy(this->name, name);
        this->index = index;
        this->reason = new char[dolzina(reason) + 1];
        std::strcpy(this->reason, reason);
    }

    DisciplinaryAction(const DisciplinaryAction &da) {
        copyTemplejt(da);
    }

    DisciplinaryAction &operator=(const DisciplinaryAction &da) {
        if (this != &da) {
            oslobodiMemory();
            copyTemplejt(da);
        }
        return *this;
    }

    void print() {
        std::cout << "Student: " << name << std::endl;
        std::cout << "Student's index: " << index << std::endl;
        std::cout << "Reason: " << reason << std::endl;
    }

    ~DisciplinaryAction() {
        oslobodiMemory();
    }

    void setIndex(int index) { this->index = index; }

    int getIndex() { return index; }
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

        cin >> name >> index >> reason;

        arr[i] = DisciplinaryAction(name, index, reason);
    }

    cout << "-- Testing operator = & print() --\n";
    arr[0].print();

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    arr[0].print();

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    merka.print();

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        arr[i].print();

    return 0;
}