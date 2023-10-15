// Lab 2 - 1

#include <iostream>
#include <cstring>

using namespace std;

class BasketballPlayer {
private:
    char ime[20];
    char prezime[20];
    int broj;
    int prvNatprevar;
    int vtorNatprevar;
    int tretNatprevar;

public:
    BasketballPlayer() {}

    ~BasketballPlayer() {}

    void setIme(char *ime) {
        strcpy(this->ime, ime);
    }

    void setPrezime(char *prezime) {
        strcpy(this->prezime, prezime);
    }

    void setBroj(int broj) {
        this->broj = broj;
    }

    void setPrvNatprevar(int prvNatprevar) {
        this->prvNatprevar = prvNatprevar;
    }

    void setVtorNatprevar(int vtorNatprevar) {
        this->vtorNatprevar = vtorNatprevar;
    }

    void setTretNatprevar(int tretNatprevar) {
        this->tretNatprevar = tretNatprevar;
    }

    float avg_pts() {
        int sum = 0;
        sum += prvNatprevar + vtorNatprevar + tretNatprevar;
        return float(sum / 3.0);
    }

    void print() {
        cout << "Player: " << ime << " " << prezime << " with number: " << broj << " has " << avg_pts()
             << " points on average" << endl;
    }
};


int main() {
    BasketballPlayer bp;

    char ime[20];
    char prezime[20];
    int broj;
    int prvNatprevar;
    int vtorNatprevar;
    int tretNatprevar;

    cin >> ime >> prezime;
    cin >> broj;
    cin >> prvNatprevar >> vtorNatprevar;
    cin >> tretNatprevar;

    bp.setIme(ime);
    bp.setPrezime(prezime);
    bp.setBroj(broj);
    bp.setPrvNatprevar(prvNatprevar);
    bp.setVtorNatprevar(vtorNatprevar);
    bp.setTretNatprevar(tretNatprevar);

    bp.print();

    return 0;
}
