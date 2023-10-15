// Lab 7 - 2

#include <iostream>
#include <cstring>

using namespace std;

class Course {
protected:
    char *ime;
    int cena;
    int rejting;
    int brojNaLekcii;

    void copy(const Course &c) {
        this->ime = new char[strlen(c.ime) + 1];
        strcpy(this->ime, c.ime);
        this->cena = c.cena;
        this->rejting = c.rejting;
        this->brojNaLekcii = c.brojNaLekcii;
    }

public:
    Course() {
        this->ime = new char[0];
        this->cena = 0;
        this->rejting = 0;
        this->brojNaLekcii = 0;
    }

    Course(char *ime, int cena, int rejting, int brojNaLekcii) {
        this->ime = new char[strlen(ime) + 1];
        strcpy(this->ime, ime);
        this->cena = cena;
        this->rejting = rejting;
        this->brojNaLekcii = brojNaLekcii;
    }

    Course(const Course &c) {
        copy(c);
    }

    Course &operator=(const Course &c) {
        if (this != &c) {
            delete[] ime;
            copy(c);
        }
        return *this;
    }

    double getTotalPrice() {
        int cena2 = brojNaLekcii * cena;
        if (rejting < 7) {
            double popust = cena2 * 0.1;
            return (cena2 - popust);
        } else {
            return cena2;
        }
    }

    void print() {
        cout << "Course: " << ime << endl;
        cout << "Price: " << getTotalPrice() << endl;
        cout << "Rating: " << rejting << endl;
    }

    ~Course() {
        delete[] ime;
    }
};

class ProgrammingCourse : public Course {
private:
    char *programskiJazik;
    bool premium;
    int nivoNaTezina;

    void copy(const ProgrammingCourse &pc) {
        this->programskiJazik = new char[strlen(pc.programskiJazik) + 1];
        strcpy(this->programskiJazik, pc.programskiJazik);
        this->premium = pc.premium;
        this->nivoNaTezina = pc.nivoNaTezina;
    }

public:
    ProgrammingCourse() : Course() {
        this->programskiJazik = new char[0];
        this->premium = false;
        this->nivoNaTezina = 0;
    }

    ProgrammingCourse(Course &c, char *programskiJazik, bool premium, int nivoNaTezina) : Course(c) {
        this->programskiJazik = new char[strlen(programskiJazik) + 1];
        strcpy(this->programskiJazik, programskiJazik);
        this->premium = premium;
        this->nivoNaTezina = nivoNaTezina;
    }

    ProgrammingCourse(char *ime, int cena, int rejting, int brojNaLekcii, char *programskiJazik, bool premium,
                      int nivoNaTezina) :
            Course(ime, cena, rejting, brojNaLekcii) {
        this->programskiJazik = new char[strlen(programskiJazik) + 1];
        strcpy(this->programskiJazik, programskiJazik);
        this->premium = premium;
        this->nivoNaTezina = nivoNaTezina;
    }

    ProgrammingCourse(const ProgrammingCourse &pc) :
            Course(pc.ime, pc.cena, pc.rejting, pc.brojNaLekcii) {
        copy(pc);
    }

    ProgrammingCourse &operator=(const ProgrammingCourse &pc) {
        if (this != &pc) {
            delete[] programskiJazik;
            Course::copy(pc);
            copy(pc);
        }
        return *this;
    }

    double getTotalPrice() {
        double cena2 = Course::getTotalPrice();
        if (premium == true) {
            int popust = cena2 * 0.2;
            return (cena2 - popust);
        } else {
            return cena2;
        }
    }

    int operator++() {
        nivoNaTezina++;
        return nivoNaTezina;
    }

    void print() {
        cout << "Course: " << ime << endl;
        cout << "Price: " << getTotalPrice() << endl;
        cout << "Rating: " << rejting << endl;
        cout << "Programming language: " << programskiJazik << endl;
        cout << "Difficulty level: " << nivoNaTezina << endl;
    }

    ~ProgrammingCourse() {
        delete[] programskiJazik;
    }
};

int main() {

    char name[100];
    int lecturePrice;
    int rating;
    int numLectures;

    char programmingLanguage[100];
    bool isPremium;
    int difficulty;

    Course *courses = new Course[5];
    ProgrammingCourse *programmingCourses = new ProgrammingCourse[5];
    int n;
    cin >> n;

    if (n == 1) {

        cout << "COURSES:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            cin >> name >> lecturePrice >> rating >> numLectures;
            courses[i] = Course(name, lecturePrice, rating, numLectures);
            courses[i].print();
            cout << endl;
        }
    } else if (n == 2) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> lecturePrice >> rating >> numLectures;
            cin >> programmingLanguage >> isPremium >> difficulty;
            courses[i] = Course(name, lecturePrice, rating, numLectures);
            programmingCourses[i] = ProgrammingCourse(courses[i], programmingLanguage, isPremium, difficulty);
        }

        cout << "COURSES:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            courses[i].print();
            cout << endl;
        }


        cout << "PROGRAMMING COURSES:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            programmingCourses[i].print();
            cout << endl;
        }

    } else if (n == 3) {

        for (int i = 0; i < 5; ++i) {
            cin >> name >> lecturePrice >> rating >> numLectures;
            cin >> programmingLanguage >> isPremium >> difficulty;
            programmingCourses[i] = ProgrammingCourse(name, lecturePrice, rating, numLectures, programmingLanguage,
                                                      isPremium, difficulty);
        }
        cout << "PROGRAMMING COURSES:" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            programmingCourses[i].print();
            cout << endl;
        }

        cout << "TESTING OPERATOR ++" << endl;
        cout << "=====================================" << endl;
        for (int i = 0; i < 5; ++i) {
            ++programmingCourses[i];
            programmingCourses[i].print();
            cout << endl;
        }


    }

    delete[] courses;
    delete[] programmingCourses;
}
