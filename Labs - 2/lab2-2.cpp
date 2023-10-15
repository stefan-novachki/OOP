// Lab 2 - 2

#include <iostream>
#include <cstring>

using namespace std;

class Film {
private:
    char name[100];
    float rating;
    float revenue;

public:
    Film() {}

    Film(const char *name, float rating, float revenue) {
        strcpy(this->name, name);
        this->rating = rating;
        this->revenue = revenue;
    }

    ~Film() {}

    void setName(const char *name) {
        strcpy(this->name, name);
    }

    void setRating(float rating) {
        this->rating = rating;
    }

    void setRevenue(float revenue) {
        this->revenue = revenue;
    }

    const char *getName() const {
        return this->name;
    }

    float getRating() const {
        return this->rating;
    }

    float getRevenue() const {
        return this->revenue;
    }

    void display() const {
        cout << "Name of film: " << name << endl;
        cout << "Rating: " << rating << endl;
        cout << "Revenue: " << revenue << endl;
    }
};

void printMostPopularFilm(Film *f, int n) {
    int maxI = 0;
    float max = f[0].getRevenue();
 
    for (int i = 1; i < n; ++i) {
        if (f[i].getRevenue() > max) {
            max = f[i].getRevenue();
            maxI = i;
        }
    }

    cout << "Name of film: " << f[maxI].getName() << endl;
    cout << "Rating: " << f[maxI].getRating() << endl;
    cout << "Revenue: " << f[maxI].getRevenue() << endl;
}

int main() {
    int n;
    cin >> n;
    Film films[100];

    char name[100];
    float rating;
    float revenue;

    for (int i = 0; i < n; i++) {
        cin >> name;
        cin >> rating;
        cin >> revenue;
        films[i] = Film(name, rating, revenue);
    }

    cout << "-->Testing set methods and display()" << endl;
    cin >> name;
    cin >> rating;
    cin >> revenue;
    films[n - 1].setName(name);
    films[n - 1].setRating(rating);
    films[n - 1].setRevenue(revenue);
    films[n - 1].display();
    cout << endl;

    cout << "-->Testing printMostPopularFilm()" << endl;
    printMostPopularFilm(films, n);

    return 0;
}

