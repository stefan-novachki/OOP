// Lab 10 - 2

#include<iostream>
#include<string.h>

using namespace std;

class InvalidTimeException {
public:
    void print() {
        cout << "The time is not valid" << endl;
    }
};

class Race {
protected:
    char grad[50];
    int godina;
    int mesec;
    float najdobroVreme;
    float dolzina;
public:
    Race(char *grad = "", int godina = 0, int mesec = 0, float najdobroVreme = 0, float dolzina = 0) {
        strcpy(this->grad, grad);
        this->mesec = mesec;
        this->godina = godina;
        this->najdobroVreme = najdobroVreme;
        this->dolzina = dolzina;
    }

    virtual float heaviness() {
        return najdobroVreme / dolzina * 1.0;
    }

    friend ostream &operator<<(ostream &out, Race &t) {
        out << t.grad << " " << t.mesec << "." << t.godina << " " << t.heaviness() << endl;
        return out;
    }
};

class CarRace : public Race {
private:
    int brojKrugovi;
    float najdobriVreminja[50];
    int n;
    static float koeficient;
public:
    CarRace(char *grad = "", int godina = 0, int mesec = 0, float najdobroVreme = 0, float dolzina = 0,
            float *najdobriVreminja = 0, int n = 0, int brojKrugovi = 0) :
            Race(grad, godina, mesec, najdobroVreme, dolzina) {
        this->brojKrugovi = brojKrugovi;
        this->n = n;
        for (int i = 0; i < n; i++) {
            this->najdobriVreminja[i] = najdobriVreminja[i];
        }
    }

    float heaviness() {
        float suma = Race::heaviness();
        float sumaProsek = 0;
        for (int i = 0; i < n; i++) {
            sumaProsek += najdobriVreminja[i];
        }
        sumaProsek = sumaProsek / n * 1.0;
        suma += sumaProsek * koeficient;
        if (brojKrugovi > 15) {
            suma *= 1.1;
        }
        return (float) suma;
    }

    CarRace &operator+=(float vreme) {
        if (vreme < 10)
            throw InvalidTimeException();
        najdobriVreminja[n++] = vreme;
        return *this;
    }

    CarRace(const CarRace &dr) {
        strcpy(this->grad, dr.grad);
        this->mesec = dr.mesec;
        this->godina = dr.godina;
        this->najdobroVreme = dr.najdobroVreme;
        this->dolzina = dr.dolzina;
        this->brojKrugovi = dr.brojKrugovi;
        this->n = dr.n;
        for (int i = 0; i < dr.n; i++)
            this->najdobriVreminja[i] = dr.najdobriVreminja[i];

    }

    static void setKoeficient(float k) {
        koeficient = k;
    }

    void setNumberLaps(int novi) {
        brojKrugovi = novi;
    }

    int getNumberLaps() {
        return brojKrugovi;
    }
};

float CarRace::koeficient = 0.3;

int main() {
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int izbor;
    int numberLaps;

    if (testCase == 1) {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        Race t(city, year, month, bestTime, length);
        cout << t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        CarRace mgt(city, year, month, bestTime, length, bestTimes, n, numberLaps);
        cout << mgt;
        CarRace mgt2;
    }
    if (testCase == 2) {
        cout << "===== Testiranje na operatorot += ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (izbor == 1) {
                niza[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje novo najdobro vreme za prvata CarRace
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++) {
            CarRace *nn = dynamic_cast<CarRace *>(niza[i]);
            if (nn != 0) {
                flag = 0;
                (*nn) += best;
                break;
            }
        }


        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3) {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin >> length;
        cin >> numberLaps;
        CarRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float vreme1, vreme2;
        cin >> vreme1 >> vreme2;
        try {
            mgt += vreme1;
            mgt += vreme2;
        }
        catch (InvalidTimeException e) {
            e.print();
        }
        cout << mgt;
    }

    if (testCase == 5) {
        cout << "===== Testiranje na static clenovi ======" << endl;
        Race **niza;
        cin >> m;
        niza = new Race *[m];
        for (int i = 0; i < m; i++) {
            cin >> izbor;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >> length;
            if (izbor == 1) {
                niza[i] = new Race(city, year, month, bestTime, length);
            } else {
                cin >> numberLaps;
                cin >> n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                niza[i] = new CarRace(city, year, month, bestTime, length, bestTimes, n, numberLaps);
            }
        }
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        CarRace::setKoeficient(0.7);
        // pecatenje na site Trki
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}