// Lab 2 - 3

#include <iostream>
#include <cstring>

using namespace std;

class Country {
private:
    char name[100];
    char capital[100];
    float area;
    float population;

public:
    Country() {}

    Country(const char *name, const char *capital, float area, float population) {
        strcpy(this->name, name);
        strcpy(this->capital, capital);
        this->area = area;
        this->population = population;
    }

    ~Country() {}

    void setName(const char *name) {
        strcpy(this->name, name);
    }

    void setCapital(const char *capital) {
        strcpy(this->capital, capital);
    }

    void setArea(float area) {
        this->area = area;
    }

    void setPopulation(float population) {
        this->population = population;
    }

    const char *getName() const {
        return name;
    }

    const char *getCapital() const {
        return capital;
    }

    float getArea() const {
        return area;
    }

    float getPopulation() const {
        return population;
    }

    void display() const {
        cout << "Country: " << name << endl;
        cout << "Capital: " << capital << endl;
        cout << "Area: " << area << endl;
        cout << "Population: " << population << endl;
    }
};

void sortCountries(Country c[], int n) {
    Country temp;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (c[j].getArea() > c[j + 1].getArea()) {
                temp = c[j];
                c[j] = c[j + 1];
                c[j + 1] = temp;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << "Country: " << c[i].getName() << endl;
        cout << "Capital: " << c[i].getCapital() << endl;
        cout << "Area: " << c[i].getArea() << endl;
        cout << "Population: " << c[i].getPopulation() << endl;
    }
}

int main() {
    int n;
    cin >> n;
    Country countries[100];

    char name[100];
    char capital[100];
    float area;
    float population;

    for (int i = 0; i < n; i++) {
        cin >> name;
        cin >> capital;
        cin >> area;
        cin >> population;
        countries[i] = Country(name, capital, area, population);
    }

    cout << "-->Testing set methods and display()" << endl;
    cin >> name;
    cin >> capital;
    cin >> area;
    cin >> population;
    countries[n - 1].setName(name);
    countries[n - 1].setCapital(capital);
    countries[n - 1].setArea(area);
    countries[n - 1].setPopulation(population);
    countries[n - 1].display();
    cout << endl;

    cout << "-->Testing sortCountries()" << endl;
    sortCountries(countries, n);

    return 0;
}

